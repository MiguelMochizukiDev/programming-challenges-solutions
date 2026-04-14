/**
 * pc110203
 * uva10050
 */

#include <stdio.h>

int main(void) {
	int t;

	if (scanf("%d", &t) != 1) {
		return 0;
	}

	for (int case_idx = 0; case_idx < t; case_idx++) {
		int n;
		int p;
		int lost = 0;
		int hartal[101];
		int is_hartal[3651] = {0};

		if (scanf("%d", &n) != 1) {
			return 0;
		}
		if (scanf("%d", &p) != 1) {
			return 0;
		}

		for (int i = 0; i < p; i++) {
			if (scanf("%d", &hartal[i]) != 1) {
				return 0;
			}
		}

		for (int i = 0; i < p; i++) {
			for (int day = hartal[i]; day <= n; day += hartal[i]) {
				int weekday = day % 7;
				if (weekday == 6 || weekday == 0) {
					continue;
				}
				if (!is_hartal[day]) {
					is_hartal[day] = 1;
					lost++;
				}
			}
		}

		printf("%d\n", lost);
	}

	return 0;
}
