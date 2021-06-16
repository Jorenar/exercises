class util {

    public static int[] randomArray(int N, int M) {
        int[] arr = new int[N];
        for (int i = 0; i < N; ++i) {
            arr[i] = (int)(Math.random() * M);
        }
        return arr;
    }

    public static int max(int[] arr, int N) {
        int m = 0;
        for (int i = 0; i < N; ++i) {
            if (arr[i] > m) {
                m = arr[i];
            }
        }
        return m;
    }

    public static void printArray(int[] arr, int N) {
        System.out.print(arr[0]);
        for (int i = 1; i < N; ++i) {
            System.out.print(", " + arr[i]);
        }
        System.out.println();
    }

}
