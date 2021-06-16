// This parody of a language is completely unsuited for anything.
// The readings of time will be different depending which version is run first.
// Even though it's THE SAME CODE! I've commented out the differences between Left and Median!
// Therefore I had to rewrite it in C to make some real measurement.

public class quicksort {
    static void swap(int[] arr, int a, int b) {
        int temp = arr[a];
        arr[a] = arr[b];
        arr[b] = temp;
    }

    public static interface Partition {
        public int execute(int[] arr, int L, int R);
    }

    public static class Median implements Partition {
        public int execute(int[] arr, int L, int R) {

            //int m = (L + R)/2;

            //if (arr[m] > arr[L]) {
            //    swap(arr, L, m);
            //}

            //if (arr[L] > arr[R]) {
            //    swap(arr, L, R);
            //}

            //if (arr[m] > arr[R]) {
            //    swap(arr, m, R);
            //}

            int pivot = arr[L];
            int i = R;

            for (int j = R; j >= L + 1; --j) {
                if (arr[j] >= pivot) {
                    swap(arr, i, j);
                    --i;
                }
            }

            swap(arr, i, L);

            return i;
        }
    }

    public static class Left implements Partition {
        public int execute(int[] arr, int L, int R) {
            int pivot = arr[L];
            int i = R;

            for (int j = R; j >= L + 1; --j) {
                if (arr[j] >= pivot) {
                    swap(arr, i, j);
                    --i;
                }
            }

            swap(arr, i, L);

            return i;
        }
    }

    public static void printArray(int[] arr, int n) {
        for (int i = 0; i < n; ++i) {
            System.out.print(arr[i] + " ");
        }
        System.out.println();
    }

    public static void quickSort(int[] arr, int L, int R, Partition partition) {
        if (L < R) {
            int q = partition.execute(arr, L, R);
            quickSort(arr, L, q, partition);
            quickSort(arr, q + 1, R, partition);
        }
    }

    public static void main(String[] args) {
        int n = 100000;
        int[] array = new int[n];
        for (int i = 0; i < n; ++i) {
            array[i] = (int)(Math.random() * 1000 + 1);
        }
        int[] arr;

        long start;
        long finish;

        // Uncommenting this part makes Median faster!!
        //  arr = array.clone();
        //  quickSort(arr, 0, n-1, new Median());

        arr = array.clone();
        quickSort(arr, 0, n-1, new Left());
        arr = array.clone();
        quickSort(arr, 0, n-1, new Median());

        arr = array.clone();
        start = System.nanoTime();
        quickSort(arr, 0, n-1, new Left());
        finish = System.nanoTime();
        System.out.println("Left:   " + (finish - start));
        //printArray(arr, n);

        arr = array.clone();
        start = System.nanoTime();
        quickSort(arr, 0, n-1, new Median());
        finish = System.nanoTime();
        System.out.println("Median: " + (finish - start));
        //printArray(arr, n);
    }
}

// vim: fen fdl=1
