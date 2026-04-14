/**
 * pc110104
 * uva706
 */

#include <stdio.h>
#include <string.h>

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

int has_segment(int mask, int segment) {
	return (mask & segment) != 0;
}

void print_horizontal(int on, int s) {
	putchar(' ');
	for (int i = 0; i < s; i++) {
		putchar(on ? '-' : ' ');
	}
	putchar(' ');
}

void print_vertical(int left_on, int right_on, int s) {
	putchar(left_on ? '|' : ' ');
	for (int i = 0; i < s; i++) {
		putchar(' ');
	}
	putchar(right_on ? '|' : ' ');
}

void print_lcd(int s, const char *n) {
	int len = (int)strlen(n);
	int rows = 2 * s + 3;

	for (int row = 0; row < rows; row++) {
		for (int i = 0; i < len; i++) {
			int digit = n[i] - '0';
			int mask = DIGIT_MASKS[digit];

			if (row == 0) {
				print_horizontal(has_segment(mask, SEG_TOP), s);
			} else if (row > 0 && row < s + 1) {
				print_vertical(has_segment(mask, SEG_UPPER_LEFT), has_segment(mask, SEG_UPPER_RIGHT), s);
			} else if (row == s + 1) {
				print_horizontal(has_segment(mask, SEG_MIDDLE), s);
			} else if (row > s + 1 && row < 2 * s + 2) {
				print_vertical(has_segment(mask, SEG_LOWER_LEFT), has_segment(mask, SEG_LOWER_RIGHT), s);
			} else {
				print_horizontal(has_segment(mask, SEG_BOTTOM), s);
			}

			if (i < len - 1) {
				putchar(' ');
			}
		}
		putchar('\n');
	}
	putchar('\n');
}

int main(void) {
	int s;
	char n[32];

	while (scanf("%d %31s", &s, n) == 2) {
		if (s == 0 && strcmp(n, "0") == 0) {
			break;
		}

		print_lcd(s, n);
	}

	return 0;
}
