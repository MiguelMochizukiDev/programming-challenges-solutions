/**
 * pc110108
 * uva10142
 */

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main() {
	string line;
	getline(cin, line);
	int cases = stoi(line);

	for (int caseIdx = 0; caseIdx < cases; caseIdx++) {
		while (getline(cin, line) && line.empty()) {
		}

		int n = stoi(line);
		vector<string> names(n);
		for (int i = 0; i < n; i++) {
			getline(cin, names[i]);
		}

		vector<vector<int>> ballots;
		while (getline(cin, line)) {
			if (line.empty()) {
				break;
			}
			istringstream iss(line);
			vector<int> ballot;
			for (int i = 0; i < n; i++) {
				int v;
				iss >> v;
				ballot.push_back(v - 1);
			}
			if ((int)ballot.size() == n) {
				ballots.push_back(ballot);
			}
		}

		vector<bool> eliminated(n, false);

		while (true) {
			vector<int> votes(n, 0);
			int maxVotes = 0;
			int minVotes = 1000000;

			for (const auto& ballot : ballots) {
				for (int rank = 0; rank < n; rank++) {
					int candidate = ballot[rank];
					if (!eliminated[candidate]) {
						votes[candidate]++;
						break;
					}
				}
			}

			for (int c = 0; c < n; c++) {
				if (!eliminated[c]) {
					if (votes[c] > maxVotes) {
						maxVotes = votes[c];
					}
					if (votes[c] < minVotes) {
						minVotes = votes[c];
					}
				}
			}

			if (maxVotes * 2 > (int)ballots.size()) {
				for (int c = 0; c < n; c++) {
					if (!eliminated[c] && votes[c] == maxVotes) {
						cout << names[c] << '\n';
					}
				}
				break;
			}

			if (maxVotes == minVotes) {
				for (int c = 0; c < n; c++) {
					if (!eliminated[c]) {
						cout << names[c] << '\n';
					}
				}
				break;
			}

			for (int c = 0; c < n; c++) {
				if (!eliminated[c] && votes[c] == minVotes) {
					eliminated[c] = true;
				}
			}
		}

		if (caseIdx < cases - 1) {
			cout << '\n';
		}
	}

	return 0;
}
