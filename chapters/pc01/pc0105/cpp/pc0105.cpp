/**
 * pc110105
 * uva10267
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void clearImage(vector<string>& image, int rows, int cols) {
	image.assign(rows, string(cols, 'O'));
}

void floodFill(vector<string>& image, int rows, int cols, int startX, int startY, char color) {
	char original = image[startY][startX];
	if (original == color) {
		return;
	}

	queue<pair<int, int>> q;
	q.push({startX, startY});
	image[startY][startX] = color;

	while (!q.empty()) {
		auto [x, y] = q.front();
		q.pop();

		if (x > 0 && image[y][x - 1] == original) {
			image[y][x - 1] = color;
			q.push({x - 1, y});
		}
		if (x + 1 < cols && image[y][x + 1] == original) {
			image[y][x + 1] = color;
			q.push({x + 1, y});
		}
		if (y > 0 && image[y - 1][x] == original) {
			image[y - 1][x] = color;
			q.push({x, y - 1});
		}
		if (y + 1 < rows && image[y + 1][x] == original) {
			image[y + 1][x] = color;
			q.push({x, y + 1});
		}
	}
}

int main() {
	vector<string> image;
	int rows = 0;
	int cols = 0;
	string line;

	while (getline(cin, line)) {
		if (line.empty()) {
			continue;
		}

		char command = line[0];
		if (command == 'X') {
			break;
		}

		istringstream iss(line);
		char cmd;
		iss >> cmd;

		if (cmd == 'I') {
			iss >> cols >> rows;
			clearImage(image, rows, cols);
		} else if (cmd == 'C') {
			if (rows > 0 && cols > 0) {
				clearImage(image, rows, cols);
			}
		} else if (cmd == 'L') {
			int x, y;
			char color;
			iss >> x >> y >> color;
			image[y - 1][x - 1] = color;
		} else if (cmd == 'V') {
			int x, y1, y2;
			char color;
			iss >> x >> y1 >> y2 >> color;
			int from = min(y1, y2);
			int to = max(y1, y2);
			for (int y = from; y <= to; y++) {
				image[y - 1][x - 1] = color;
			}
		} else if (cmd == 'H') {
			int x1, x2, y;
			char color;
			iss >> x1 >> x2 >> y >> color;
			int from = min(x1, x2);
			int to = max(x1, x2);
			for (int x = from; x <= to; x++) {
				image[y - 1][x - 1] = color;
			}
		} else if (cmd == 'K') {
			int x1, y1, x2, y2;
			char color;
			iss >> x1 >> y1 >> x2 >> y2 >> color;
			int fromX = min(x1, x2);
			int toX = max(x1, x2);
			int fromY = min(y1, y2);
			int toY = max(y1, y2);
			for (int y = fromY; y <= toY; y++) {
				for (int x = fromX; x <= toX; x++) {
					image[y - 1][x - 1] = color;
				}
			}
		} else if (cmd == 'F') {
			int x, y;
			char color;
			iss >> x >> y >> color;
			floodFill(image, rows, cols, x - 1, y - 1, color);
		} else if (cmd == 'S') {
			string name;
			iss >> name;
			cout << name << '\n';
			for (int y = 0; y < rows; y++) {
				cout << image[y] << '\n';
			}
		}
	}

	return 0;
}
