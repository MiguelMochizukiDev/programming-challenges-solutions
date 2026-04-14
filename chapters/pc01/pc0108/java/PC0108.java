/*
 * pc110108
 * uva10142
 */

package chapters.pc01.pc0108.java;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class PC0108 {

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder out = new StringBuilder();

        int cases = Integer.parseInt(br.readLine().trim());

        for (int caseIdx = 0; caseIdx < cases; caseIdx++) {
            String line;
            while ((line = br.readLine()) != null && line.trim().isEmpty()) {
            }

            int n = Integer.parseInt(line.trim());
            String[] names = new String[n];
            for (int i = 0; i < n; i++) {
                names[i] = br.readLine();
            }

            ArrayList<int[]> ballots = new ArrayList<>();
            while ((line = br.readLine()) != null && !line.trim().isEmpty()) {
                StringTokenizer st = new StringTokenizer(line);
                int[] ballot = new int[n];
                for (int i = 0; i < n; i++) {
                    ballot[i] = Integer.parseInt(st.nextToken()) - 1;
                }
                ballots.add(ballot);
            }

            boolean[] eliminated = new boolean[n];

            while (true) {
                int[] votes = new int[n];
                int maxVotes = 0;
                int minVotes = 1000000;

                for (int[] ballot : ballots) {
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

                if (maxVotes * 2 > ballots.size()) {
                    for (int c = 0; c < n; c++) {
                        if (!eliminated[c] && votes[c] == maxVotes) {
                            out.append(names[c]).append('\n');
                        }
                    }
                    break;
                }

                if (maxVotes == minVotes) {
                    for (int c = 0; c < n; c++) {
                        if (!eliminated[c]) {
                            out.append(names[c]).append('\n');
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
                out.append('\n');
            }
        }

        System.out.print(out);
    }
}
