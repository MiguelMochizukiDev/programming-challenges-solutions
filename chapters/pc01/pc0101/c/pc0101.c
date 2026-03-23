/**
 * pc110101
 * uva100
 */

#include <stdio.h>

int calculate_collatz_len(int num) {
	int collatz_len = 1;

	long current = (long)num;
	while (current != 1) {
		if (current & 1) {
			current += (current << 1) + 1;
		} else {
			current = current >> 1;
		}
		collatz_len++;
	}

	return collatz_len;
}

int find_highest_collatz_len(int i, int j) {
	int highest_collatz_len;

	int min = (i < j) ? i : j;
	int max = (i > j) ? i : j;

	highest_collatz_len = 1;
	for (int num = min; num <= max; num++) {
		int collatz_len = calculate_collatz_len(num);
		if (collatz_len > highest_collatz_len) {
			highest_collatz_len = collatz_len;
		}
	}

	return highest_collatz_len;
}

int main(void) {
	int i;
	int j;

	while (scanf("%d %d", &i, &j) == 2) {
		int highest_collatz_len = find_highest_collatz_len(i, j);
		printf("%d %d %d\n", i, j, highest_collatz_len);
	}

	return 0;
}