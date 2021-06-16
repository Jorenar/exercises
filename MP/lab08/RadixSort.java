class RadixSort {

    static boolean showIntermediate = true;

    public static int[] countSort(int[] arr, int N, int X) { // modified to work with RadixSort
        int[] count = new int[10]; // guaranteed to be initialized to 0 by language specification (§4.12.5)
        int[] out   = new int[N];

        for (int i = 0; i < N; ++i) {
            ++count[(arr[i]/X)%10];
        }

        for (int i = 1; i < 10; ++i) {
            count[i] += count[i-1];
        }

        for (int i = N-1; i >= 0; --i) {
            --count[(arr[i]/X)%10];
            out[count[(arr[i]/X)%10]] = arr[i];
        }

        return out;
    }

    static int[] sort(int[] arr, int N) {
        int m = util.max(arr, N);
        int[] out = new int[N];

        if (showIntermediate) {
            System.out.println("Intermediate:");
        }

        for (int X = 1; m/X > 0; X *= 10) {
            out = countSort(arr, N, X);
            if (showIntermediate) {
                System.out.print("  ");
                util.printArray(out, N);
            }
        }
        return out;
    }

    public static void main(String[] args) {
        int N = 10; // amount of elements

        int[] a = util.randomArray(N, 1000);
        util.printArray(a, N);

        int[] b = sort(a, N);
        System.out.println();
        util.printArray(b, N);
    }

}

/* Example output:
 *
 *  768, 763, 865, 53, 533, 221, 560, 752, 711, 2
 *  Intermediate:
 *    560, 221, 711, 752, 2, 763, 53, 533, 865, 768
 *    2, 711, 221, 533, 53, 752, 768, 763, 865, 560
 *    53, 2, 221, 533, 560, 768, 763, 752, 711, 865
 *
 *  53, 2, 221, 533, 560, 768, 763, 752, 711, 865
 *
 */

// vim: fen fdl=1
