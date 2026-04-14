"""
pc110105
uva10267
"""

import sys
from collections import deque


def clear_image(image, rows, cols):
    for y in range(rows):
        for x in range(cols):
            image[y][x] = 'O'


def flood_fill(image, rows, cols, start_x, start_y, color):
    original = image[start_y][start_x]
    if original == color:
        return

    q = deque([(start_x, start_y)])
    image[start_y][start_x] = color

    while q:
        x, y = q.popleft()

        if x > 0 and image[y][x - 1] == original:
            image[y][x - 1] = color
            q.append((x - 1, y))
        if x + 1 < cols and image[y][x + 1] == original:
            image[y][x + 1] = color
            q.append((x + 1, y))
        if y > 0 and image[y - 1][x] == original:
            image[y - 1][x] = color
            q.append((x, y - 1))
        if y + 1 < rows and image[y + 1][x] == original:
            image[y + 1][x] = color
            q.append((x, y + 1))


def main():
    image = [['O'] * 250 for _ in range(250)]
    rows = 0
    cols = 0
    out = []

    for raw_line in sys.stdin:
        line = raw_line.strip()
        if not line:
            continue

        command = line[0]
        if command == 'X':
            break

        parts = line.split()

        if command == 'I':
            cols = int(parts[1])
            rows = int(parts[2])
            clear_image(image, rows, cols)
        elif command == 'C':
            if rows > 0 and cols > 0:
                clear_image(image, rows, cols)
        elif command == 'L':
            x, y, color = int(parts[1]), int(parts[2]), parts[3]
            image[y - 1][x - 1] = color
        elif command == 'V':
            x, y1, y2, color = int(parts[1]), int(parts[2]), int(parts[3]), parts[4]
            for y in range(min(y1, y2), max(y1, y2) + 1):
                image[y - 1][x - 1] = color
        elif command == 'H':
            x1, x2, y, color = int(parts[1]), int(parts[2]), int(parts[3]), parts[4]
            for x in range(min(x1, x2), max(x1, x2) + 1):
                image[y - 1][x - 1] = color
        elif command == 'K':
            x1, y1, x2, y2, color = int(parts[1]), int(parts[2]), int(parts[3]), int(parts[4]), parts[5]
            for y in range(min(y1, y2), max(y1, y2) + 1):
                for x in range(min(x1, x2), max(x1, x2) + 1):
                    image[y - 1][x - 1] = color
        elif command == 'F':
            x, y, color = int(parts[1]), int(parts[2]), parts[3]
            flood_fill(image, rows, cols, x - 1, y - 1, color)
        elif command == 'S':
            name = parts[1]
            out.append(name)
            for y in range(rows):
                out.append(''.join(image[y][:cols]))

    if out:
        sys.stdout.write('\n'.join(out) + '\n')


if __name__ == '__main__':
    main()
