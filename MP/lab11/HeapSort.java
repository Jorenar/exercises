// Only one change was needed to version from lecture: instead max-heap to use min-heap

class HeapSort {

    public static void printArray(int[] a) {
        for (int i = 0; i < a.length; ++i) {
            System.out.print(a[i] + " ");
        }
        System.out.println();
    }

    private static void swap(int[] arr, int a, int b) {
        int temp = arr[a];
        arr[a] = arr[b];
        arr[b] = temp;
    }

    private static void downheap(int[] arr, int k, int n) {
        int temp = arr[k];
        while (k < n/2) {
            int j = 2 * k + 1;
            if (j < n-1 && arr[j] > arr[j+1]) {
                ++j;
            }
            if (temp <= arr[j]) { // CHANGE
                break;
            }
            arr[k] = arr[j];
            k = j;
        }
        arr[k] = temp;
    }

    public static void sort(int[] arr) {
        int n = arr.length;
        for (int i = (n-1)/2; i >= 0; --i) {
            downheap(arr, i, n);
        }
        while (n > 0) {
            --n;
            swap(arr, 0, n);
            downheap(arr, 0, n);
        }
    }

    public static void main(String[] args) {
        int N = 20;
        int M = 100;
        int[] arr = new int[N];
        for (int i = 0; i < N; ++i) {
            arr[i] = (int)(Math.random() * 60);
        }

        System.out.print("Before: ");
        printArray(arr);

        sort(arr);

        System.out.print("After:  ");
        printArray(arr);
    }

}

// vim: fen fdl=1
