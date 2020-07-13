class interpolacyjne {

    public static int search(int[] arr, int n, int x) {
        int p = 0;
        int k = n - 1;
        while (p <= k) {
            int m = p + (x - arr[p])*(k - p) / (arr[k] - arr[p]);
            if (arr[m] < x) {
                p = m + 1;
            } else if (arr[m] > x) {
                k = m - 1;
            } else {
                while (arr[m] == x) m++;
                return m;
            }
        }
        return R;
    }

    public static void main (String[] args) {
        int[] a = { 1, 1, 1, 2, 3, 5, 6, 8, 10, 11, 11, 11 };
        System.out.println(search(a, a.length, 1));
        System.out.println(search(a, a.length, 11));
    }
}
