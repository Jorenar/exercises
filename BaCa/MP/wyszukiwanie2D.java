// Jakub Lukasiewicz - 3

import java.util.Scanner;

class Source {
    public static Scanner in = new Scanner(System.in);

    static class Pair {
        int i;
        int j;
        Pair(int i_, int j_) { i = i_; j = j_; }
    }

    static Pair RekPier(int[][] arr, int n, int m, int i, int j, int x) {
        if (i < n && j >= 0) {
            if (arr[i][j] == x) {
                if (j > 0 && arr[i][j-1] == x) {
                    return RekPier(arr, n, m, i, j-1, x);
                } else {
                    return new Pair(i, j);
                }
            } else if (arr[i][j] > x) {
                return RekPier(arr, n, m, i, j-1, x);
            } else {
                return RekPier(arr, n, m, i+1, j, x);
            }
        } else {
            return new Pair(-1, -1);
        }
    }

    static Pair RekOst(int[][] arr, int n, int m, int i, int j, int x) {
        if (i >= 0 && j < m) {
            if (arr[i][j] == x) {
                if (j < m-1 && arr[i][j+1] == x) {
                    return RekOst(arr, n, m, i, j+1, x);
                } else {
                    return new Pair(i, j);
                }
            } else if (arr[i][j] < x) {
                return RekOst(arr, n, m, i, j+1, x);
            } else {
                return RekOst(arr, n, m, i-1, j, x);
            }
        } else {
            return new Pair(-1, -1);
        }
    }

    static Pair IterPier(int[][] arr, int n, int m, int x) {
        int i = 0;
        int j = m - 1;

        while (i < n && j >= 0) {
            if (arr[i][j] == x) {
                if (j > 0 && arr[i][j-1] == x) {
                    j--;
                } else {
                    return new Pair(i, j);
                }
            } else if (arr[i][j] >= x) {
                j--;
            } else {
                i++;
            }
        }

        return new Pair(-1, -1);
    }

    static Pair IterOst(int[][] arr, int n, int m, int x) {
        int i = n - 1;
        int j = 0;

        while (i >= 0 && j < m) {
            if (arr[i][j] == x) {
                if (j < m-1 && arr[i][j+1] == x) {
                    j++;
                } else {
                    return new Pair(i, j);
                }
            } else if (arr[i][j] < x) {
                j++;
            } else {
                i--;
            }
        }

        return new Pair(-1, -1);
    }

    static void printResults(String alg, int x, Pair result) {
        System.out.print(alg + ": ");
        if (result.i != -1 && result.j != -1) {
            System.out.println(x + " w (" + result.i + "," + result.j + ")");
        } else {
            System.out.println("nie ma " + x);
        }
    }

    public static void main(String[] args) {
        int Z = in.nextInt();
        for (int z = 0; z < Z; ++z) {
            int n = in.nextInt();
            int m = in.nextInt();
            int[][] arr = new int[n][m];
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    arr[i][j] = in.nextInt();
                }
            }
            int x = in.nextInt();

            printResults("RekPier",  x, RekPier(arr, n, m, 0, m-1, x));
            printResults("RekOst",   x, RekOst(arr, n, m, n-1, 0, x));
            printResults("IterPier", x, IterPier(arr, n, m, x));
            printResults("IterOst",  x, IterOst(arr, n, m, x));
            System.out.println("---");
        }
    }
}

// Complexity: O(n+m)

/* Tests:
 *  4
 *  3 4
 *  10 10 10 10
 *  10 20 20 30
 *  20 20 20 40
 *  20
 *  3 4
 *  10 10 10 10
 *  10 20 20 30
 *  20 20 20 40
 *  50
 *  3 3
 *  10 10 10
 *  10 20 20
 *  20 20 20
 *  10
 *  5 4
 *  10 20 30 40
 *  15 25 35 45
 *  27 29 37 48
 *  28 29 39 50
 *  33 34 40 51
 *  40
 */

// vim: fen fdl=1
