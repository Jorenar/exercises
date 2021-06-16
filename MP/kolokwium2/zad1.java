// 1162034

class zad1 {

    static double[] U  = { 0.1, 0.2, 0.3, 1.3, 1.4, 1.5 }; // possible values (universe)

    static int binSearch(double arr[], double x) {
        int L = 0;
        int R = arr.length - 1;
        while (L <= R) {
            int m = L + (R - L) / 2;
            if (arr[m] == x) {
                return m;
            }
            if (arr[m] < x) {
                L = m + 1;
            } else {
                R = m - 1;
            }
        }
        return -1;
    }

    static void BucketSort(double[] A) { // "bucket sort", yeah, from the lecture
        int n = A.length;
        int b = U.length; // number of buckets

        int[] count = new int[b]; // initialized to 0 by default

        for (int i = 0; i < n; ++i) {
            int m = binSearch(U, A[i]); // number of bucket `A[i]` belongs to
            count[m]++;
        }

        int k = 0;
        for (int i = b-1; i >= 0; --i) { // change which was needed was reading from `count` from the end, instead of beginning
            for (int j = 1; j <= count[i]; ++j) { // no reason for `if (k == 0) continue ...` as `for` loop already checks that
                A[k] = U[i];
                k++;
            }
        }
    }

    public static void main(String[] args) {
        double[] arr = { 1.5, 0.2, 1.4, 0.2, 0.1, 0.3 };

        BucketSort(arr);

        // Print sorted array
        for (int i = 0; i < arr.length; ++i) {
            System.out.print(arr[i] + " ");
        }
        System.out.println();
    }

}
