/**
 * pc110204
 * uva843
 */

#include <algorithm>
#include <array>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

vector<string> dictByLen[17];
unordered_set<string> failedStates;

string patternOf(const string& word) {
	array<int, 26> first;
	first.fill(-1);
	int nextId = 0;
	string pattern;
	pattern.reserve(word.size());

	for (char ch : word) {
		int idx = ch - 'a';
		if (first[idx] == -1) {
			first[idx] = nextId++;
		}
		pattern.push_back((char)('a' + first[idx]));
	}

	return pattern;
}

bool fits(const string& enc, const string& plain, const array<int, 26>& toPlain, const array<int, 26>& toEnc) {
	for (int i = 0; i < (int)enc.size(); i++) {
		int e = enc[i] - 'a';
		int p = plain[i] - 'a';
		if ((toPlain[e] != -1 && toPlain[e] != p) || (toEnc[p] != -1 && toEnc[p] != e)) {
			return false;
		}
	}
	return true;
}

string stateKey(int idx, const array<int, 26>& toPlain, const array<int, 26>& toEnc) {
	string key = to_string(idx) + "|";
	for (int v : toPlain) {
		key += char((v + 1) / 10 + '0');
		key += char((v + 1) % 10 + '0');
	}
	key += '|';
	for (int v : toEnc) {
		key += char((v + 1) / 10 + '0');
		key += char((v + 1) % 10 + '0');
	}
	return key;
}

bool solveTopDown(
	const vector<string>& words,
	const vector<string>& patterns,
	const vector<int>& order,
	int idx,
	array<int, 26>& toPlain,
	array<int, 26>& toEnc
) {
	if (idx == (int)order.size()) {
		return true;
	}

	string key = stateKey(idx, toPlain, toEnc);
	if (failedStates.find(key) != failedStates.end()) {
		return false;
	}

	int widx = order[idx];
	const string& encWord = words[widx];
	const string& encPattern = patterns[widx];
	const vector<string>& cands = dictByLen[encWord.size()];

	for (const string& cand : cands) {
		if (patternOf(cand) != encPattern) {
			continue;
		}
		if (!fits(encWord, cand, toPlain, toEnc)) {
			continue;
		}

		vector<pair<int, int>> changedPlain;
		vector<pair<int, int>> changedEnc;

		for (int i = 0; i < (int)encWord.size(); i++) {
			int e = encWord[i] - 'a';
			int p = cand[i] - 'a';
			if (toPlain[e] == -1) {
				changedPlain.push_back({e, -1});
				toPlain[e] = p;
			}
			if (toEnc[p] == -1) {
				changedEnc.push_back({p, -1});
				toEnc[p] = e;
			}
		}

		if (solveTopDown(words, patterns, order, idx + 1, toPlain, toEnc)) {
			return true;
		}

		for (auto [i, oldVal] : changedPlain) {
			toPlain[i] = oldVal;
		}
		for (auto [i, oldVal] : changedEnc) {
			toEnc[i] = oldVal;
		}
	}

	failedStates.insert(key);
	return false;
}

int main() {
	int n;
	if (!(cin >> n)) {
		return 0;
	}

	for (int i = 0; i < 17; i++) {
		dictByLen[i].clear();
	}

	for (int i = 0; i < n; i++) {
		string w;
		cin >> w;
		dictByLen[w.size()].push_back(w);
	}

	string line;
	getline(cin, line);

	while (getline(cin, line)) {
		vector<string> words;
		vector<string> patterns;
		istringstream iss(line);
		string w;
		while (iss >> w) {
			words.push_back(w);
			patterns.push_back(patternOf(w));
		}

		vector<int> order(words.size());
		for (int i = 0; i < (int)order.size(); i++) {
			order[i] = i;
		}
		sort(order.begin(), order.end(), [&](int a, int b) {
			return dictByLen[words[a].size()].size() < dictByLen[words[b].size()].size();
		});

		array<int, 26> toPlain;
		array<int, 26> toEnc;
		toPlain.fill(-1);
		toEnc.fill(-1);

		failedStates.clear();
		bool ok = solveTopDown(words, patterns, order, 0, toPlain, toEnc);

		string out = line;
		if (ok) {
			for (char& ch : out) {
				if (ch != ' ') {
					int m = toPlain[ch - 'a'];
					ch = (m == -1) ? '*' : (char)('a' + m);
				}
			}
		} else {
			for (char& ch : out) {
				if (ch != ' ') {
					ch = '*';
				}
			}
		}

		cout << out << '\n';
	}

	return 0;
}
