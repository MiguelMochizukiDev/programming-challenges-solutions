/*
 * pc0101
 * uva100
 */

package chapters.pc01.pc0101.java;

import java.util.Scanner;

public class PC0101 {

    public static int calculateCollatzLen(int num) {
        int collatzLen = 1;

        long current = num;

        while (current != 1) {
            if ((current & 1) == 1) {
                current += (current << 1) + 1;
            } else {
                current >>= 1;
            }
            collatzLen++;
        }

        return collatzLen;
    }

    public static int findHighestCollatzLen(int i, int j) {
        int highestCollatzLen;

        int min = Math.min(i, j);
        int max = Math.max(i, j);

        highestCollatzLen = 1;
        for (int num = min; num <= max; num++) {
            int collatzLen = calculateCollatzLen(num);
            if (collatzLen > highestCollatzLen) {
                highestCollatzLen = collatzLen;
            }
        }

        return highestCollatzLen;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        while (sc.hasNextInt()) {
            int i = sc.nextInt();
            int j = sc.nextInt();

            int result = findHighestCollatzLen(i, j);
            System.out.println(i + " " + j + " " + result);
        }

        sc.close();
    }
}