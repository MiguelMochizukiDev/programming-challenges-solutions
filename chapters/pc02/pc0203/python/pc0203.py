"""
pc110203
uva10050
"""

import sys


def main():
    data = list(map(int, sys.stdin.read().split()))
    if not data:
        return

    idx = 0
    t = data[idx]
    idx += 1
    out = []

    for _ in range(t):
        n = data[idx]
        idx += 1
        p = data[idx]
        idx += 1

        h = data[idx:idx + p]
        idx += p

        is_hartal = [False] * (n + 1)
        lost = 0

        for interval in h:
            for day in range(interval, n + 1, interval):
                weekday = day % 7
                if weekday == 6 or weekday == 0:
                    continue

                if not is_hartal[day]:
                    is_hartal[day] = True
                    lost += 1

        out.append(str(lost))

    sys.stdout.write('\n'.join(out) + '\n')


if __name__ == '__main__':
    main()
