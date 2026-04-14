/**
 * pc110201
 * uva10038
 */

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main() {
	string line;

	while (getline(cin, line)) {
		if (line.empty()) {
			continue;
		}

		istringstream iss(line);
		int n;
		iss >> n;

		if (n <= 1) {
			cout << "Jolly\n";
			continue;
		}

		vector<int> seq(n);
		for (int i = 0; i < n; i++) {
			iss >> seq[i];
		}

		vector<bool> seen(n, false);
		for (int i = 1; i < n; i++) {
			int diff = seq[i] - seq[i - 1];
			if (diff < 0) {
				diff = -diff;
			}
			if (diff >= 1 && diff <= n - 1) {
				seen[diff] = true;
			}
		}

		bool jolly = true;
		for (int d = 1; d <= n - 1; d++) {
			if (!seen[d]) {
				jolly = false;
				break;
			}
		}

		cout << (jolly ? "Jolly" : "Not jolly") << '\n';
	}

	return 0;
}
