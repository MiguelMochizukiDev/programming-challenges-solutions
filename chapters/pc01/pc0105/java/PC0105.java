/*
 * pc110105
 * uva10267
 */

package chapters.pc01.pc0105.java;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayDeque;
import java.util.StringTokenizer;

public class PC0105 {

    public static void clearImage(char[][] image, int rows, int cols) {
        for (int y = 0; y < rows; y++) {
            for (int x = 0; x < cols; x++) {
                image[y][x] = 'O';
            }
        }
    }

    public static void floodFill(char[][] image, int rows, int cols, int startX, int startY, char color) {
        char original = image[startY][startX];
        if (original == color) {
            return;
        }

        ArrayDeque<int[]> queue = new ArrayDeque<>();
        queue.add(new int[]{startX, startY});
        image[startY][startX] = color;

        while (!queue.isEmpty()) {
            int[] current = queue.poll();
            int x = current[0];
            int y = current[1];

            if (x > 0 && image[y][x - 1] == original) {
                image[y][x - 1] = color;
                queue.add(new int[]{x - 1, y});
            }
            if (x + 1 < cols && image[y][x + 1] == original) {
                image[y][x + 1] = color;
                queue.add(new int[]{x + 1, y});
            }
            if (y > 0 && image[y - 1][x] == original) {
                image[y - 1][x] = color;
                queue.add(new int[]{x, y - 1});
            }
            if (y + 1 < rows && image[y + 1][x] == original) {
                image[y + 1][x] = color;
                queue.add(new int[]{x, y + 1});
            }
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder out = new StringBuilder();

        char[][] image = new char[250][250];
        int rows = 0;
        int cols = 0;

        String line;
        while ((line = br.readLine()) != null) {
            if (line.isEmpty()) {
                continue;
            }

            char cmd = line.charAt(0);
            if (cmd == 'X') {
                break;
            }

            StringTokenizer st = new StringTokenizer(line);
            char command = st.nextToken().charAt(0);

            if (command == 'I') {
                cols = Integer.parseInt(st.nextToken());
                rows = Integer.parseInt(st.nextToken());
                clearImage(image, rows, cols);
            } else if (command == 'C') {
                if (rows > 0 && cols > 0) {
                    clearImage(image, rows, cols);
                }
            } else if (command == 'L') {
                int x = Integer.parseInt(st.nextToken());
                int y = Integer.parseInt(st.nextToken());
                char color = st.nextToken().charAt(0);
                image[y - 1][x - 1] = color;
            } else if (command == 'V') {
                int x = Integer.parseInt(st.nextToken());
                int y1 = Integer.parseInt(st.nextToken());
                int y2 = Integer.parseInt(st.nextToken());
                char color = st.nextToken().charAt(0);

                int from = Math.min(y1, y2);
                int to = Math.max(y1, y2);
                for (int y = from; y <= to; y++) {
                    image[y - 1][x - 1] = color;
                }
            } else if (command == 'H') {
                int x1 = Integer.parseInt(st.nextToken());
                int x2 = Integer.parseInt(st.nextToken());
                int y = Integer.parseInt(st.nextToken());
                char color = st.nextToken().charAt(0);

                int from = Math.min(x1, x2);
                int to = Math.max(x1, x2);
                for (int x = from; x <= to; x++) {
                    image[y - 1][x - 1] = color;
                }
            } else if (command == 'K') {
                int x1 = Integer.parseInt(st.nextToken());
                int y1 = Integer.parseInt(st.nextToken());
                int x2 = Integer.parseInt(st.nextToken());
                int y2 = Integer.parseInt(st.nextToken());
                char color = st.nextToken().charAt(0);

                int fromX = Math.min(x1, x2);
                int toX = Math.max(x1, x2);
                int fromY = Math.min(y1, y2);
                int toY = Math.max(y1, y2);

                for (int y = fromY; y <= toY; y++) {
                    for (int x = fromX; x <= toX; x++) {
                        image[y - 1][x - 1] = color;
                    }
                }
            } else if (command == 'F') {
                int x = Integer.parseInt(st.nextToken());
                int y = Integer.parseInt(st.nextToken());
                char color = st.nextToken().charAt(0);
                floodFill(image, rows, cols, x - 1, y - 1, color);
            } else if (command == 'S') {
                String name = st.nextToken();
                out.append(name).append('\n');
                for (int y = 0; y < rows; y++) {
                    for (int x = 0; x < cols; x++) {
                        out.append(image[y][x]);
                    }
                    out.append('\n');
                }
            }
        }

        System.out.print(out);
    }
}
