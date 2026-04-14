/*
 * pc110104
 * uva706
 */

package chapters.pc01.pc0104.java;

import java.util.Scanner;

public class PC0104 {

    private static final int SEG_TOP = 1 << 0;
    private static final int SEG_UPPER_LEFT = 1 << 1;
    private static final int SEG_UPPER_RIGHT = 1 << 2;
    private static final int SEG_MIDDLE = 1 << 3;
    private static final int SEG_LOWER_LEFT = 1 << 4;
    private static final int SEG_LOWER_RIGHT = 1 << 5;
    private static final int SEG_BOTTOM = 1 << 6;

    private static final int[] DIGIT_MASKS = {
        SEG_TOP | SEG_UPPER_LEFT | SEG_UPPER_RIGHT | SEG_LOWER_LEFT | SEG_LOWER_RIGHT | SEG_BOTTOM,
        SEG_UPPER_RIGHT | SEG_LOWER_RIGHT,
        SEG_TOP | SEG_UPPER_RIGHT | SEG_MIDDLE | SEG_LOWER_LEFT | SEG_BOTTOM,
        SEG_TOP | SEG_UPPER_RIGHT | SEG_MIDDLE | SEG_LOWER_RIGHT | SEG_BOTTOM,
        SEG_UPPER_LEFT | SEG_UPPER_RIGHT | SEG_MIDDLE | SEG_LOWER_RIGHT,
        SEG_TOP | SEG_UPPER_LEFT | SEG_MIDDLE | SEG_LOWER_RIGHT | SEG_BOTTOM,
        SEG_TOP | SEG_UPPER_LEFT | SEG_MIDDLE | SEG_LOWER_LEFT | SEG_LOWER_RIGHT | SEG_BOTTOM,
        SEG_TOP | SEG_UPPER_RIGHT | SEG_LOWER_RIGHT,
        SEG_TOP | SEG_UPPER_LEFT | SEG_UPPER_RIGHT | SEG_MIDDLE | SEG_LOWER_LEFT | SEG_LOWER_RIGHT | SEG_BOTTOM,
        SEG_TOP | SEG_UPPER_LEFT | SEG_UPPER_RIGHT | SEG_MIDDLE | SEG_LOWER_RIGHT | SEG_BOTTOM
    };

    public static boolean hasSegment(int mask, int segment) {
        return (mask & segment) != 0;
    }

    public static String horizontal(int on, int s) {
        StringBuilder sb = new StringBuilder();
        sb.append(' ');
        for (int i = 0; i < s; i++) {
            sb.append(on == 1 ? '-' : ' ');
        }
        sb.append(' ');
        return sb.toString();
    }

    public static String vertical(int leftOn, int rightOn, int s) {
        StringBuilder sb = new StringBuilder();
        sb.append(leftOn == 1 ? '|' : ' ');
        for (int i = 0; i < s; i++) {
            sb.append(' ');
        }
        sb.append(rightOn == 1 ? '|' : ' ');
        return sb.toString();
    }

    public static void printLcd(int s, String n) {
        int rows = 2 * s + 3;

        for (int row = 0; row < rows; row++) {
            StringBuilder line = new StringBuilder();

            for (int i = 0; i < n.length(); i++) {
                int digit = n.charAt(i) - '0';
                int mask = DIGIT_MASKS[digit];

                if (row == 0) {
                    line.append(horizontal(hasSegment(mask, SEG_TOP) ? 1 : 0, s));
                } else if (row > 0 && row < s + 1) {
                    line.append(vertical(hasSegment(mask, SEG_UPPER_LEFT) ? 1 : 0, hasSegment(mask, SEG_UPPER_RIGHT) ? 1 : 0, s));
                } else if (row == s + 1) {
                    line.append(horizontal(hasSegment(mask, SEG_MIDDLE) ? 1 : 0, s));
                } else if (row > s + 1 && row < 2 * s + 2) {
                    line.append(vertical(hasSegment(mask, SEG_LOWER_LEFT) ? 1 : 0, hasSegment(mask, SEG_LOWER_RIGHT) ? 1 : 0, s));
                } else {
                    line.append(horizontal(hasSegment(mask, SEG_BOTTOM) ? 1 : 0, s));
                }

                if (i < n.length() - 1) {
                    line.append(' ');
                }
            }

            System.out.println(line);
        }

        System.out.println();
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        while (sc.hasNextInt()) {
            int s = sc.nextInt();
            String n = sc.next();

            if (s == 0 && n.equals("0")) {
                break;
            }

            printLcd(s, n);
        }

        sc.close();
    }
}
