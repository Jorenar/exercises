class CountSort {

    public static int[] sort(int[] arr, int N, int M) {
        int[] count = new int[M+1]; // guaranteed to be initialized to 0 by language specification (§4.12.5)
        int[] out   = new int[N];

        for (int i = 0; i < N; ++i) {
            ++count[arr[i]];
        }

        for (int i = 1; i <= M; ++i) {
            count[i] += count[i-1];
        }

        for (int i = N-1; i >= 0; --i) {
            --count[arr[i]];
            out[count[arr[i]]] = arr[i];
        }

        return out;
    }

    public static void main(String args[]) {
        int N = 40;   // amount of elements

        int[] a = util.randomArray(N, 1000);
        util.printArray(a, N);

        int[] b = sort(a, N, util.max(a, N));
        System.out.println();
        util.printArray(b, N);
    }

}

/* Example outputs:
 *
 *   10, 14, 375, 527, 140, 706, 431, 566, 768, 350, 274, 401, 644, 2, 801, 831, 390, 889, 4, 233, 529, 623, 931, 183, 555, 620, 682, 265, 148, 592, 944, 579, 296, 29, 58, 99, 707, 919, 684, 287
 *   2, 4, 10, 14, 29, 58, 99, 140, 148, 183, 233, 265, 274, 287, 296, 350, 375, 390, 401, 431, 527, 529, 555, 566, 579, 592, 620, 623, 644, 682, 684, 706, 707, 768, 801, 831, 889, 919, 931, 944
 *
 *   139, 550, 986, 471, 693, 581, 198, 337, 287, 831, 279, 140, 729, 270, 177, 89, 650, 308, 787, 309, 566, 319, 192, 484, 869, 677, 908, 423, 743, 946, 139, 613, 858, 882, 796, 293, 511, 1, 962, 522
 *   1, 89, 139, 139, 140, 177, 192, 198, 270, 279, 287, 293, 308, 309, 319, 337, 423, 471, 484, 511, 522, 550, 566, 581, 613, 650, 677, 693, 729, 743, 787, 796, 831, 858, 869, 882, 908, 946, 962, 986
 *
 */

// vim: fen fdl=1
