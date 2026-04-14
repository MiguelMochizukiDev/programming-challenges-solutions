/*
 * pc110204
 * uva843
 */

package chapters.pc02.pc0204.java;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.StringTokenizer;

public class PC0204 {

    static List<String>[] dictByLen;
    static HashSet<String> failedStates;

    static String patternOf(String word) {
        int[] first = new int[26];
        Arrays.fill(first, -1);
        int nextId = 0;
        StringBuilder sb = new StringBuilder();

        for (int i = 0; i < word.length(); i++) {
            int idx = word.charAt(i) - 'a';
            if (first[idx] == -1) {
                first[idx] = nextId++;
            }
            sb.append((char) ('a' + first[idx]));
        }

        return sb.toString();
    }

    static boolean fits(String enc, String plain, int[] toPlain, int[] toEnc) {
        for (int i = 0; i < enc.length(); i++) {
            int e = enc.charAt(i) - 'a';
            int p = plain.charAt(i) - 'a';
            if ((toPlain[e] != -1 && toPlain[e] != p) || (toEnc[p] != -1 && toEnc[p] != e)) {
                return false;
            }
        }
        return true;
    }

    static String stateKey(int idx, int[] toPlain, int[] toEnc) {
        StringBuilder sb = new StringBuilder();
        sb.append(idx).append('|');
        for (int v : toPlain) {
            int x = v + 1;
            sb.append((char) ('0' + (x / 10))).append((char) ('0' + (x % 10)));
        }
        sb.append('|');
        for (int v : toEnc) {
            int x = v + 1;
            sb.append((char) ('0' + (x / 10))).append((char) ('0' + (x % 10)));
        }
        return sb.toString();
    }

    static boolean solveTopDown(
        List<String> words,
        List<String> patterns,
        int[] order,
        int idx,
        int[] toPlain,
        int[] toEnc
    ) {
        if (idx == order.length) {
            return true;
        }

        String key = stateKey(idx, toPlain, toEnc);
        if (failedStates.contains(key)) {
            return false;
        }

        int widx = order[idx];
        String encWord = words.get(widx);
        String encPattern = patterns.get(widx);

        for (String cand : dictByLen[encWord.length()]) {
            if (!patternOf(cand).equals(encPattern)) {
                continue;
            }
            if (!fits(encWord, cand, toPlain, toEnc)) {
                continue;
            }

            int[] changedPlain = new int[26];
            int[] changedEnc = new int[26];
            int cp = 0;
            int ce = 0;

            for (int i = 0; i < encWord.length(); i++) {
                int e = encWord.charAt(i) - 'a';
                int p = cand.charAt(i) - 'a';
                if (toPlain[e] == -1) {
                    toPlain[e] = p;
                    changedPlain[cp++] = e;
                }
                if (toEnc[p] == -1) {
                    toEnc[p] = e;
                    changedEnc[ce++] = p;
                }
            }

            if (solveTopDown(words, patterns, order, idx + 1, toPlain, toEnc)) {
                return true;
            }

            for (int i = 0; i < cp; i++) {
                toPlain[changedPlain[i]] = -1;
            }
            for (int i = 0; i < ce; i++) {
                toEnc[changedEnc[i]] = -1;
            }
        }

        failedStates.add(key);
        return false;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        String first = br.readLine();
        if (first == null || first.trim().isEmpty()) {
            return;
        }

        int n = Integer.parseInt(first.trim());
        dictByLen = new ArrayList[17];
        for (int i = 0; i < 17; i++) {
            dictByLen[i] = new ArrayList<>();
        }

        for (int i = 0; i < n; i++) {
            String w = br.readLine();
            dictByLen[w.length()].add(w);
        }

        StringBuilder out = new StringBuilder();
        String line;

        while ((line = br.readLine()) != null) {
            StringTokenizer st = new StringTokenizer(line);
            List<String> words = new ArrayList<>();
            List<String> patterns = new ArrayList<>();

            while (st.hasMoreTokens()) {
                String w = st.nextToken();
                words.add(w);
                patterns.add(patternOf(w));
            }

            int[] order = new int[words.size()];
            for (int i = 0; i < order.length; i++) {
                order[i] = i;
            }
            for (int i = 0; i < order.length; i++) {
                for (int j = i + 1; j < order.length; j++) {
                    int ci = dictByLen[words.get(order[i]).length()].size();
                    int cj = dictByLen[words.get(order[j]).length()].size();
                    if (cj < ci) {
                        int t = order[i];
                        order[i] = order[j];
                        order[j] = t;
                    }
                }
            }

            int[] toPlain = new int[26];
            int[] toEnc = new int[26];
            Arrays.fill(toPlain, -1);
            Arrays.fill(toEnc, -1);

            failedStates = new HashSet<>();
            boolean ok = solveTopDown(words, patterns, order, 0, toPlain, toEnc);

            StringBuilder decoded = new StringBuilder();
            for (int i = 0; i < line.length(); i++) {
                char ch = line.charAt(i);
                if (ch == ' ') {
                    decoded.append(' ');
                } else if (ok) {
                    int m = toPlain[ch - 'a'];
                    decoded.append(m == -1 ? '*' : (char) ('a' + m));
                } else {
                    decoded.append('*');
                }
            }

            out.append(decoded).append('\n');
        }

        System.out.print(out);
    }
}
