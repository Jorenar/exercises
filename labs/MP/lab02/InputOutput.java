
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Scanner;

public class InputOutput {

    public static String getString() throws IOException {
        String line;
        InputStreamReader isr = new InputStreamReader(System.in);
        BufferedReader br = new BufferedReader(isr);
        line = br.readLine();
        return line;
    }
/*
    public static String getString2() {
        String line;
        InputStreamReader isr = new InputStreamReader(System.in);
        BufferedReader br = new BufferedReader(isr);
        try {
            line = br.readLine();
            return line;
        } catch (IOException e) {
            System.out.println("Blad odczytu.");
            return "";
        }
    }
*/
    public static int getInt() throws IOException {
        String line = getString();
        return Integer.parseInt(line);
    }
/*
    public int getInt2() {
        Scanner cons = new Scanner(System.in);
        System.out.print("Podaj liczbe calkowita: ");
        while (!cons.hasNextInt()) {
            System.out.println("Error");
            System.out.print("Podaj liczbe calkowita: ");
            cons.next();
        }
        int i = cons.nextInt();
        return i;
    }
*/
    public static void main(String[] args) throws IOException {
        System.out.println("Podaj liczbę całkowitą");
        System.out.println(InputOutput.getInt());
    
    
/*
        int n = 0, m = 0, z, i, j;
        int a[][] = new int[100][100]; // tworzy obiekt tablicy a

        Scanner in = new Scanner(System.in);//tworzy jeden obiekt 'in’
        System.out.println("Podaj liczbę zestawów");
        z = in.nextInt();
        while (z-- > 0) { //wykona się ‘z’ razy
            System.out.println("Podaj N");
            n = in.nextInt(); //wczytuje wymiary tablicy
            System.out.println("Podaj M");
            m = in.nextInt();
            for (i = 0; i < n; i++) //wczytuje tablicę wierszami
            {
                for (j = 0; j < m; j++) {
                    a[i][j] = in.nextInt();
                    System.out.println("a[" + i + ", " + j + "]=" + a[i][j]);
                }
            }
        }*/
    }
}
