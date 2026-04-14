/**
 * pc110201
 * uva10038
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	char line[65536];

	while (fgets(line, sizeof(line), stdin) != NULL) {
		char *token = strtok(line, " \t\r\n");
		if (token == NULL) {
			continue;
		}

		int n = atoi(token);
		if (n <= 1) {
			printf("Jolly\n");
			continue;
		}

		int prev;
		token = strtok(NULL, " \t\r\n");
		if (token == NULL) {
			printf("Not jolly\n");
			continue;
		}
		prev = atoi(token);

		int *seen = (int *)calloc((size_t)n, sizeof(int));
		int valid = 1;

		for (int i = 1; i < n; i++) {
			token = strtok(NULL, " \t\r\n");
			if (token == NULL) {
				valid = 0;
				break;
			}

			int current = atoi(token);
			int diff = current - prev;
			if (diff < 0) {
				diff = -diff;
			}

			if (diff >= 1 && diff <= n - 1) {
				seen[diff] = 1;
			} else {
				valid = 0;
			}

			prev = current;
		}

		if (valid) {
			for (int d = 1; d <= n - 1; d++) {
				if (!seen[d]) {
					valid = 0;
					break;
				}
			}
		}

		printf(valid ? "Jolly\n" : "Not jolly\n");
		free(seen);
	}

	return 0;
}
