/*
 * Lab 1: The Multi-Paradigm Tour -- C implementation.
 *
 * Compile: gcc -O2 -o stats_c stats.c
 * Run:     ./stats_c 4 8 15 16 23 42
 *
 * Complete the TODO section. See the assignment,
 * Part B, for the full shared contract (all three language versions
 * must match it exactly, including the tie-breaking mode rule).
 */

#include <stdio.h>
#include <stdlib.h>

int compare_ints(const void *a, const void *b) {
    int int_a = *(const int *)a;
    int int_b = *(const int *)b;
    return (int_a > int_b) - (int_a < int_b);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }

    int n = argc - 1;
    int *nums = malloc(n * sizeof(int));
    if (nums == NULL) {
        return 1;
    }
    for (int i = 0; i < n; i++) {
        nums[i] = atoi(argv[i + 1]);
    }

    double mean = 0.0;
    long sum = 0;
    for (int i = 0; i < n; i++) {
        sum += nums[i];
    }
    mean = (double)sum / n;

    int *sorted = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        sorted[i] = nums[i];
    }
    qsort(sorted, n, sizeof(int), compare_ints);

    double median = 0.0;
    if (n % 2 == 1) {
        median = sorted[n / 2];
    } else {
        median = (sorted[n/2 - 1] + sorted[n/2]) / 2.0;
    }

    int mode = sorted[0];
    int best_count = 1;

    for (int i = 0; i < n; i++) {
        int count = 1;
        for (int j = i + 1; j < n; j++) {
            if (sorted[j] == sorted[i]) {
                count++;
            }
        }
        if (count > best_count || (count == best_count && sorted[i] < mode)) {
            best_count = count;
            mode = sorted[i];
        }
    }

    printf("Mean: %.2f\n", mean);
    printf("Median: %.2f\n", median);
    printf("Mode: %d\n", mode);

    free(nums);
    return 0;
}
