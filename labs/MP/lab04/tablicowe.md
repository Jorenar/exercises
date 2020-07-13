# Podaj przypadek, dla którego sortowanie Bubble Sort przy każdym porównaniu elementów wykonuje ich zamianę (wyjaśnij dlaczego tak się dzieje)

Przypadkiem, dla którego sortowanie bąbelkowe wykona zamianę dla każdego elementu
jest tablica posortowana w sposób "odwrotny" do zamierzonego, tj. gdy np. algorytm
sortuje rosnąco, takim zestawem danych będzie zestaw posortowany malejąco.

Przykład: `5 4 3 2 1 0`

Jak widać element na pozycji pierwszej (liczba 5) zostanie porównany z każdym
innym elementem, aby "wypłynąć" na pozycję ostatnią w sposób następujący:

    5 4 3 2 1 0 | 5 > 4
    4 5 3 2 1 0 | 5 > 3
    4 3 5 2 1 0 | 5 > 2
    4 3 2 5 1 0 | 5 > 1
    4 3 2 1 5 0 | 5 > 0
    4 3 2 1 0 5 | element jest na swoim miejscu

Następnie algorytm zostanie wykonany dla podtablicy `4 3 2 1 0` i zadziała
w sposób analogiczny dla elementu `(4)` jak dla elementu `(5)`.

Analogicznie też dla każdej następnej podtablicy.

# Pokaż że Bubble Sort jest sortowaniem stabilnym

Sortowanie bąbelkowe jest sortowaniem stabilnym, ponieważ zamienia elementy
tylko gdy występuje pomiędzy nimi silna nierówność, ergo zachowuje zastaną
relację porządku pomiędzy elementami o takich samych kluczach.

Przykład: posortować tablicę `a.2  b.4  c.2  d.1` według kluczy numerycznych.
Jak widać elementy `a.2` oraz `c.2` mają takie same klucze, więc muszą pozostać
w tej samej kolejności względem siebie. Elementy po `/` są już posortowane.
Element `[x]` to obecnie sprawdzany element.

     [a.2]   b.4   c.2   d.1     | a.2 < b.4
      a.2   [b.4]  c.2   d.1     | b.4 > c.2
      a.2    c.2  [b.4]  d.1     | b.4 > d.1
     [a.2]   c.2   d.1   / b.4   | a.2 = c.2
      a.2   [c.2]  d.1   / b.4   | c.2 > d.1
      a.2    d.1   / c.2   b.4   | c.2 > d.1
     [a.2]   d.1   / c.2   b.4   | a.2 > d.1
      d.1    / a.2   c.2   b.4   |
      / d.1    a.2   c.2   b.4   |

Jak widać kolejność `a.2` i `c.2` została zachowana.

# Zmodyfikuj Selection Sort tak, aby stał się stabilny

Ażeby algorytm sortowania przez wstawianie stał się stabilny, należy zamiast
używać zmieniać miejscami elementy, użyć techniki znanej z sortowania przez
wstawianie:

```cpp
void selectionSort(int a[], int n)
{
    for (int i = 0; i < n - 1; ++i) {
        int m = i;
        for (int j = i + 1; j < n; ++j) {
            if (a[m] > a[j]) {
                m = j;
            }
        }

        // zamiast `swap(&a[m], &a[i])` :
        int temp = a[m];
        while (m > i) {
            a[m] = a[m-1];
            --m;
        }
        a[i] = temp;
    }
}
```

# Zastosuj kolejkę LIFO do odwrócenia słowa

Aby odwrócić słowo kolejką LIFO wystarczy wprowadzić znaki do kolejki,
a następnie je "wyciągnąć".

Przedstawienie rozwiązania za pomocą kodu C++ :

```cpp
for (char x: word) {
    q.push(x);
}

for (int i = 0; i < word.size(); ++i) {
    word[i] = q.pop();
}
```

Gdzie `word` to odwracane słowo, a `q` to kolejka.
