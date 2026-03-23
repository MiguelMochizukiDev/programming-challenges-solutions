/*
 * pc110102
 * uva10189
 */

package chapters.pc01.pc0102.java;

import java.util.Scanner;

public class PC0102 {

    private static final int[][] DIRECTIONS = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1}, {0, 1},
        {1, -1}, {1, 0}, {1, 1}
    };

    public static int countAdjacentMines(char[][] board, int numRows, int numCols, int row, int col) {
        int count = 0;

        for (int i = 0; i < DIRECTIONS.length; i++) {
            int newRow = row + DIRECTIONS[i][0];
            int newCol = col + DIRECTIONS[i][1];

            if (newRow >= 0 && newRow < numRows &&
                newCol >= 0 && newCol < numCols &&
                board[newRow][newCol] == '*') {
                count++;
            }
        }

        return count;
    }

    public static void printMinesweeperBoard(char[][] board, int numRows, int numCols) {
        for (int row = 0; row < numRows; row++) {
            for (int col = 0; col < numCols; col++) {
                if (board[row][col] == '*') {
                    System.out.print('*');
                } else {
                    System.out.print(countAdjacentMines(board, numRows, numCols, row, col));
                }
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int fieldNumber = 1;

        while (sc.hasNextInt()) {
            int numRows = sc.nextInt();
            int numCols = sc.nextInt();

            if (numRows == 0 && numCols == 0) {
                break;
            }

            char[][] board = new char[numRows][numCols];
            for (int i = 0; i < numRows; i++) {
                String line = sc.next();
                board[i] = line.toCharArray();
            }

            if (fieldNumber > 1) {
                System.out.println();
            }

            System.out.println("Field #" + fieldNumber + ":");
            printMinesweeperBoard(board, numRows, numCols);

            fieldNumber++;
        }

        sc.close();
    }
}