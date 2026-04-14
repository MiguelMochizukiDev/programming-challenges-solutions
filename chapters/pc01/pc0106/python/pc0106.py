"""
pc110106
uva10033
"""

import sys


def run_program(ram):
    reg = [0] * 10
    pc = 0
    count = 0

    while True:
        instr = ram[pc]
        pc = (pc + 1) % 1000
        count += 1

        opcode = instr // 100
        d = (instr // 10) % 10
        s_or_n = instr % 10

        if opcode == 1:
            break
        if opcode == 2:
            reg[d] = s_or_n
        elif opcode == 3:
            reg[d] = (reg[d] + s_or_n) % 1000
        elif opcode == 4:
            reg[d] = (reg[d] * s_or_n) % 1000
        elif opcode == 5:
            reg[d] = reg[s_or_n]
        elif opcode == 6:
            reg[d] = (reg[d] + reg[s_or_n]) % 1000
        elif opcode == 7:
            reg[d] = (reg[d] * reg[s_or_n]) % 1000
        elif opcode == 8:
            reg[d] = ram[reg[s_or_n]]
        elif opcode == 9:
            ram[reg[s_or_n]] = reg[d]
        elif opcode == 0 and reg[s_or_n] != 0:
            pc = reg[d]

    return count


def main():
    lines = sys.stdin.read().splitlines()
    cases = int(lines[0].strip())
    idx = 1
    results = []

    for _ in range(cases):
        while idx < len(lines) and not lines[idx].strip():
            idx += 1

        ram = [0] * 1000
        addr = 0

        while idx < len(lines) and lines[idx].strip():
            ram[addr] = int(lines[idx].strip())
            addr += 1
            idx += 1

        results.append(str(run_program(ram)))

    sys.stdout.write('\n\n'.join(results) + '\n')


if __name__ == '__main__':
    main()
