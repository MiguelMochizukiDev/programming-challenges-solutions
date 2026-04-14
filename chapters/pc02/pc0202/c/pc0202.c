/**
 * pc110202
 * uva10315
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	int rank;
	int tiebreak[5];
} HandValue;

int card_value(char c) {
	if (c >= '2' && c <= '9') {
		return c - '0';
	}
	if (c == 'T') return 10;
	if (c == 'J') return 11;
	if (c == 'Q') return 12;
	if (c == 'K') return 13;
	return 14;
}

int cmp_desc(const void *a, const void *b) {
	int x = *(const int *)a;
	int y = *(const int *)b;
	return y - x;
}

void evaluate_hand(char cards[5][3], HandValue *hv) {
	int values[5];
	char suits[5];
	int count[15] = {0};
	int sorted[5];
	int freq_vals[5];
	int freq_cnts[5];
	int freq_size = 0;

	for (int i = 0; i < 5; i++) {
		values[i] = card_value(cards[i][0]);
		suits[i] = cards[i][1];
		count[values[i]]++;
		sorted[i] = values[i];
	}
	qsort(sorted, 5, sizeof(int), cmp_desc);

	int flush = 1;
	for (int i = 1; i < 5; i++) {
		if (suits[i] != suits[0]) {
			flush = 0;
			break;
		}
	}

	int straight = 1;
	for (int i = 0; i < 4; i++) {
		if (sorted[i] - 1 != sorted[i + 1]) {
			straight = 0;
			break;
		}
	}
	int straight_high = sorted[0];

	for (int v = 14; v >= 2; v--) {
		if (count[v] > 0) {
			freq_vals[freq_size] = v;
			freq_cnts[freq_size] = count[v];
			freq_size++;
		}
	}

	for (int i = 0; i < freq_size; i++) {
		for (int j = i + 1; j < freq_size; j++) {
			if (freq_cnts[j] > freq_cnts[i] ||
			   (freq_cnts[j] == freq_cnts[i] && freq_vals[j] > freq_vals[i])) {
				int tv = freq_vals[i];
				freq_vals[i] = freq_vals[j];
				freq_vals[j] = tv;
				int tc = freq_cnts[i];
				freq_cnts[i] = freq_cnts[j];
				freq_cnts[j] = tc;
			}
		}
	}

	memset(hv->tiebreak, 0, sizeof(hv->tiebreak));

	if (straight && flush) {
		hv->rank = 8;
		hv->tiebreak[0] = straight_high;
		return;
	}
	if (freq_cnts[0] == 4) {
		hv->rank = 7;
		hv->tiebreak[0] = freq_vals[0];
		hv->tiebreak[1] = freq_vals[1];
		return;
	}
	if (freq_cnts[0] == 3 && freq_cnts[1] == 2) {
		hv->rank = 6;
		hv->tiebreak[0] = freq_vals[0];
		return;
	}
	if (flush) {
		hv->rank = 5;
		for (int i = 0; i < 5; i++) hv->tiebreak[i] = sorted[i];
		return;
	}
	if (straight) {
		hv->rank = 4;
		hv->tiebreak[0] = straight_high;
		return;
	}
	if (freq_cnts[0] == 3) {
		hv->rank = 3;
		hv->tiebreak[0] = freq_vals[0];
		int k = 1;
		for (int i = 1; i < freq_size; i++) hv->tiebreak[k++] = freq_vals[i];
		return;
	}
	if (freq_cnts[0] == 2 && freq_cnts[1] == 2) {
		hv->rank = 2;
		hv->tiebreak[0] = freq_vals[0];
		hv->tiebreak[1] = freq_vals[1];
		hv->tiebreak[2] = freq_vals[2];
		return;
	}
	if (freq_cnts[0] == 2) {
		hv->rank = 1;
		hv->tiebreak[0] = freq_vals[0];
		int k = 1;
		for (int i = 1; i < freq_size; i++) hv->tiebreak[k++] = freq_vals[i];
		return;
	}

	hv->rank = 0;
	for (int i = 0; i < 5; i++) hv->tiebreak[i] = sorted[i];
}

int compare_hands(HandValue a, HandValue b) {
	if (a.rank != b.rank) {
		return (a.rank > b.rank) ? 1 : -1;
	}
	for (int i = 0; i < 5; i++) {
		if (a.tiebreak[i] != b.tiebreak[i]) {
			return (a.tiebreak[i] > b.tiebreak[i]) ? 1 : -1;
		}
	}
	return 0;
}

int main(void) {
	char black[5][3];
	char white[5][3];

	while (scanf("%2s %2s %2s %2s %2s %2s %2s %2s %2s %2s",
		black[0], black[1], black[2], black[3], black[4],
		white[0], white[1], white[2], white[3], white[4]) == 10) {
		HandValue hb, hw;
		evaluate_hand(black, &hb);
		evaluate_hand(white, &hw);

		int cmp = compare_hands(hb, hw);
		if (cmp > 0) {
			printf("Black wins.\n");
		} else if (cmp < 0) {
			printf("White wins.\n");
		} else {
			printf("Tie.\n");
		}
	}

	return 0;
}
