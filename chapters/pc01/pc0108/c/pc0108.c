/**
 * pc110108
 * uva10142
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CANDIDATES 20
#define MAX_BALLOTS 1000
#define MAX_NAME_LEN 128
#define MAX_LINE_LEN 512

int is_blank_line(const char *line) {
	for (int i = 0; line[i] != '\0'; i++) {
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n' && line[i] != '\r') {
			return 0;
		}
	}
	return 1;
}

void trim_newline(char *s) {
	int len = (int)strlen(s);
	while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r')) {
		s[len - 1] = '\0';
		len--;
	}
}

int main(void) {
	char line[MAX_LINE_LEN];
	int cases;

	if (fgets(line, sizeof(line), stdin) == NULL) {
		return 0;
	}
	cases = atoi(line);

	for (int case_idx = 0; case_idx < cases; case_idx++) {
		int n;
		char names[MAX_CANDIDATES][MAX_NAME_LEN];
		int ballots[MAX_BALLOTS][MAX_CANDIDATES];
		int ballot_count = 0;
		int eliminated[MAX_CANDIDATES] = {0};

		while (fgets(line, sizeof(line), stdin) != NULL && is_blank_line(line)) {
		}
		if (feof(stdin)) {
			break;
		}

		n = atoi(line);
		for (int i = 0; i < n; i++) {
			if (fgets(names[i], sizeof(names[i]), stdin) == NULL) {
				return 0;
			}
			trim_newline(names[i]);
		}

		while (fgets(line, sizeof(line), stdin) != NULL) {
			if (is_blank_line(line)) {
				break;
			}

			char *token = strtok(line, " \t\r\n");
			int idx = 0;
			while (token != NULL && idx < n) {
				ballots[ballot_count][idx] = atoi(token) - 1;
				idx++;
				token = strtok(NULL, " \t\r\n");
			}
			if (idx == n) {
				ballot_count++;
			}
		}

		while (1) {
			int votes[MAX_CANDIDATES] = {0};
			int active_candidates = 0;
			int max_votes = 0;
			int min_votes = 1000000;

			for (int c = 0; c < n; c++) {
				if (!eliminated[c]) {
					active_candidates++;
				}
			}

			for (int b = 0; b < ballot_count; b++) {
				for (int rank = 0; rank < n; rank++) {
					int candidate = ballots[b][rank];
					if (!eliminated[candidate]) {
						votes[candidate]++;
						break;
					}
				}
			}

			for (int c = 0; c < n; c++) {
				if (!eliminated[c]) {
					if (votes[c] > max_votes) {
						max_votes = votes[c];
					}
					if (votes[c] < min_votes) {
						min_votes = votes[c];
					}
				}
			}

			if (max_votes * 2 > ballot_count) {
				for (int c = 0; c < n; c++) {
					if (!eliminated[c] && votes[c] == max_votes) {
						printf("%s\n", names[c]);
					}
				}
				break;
			}

			if (max_votes == min_votes) {
				for (int c = 0; c < n; c++) {
					if (!eliminated[c]) {
						printf("%s\n", names[c]);
					}
				}
				break;
			}

			for (int c = 0; c < n; c++) {
				if (!eliminated[c] && votes[c] == min_votes) {
					eliminated[c] = 1;
				}
			}

			if (active_candidates == 0) {
				break;
			}
		}

		if (case_idx < cases - 1) {
			printf("\n");
		}
	}

	return 0;
}
