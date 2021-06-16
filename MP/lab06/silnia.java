class silnia {
    public static int normal(int n) {
        if (n == 0) {
            return 1;
        }
        return n * normal(n - 1);
    }

    public static int tail(int n, int ac) {
        if (n == 0) {
            return ac;
        }
        return tail(n - 1, ac * n);
    }

    public static void main(String[] args) {
        int x = Integer.parseInt(args[0]);
        System.out.println("Zwykla:  " + normal(x));
        System.out.println("Ogonowa: " + tail(x, 1));
    }
}
