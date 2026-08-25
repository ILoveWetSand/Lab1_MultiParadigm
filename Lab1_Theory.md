## The Compilation vs. Interpretation Dilemma

C is ahead of time compiled ahead of time because C prioritizes raw performance and as little work as possible during runtime. Without compiling C, a machine won't be able to read the code and will not execute natively.
Python is interpreted because during runtime it turns the code into machine readable code and then executes the line it reads. I did find that it is also compiled to bytecode and then gets converted using a python virtual machine to the corresponding operating system but this all happens behind the scenes where programmers can't see it.
GO is ahead of time compiled even though it ships a managed runtime inside its binary because, its source code is translated directly into native binary code before executing.

## Pipeline Tracing

### C Path

Starting with  
-> Source text (The characters in the .c file)  
-> Lexical Tokens (IDENT(total), '=', INT(5), '+', INT(3), '*', INT(2), ';')  
-> AST  Assignment  
├── Identifier("total")  
└── Add  
    ├── Literal(5)  
    └── Multiply  
        ├── Literal(3)  
        └── Literal(2)  
-> Semantic Analysis (Type checking and scope resolution)  
-> Machine Code Generation (Assembly -> Machine code)  
-> Compilation (Divergence point and what happens is C stops since the compiler already computed the answer)  
-> CPU Execution (11 gets stored into memory)

### Python Path

Starting with  
-> Source text (The characters in the .py file)  
-> Lexical Tokens (NAME(total), '=', NUMBER(5), '+', NUMBER(3), '*', NUMBER(2), NEWLINE)  
-> AST   Assign  
├── Name("total")  
└── BinOp(  
    left=Constant(5),  
    op=Add,  
    right=BinOp(  
        left=Constant(3),  
        op=Mult,  
        right=Constant(2)  
    )  
)  
-> Bytecode Generation  
LOAD_CONST 5  
LOAD_CONST 3  
LOAD_CONST 2  
BINARY_MULTIPLY  
BINARY_ADD  
STORE_NAME total  
-> Interpretation (Divergence point and bytecode is executed using the Python Virtual Machine(PVM))  
-> Interpreter Execution Loop (PVM runs its dispatch loop)  
-> Runtime Evaluation  
Push 5  
Push 3  
Push 2  
Multiply -> push 6  
Add -> push 11  
Store total = 11  
-> CPU Execution (The CPU executes the interpreter's machine code)

## Paradigm Classification

### Imperative

for i from 0 to n-1: list[i] = list[i] * list[i]

### Object Oriented

list.squareEach()

### Functional

squaredList = map(square, list)

### Logic

square(x,y): y is x * x.

### Paradigm used

C used Imperative because I used manual loops and mutable variables. There are no functional or object oriented constructs in C meaning it cannot change paradigms and it is always imperative.  
Go used Imperative because I used loops and stepwise accumulation. Go can change only if it is written in pure functions.  
Python used Imperative because I used loops and step by step updates. However, Python can change when using map or lambda.

## Start up Latency in the Real World

### My start up numbers and size

Language | Size (bytes) | Avg cold-start (ms)  
-------- | ------------- | -------------------  
Python   | 1314          | 72.74  
C        | 264869        | 10.49  
Go       | 2534912       | 16.60

### Explanation

The cold start penalty in interpreted languages exists because the platform has to initialize the language runtime before executing code. Python, for example, has to start the interpreter, allocate objects, and parse bytecode which all adds on to the startup latency. C, on the other hand, avoids all this during startup by compiling the code into a native executable.

A JIT compiler begins interpreting code, then profiles the running program and compiles paths into optimized machine code which differs from both extremes. This does improve long running performance but uses more memory and runtime code generation. A CubeSat flight computer needs minimal resource usage and predictable execution every time meaning they would probably never use a JIT.
