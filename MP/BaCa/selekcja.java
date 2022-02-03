// Jakub Lukasiewicz - 3

import java.util.Scanner;

class Source {
    public static Scanner in = new Scanner(System.in);

    static void swap(int[] arr, int a, int b) {
        int temp = arr[a];
        arr[a] = arr[b];
        arr[b] = temp;
    }

    // Worst time of insertion sort is O(n^2),
    // but thanks to magic fives of Median of medians it becomes irrelevant
    // and for, let's say n = 1000, it will do 5000 steps instead of million
    // (in worst case, in best it has linear complexity)
    static void sort(int[] arr, int I, int n) {
        for (int i = I + 1; i < n; ++i) {
            int x = arr[i];
            int j = i - 1;

            while (j >= I && arr[j] > x) {
                arr[j + 1] = arr[j];
                --j;
            }
            arr[j + 1] = x;
        }
    }

    // one loop, complexity O(n)
    static void partition(int[] arr, int M, int L, int R) {
        int l = L;
        int r = R-1;

        int i = L;
        while (i <= r) {
            if (arr[i] < M) {
                swap(arr, l, i);
                l++;
                i++;
            } else if (arr[i] > M) {
                swap(arr, i, r);
                r--;
            } else {
                i++;
            }
        }
    }

    // Median of medians; complexity O(n)
    static int select(int[] arr, int k, int L, int R) {

        if (R - L <= 1) {
            return arr[L];
        }

        int m = 0; // count of medians
        for (int i = L; i < R; i += 5) {
            int n = i + 5 < R ? i + 5 : R;
            sort(arr, i, n);
            swap(arr, L+m, (i+n)/2); // medians are moved at the beginning of array
            ++m;
        }

        int M = select(arr, (m+1)/2, L, L + m); // pivot = median of medians

        partition(arr, M, L, R);

        int i = L;

        while (arr[i] < M) {
            ++i;
        }
        int s1 = i - 1; // index of last element smaller than M

        while (i < R && arr[i] == M) {
            ++i;
        }
        int s2 = i - 1; // index of last M

        if (k <= s1 - L) {
            return select(arr, k, L, s1+1);
        } else if (k <= s2 - L) {
            return M;
        } else {
            return select(arr, k - (s2 - L + 1), s2 + 1, R);
        }
    }

    public static void main(String[] args) {

        int Z = in.nextInt();
        for (int z = 0; z < Z; ++z) {

            int n = in.nextInt();
            int[] arr = new int[n];
            for (int i = 0; i < n; ++i) {
                arr[i] = in.nextInt();
            }

            int M = in.nextInt();
            for (int m = 0; m < M; ++m) {
                int k = in.nextInt();
                System.out.print(k + " ");
                if (k > 0 && k <= n) {
                    System.out.println(select(arr, k-1, 0, n));
                } else {
                    System.out.println("brak");
                }
            }
        }

    }

}

// vim: fan fdl=1

/* Tests:
 *    8
 *
 *    5
 *    1 2 3 4 5
 *    1
 *    5
 *
 *    100
 *    100 99 98 97 96 95 94 93 92 91 90 89 88 87 86 85 84 83 82 81 80 79 78 77 76 75 74 73 72 71 70 69 68 67 66 65 64 63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34 33 32 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
 *    5
 *    1 10 100 5 50
 *
 *    1
 *    9990
 *    5
 *    1 2 3 4 5
 *    52
 *    54 34 8 30 80 37 7 71
 *    14 94 12 81 25 43 98 50
 *    92 82 91 74 18 43 6 20 98
 *    63 24 6 34 76 44 3 49 70
 *    18 55 31 54 32 64 27 61
 *    79 8 43 22 52 25 80 62
 *    30 16
 *    10
 *    53 1 2 3 4 5 6 7 51 52
 *    5
 *    32132 1 1231 21 1
 *    7
 *    1 2 3 4 5 8 12345
 *
 *    5
 *    1 2 3 4 5
 *    3
 *    1 2 3
 *    5
 *    5 3 4 4 3
 *    5
 *    2 5 1 3 4
 *    10
 *    1 1 1 1 1 1 1 1 1 1
 *    5
 *    1 10 0 -1 11
*/
