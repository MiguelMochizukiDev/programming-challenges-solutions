/**
 * pc110102
 * uva10189
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int DIRECTIONS[8][2] = {
	{-1, -1}, {-1, 0}, {-1, 1},
	{0, -1}, {0, 1},
	{1, -1}, {1, 0}, {1, 1}
};

int count_adjacent_mines(const vector<string>& board, int num_rows, int num_cols, int row, int col) {
	int count = 0;

	for (int i = 0; i < 8; i++) {
	int new_row = row + DIRECTIONS[i][0];
	int new_col = col + DIRECTIONS[i][1];

	if (new_row >= 0 && new_row < num_rows &&
		new_col >= 0 && new_col < num_cols &&
		board[new_row][new_col] == '*') {
		count++;
	}
	}

	return count;
}

void print_minesweeper_board(const vector<string>& board, int num_rows, int num_cols) {
	for (int row = 0; row < num_rows; row++) {
	for (int col = 0; col < num_cols; col++) {
		if (board[row][col] == '*') {
		cout << '*';
		} else {
		cout << count_adjacent_mines(board, num_rows, num_cols, row, col);
		}
	}
	cout << '\n';
	}
}

int main() {
	int num_rows, num_cols;
	int field_number = 1;

	while (cin >> num_rows >> num_cols && (num_rows || num_cols)) {
	vector<string> board(num_rows);

	for (int i = 0; i < num_rows; i++) {
		cin >> board[i];
	}

	if (field_number > 1) {
		cout << '\n';
	}

	cout << "Field #" << field_number << ":\n";
	print_minesweeper_board(board, num_rows, num_cols);

	field_number++;
	}

	return 0;
}