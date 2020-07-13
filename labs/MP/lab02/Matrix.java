
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

class Helper {

    public static int getInt() throws IOException {
        InputStreamReader isr = new InputStreamReader(System.in);
        BufferedReader br = new BufferedReader(isr);
        String line = br.readLine();
        return Integer.parseInt(line);
    }

}

public class Matrix {

    public static void main(String[] args) throws IOException {

        System.out.println("Matrix");

        int[][] matrix = new int[5][7]; //deklaracja i przypisanie (utworzenie)
        //System.out.println(matrix.length);
        matrix[2][3] = Helper.getInt();
        System.out.println(matrix[2][3]);

    }

}

//Maksymalna podtablica
/*
b = 0; e = 0; max = 0; // pierwsze przybliżenie
for (i=0; i<n; i++) // i-początek podtablicy
for {j=i; j<n; j++) { // j-koniec podtablicy
sum = 0; // sumuj podtablicę a[i..j]
for (k=i; k<=j; k++)
sum = sum + a[k] ;
if (sum > max){
max = sum;
b = i;
e = j; }
}
*/