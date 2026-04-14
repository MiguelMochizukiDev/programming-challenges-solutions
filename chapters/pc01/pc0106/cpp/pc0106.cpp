/**
 * pc110106
 * uva10033
 */

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int runProgram(vector<int>& ram) {
	vector<int> reg(10, 0);
	int pc = 0;
	int count = 0;

	while (true) {
		int instr = ram[pc];
		int opcode;
		int d;
		int sOrN;

		pc = (pc + 1) % 1000;
		count++;

		opcode = instr / 100;
		d = (instr / 10) % 10;
		sOrN = instr % 10;

		if (opcode == 1) {
			break;
		} else if (opcode == 2) {
			reg[d] = sOrN;
		} else if (opcode == 3) {
			reg[d] = (reg[d] + sOrN) % 1000;
		} else if (opcode == 4) {
			reg[d] = (reg[d] * sOrN) % 1000;
		} else if (opcode == 5) {
			reg[d] = reg[sOrN];
		} else if (opcode == 6) {
			reg[d] = (reg[d] + reg[sOrN]) % 1000;
		} else if (opcode == 7) {
			reg[d] = (reg[d] * reg[sOrN]) % 1000;
		} else if (opcode == 8) {
			reg[d] = ram[reg[sOrN]];
		} else if (opcode == 9) {
			ram[reg[sOrN]] = reg[d];
		} else if (opcode == 0) {
			if (reg[sOrN] != 0) {
				pc = reg[d];
			}
		}
	}

	return count;
}

int main() {
	string line;
	getline(cin, line);
	int cases = stoi(line);

	for (int caseIdx = 0; caseIdx < cases; caseIdx++) {
		vector<int> ram(1000, 0);
		int addr = 0;

		while (getline(cin, line) && line.empty()) {
		}

		if (!line.empty()) {
			ram[addr++] = stoi(line);
		}

		while (addr < 1000 && getline(cin, line)) {
			if (line.empty()) {
				break;
			}
			ram[addr++] = stoi(line);
		}

		cout << runProgram(ram) << '\n';
		if (caseIdx < cases - 1) {
			cout << '\n';
		}
	}

	return 0;
}
