import java.util.Random;
import java.util.Arrays;

class Vector {

    private int[] a; // referencja do wektora
    private int maxSize; // maksymalna długość wektora
    private int n; // aktualna długość wektora

    public Vector(int m) { //konstruktor
        maxSize = m;
        n = 0;
        a = new int[maxSize];
    }

    //Dopisz:

    //konstruktor przyjmujący maksymalny rozmiar "m" i wypełniający wektor
    //"l" losowymi wartościami z przedziału 0-100 (proszę znaleźć jak losować w Internecie)
    public Vector(int m, int l) {
        this(m);
        n = l < maxSize ? l : maxSize;
        Random rand = new Random();
        for (int i = 0; i < n; i++) {
            a[i] = rand.nextInt(101);
        }
    }

    //wyświetl wektor na ekran
    public void display() {
        System.out.println(this.toString());
    }

    //zwróć Stringa z kolejnymi wartościami z wektora rozdzielonymi spacją
    @Override
    public String toString() {
        return Arrays.toString(Arrays.copyOfRange(a, 0, n)).replaceAll(",", "").replace("[", "").replace("]", "");
    }

    //wstaw "x" na koniec wektora (uwaga na mksymalny rozmiar)
    public void insert(int x) {
        if (n < maxSize) {
            a[n++] = x;
        }
    }

    //usuń z wektora wszystkie wystąpienia liczby "x"
    public void remove(int x) {
        int[] b = new int[maxSize];
        int m = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] != x) {
                b[m++] = a[i];
            }
        }
        n = m;
        a = b;
    }

    //zwraca element o podanym indeksie (uwaga na nieprawidłowe indeksy)
    public int at(int i) {
        return i < n ? a[i] : 0;
    }

    //Stwórz w funkcji main prezentację wszystkich funkcji
    public static void main(String[] args) {
        Vector foo = new Vector(15, 5);
        foo.display();
        foo.insert(5);
        foo.insert(11);
        foo.insert(26);
        foo.insert(11);
        foo.insert(0);
        foo.insert(11);
        foo.insert(10);
        foo.insert(11);
        System.out.println(foo.toString());
        foo.remove(11);
        foo.display();
    }

}
