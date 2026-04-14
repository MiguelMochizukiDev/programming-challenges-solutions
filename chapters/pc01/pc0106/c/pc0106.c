/**
 * pc110106
 * uva10033
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_blank_line(const char *line) {
	for (int i = 0; line[i] != '\0'; i++) {
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n' && line[i] != '\r') {
			return 0;
		}
	}
	return 1;
}

int run_program(int ram[1000]) {
	int reg[10] = {0};
	int pc = 0;
	int count = 0;

	while (1) {
		int instr = ram[pc];
		int opcode;
		int d;
		int s_or_n;

		pc = (pc + 1) % 1000;
		count++;

		opcode = instr / 100;
		d = (instr / 10) % 10;
		s_or_n = instr % 10;

		if (opcode == 1) {
			break;
		} else if (opcode == 2) {
			reg[d] = s_or_n;
		} else if (opcode == 3) {
			reg[d] = (reg[d] + s_or_n) % 1000;
		} else if (opcode == 4) {
			reg[d] = (reg[d] * s_or_n) % 1000;
		} else if (opcode == 5) {
			reg[d] = reg[s_or_n];
		} else if (opcode == 6) {
			reg[d] = (reg[d] + reg[s_or_n]) % 1000;
		} else if (opcode == 7) {
			reg[d] = (reg[d] * reg[s_or_n]) % 1000;
		} else if (opcode == 8) {
			reg[d] = ram[reg[s_or_n]];
		} else if (opcode == 9) {
			ram[reg[s_or_n]] = reg[d];
		} else if (opcode == 0) {
			if (reg[s_or_n] != 0) {
				pc = reg[d];
			}
		}
	}

	return count;
}

int main(void) {
	char line[64];
	int cases;

	if (fgets(line, sizeof(line), stdin) == NULL) {
		return 0;
	}
	cases = atoi(line);

	for (int case_idx = 0; case_idx < cases; case_idx++) {
		int ram[1000] = {0};
		int addr = 0;

		while (fgets(line, sizeof(line), stdin) != NULL) {
			if (!is_blank_line(line)) {
				break;
			}
		}

		if (!feof(stdin) && !is_blank_line(line)) {
			ram[addr++] = atoi(line);
		}

		while (addr < 1000 && fgets(line, sizeof(line), stdin) != NULL) {
			if (is_blank_line(line)) {
				break;
			}
			ram[addr++] = atoi(line);
		}

		printf("%d\n", run_program(ram));
		if (case_idx < cases - 1) {
			printf("\n");
		}
	}

	return 0;
}
