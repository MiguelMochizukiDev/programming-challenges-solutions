/**
 * pc110104
 * uva706
 */

#include <iostream>
#include <string>

using namespace std;

enum {
	SEG_TOP = 1 << 0,
	SEG_UPPER_LEFT = 1 << 1,
	SEG_UPPER_RIGHT = 1 << 2,
	SEG_MIDDLE = 1 << 3,
	SEG_LOWER_LEFT = 1 << 4,
	SEG_LOWER_RIGHT = 1 << 5,
	SEG_BOTTOM = 1 << 6
};

const int DIGIT_MASKS[10] = {
	SEG_TOP | SEG_UPPER_LEFT | SEG_UPPER_RIGHT | SEG_LOWER_LEFT | SEG_LOWER_RIGHT | SEG_BOTTOM,
	SEG_UPPER_RIGHT | SEG_LOWER_RIGHT,
	SEG_TOP | SEG_UPPER_RIGHT | SEG_MIDDLE | SEG_LOWER_LEFT | SEG_BOTTOM,
	SEG_TOP | SEG_UPPER_RIGHT | SEG_MIDDLE | SEG_LOWER_RIGHT | SEG_BOTTOM,
	SEG_UPPER_LEFT | SEG_UPPER_RIGHT | SEG_MIDDLE | SEG_LOWER_RIGHT,
	SEG_TOP | SEG_UPPER_LEFT | SEG_MIDDLE | SEG_LOWER_RIGHT | SEG_BOTTOM,
	SEG_TOP | SEG_UPPER_LEFT | SEG_MIDDLE | SEG_LOWER_LEFT | SEG_LOWER_RIGHT | SEG_BOTTOM,
	SEG_TOP | SEG_UPPER_RIGHT | SEG_LOWER_RIGHT,
	SEG_TOP | SEG_UPPER_LEFT | SEG_UPPER_RIGHT | SEG_MIDDLE | SEG_LOWER_LEFT | SEG_LOWER_RIGHT | SEG_BOTTOM,
	SEG_TOP | SEG_UPPER_LEFT | SEG_UPPER_RIGHT | SEG_MIDDLE | SEG_LOWER_RIGHT | SEG_BOTTOM
};

bool hasSegment(int mask, int segment) {
	return (mask & segment) != 0;
}

void printHorizontal(int on, int s) {
	cout << ' ';
	for (int i = 0; i < s; i++) {
		cout << (on ? '-' : ' ');
	}
	cout << ' ';
}

void printVertical(int leftOn, int rightOn, int s) {
	cout << (leftOn ? '|' : ' ');
	for (int i = 0; i < s; i++) {
		cout << ' ';
	}
	cout << (rightOn ? '|' : ' ');
}

void printLcd(int s, const string& n) {
	int rows = 2 * s + 3;

	for (int row = 0; row < rows; row++) {
		for (int i = 0; i < (int)n.size(); i++) {
			int digit = n[i] - '0';
			int mask = DIGIT_MASKS[digit];

			if (row == 0) {
				printHorizontal(hasSegment(mask, SEG_TOP), s);
			} else if (row > 0 && row < s + 1) {
				printVertical(hasSegment(mask, SEG_UPPER_LEFT), hasSegment(mask, SEG_UPPER_RIGHT), s);
			} else if (row == s + 1) {
				printHorizontal(hasSegment(mask, SEG_MIDDLE), s);
			} else if (row > s + 1 && row < 2 * s + 2) {
				printVertical(hasSegment(mask, SEG_LOWER_LEFT), hasSegment(mask, SEG_LOWER_RIGHT), s);
			} else {
				printHorizontal(hasSegment(mask, SEG_BOTTOM), s);
			}

			if (i < (int)n.size() - 1) {
				cout << ' ';
			}
		}
		cout << '\n';
	}
	cout << '\n';
}

int main() {
	int s;
	string n;

	while (cin >> s >> n) {
		if (s == 0 && n == "0") {
			break;
		}

		printLcd(s, n);
	}

	return 0;
}
