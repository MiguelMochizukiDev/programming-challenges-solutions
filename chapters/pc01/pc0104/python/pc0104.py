"""
pc110104
uva706
"""

import sys

SEG_TOP = 1 << 0
SEG_UPPER_LEFT = 1 << 1
SEG_UPPER_RIGHT = 1 << 2
SEG_MIDDLE = 1 << 3
SEG_LOWER_LEFT = 1 << 4
SEG_LOWER_RIGHT = 1 << 5
SEG_BOTTOM = 1 << 6

DIGIT_MASKS = {
    '0': SEG_TOP | SEG_UPPER_LEFT | SEG_UPPER_RIGHT | SEG_LOWER_LEFT | SEG_LOWER_RIGHT | SEG_BOTTOM,
    '1': SEG_UPPER_RIGHT | SEG_LOWER_RIGHT,
    '2': SEG_TOP | SEG_UPPER_RIGHT | SEG_MIDDLE | SEG_LOWER_LEFT | SEG_BOTTOM,
    '3': SEG_TOP | SEG_UPPER_RIGHT | SEG_MIDDLE | SEG_LOWER_RIGHT | SEG_BOTTOM,
    '4': SEG_UPPER_LEFT | SEG_UPPER_RIGHT | SEG_MIDDLE | SEG_LOWER_RIGHT,
    '5': SEG_TOP | SEG_UPPER_LEFT | SEG_MIDDLE | SEG_LOWER_RIGHT | SEG_BOTTOM,
    '6': SEG_TOP | SEG_UPPER_LEFT | SEG_MIDDLE | SEG_LOWER_LEFT | SEG_LOWER_RIGHT | SEG_BOTTOM,
    '7': SEG_TOP | SEG_UPPER_RIGHT | SEG_LOWER_RIGHT,
    '8': SEG_TOP | SEG_UPPER_LEFT | SEG_UPPER_RIGHT | SEG_MIDDLE | SEG_LOWER_LEFT | SEG_LOWER_RIGHT | SEG_BOTTOM,
    '9': SEG_TOP | SEG_UPPER_LEFT | SEG_UPPER_RIGHT | SEG_MIDDLE | SEG_LOWER_RIGHT | SEG_BOTTOM,
}


def has_segment(mask, segment):
    return (mask & segment) != 0


def horizontal(on, s):
    return ' ' + ('-' * s if on else ' ' * s) + ' '


def vertical(left_on, right_on, s):
    return ('|' if left_on else ' ') + (' ' * s) + ('|' if right_on else ' ')


def render_lcd(s, n):
    rows = 2 * s + 3
    lines = []

    for row in range(rows):
        parts = []

        for digit in n:
            mask = DIGIT_MASKS[digit]

            if row == 0:
                parts.append(horizontal(has_segment(mask, SEG_TOP), s))
            elif 0 < row < s + 1:
                parts.append(vertical(has_segment(mask, SEG_UPPER_LEFT), has_segment(mask, SEG_UPPER_RIGHT), s))
            elif row == s + 1:
                parts.append(horizontal(has_segment(mask, SEG_MIDDLE), s))
            elif s + 1 < row < 2 * s + 2:
                parts.append(vertical(has_segment(mask, SEG_LOWER_LEFT), has_segment(mask, SEG_LOWER_RIGHT), s))
            else:
                parts.append(horizontal(has_segment(mask, SEG_BOTTOM), s))

        lines.append(' '.join(parts))

    return lines


def main():
    for raw_line in sys.stdin:
        raw_line = raw_line.strip()
        if not raw_line:
            continue

        s_str, n = raw_line.split()
        s = int(s_str)

        if s == 0 and n == '0':
            break

        lines = render_lcd(s, n)
        for line in lines:
            print(line)
        print()


if __name__ == '__main__':
    main()
