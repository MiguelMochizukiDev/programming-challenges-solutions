/**
 * pc110103
 * uva10137
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long parse_cents(const char *amount_str) {
	long dollars = strtol(amount_str, NULL, 10);
	long cents = 0;
	const char *dot = strchr(amount_str, '.');

	if (dot != NULL) {
		if (dot[1] >= '0' && dot[1] <= '9') {
			cents += (dot[1] - '0') * 10;
		}
		if (dot[2] >= '0' && dot[2] <= '9') {
			cents += dot[2] - '0';
		}
	}

	return dollars * 100 + cents;
}

int main(void) {
	int n;

	while (scanf("%d", &n) == 1 && n != 0) {
		long expenses[1000];
		long total = 0;
		char amount_str[32];

		for (int i = 0; i < n; i++) {
			if (scanf("%31s", amount_str) != 1) {
				return 0;
			}
			expenses[i] = parse_cents(amount_str);
			total += expenses[i];
		}

		long avg_floor = total / n;
		long avg_ceil = (total % n == 0) ? avg_floor : (avg_floor + 1);
		long give = 0;
		long take = 0;

		for (int i = 0; i < n; i++) {
			if (expenses[i] > avg_ceil) {
				give += expenses[i] - avg_ceil;
			} else if (expenses[i] < avg_floor) {
				take += avg_floor - expenses[i];
			}
		}

		long exchange = (give > take) ? give : take;
		printf("$%ld.%02ld\n", exchange / 100, exchange % 100);
	}

	return 0;
}
