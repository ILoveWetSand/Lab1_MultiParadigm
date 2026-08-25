"""
Lab 1: The Multi-Paradigm Tour -- Python implementation.

Run: python stats.py 4 8 15 16 23 42
Complete compute_stats() below. See the assignment,
Part B, for the full shared contract (all three language versions
must match it exactly).
"""

import sys
from typing import List, Tuple


def compute_stats(nums: List[int]) -> Tuple[float, float, int]:
    #Mean
    total = sum(nums)
    mean = total / len(nums)

    #Median
    sorted_nums = sorted(nums)
    n = len(sorted_nums)

    if n % 2 == 1:
        median = float(sorted_nums[n // 2])
    else:
        median = (sorted_nums[n // 2 - 1] + sorted_nums[n // 2]) / 2.0

    #Mode
    freq = {}
    for v in sorted_nums:
        freq[v] = freq.get(v, 0) + 1

    #Smallest value in sorted order
    mode = sorted_nums[0]
    best_count = freq[mode]

    for value, count in freq.items():
        if count > best_count or (count == best_count and value < mode):
            mode = value
            best_count = count

    return mean, median, mode


def main() -> int:
    if len(sys.argv) < 2:
        return 1
    nums = [int(a) for a in sys.argv[1:]]
    mean, median, mode = compute_stats(nums)
    print(f"Mean: {mean:.2f}")
    print(f"Median: {median:.2f}")
    print(f"Mode: {mode}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
