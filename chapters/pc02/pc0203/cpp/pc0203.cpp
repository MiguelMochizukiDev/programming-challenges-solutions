/**
 * pc110203
 * uva10050
 */

#include <iostream>
#include <vector>

using namespace std;

int main() {
	int t;
	if (!(cin >> t)) {
		return 0;
	}

	while (t--) {
		int n;
		int p;
		cin >> n >> p;

		vector<int> h(p);
		for (int i = 0; i < p; i++) {
			cin >> h[i];
		}

		vector<bool> isHartal(n + 1, false);
		int lost = 0;

		for (int i = 0; i < p; i++) {
			for (int day = h[i]; day <= n; day += h[i]) {
				int weekday = day % 7;
				if (weekday == 6 || weekday == 0) {
					continue;
				}
				if (!isHartal[day]) {
					isHartal[day] = true;
					lost++;
				}
			}
		}

		cout << lost << '\n';
	}

	return 0;
}
