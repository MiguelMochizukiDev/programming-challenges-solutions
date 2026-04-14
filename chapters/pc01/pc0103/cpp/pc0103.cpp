/**
 * pc110103
 * uva10137
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

long parseCents(const string& amountStr) {
	size_t dotPos = amountStr.find('.');
	long dollars = stol(amountStr.substr(0, dotPos));
	long cents = 0;

	if (dotPos != string::npos) {
		if (dotPos + 1 < amountStr.size() && amountStr[dotPos + 1] >= '0' && amountStr[dotPos + 1] <= '9') {
			cents += (amountStr[dotPos + 1] - '0') * 10;
		}
		if (dotPos + 2 < amountStr.size() && amountStr[dotPos + 2] >= '0' && amountStr[dotPos + 2] <= '9') {
			cents += amountStr[dotPos + 2] - '0';
		}
	}

	return dollars * 100 + cents;
}

int main() {
	int n;

	while (cin >> n && n != 0) {
		vector<long> expenses(n);
		long total = 0;

		for (int i = 0; i < n; i++) {
			string amountStr;
			cin >> amountStr;
			expenses[i] = parseCents(amountStr);
			total += expenses[i];
		}

		long avgFloor = total / n;
		long avgCeil = (total % n == 0) ? avgFloor : (avgFloor + 1);
		long give = 0;
		long take = 0;

		for (int i = 0; i < n; i++) {
			if (expenses[i] > avgCeil) {
				give += expenses[i] - avgCeil;
			} else if (expenses[i] < avgFloor) {
				take += avgFloor - expenses[i];
			}
		}

		long exchange = max(give, take);
		cout << "$" << (exchange / 100) << ".";
		if (exchange % 100 < 10) {
			cout << "0";
		}
		cout << (exchange % 100) << "\n";
	}

	return 0;
}
