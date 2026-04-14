/*
 * pc110201
 * uva10038
 */

package chapters.pc02.pc0201.java;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class PC0201 {

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder out = new StringBuilder();
        String line;

        while ((line = br.readLine()) != null) {
            if (line.trim().isEmpty()) {
                continue;
            }

            StringTokenizer st = new StringTokenizer(line);
            int n = Integer.parseInt(st.nextToken());

            if (n <= 1) {
                out.append("Jolly\n");
                continue;
            }

            int[] seq = new int[n];
            for (int i = 0; i < n; i++) {
                seq[i] = Integer.parseInt(st.nextToken());
            }

            boolean[] seen = new boolean[n];
            for (int i = 1; i < n; i++) {
                int diff = Math.abs(seq[i] - seq[i - 1]);
                if (diff >= 1 && diff <= n - 1) {
                    seen[diff] = true;
                }
            }

            boolean jolly = true;
            for (int d = 1; d <= n - 1; d++) {
                if (!seen[d]) {
                    jolly = false;
                    break;
                }
            }

            out.append(jolly ? "Jolly\n" : "Not jolly\n");
        }

        System.out.print(out);
    }
}
