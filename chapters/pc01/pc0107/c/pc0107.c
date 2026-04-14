/**
 * pc110107
 * uva10196
 */

#include <stdio.h>
#include <string.h>

int in_bounds(int r, int c) {
	return r >= 0 && r < 8 && c >= 0 && c < 8;
}

int is_attacked_by_black(char board[8][9], int kr, int kc) {
	int knight_dr[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
	int knight_dc[8] = {-1, 1, -2, 2, -2, 2, -1, 1};
	int king_dr[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
	int king_dc[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
	int rook_dr[4] = {-1, 1, 0, 0};
	int rook_dc[4] = {0, 0, -1, 1};
	int bishop_dr[4] = {-1, -1, 1, 1};
	int bishop_dc[4] = {-1, 1, -1, 1};

	if (in_bounds(kr - 1, kc - 1) && board[kr - 1][kc - 1] == 'p') {
		return 1;
	}
	if (in_bounds(kr - 1, kc + 1) && board[kr - 1][kc + 1] == 'p') {
		return 1;
	}

	for (int i = 0; i < 8; i++) {
		int nr = kr + knight_dr[i];
		int nc = kc + knight_dc[i];
		if (in_bounds(nr, nc) && board[nr][nc] == 'n') {
			return 1;
		}
	}

	for (int i = 0; i < 8; i++) {
		int nr = kr + king_dr[i];
		int nc = kc + king_dc[i];
		if (in_bounds(nr, nc) && board[nr][nc] == 'k') {
			return 1;
		}
	}

	for (int d = 0; d < 4; d++) {
		int nr = kr + rook_dr[d];
		int nc = kc + rook_dc[d];
		while (in_bounds(nr, nc)) {
			char piece = board[nr][nc];
			if (piece != '.') {
				if (piece == 'r' || piece == 'q') {
					return 1;
				}
				break;
			}
			nr += rook_dr[d];
			nc += rook_dc[d];
		}
	}

	for (int d = 0; d < 4; d++) {
		int nr = kr + bishop_dr[d];
		int nc = kc + bishop_dc[d];
		while (in_bounds(nr, nc)) {
			char piece = board[nr][nc];
			if (piece != '.') {
				if (piece == 'b' || piece == 'q') {
					return 1;
				}
				break;
			}
			nr += bishop_dr[d];
			nc += bishop_dc[d];
		}
	}

	return 0;
}

int is_attacked_by_white(char board[8][9], int kr, int kc) {
	int knight_dr[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
	int knight_dc[8] = {-1, 1, -2, 2, -2, 2, -1, 1};
	int king_dr[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
	int king_dc[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
	int rook_dr[4] = {-1, 1, 0, 0};
	int rook_dc[4] = {0, 0, -1, 1};
	int bishop_dr[4] = {-1, -1, 1, 1};
	int bishop_dc[4] = {-1, 1, -1, 1};

	if (in_bounds(kr + 1, kc - 1) && board[kr + 1][kc - 1] == 'P') {
		return 1;
	}
	if (in_bounds(kr + 1, kc + 1) && board[kr + 1][kc + 1] == 'P') {
		return 1;
	}

	for (int i = 0; i < 8; i++) {
		int nr = kr + knight_dr[i];
		int nc = kc + knight_dc[i];
		if (in_bounds(nr, nc) && board[nr][nc] == 'N') {
			return 1;
		}
	}

	for (int i = 0; i < 8; i++) {
		int nr = kr + king_dr[i];
		int nc = kc + king_dc[i];
		if (in_bounds(nr, nc) && board[nr][nc] == 'K') {
			return 1;
		}
	}

	for (int d = 0; d < 4; d++) {
		int nr = kr + rook_dr[d];
		int nc = kc + rook_dc[d];
		while (in_bounds(nr, nc)) {
			char piece = board[nr][nc];
			if (piece != '.') {
				if (piece == 'R' || piece == 'Q') {
					return 1;
				}
				break;
			}
			nr += rook_dr[d];
			nc += rook_dc[d];
		}
	}

	for (int d = 0; d < 4; d++) {
		int nr = kr + bishop_dr[d];
		int nc = kc + bishop_dc[d];
		while (in_bounds(nr, nc)) {
			char piece = board[nr][nc];
			if (piece != '.') {
				if (piece == 'B' || piece == 'Q') {
					return 1;
				}
				break;
			}
			nr += bishop_dr[d];
			nc += bishop_dc[d];
		}
	}

	return 0;
}

int is_empty_board(char board[8][9]) {
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			if (board[r][c] != '.') {
				return 0;
			}
		}
	}
	return 1;
}

int main(void) {
	char board[8][9];
	int game = 1;

	while (1) {
		for (int r = 0; r < 8; r++) {
			if (scanf("%8s", board[r]) != 1) {
				return 0;
			}
		}

		if (is_empty_board(board)) {
			break;
		}

		int white_kr = -1;
		int white_kc = -1;
		int black_kr = -1;
		int black_kc = -1;

		for (int r = 0; r < 8; r++) {
			for (int c = 0; c < 8; c++) {
				if (board[r][c] == 'K') {
					white_kr = r;
					white_kc = c;
				} else if (board[r][c] == 'k') {
					black_kr = r;
					black_kc = c;
				}
			}
		}

		if (is_attacked_by_black(board, white_kr, white_kc)) {
			printf("Game #%d: white king is in check.\n", game);
		} else if (is_attacked_by_white(board, black_kr, black_kc)) {
			printf("Game #%d: black king is in check.\n", game);
		} else {
			printf("Game #%d: no king is in check.\n", game);
		}

		game++;
	}

	return 0;
}
