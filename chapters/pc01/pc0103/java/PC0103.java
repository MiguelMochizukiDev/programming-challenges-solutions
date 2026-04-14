/*
 * pc110103
 * uva10137
 */

package chapters.pc01.pc0103.java;

import java.util.Scanner;

public class PC0103 {

    public static long parseCents(String amount) {
        String[] parts = amount.split("\\.");
        long dollars = Long.parseLong(parts[0]);
        String centsPart = parts[1];

        if (centsPart.length() == 1) {
            centsPart = centsPart + "0";
        } else if (centsPart.length() > 2) {
            centsPart = centsPart.substring(0, 2);
        }

        long cents = Long.parseLong(centsPart);

        return dollars * 100 + cents;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        while (sc.hasNextInt()) {
            int n = sc.nextInt();
            if (n == 0) {
                break;
            }

            long[] expenses = new long[n];
            long total = 0;

            for (int i = 0; i < n; i++) {
                String amount = sc.next();
                expenses[i] = parseCents(amount);
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

            long exchange = Math.max(give, take);
            System.out.printf("$%d.%02d%n", exchange / 100, exchange % 100);
        }

        sc.close();
    }
}
