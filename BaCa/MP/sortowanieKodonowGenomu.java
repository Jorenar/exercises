// Jakub Lukasiewicz - 3

import java.util.Scanner;

class Sort {

    static void swap(StringBuffer g, int a, int b) {
        if (a > b) {
            int temp = a;
            a = b;
            b = temp;
        }

        if (a != b) {
            a *= 3;
            b *= 3;
            g.replace(0, g.length(),
                    g.substring(0,a) + g.substring(b, b+3) + g.substring(a+3, b) +
                    g.substring(a, a+3) + g.substring(b+3, g.length()));
        }
    }

    static int partition(StringBuffer g, int L, int R, int o) {
        char pivot = g.charAt(3*L+o);
        int i = R;

        for (int j = R; j >= L + 1; --j) {
            if (g.charAt(3*j+o) >= pivot) {
                swap(g, i, j);
                --i;
            }
        }

        swap(g, i, L);

        return i;
    }

    static void quickSort(StringBuffer g, int L, int R, int o) {
        int[] ends = new int[R + 2];

        int i = -1;

        ends[++i] = L;
        ends[++i] = R;

        while (i >= 0) {
            R = ends[i--];
            L = ends[i--];

            int q = partition(g, L, R, o);

            if (q - 1 > L) {
                ends[++i] = L;
                ends[++i] = q - 1;
            }

            if (q + 1 < R) {
                ends[++i] = q + 1;
                ends[++i] = R;
            }
        }
    }

    static void sortLastLetter(StringBuffer g, int i, int n) {
        int j;

        j = i;
        while (i < n && g.charAt(i+1) == 'A') { i += 3; }
        if (i > j && i <= n) { quickSort(g, j/3, i/3 - 1, 2); }

        j = i;
        while (i < n && g.charAt(i+1) == 'C') { i += 3; }
        if (i > j && i <= n) { quickSort(g, j/3, i/3 - 1, 2); }

        j = i;
        while (i < n && g.charAt(i+1) == 'G') { i += 3; }
        if (i > j && i <= n) { quickSort(g, j/3, i/3 - 1, 2); }

        j = i;
        while (i < n && g.charAt(i+1) == 'T') { i += 3; }
        if (i > j && i <= n) { quickSort(g, j/3, i/3 - 1, 2); }
    }

    Sort(StringBuffer g) {
        int n = g.length();
        quickSort(g, 0, n/3 - 1, 0);

        int i = 0;
        int j;

        j = i;
        while (i < n && g.charAt(i) == 'A') { i += 3; }
        if (i > j && i <= n) {
            quickSort(g, j/3, i/3 - 1, 1);
            sortLastLetter(g, j, i);
        }

        j = i;
        while (i < n && g.charAt(i) == 'C') { i += 3; }
        if (i > j && i <= n) {
            quickSort(g, j/3, i/3 - 1, 1);
            sortLastLetter(g, j, i);
        }

        j = i;
        while (i < n && g.charAt(i) == 'G') { i += 3; }
        if (i > j && i <= n) {
            quickSort(g, j/3, i/3 - 1, 1);
            sortLastLetter(g, j, i);
        }

        j = i;
        while (i < n && g.charAt(i) == 'T') { i += 3; }
        if (i > j && i <= n) {
            quickSort(g, j/3, i/3 - 1, 1);
            sortLastLetter(g, j, i);
        }
    }

}

class Source {
    public static Scanner in = new Scanner(System.in);

    static boolean cmpSeq(String data, String seq, int i) {
        return i+3 > data.length() ? false : seq.equals(data.substring(i, i+3));
    }

    static int parse(String data, StringBuffer out) {
        data = data.toUpperCase();
        int i = 0;
        int n = data.length();

        if (n != data.replaceAll("[^ACGT]", "").length()) {
            return 2;
        }

        // find START codon
        while (i < n-2 && !cmpSeq(data, "ATG", i)) {
            ++i;
        }

        if (i == n - 2) {
            return 1;
        } else {
            i += 3;
        }

        // read until STOP codon
        boolean foundSTOP = false;
        boolean repeatedSTART = false;
        while (i < n-2 && !foundSTOP ) {
            if ( cmpSeq(data, "TAA", i) || cmpSeq(data, "TGA", i) || cmpSeq(data, "TAG", i) ) {
                foundSTOP = true;
            } else {
                repeatedSTART = cmpSeq(data, "ATG", i);
                out.append(data.substring(i, i+3));
            }
            i += 3;
        }

        if (!foundSTOP) {
            return 1;
        } else if (repeatedSTART) {
            return 3;
        }

        // check for repeated STOP
        while (i < n) {
            if (cmpSeq(data, "TAA", i) || cmpSeq(data, "TGA", i) || cmpSeq(data, "TAG", i)) {
                return 3;
            }
            i += 3;
        }

        if (out.length() == 0) { // check if there is any valid DNA
            return 1;
        }

        return 0; // no problems

    }

    public static void main(String[] args) {
        int Z = Integer.parseInt(in.nextLine());
        for (int z = 0; z < Z; ++z) {
            String data = in.nextLine();
            StringBuffer genome = new StringBuffer();
            switch (parse(data, genome)) {
                case 1:
                    System.out.println("Wrong DNA sequence.");
                    break;
                case 2:
                    System.out.println("Wrong character in DNA sequence.");
                    break;
                case 3:
                    System.out.println("More than one START/STOP codon.");
                    break;
                default:
                    new Sort(genome);
                    System.out.println(genome);
            }
        }
    }

}

// vim: fen fdl=1
