<!-- Do pełnego wyświetlania treści tego pliku potrzebny jest Github Markdown renderer -->

Sejfowe grafy
-------------

## Opis zadania

Mamy $n$ sejfów. Każdy z nich można otworzyć odpowiednim kluczem lub zniszczyć,
żeby dostać się do zawartości. \
Klucze do tych sejfów znajdują się w tych samych sejfach; w każdym sejfie może
być $0$, $1$ lub więcej kluczy. \
Do każdego sejfu pasuje tylko jeden klucz i wiemy, w którym sejfie znajduje się
on znajduje.

Zadaniem jest napisanie programu, który zwróci informację jaka jest najmniejsza
liczba sejfów, które trzeba zniszczyć żeby dostać się do zawartości wszystkich
z nich.

Przykładowe wejście do programu może składać się z jednej liczby $n$
oznaczającej liczbę sejfów, oraz listy $n$ liczb, w której $i$-ta liczba
to indeks sejfu w którym znajduje się klucz do $i$-tego sejfu.

### Przykład:
```
4
2 1 2 4
```
Oznacza to, że są $4$ sejfy. Klucz do pierwszego sejfu znajduje się w sejfie $2$
($2$ na pozycji pierwszej), do drugiego w sejfie $1$ ($1$ na pozycji drugiej),
do $3$ w sejfie $2$ itd.

Dla takiego wejścia, prawidłowa odpowiedź to $2$ (gdyż należałoby zniszczyć sejfy $1$ i $4$).

## Analiza

Zauważamy, że można zbudować graf zależności, taki że:

$$
\mbox{\large $\forall$}_{(v,u) \in G.E} : k_u \in v \textrm{, gdzie } k_u \textrm{ &ndash; klucz otwierający sejf } u
$$

Z faktu istnienia grafu nasuwa się wniosek, iż prawdopodobnie należy będzie
wyznaczyć wspólne składowe.

Zauważamy, z faktu istnienia tylko jednego pasującego klucza per sejf, że nie
występuje sytuacja gdzie dwie krawędzie prowadzą do tego samego wierzchołka.

Stąd wiemy, że każda składowa będzie pojedynczym wierzchołkiem, ścieżką
skierowaną (z ewentualnymi krawędziami powrotnymi), bądź cyklem. Innymi
słowy, nie ma weń "jednokierunkowych uliczek pod prąd".

Oznacza to, że w każdej składowej wystarczy zniszczyć tylko jeden sejf,
by dostać się do pozostałych. \
Ergo, liczba potrzebnych do zniszczenia sejfów będzie równa ilości spójnych składowych.

Ponieważ nie interesuje nas ani dokładna postać składowej, ani nawet które sejfy
należy zniszczyć, to z faktu jakie postaci może przyjąć, potraktujemy graf jako
nieskierowany, gdyż nie jest istotne, w którą "stronę" zachodzi relacja.

Aby wyznaczyć spójne w grafie nieskierowanym kolorujemy inaczej każde
nierekurencyjne wywołanie procedury $DFS–visit$. \
Ponieważ nie wyznaczamy spójnych składowych, a ich ilość, wystarczy zliczyć
nierekurencyjne wywołania tejże procedury.

## Rozwiązanie

Kod programu rozwiązującego to zadanie zawarty jest w pliku `safes.cpp`.

Wejście jak w przykładzie; w odpowiedzi program wypisuje liczbę sejfów do zniszczenia.
