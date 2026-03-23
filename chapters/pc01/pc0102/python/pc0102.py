"""
pc110102
uva10189
"""

import sys

DIRECTIONS = [
    (-1, -1), (-1, 0), (-1, 1),
    (0, -1), (0, 1),
    (1, -1), (1, 0), (1, 1)
]

def count_adjacent_mines(board, num_rows, num_cols, row, col):
    count = 0

    for dr, dc in DIRECTIONS:
        new_row = row + dr
        new_col = col + dc

        if 0 <= new_row < num_rows and 0 <= new_col < num_cols:
            if board[new_row][new_col] == '*':
                count += 1

    return count

def print_minesweeper_board(board, num_rows, num_cols):
    for row in range(num_rows):
        for col in range(num_cols):
            if board[row][col] == '*':
                print('*', end='')
            else:
                print(count_adjacent_mines(board, num_rows, num_cols, row, col), end='')
        print()

def main():
    field_number = 1
    lines = sys.stdin.read().strip().split('\n')
    i = 0

    while i < len(lines):
        if not lines[i].strip():
            i += 1
            continue

        num_rows, num_cols = map(int, lines[i].split())
        i += 1

        if num_rows == 0 and num_cols == 0:
            break

        board = []
        for _ in range(num_rows):
            board.append(list(lines[i].strip()))
            i += 1

        if field_number > 1:
            print()

        print(f"Field #{field_number}:")
        print_minesweeper_board(board, num_rows, num_cols)

        field_number += 1

if __name__ == "__main__":
    main()