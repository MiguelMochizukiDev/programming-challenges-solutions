"""
pc110103
uva10137
"""

import sys


def parse_cents(amount):
    dollars, cents = amount.strip().split('.')
    if len(cents) == 1:
        cents = cents + '0'
    elif len(cents) > 2:
        cents = cents[:2]

    cents_value = int(cents)
    return int(dollars) * 100 + cents_value


def main():
    data = [line.strip() for line in sys.stdin if line.strip()]
    i = 0

    while i < len(data):
        n = int(data[i])
        i += 1

        if n == 0:
            break

        expenses = []
        total = 0

        for _ in range(n):
            amount = data[i]
            i += 1
            cents = parse_cents(amount)
            expenses.append(cents)
            total += cents

        avg_floor = total // n
        avg_ceil = avg_floor if total % n == 0 else avg_floor + 1
        give = 0
        take = 0

        for expense in expenses:
            if expense > avg_ceil:
                give += expense - avg_ceil
            elif expense < avg_floor:
                take += avg_floor - expense

        exchange = max(give, take)
        print(f"${exchange // 100}.{exchange % 100:02d}")


if __name__ == "__main__":
    main()
