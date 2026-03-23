/**
 * pc110102
 * uva10189
 */

#include <stdio.h>
#include <stdlib.h>

const int DIRECTIONS[8][2] = {
	{-1, -1}, {-1, 0}, {-1, 1},
	{0, -1}, {0, 1},
	{1, -1}, {1, 0}, {1, 1}
};

int count_adjacent_mines(char **board, int num_rows, int num_cols, int row, int col) {
	int count = 0;

	for (int i = 0; i < 8; i++) {
		int new_row = row + DIRECTIONS[i][0];
		int new_col = col + DIRECTIONS[i][1];

		if (new_row >= 0 && new_row < num_rows && new_col >= 0 && new_col < num_cols) {
			if (board[new_row][new_col] == '*') {
				count++;
			}
		}
	}
	return count;
}

void print_minesweeper_board(char **board, int num_rows, int num_cols) {
	for (int row = 0; row < num_rows; row++) {
		for (int col = 0; col < num_cols; col++) {
			if (board[row][col] == '*') {
				printf("*");
			} else {
				int adjacent_mines = count_adjacent_mines(board, num_rows, num_cols, row, col);
				printf("%d", adjacent_mines);
			}
		}
		printf("\n");
	}
}

int main(void) {
	int num_rows;
	int num_cols;
	int field_number = 1;

	while (scanf("%d %d", &num_rows, &num_cols) == 2 && (num_rows != 0 && num_cols != 0)) {
		char **board = (char **)malloc(num_rows * sizeof(char *));
		for (int i = 0; i < num_rows; i++) {
			board[i] = (char *)malloc((num_cols + 1) * sizeof(char));
			if (scanf("%s", board[i]) != 1) {
				return EXIT_FAILURE;
			};
		}

		if (field_number > 1) {
			printf("\n");
		}
		printf("Field #%d:\n", field_number);
		print_minesweeper_board(board, num_rows, num_cols);

		for (int i = 0; i < num_rows; i++) {
			free(board[i]);
		}
		free(board);

		field_number++;
	}

	return 0;
}