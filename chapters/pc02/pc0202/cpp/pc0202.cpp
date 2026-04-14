/**
 * pc110202
 * uva10315
 */

#include <algorithm>
#include <array>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

struct HandValue {
	int rank;
	array<int, 5> tiebreak;
};

int cardValue(char c) {
	if (c >= '2' && c <= '9') return c - '0';
	if (c == 'T') return 10;
	if (c == 'J') return 11;
	if (c == 'Q') return 12;
	if (c == 'K') return 13;
	return 14;
}

HandValue evaluateHand(const array<string, 5>& cards) {
	vector<int> values;
	vector<char> suits;
	map<int, int> freq;

	for (const string& card : cards) {
		int v = cardValue(card[0]);
		values.push_back(v);
		suits.push_back(card[1]);
		freq[v]++;
	}

	sort(values.begin(), values.end(), greater<int>());

	bool flush = true;
	for (int i = 1; i < 5; i++) {
		if (suits[i] != suits[0]) {
			flush = false;
			break;
		}
	}

	bool straight = true;
	for (int i = 0; i < 4; i++) {
		if (values[i] - 1 != values[i + 1]) {
			straight = false;
			break;
		}
	}
	int straightHigh = values[0];

	vector<pair<int, int>> grouped;
	for (auto [val, cnt] : freq) {
		grouped.push_back({cnt, val});
	}
	sort(grouped.begin(), grouped.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
		if (a.first != b.first) return a.first > b.first;
		return a.second > b.second;
	});

	HandValue hv{0, {0, 0, 0, 0, 0}};

	if (straight && flush) {
		hv.rank = 8;
		hv.tiebreak[0] = straightHigh;
		return hv;
	}
	if (grouped[0].first == 4) {
		hv.rank = 7;
		hv.tiebreak[0] = grouped[0].second;
		hv.tiebreak[1] = grouped[1].second;
		return hv;
	}
	if (grouped[0].first == 3 && grouped[1].first == 2) {
		hv.rank = 6;
		hv.tiebreak[0] = grouped[0].second;
		return hv;
	}
	if (flush) {
		hv.rank = 5;
		for (int i = 0; i < 5; i++) hv.tiebreak[i] = values[i];
		return hv;
	}
	if (straight) {
		hv.rank = 4;
		hv.tiebreak[0] = straightHigh;
		return hv;
	}
	if (grouped[0].first == 3) {
		hv.rank = 3;
		hv.tiebreak[0] = grouped[0].second;
		hv.tiebreak[1] = grouped[1].second;
		hv.tiebreak[2] = grouped[2].second;
		return hv;
	}
	if (grouped[0].first == 2 && grouped[1].first == 2) {
		hv.rank = 2;
		hv.tiebreak[0] = grouped[0].second;
		hv.tiebreak[1] = grouped[1].second;
		hv.tiebreak[2] = grouped[2].second;
		return hv;
	}
	if (grouped[0].first == 2) {
		hv.rank = 1;
		hv.tiebreak[0] = grouped[0].second;
		hv.tiebreak[1] = grouped[1].second;
		hv.tiebreak[2] = grouped[2].second;
		hv.tiebreak[3] = grouped[3].second;
		return hv;
	}

	hv.rank = 0;
	for (int i = 0; i < 5; i++) hv.tiebreak[i] = values[i];
	return hv;
}

int compareHands(const HandValue& a, const HandValue& b) {
	if (a.rank != b.rank) return (a.rank > b.rank) ? 1 : -1;
	for (int i = 0; i < 5; i++) {
		if (a.tiebreak[i] != b.tiebreak[i]) return (a.tiebreak[i] > b.tiebreak[i]) ? 1 : -1;
	}
	return 0;
}

int main() {
	array<string, 5> black;
	array<string, 5> white;

	while (cin >> black[0] >> black[1] >> black[2] >> black[3] >> black[4]
	          >> white[0] >> white[1] >> white[2] >> white[3] >> white[4]) {
		HandValue hb = evaluateHand(black);
		HandValue hw = evaluateHand(white);

		int cmp = compareHands(hb, hw);
		if (cmp > 0) {
			cout << "Black wins." << '\n';
		} else if (cmp < 0) {
			cout << "White wins." << '\n';
		} else {
			cout << "Tie." << '\n';
		}
	}

	return 0;
}
