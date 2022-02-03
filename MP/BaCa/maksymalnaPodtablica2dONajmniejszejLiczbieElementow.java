// Lukasiewicz Jakub - 3

import java.util.Scanner;

class Source {
    public static Scanner in = new Scanner(System.in);

    public static void main(String[] args) {
        int E = in.nextInt();
        for (int e = 0; e < E; e++) {
            int n = in.nextInt();
            int m = in.nextInt();
            int[][] tab = new int[n][m];
            int[][] M   = new int[n][m];

            boolean empty = true;

            for (int b = 0; b < n*m; b++) {
                int p = in.nextInt();
                tab[b/m][b%m] = p;
                if (p >= 0) {
                    empty = false;
                }
            }

            if (!empty) {

                int max = 0;
                int X = 0;
                int Y = 0;
                int I = 0;
                int J = 0;
                int D = n*m;

                for (int b = 0; b < n*m; b++) {
                    int x = b/m;
                    int y = b%m;
                    for (int i = x; i < n; i++) {
                        for (int j = y; j < m; j++) {
                            M[i][j] = tab[i][j];
                            if (i > x) {
                                M[i][j] += M[i-1][j];
                            }
                            if (j > y) {
                                M[i][j] += M[i][j-1];
                            }
                            if (i > x && j > y) {
                                M[i][j] -= M[i-1][j-1];
                            }

                            int d = (i-x+1)*(j-y+1);

                            if (M[i][j] > max || (M[i][j] == max && d < D)) {
                                max = M[i][j];
                                X = x;
                                Y = y;
                                I = i;
                                J = j;
                                D = d;
                            }
                        }
                    }
                }
                System.out.printf("max_sum = %d, a[%d..%d][%d..%d]\n", max, X, I, Y, J);

            } else {
                System.out.println("empty");
            }

        }
    }
}
