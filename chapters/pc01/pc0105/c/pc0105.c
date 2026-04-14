/**
 * pc110105
 * uva10267
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int x;
	int y;
} Point;

void clear_image(char image[250][250], int rows, int cols) {
	for (int y = 0; y < rows; y++) {
		for (int x = 0; x < cols; x++) {
			image[y][x] = 'O';
		}
	}
}

void flood_fill(char image[250][250], int rows, int cols, int start_x, int start_y, char color) {
	char original = image[start_y][start_x];
	if (original == color) {
		return;
	}

	Point *queue = (Point *)malloc((size_t)rows * (size_t)cols * sizeof(Point));
	int head = 0;
	int tail = 0;

	queue[tail++] = (Point){start_x, start_y};
	image[start_y][start_x] = color;

	while (head < tail) {
		Point p = queue[head++];
		int x = p.x;
		int y = p.y;

		if (x > 0 && image[y][x - 1] == original) {
			image[y][x - 1] = color;
			queue[tail++] = (Point){x - 1, y};
		}
		if (x + 1 < cols && image[y][x + 1] == original) {
			image[y][x + 1] = color;
			queue[tail++] = (Point){x + 1, y};
		}
		if (y > 0 && image[y - 1][x] == original) {
			image[y - 1][x] = color;
			queue[tail++] = (Point){x, y - 1};
		}
		if (y + 1 < rows && image[y + 1][x] == original) {
			image[y + 1][x] = color;
			queue[tail++] = (Point){x, y + 1};
		}
	}

	free(queue);
}

int main(void) {
	char image[250][250];
	int rows = 0;
	int cols = 0;
	char line[256];

	while (fgets(line, sizeof(line), stdin) != NULL) {
		char command = line[0];

		if (command == 'X') {
			break;
		}

		if (command == 'I') {
			int m;
			int n;
			if (sscanf(line, "I %d %d", &m, &n) == 2) {
				cols = m;
				rows = n;
				clear_image(image, rows, cols);
			}
		} else if (command == 'C') {
			if (rows > 0 && cols > 0) {
				clear_image(image, rows, cols);
			}
		} else if (command == 'L') {
			int x;
			int y;
			char color;
			if (sscanf(line, "L %d %d %c", &x, &y, &color) == 3) {
				image[y - 1][x - 1] = color;
			}
		} else if (command == 'V') {
			int x;
			int y1;
			int y2;
			char color;
			if (sscanf(line, "V %d %d %d %c", &x, &y1, &y2, &color) == 4) {
				int from = (y1 < y2) ? y1 : y2;
				int to = (y1 > y2) ? y1 : y2;
				for (int y = from; y <= to; y++) {
					image[y - 1][x - 1] = color;
				}
			}
		} else if (command == 'H') {
			int x1;
			int x2;
			int y;
			char color;
			if (sscanf(line, "H %d %d %d %c", &x1, &x2, &y, &color) == 4) {
				int from = (x1 < x2) ? x1 : x2;
				int to = (x1 > x2) ? x1 : x2;
				for (int x = from; x <= to; x++) {
					image[y - 1][x - 1] = color;
				}
			}
		} else if (command == 'K') {
			int x1;
			int y1;
			int x2;
			int y2;
			char color;
			if (sscanf(line, "K %d %d %d %d %c", &x1, &y1, &x2, &y2, &color) == 5) {
				int from_x = (x1 < x2) ? x1 : x2;
				int to_x = (x1 > x2) ? x1 : x2;
				int from_y = (y1 < y2) ? y1 : y2;
				int to_y = (y1 > y2) ? y1 : y2;
				for (int y = from_y; y <= to_y; y++) {
					for (int x = from_x; x <= to_x; x++) {
						image[y - 1][x - 1] = color;
					}
				}
			}
		} else if (command == 'F') {
			int x;
			int y;
			char color;
			if (sscanf(line, "F %d %d %c", &x, &y, &color) == 3) {
				flood_fill(image, rows, cols, x - 1, y - 1, color);
			}
		} else if (command == 'S') {
			char name[256];
			if (sscanf(line, "S %255s", name) == 1) {
				printf("%s\n", name);
				for (int y = 0; y < rows; y++) {
					for (int x = 0; x < cols; x++) {
						putchar(image[y][x]);
					}
					putchar('\n');
				}
			}
		}
	}

	return 0;
}
