/*
 * pc110203
 * uva10050
 */

package chapters.pc02.pc0203.java;

import java.util.Scanner;

public class PC0203 {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        if (!sc.hasNextInt()) {
            sc.close();
            return;
        }

        int t = sc.nextInt();

        for (int caseIdx = 0; caseIdx < t; caseIdx++) {
            int n = sc.nextInt();
            int p = sc.nextInt();

            int[] h = new int[p];
            for (int i = 0; i < p; i++) {
                h[i] = sc.nextInt();
            }

            boolean[] isHartal = new boolean[n + 1];
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

            System.out.println(lost);
        }

        sc.close();
    }
}
