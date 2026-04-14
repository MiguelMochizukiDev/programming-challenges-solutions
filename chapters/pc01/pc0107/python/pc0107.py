"""
pc110107
uva10196
"""

import sys


def in_bounds(r, c):
    return 0 <= r < 8 and 0 <= c < 8


def attacked_by_black(board, kr, kc):
    knight_moves = [(-2, -1), (-2, 1), (-1, -2), (-1, 2), (1, -2), (1, 2), (2, -1), (2, 1)]
    king_moves = [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)]

    if in_bounds(kr - 1, kc - 1) and board[kr - 1][kc - 1] == 'p':
        return True
    if in_bounds(kr - 1, kc + 1) and board[kr - 1][kc + 1] == 'p':
        return True

    for dr, dc in knight_moves:
        nr, nc = kr + dr, kc + dc
        if in_bounds(nr, nc) and board[nr][nc] == 'n':
            return True

    for dr, dc in king_moves:
        nr, nc = kr + dr, kc + dc
        if in_bounds(nr, nc) and board[nr][nc] == 'k':
            return True

    for dr, dc in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
        nr, nc = kr + dr, kc + dc
        while in_bounds(nr, nc):
            piece = board[nr][nc]
            if piece != '.':
                if piece in ('r', 'q'):
                    return True
                break
            nr += dr
            nc += dc

    for dr, dc in [(-1, -1), (-1, 1), (1, -1), (1, 1)]:
        nr, nc = kr + dr, kc + dc
        while in_bounds(nr, nc):
            piece = board[nr][nc]
            if piece != '.':
                if piece in ('b', 'q'):
                    return True
                break
            nr += dr
            nc += dc

    return False


def attacked_by_white(board, kr, kc):
    knight_moves = [(-2, -1), (-2, 1), (-1, -2), (-1, 2), (1, -2), (1, 2), (2, -1), (2, 1)]
    king_moves = [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)]

    if in_bounds(kr + 1, kc - 1) and board[kr + 1][kc - 1] == 'P':
        return True
    if in_bounds(kr + 1, kc + 1) and board[kr + 1][kc + 1] == 'P':
        return True

    for dr, dc in knight_moves:
        nr, nc = kr + dr, kc + dc
        if in_bounds(nr, nc) and board[nr][nc] == 'N':
            return True

    for dr, dc in king_moves:
        nr, nc = kr + dr, kc + dc
        if in_bounds(nr, nc) and board[nr][nc] == 'K':
            return True

    for dr, dc in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
        nr, nc = kr + dr, kc + dc
        while in_bounds(nr, nc):
            piece = board[nr][nc]
            if piece != '.':
                if piece in ('R', 'Q'):
                    return True
                break
            nr += dr
            nc += dc

    for dr, dc in [(-1, -1), (-1, 1), (1, -1), (1, 1)]:
        nr, nc = kr + dr, kc + dc
        while in_bounds(nr, nc):
            piece = board[nr][nc]
            if piece != '.':
                if piece in ('B', 'Q'):
                    return True
                break
            nr += dr
            nc += dc

    return False


def is_empty_board(board):
    return all(cell == '.' for row in board for cell in row)


def main():
    lines = sys.stdin.read().splitlines()
    idx = 0
    game = 1
    out = []

    while idx + 7 < len(lines):
        board = [list(lines[idx + r]) for r in range(8)]
        idx += 8

        if is_empty_board(board):
            break

        white_kr = white_kc = black_kr = black_kc = -1
        for r in range(8):
            for c in range(8):
                if board[r][c] == 'K':
                    white_kr, white_kc = r, c
                elif board[r][c] == 'k':
                    black_kr, black_kc = r, c

        if attacked_by_black(board, white_kr, white_kc):
            out.append(f"Game #{game}: white king is in check.")
        elif attacked_by_white(board, black_kr, black_kc):
            out.append(f"Game #{game}: black king is in check.")
        else:
            out.append(f"Game #{game}: no king is in check.")

        game += 1

        while idx < len(lines) and lines[idx] == '':
            idx += 1

    sys.stdout.write('\n'.join(out) + '\n')


if __name__ == '__main__':
    main()
