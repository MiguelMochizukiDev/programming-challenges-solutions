/*
 * pc110107
 * uva10196
 */

package chapters.pc01.pc0107.java;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class PC0107 {

    public static boolean inBounds(int r, int c) {
        return r >= 0 && r < 8 && c >= 0 && c < 8;
    }

    public static boolean attackedByBlack(char[][] board, int kr, int kc) {
        int[] knightDr = {-2, -2, -1, -1, 1, 1, 2, 2};
        int[] knightDc = {-1, 1, -2, 2, -2, 2, -1, 1};
        int[] kingDr = {-1, -1, -1, 0, 0, 1, 1, 1};
        int[] kingDc = {-1, 0, 1, -1, 1, -1, 0, 1};
        int[] rookDr = {-1, 1, 0, 0};
        int[] rookDc = {0, 0, -1, 1};
        int[] bishopDr = {-1, -1, 1, 1};
        int[] bishopDc = {-1, 1, -1, 1};

        if (inBounds(kr - 1, kc - 1) && board[kr - 1][kc - 1] == 'p') {
            return true;
        }
        if (inBounds(kr - 1, kc + 1) && board[kr - 1][kc + 1] == 'p') {
            return true;
        }

        for (int i = 0; i < 8; i++) {
            int nr = kr + knightDr[i];
            int nc = kc + knightDc[i];
            if (inBounds(nr, nc) && board[nr][nc] == 'n') {
                return true;
            }
        }

        for (int i = 0; i < 8; i++) {
            int nr = kr + kingDr[i];
            int nc = kc + kingDc[i];
            if (inBounds(nr, nc) && board[nr][nc] == 'k') {
                return true;
            }
        }

        for (int d = 0; d < 4; d++) {
            int nr = kr + rookDr[d];
            int nc = kc + rookDc[d];
            while (inBounds(nr, nc)) {
                char piece = board[nr][nc];
                if (piece != '.') {
                    if (piece == 'r' || piece == 'q') {
                        return true;
                    }
                    break;
                }
                nr += rookDr[d];
                nc += rookDc[d];
            }
        }

        for (int d = 0; d < 4; d++) {
            int nr = kr + bishopDr[d];
            int nc = kc + bishopDc[d];
            while (inBounds(nr, nc)) {
                char piece = board[nr][nc];
                if (piece != '.') {
                    if (piece == 'b' || piece == 'q') {
                        return true;
                    }
                    break;
                }
                nr += bishopDr[d];
                nc += bishopDc[d];
            }
        }

        return false;
    }

    public static boolean attackedByWhite(char[][] board, int kr, int kc) {
        int[] knightDr = {-2, -2, -1, -1, 1, 1, 2, 2};
        int[] knightDc = {-1, 1, -2, 2, -2, 2, -1, 1};
        int[] kingDr = {-1, -1, -1, 0, 0, 1, 1, 1};
        int[] kingDc = {-1, 0, 1, -1, 1, -1, 0, 1};
        int[] rookDr = {-1, 1, 0, 0};
        int[] rookDc = {0, 0, -1, 1};
        int[] bishopDr = {-1, -1, 1, 1};
        int[] bishopDc = {-1, 1, -1, 1};

        if (inBounds(kr + 1, kc - 1) && board[kr + 1][kc - 1] == 'P') {
            return true;
        }
        if (inBounds(kr + 1, kc + 1) && board[kr + 1][kc + 1] == 'P') {
            return true;
        }

        for (int i = 0; i < 8; i++) {
            int nr = kr + knightDr[i];
            int nc = kc + knightDc[i];
            if (inBounds(nr, nc) && board[nr][nc] == 'N') {
                return true;
            }
        }

        for (int i = 0; i < 8; i++) {
            int nr = kr + kingDr[i];
            int nc = kc + kingDc[i];
            if (inBounds(nr, nc) && board[nr][nc] == 'K') {
                return true;
            }
        }

        for (int d = 0; d < 4; d++) {
            int nr = kr + rookDr[d];
            int nc = kc + rookDc[d];
            while (inBounds(nr, nc)) {
                char piece = board[nr][nc];
                if (piece != '.') {
                    if (piece == 'R' || piece == 'Q') {
                        return true;
                    }
                    break;
                }
                nr += rookDr[d];
                nc += rookDc[d];
            }
        }

        for (int d = 0; d < 4; d++) {
            int nr = kr + bishopDr[d];
            int nc = kc + bishopDc[d];
            while (inBounds(nr, nc)) {
                char piece = board[nr][nc];
                if (piece != '.') {
                    if (piece == 'B' || piece == 'Q') {
                        return true;
                    }
                    break;
                }
                nr += bishopDr[d];
                nc += bishopDc[d];
            }
        }

        return false;
    }

    public static boolean isEmptyBoard(char[][] board) {
        for (int r = 0; r < 8; r++) {
            for (int c = 0; c < 8; c++) {
                if (board[r][c] != '.') {
                    return false;
                }
            }
        }
        return true;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder out = new StringBuilder();
        int game = 1;

        while (true) {
            char[][] board = new char[8][8];
            for (int r = 0; r < 8; r++) {
                String line = br.readLine();
                if (line == null) {
                    System.out.print(out);
                    return;
                }
                board[r] = line.toCharArray();
            }

            if (isEmptyBoard(board)) {
                break;
            }

            int whiteKr = -1;
            int whiteKc = -1;
            int blackKr = -1;
            int blackKc = -1;

            for (int r = 0; r < 8; r++) {
                for (int c = 0; c < 8; c++) {
                    if (board[r][c] == 'K') {
                        whiteKr = r;
                        whiteKc = c;
                    } else if (board[r][c] == 'k') {
                        blackKr = r;
                        blackKc = c;
                    }
                }
            }

            if (attackedByBlack(board, whiteKr, whiteKc)) {
                out.append("Game #").append(game).append(": white king is in check.\n");
            } else if (attackedByWhite(board, blackKr, blackKc)) {
                out.append("Game #").append(game).append(": black king is in check.\n");
            } else {
                out.append("Game #").append(game).append(": no king is in check.\n");
            }

            game++;
            br.readLine();
        }

        System.out.print(out);
    }
}
