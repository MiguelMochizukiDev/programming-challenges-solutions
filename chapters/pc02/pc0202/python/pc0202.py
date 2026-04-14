"""
pc110202
uva10315
"""

import sys
from collections import Counter


def card_value(c):
    if '2' <= c <= '9':
        return int(c)
    return {'T': 10, 'J': 11, 'Q': 12, 'K': 13, 'A': 14}[c]


def evaluate_hand(cards):
    values = [card_value(card[0]) for card in cards]
    suits = [card[1] for card in cards]
    values.sort(reverse=True)

    flush = len(set(suits)) == 1
    straight = all(values[i] - 1 == values[i + 1] for i in range(4))
    straight_high = values[0]

    freq = Counter(values)
    grouped = sorted(((cnt, val) for val, cnt in freq.items()), reverse=True)

    if straight and flush:
        return 8, [straight_high]
    if grouped[0][0] == 4:
        return 7, [grouped[0][1], grouped[1][1]]
    if grouped[0][0] == 3 and grouped[1][0] == 2:
        return 6, [grouped[0][1]]
    if flush:
        return 5, values
    if straight:
        return 4, [straight_high]
    if grouped[0][0] == 3:
        return 3, [grouped[0][1], grouped[1][1], grouped[2][1]]
    if grouped[0][0] == 2 and grouped[1][0] == 2:
        return 2, [grouped[0][1], grouped[1][1], grouped[2][1]]
    if grouped[0][0] == 2:
        return 1, [grouped[0][1], grouped[1][1], grouped[2][1], grouped[3][1]]
    return 0, values


def compare_hands(black, white):
    rb, tb = evaluate_hand(black)
    rw, tw = evaluate_hand(white)

    if rb != rw:
        return 1 if rb > rw else -1

    i = 0
    while i < max(len(tb), len(tw)):
        bv = tb[i] if i < len(tb) else 0
        wv = tw[i] if i < len(tw) else 0
        if bv != wv:
            return 1 if bv > wv else -1
        i += 1

    return 0


def main():
    out = []
    for line in sys.stdin:
        line = line.strip()
        if not line:
            continue
        cards = line.split()
        black = cards[:5]
        white = cards[5:]

        cmp = compare_hands(black, white)
        if cmp > 0:
            out.append('Black wins.')
        elif cmp < 0:
            out.append('White wins.')
        else:
            out.append('Tie.')

    sys.stdout.write('\n'.join(out) + '\n')


if __name__ == '__main__':
    main()
