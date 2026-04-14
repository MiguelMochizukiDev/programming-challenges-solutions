/**
 * pc110107
 * uva10196
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool inBounds(int r, int c) {
	return r >= 0 && r < 8 && c >= 0 && c < 8;
}

bool attackedByBlack(const vector<string>& board, int kr, int kc) {
	const int knightDr[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
	const int knightDc[8] = {-1, 1, -2, 2, -2, 2, -1, 1};
	const int kingDr[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
	const int kingDc[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
	const int rookDr[4] = {-1, 1, 0, 0};
	const int rookDc[4] = {0, 0, -1, 1};
	const int bishopDr[4] = {-1, -1, 1, 1};
	const int bishopDc[4] = {-1, 1, -1, 1};

	if (inBounds(kr - 1, kc - 1) && board[kr - 1][kc - 1] == 'p') {
		return true;
	}
	if (inBounds(kr - 1, kc + 1) && board[kr - 1][kc + 1] == 'p') {
		return true;
	}

	for (int i = 0; i < 8; i++) {
		int nr = kr + knightDr[i];
		int nc = kc + knightDc[i];
		if (inBounds(nr, nc) && board[nr][nc] == 'n') {
			return true;
		}
	}

	for (int i = 0; i < 8; i++) {
		int nr = kr + kingDr[i];
		int nc = kc + kingDc[i];
		if (inBounds(nr, nc) && board[nr][nc] == 'k') {
			return true;
		}
	}

	for (int d = 0; d < 4; d++) {
		int nr = kr + rookDr[d];
		int nc = kc + rookDc[d];
		while (inBounds(nr, nc)) {
			char piece = board[nr][nc];
			if (piece != '.') {
				if (piece == 'r' || piece == 'q') {
					return true;
				}
				break;
			}
			nr += rookDr[d];
			nc += rookDc[d];
		}
	}

	for (int d = 0; d < 4; d++) {
		int nr = kr + bishopDr[d];
		int nc = kc + bishopDc[d];
		while (inBounds(nr, nc)) {
			char piece = board[nr][nc];
			if (piece != '.') {
				if (piece == 'b' || piece == 'q') {
					return true;
				}
				break;
			}
			nr += bishopDr[d];
			nc += bishopDc[d];
		}
	}

	return false;
}

bool attackedByWhite(const vector<string>& board, int kr, int kc) {
	const int knightDr[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
	const int knightDc[8] = {-1, 1, -2, 2, -2, 2, -1, 1};
	const int kingDr[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
	const int kingDc[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
	const int rookDr[4] = {-1, 1, 0, 0};
	const int rookDc[4] = {0, 0, -1, 1};
	const int bishopDr[4] = {-1, -1, 1, 1};
	const int bishopDc[4] = {-1, 1, -1, 1};

	if (inBounds(kr + 1, kc - 1) && board[kr + 1][kc - 1] == 'P') {
		return true;
	}
	if (inBounds(kr + 1, kc + 1) && board[kr + 1][kc + 1] == 'P') {
		return true;
	}

	for (int i = 0; i < 8; i++) {
		int nr = kr + knightDr[i];
		int nc = kc + knightDc[i];
		if (inBounds(nr, nc) && board[nr][nc] == 'N') {
			return true;
		}
	}

	for (int i = 0; i < 8; i++) {
		int nr = kr + kingDr[i];
		int nc = kc + kingDc[i];
		if (inBounds(nr, nc) && board[nr][nc] == 'K') {
			return true;
		}
	}

	for (int d = 0; d < 4; d++) {
		int nr = kr + rookDr[d];
		int nc = kc + rookDc[d];
		while (inBounds(nr, nc)) {
			char piece = board[nr][nc];
			if (piece != '.') {
				if (piece == 'R' || piece == 'Q') {
					return true;
				}
				break;
			}
			nr += rookDr[d];
			nc += rookDc[d];
		}
	}

	for (int d = 0; d < 4; d++) {
		int nr = kr + bishopDr[d];
		int nc = kc + bishopDc[d];
		while (inBounds(nr, nc)) {
			char piece = board[nr][nc];
			if (piece != '.') {
				if (piece == 'B' || piece == 'Q') {
					return true;
				}
				break;
			}
			nr += bishopDr[d];
			nc += bishopDc[d];
		}
	}

	return false;
}

bool isEmptyBoard(const vector<string>& board) {
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			if (board[r][c] != '.') {
				return false;
			}
		}
	}
	return true;
}

int main() {
	int game = 1;

	while (true) {
		vector<string> board(8);
		for (int r = 0; r < 8; r++) {
			if (!(cin >> board[r])) {
				return 0;
			}
		}

		if (isEmptyBoard(board)) {
			break;
		}

		int whiteKr = -1;
		int whiteKc = -1;
		int blackKr = -1;
		int blackKc = -1;

		for (int r = 0; r < 8; r++) {
			for (int c = 0; c < 8; c++) {
				if (board[r][c] == 'K') {
					whiteKr = r;
					whiteKc = c;
				} else if (board[r][c] == 'k') {
					blackKr = r;
					blackKc = c;
				}
			}
		}

		if (attackedByBlack(board, whiteKr, whiteKc)) {
			cout << "Game #" << game << ": white king is in check." << '\n';
		} else if (attackedByWhite(board, blackKr, blackKc)) {
			cout << "Game #" << game << ": black king is in check." << '\n';
		} else {
			cout << "Game #" << game << ": no king is in check." << '\n';
		}

		game++;
	}

	return 0;
}
