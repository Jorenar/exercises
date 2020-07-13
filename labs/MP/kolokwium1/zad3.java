class sort {

    static void swap(int[] arr, int a, int b) {
        int temp = arr[a];
        arr[a] = arr[b];
        arr[b] = temp;
    }

    static boolean le(int a, int b) { // lesser or equal
        if ((a % 3 == 0 && b % 3 == 0) || (a % 3 != 0 && b % 3 != 0)) {
            return a <= b;
        } else if (a % 3 == 0) {
            return false;
        } else {
            return true;
        }
    }

    static void insertionSort(int[] arr, int I, int n) {
        for (int i = I + 1; i < n; ++i) {
            int x = arr[i];
            int j = i - 1;

            while (j >= I && le(arr[j], x)) {
                arr[j + 1] = arr[j];
                --j;
            }
            arr[j + 1] = x;
        }
    }

    static int partition(int[] arr, int L, int R) {
        int pivot = arr[L];
        int i = R;

        for (int j = R; j >= L + 1; --j) {
            if (le(arr[j], pivot)) {
                swap(arr, i, j);
                --i;
            }
        }

        swap(arr, i, L);

        return i;
    }

    static void quickSort(int[] arr, int L, int R) {
        if (L < R) {
            int q = partition(arr, L, R);

            if (q-L > 20) {
                quickSort(arr, L, q);
            } else {
                insertionSort(arr, L, q+1);
            }

            if (R - q - 1 > 20) {
                quickSort(arr, q + 1, R);
            } else {
                insertionSort(arr, q+1, R+1);
            }
        }
    }

    static void sort(int[] arr, int n) {
        if (n < 20) {
            insertionSort(arr, 0, n);
        } else {
            quickSort(arr, 0, n-1);
        }
    }

    static void printArray(int[] arr, int n) {
        for (int i = 0; i < n; ++i) {
            System.out.print(arr[i] + " ");
        }
        System.out.println();
    }

    public static void main(String[] args) {
        int[] arr = { 1, 7, 2, 9, 10, 6, 3 };
        int n = arr.length;
        sort(arr, n);
        printArray(arr, n);
    }

}

// vim: fen fdl=1
