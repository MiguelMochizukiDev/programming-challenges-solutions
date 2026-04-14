/*
 * pc110202
 * uva10315
 */

package chapters.pc02.pc0202.java;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.StringTokenizer;

public class PC0202 {

    static class HandValue {
        int rank;
        int[] tiebreak;

        HandValue(int rank, int[] tiebreak) {
            this.rank = rank;
            this.tiebreak = tiebreak;
        }
    }

    static int cardValue(char c) {
        if (c >= '2' && c <= '9') return c - '0';
        if (c == 'T') return 10;
        if (c == 'J') return 11;
        if (c == 'Q') return 12;
        if (c == 'K') return 13;
        return 14;
    }

    static HandValue evaluateHand(String[] cards) {
        List<Integer> values = new ArrayList<>();
        char[] suits = new char[5];
        Map<Integer, Integer> freq = new HashMap<>();

        for (int i = 0; i < 5; i++) {
            int v = cardValue(cards[i].charAt(0));
            values.add(v);
            suits[i] = cards[i].charAt(1);
            freq.put(v, freq.getOrDefault(v, 0) + 1);
        }

        values.sort(Collections.reverseOrder());

        boolean flush = true;
        for (int i = 1; i < 5; i++) {
            if (suits[i] != suits[0]) {
                flush = false;
                break;
            }
        }

        boolean straight = true;
        for (int i = 0; i < 4; i++) {
            if (values.get(i) - 1 != values.get(i + 1)) {
                straight = false;
                break;
            }
        }
        int straightHigh = values.get(0);

        List<int[]> grouped = new ArrayList<>();
        for (Map.Entry<Integer, Integer> e : freq.entrySet()) {
            grouped.add(new int[]{e.getValue(), e.getKey()});
        }
        grouped.sort((a, b) -> {
            if (a[0] != b[0]) return b[0] - a[0];
            return b[1] - a[1];
        });

        int[] tb = new int[5];

        if (straight && flush) {
            tb[0] = straightHigh;
            return new HandValue(8, tb);
        }
        if (grouped.get(0)[0] == 4) {
            tb[0] = grouped.get(0)[1];
            tb[1] = grouped.get(1)[1];
            return new HandValue(7, tb);
        }
        if (grouped.get(0)[0] == 3 && grouped.get(1)[0] == 2) {
            tb[0] = grouped.get(0)[1];
            return new HandValue(6, tb);
        }
        if (flush) {
            for (int i = 0; i < 5; i++) tb[i] = values.get(i);
            return new HandValue(5, tb);
        }
        if (straight) {
            tb[0] = straightHigh;
            return new HandValue(4, tb);
        }
        if (grouped.get(0)[0] == 3) {
            tb[0] = grouped.get(0)[1];
            tb[1] = grouped.get(1)[1];
            tb[2] = grouped.get(2)[1];
            return new HandValue(3, tb);
        }
        if (grouped.get(0)[0] == 2 && grouped.get(1)[0] == 2) {
            tb[0] = grouped.get(0)[1];
            tb[1] = grouped.get(1)[1];
            tb[2] = grouped.get(2)[1];
            return new HandValue(2, tb);
        }
        if (grouped.get(0)[0] == 2) {
            tb[0] = grouped.get(0)[1];
            tb[1] = grouped.get(1)[1];
            tb[2] = grouped.get(2)[1];
            tb[3] = grouped.get(3)[1];
            return new HandValue(1, tb);
        }

        for (int i = 0; i < 5; i++) tb[i] = values.get(i);
        return new HandValue(0, tb);
    }

    static int compareHands(HandValue a, HandValue b) {
        if (a.rank != b.rank) return a.rank > b.rank ? 1 : -1;
        for (int i = 0; i < 5; i++) {
            if (a.tiebreak[i] != b.tiebreak[i]) return a.tiebreak[i] > b.tiebreak[i] ? 1 : -1;
        }
        return 0;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder out = new StringBuilder();
        String line;

        while ((line = br.readLine()) != null) {
            if (line.trim().isEmpty()) {
                continue;
            }

            StringTokenizer st = new StringTokenizer(line);
            String[] black = new String[5];
            String[] white = new String[5];

            for (int i = 0; i < 5; i++) black[i] = st.nextToken();
            for (int i = 0; i < 5; i++) white[i] = st.nextToken();

            HandValue hb = evaluateHand(black);
            HandValue hw = evaluateHand(white);

            int cmp = compareHands(hb, hw);
            if (cmp > 0) out.append("Black wins.\n");
            else if (cmp < 0) out.append("White wins.\n");
            else out.append("Tie.\n");
        }

        System.out.print(out);
    }
}
