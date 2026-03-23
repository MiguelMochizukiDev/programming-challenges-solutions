"""
pc110101
uva100
"""

import sys

def calculate_collatz_len(num):
    collatz_len = 1

    while num != 1:
        if num % 2 == 1:
            num += (num << 1) + 1
        else:
            num = num >> 1

        collatz_len += 1

    return collatz_len

def find_highest_collatz_len(i, j):
    highest_collatz_len = 1

    min_num = min(i, j)
    max_num = max(i, j)

    for num in range(min_num, max_num + 1):
        collatz_len = calculate_collatz_len(num)
        if collatz_len > highest_collatz_len:
            highest_collatz_len = collatz_len

    return highest_collatz_len

def main():
    for line in sys.stdin:
        i, j = map(int, line.split())
        highest_collatz_len = find_highest_collatz_len(i, j)
        print(f"{i} {j} {highest_collatz_len}")


if __name__ == "__main__":
    main()