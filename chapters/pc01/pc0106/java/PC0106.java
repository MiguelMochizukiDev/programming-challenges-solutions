/*
 * pc110106
 * uva10033
 */

package chapters.pc01.pc0106.java;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class PC0106 {

    public static int runProgram(int[] ram) {
        int[] reg = new int[10];
        int pc = 0;
        int count = 0;

        while (true) {
            int instr = ram[pc];
            pc = (pc + 1) % 1000;
            count++;

            int opcode = instr / 100;
            int d = (instr / 10) % 10;
            int sOrN = instr % 10;

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

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder out = new StringBuilder();

        int cases = Integer.parseInt(br.readLine().trim());

        for (int caseIdx = 0; caseIdx < cases; caseIdx++) {
            int[] ram = new int[1000];
            int addr = 0;
            String line;

            while ((line = br.readLine()) != null && line.trim().isEmpty()) {
            }

            if (line != null && !line.trim().isEmpty()) {
                ram[addr++] = Integer.parseInt(line.trim());
            }

            while (addr < 1000 && (line = br.readLine()) != null) {
                if (line.trim().isEmpty()) {
                    break;
                }
                ram[addr++] = Integer.parseInt(line.trim());
            }

            out.append(runProgram(ram)).append('\n');
            if (caseIdx < cases - 1) {
                out.append('\n');
            }
        }

        System.out.print(out);
    }
}
