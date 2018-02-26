import java.util.Scanner;

public class Gauss extends MiniJava {
    private static int lines;

    public static int[] readMatrix() {
        int[] inputValue = new int[lines * (lines + 1)];
        for (int row = 0; row < lines; row++) {
            for (int column = 0; column < lines + 1; column++) {
                inputValue[row * (lines + 1) + column] = read("Enter a number that locate at " + (row + 1) + " row and " + (column + 1) + " column."); // Здесь считывание, замени на считывание в MiniJava
            }
        }
        return inputValue;
    }

    public static int get(int[] matrix, int row, int column) {
        return matrix[row * (lines + 1) + column];
    }

    public static void set(int[] matrix, int row, int column, int value) {
        matrix[row * (lines + 1) + column] = value;
    }

    public static void printMatrix(int[] matrix) {
        for (int row = 0; row < lines; row++) {
            for (int column = 0; column < lines + 1; column++) {
                if (column < lines)
                    write(get(matrix, row, column) + " ");
                else
                    write(get(matrix, row, column) + "\n");
            }
        }
    }

    public static void multLine(int[] matrix, int line, int factor) {
        for (int column = 0; column < lines + 1; column++) {
            set(matrix, line, column, get(matrix, line, column) * factor);
        }
    }

    public static void multAddLine(int[] matrix, int line, int otherLine, int factor) {
        for (int column = 0; column < lines + 1; column++) {
            set(matrix, line, column, get(matrix, line, column) + get(matrix, otherLine, column) * factor);
        }
    }

    public static void swap(int[] matrix, int lineA, int lineB) {
        for (int column = 0; column < lines + 1; column++) {
            int tmp = get(matrix, lineA, column);
            set(matrix, lineA, column, get(matrix, lineB, column));
            set(matrix, lineB, column, tmp);
        }
    }

    public static void searchSwap(int[] matrix, int fromLine) {
        int toSwap = -1;
        for (int row = lines - 1; row >= fromLine; row--) {
            if (get(matrix, row, fromLine) != 0) {
                toSwap = row;
            }
        }
        swap(matrix, fromLine, toSwap);
    }

    public static int kgv(int a, int b) {
        int mul = a * b;
        // Найдем наибольший общий делитель
        while (b != 0) {
            a = a % b;
            int tmp = a;
            a = b;
            b = tmp;
        }
        // Наибольший общий делитель в a
        return mul / a;
    }

    public static int[] rowEchelonToResult(int[] matrix) {
        int[] answer = new int[lines];
        for (int row = lines - 1; row >= 0; row--) {
            int currentSum = get(matrix, row, lines);
            for (int column = lines - 1; column > row; column--)
                currentSum = currentSum - answer[column] * get(matrix, row, column);
            answer[row] = currentSum / get(matrix, row, row);
        }
        return answer;
    }

    public static int[] solveSystem(int[] matrix) {
        for (int row = 0; row < lines; row++) {
            searchSwap(matrix, row);
            for (int otherRow = row; otherRow < lines; otherRow++)
                if (get(matrix, otherRow, row) < 0)
                    multLine(matrix, otherRow, -1);
            for (int otherRow = row + 1; otherRow < lines; otherRow++) {
                if (get(matrix, otherRow, row) != 0) {
                    int KGV = kgv(get(matrix, row, row), get(matrix, otherRow, row));
                    multLine(matrix, otherRow, KGV / get(matrix, otherRow, row));
                    multAddLine(matrix, otherRow, row, -KGV / get(matrix, row, row));
                }
            }
        }
        return rowEchelonToResult(matrix);
    }

    public static void main(String[] args) {
        lines = read("Please enter numbers of equals\n");
        int[] matrix = readMatrix();
        int[] answer = solveSystem(matrix);
        for (int x = 0; x < lines; x++)
            write("x" + (x + 1) + " = " + answer[x]);

    }
}
