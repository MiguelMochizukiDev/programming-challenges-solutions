"""
pc110201
uva10038
"""

import sys


def main():
    out = []

    for line in sys.stdin:
        line = line.strip()
        if not line:
            continue

        values = list(map(int, line.split()))
        n = values[0]

        if n <= 1:
            out.append('Jolly')
            continue

        seq = values[1:1 + n]
        seen = [False] * n

        for i in range(1, n):
            diff = abs(seq[i] - seq[i - 1])
            if 1 <= diff <= n - 1:
                seen[diff] = True

        jolly = all(seen[1:])
        out.append('Jolly' if jolly else 'Not jolly')

    sys.stdout.write('\n'.join(out) + '\n')


if __name__ == '__main__':
    main()
