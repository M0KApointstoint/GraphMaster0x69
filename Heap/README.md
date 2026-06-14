# Probleme cu heap din anii precedenti

## 2025:

**[2p.]:**
```
Se considera vectorul v cu elementele: 1, 2, 5, 10, 14, 3, 8, 20.
Poate acesta sa reprezinte un min-heap?. Explicati.
```

*Rezolvare:*
Se poate reprezenta arborele de selectie corespunzator lui v si
se constata ca parintele lui 3 este 5, dar 5 >= 3, deci v nu poate
sa reprezinte un min-heap.

```
                1
             /     \
            2       5
          /  \     / \
        10   14   3   8
       /
     20
```

Raspuns final: **NU**.

## 2024:

**[6p.]:**
```
Fie un max-heap.
a.) Specificati definitia acestuia. [1p.]

b.) Specificati unde se afla elementul maxim, dar elementul minim?. [2p.]

c.) Se considera secventa 13, 70, 50, 10, 12, 40, 60. Construiti max-heap-ul
prin inserarea succesiva a elementelor. In heapul construit, realizati o
extragere.
Explicati cum au fost realizate inserarile, respectiv extragerea. [3p.]
```

*Rezolvare:*
a.) Un max-heap este o structura de date care poate fi reprezentat prin
intermediul unui arbore complet(numit si arbore de selectie),
in care fiecare nod are asociata o cheie care are o prioritate mai mare decat
prioritatile cheilor copiilor sai (daca exista), asadar, radacina arborelui
va fi mereu nodul cu cheia care are cea mai mare prioritate din heap.

**ATENTIE! ELEMENTUL MINIM NU ESTE NEAPARAT IN EXTREMITATEA DIN DREAPTA JOS!**

b.) Elementul maxim se afla la radacina arborelui, iar elementul minim se va
afla intr-una dintre frunzele arborelui, dar nu se poate determina cu
exactitate decat daca se analizeaza fiecare frunza in parte.

c.) Se poate realiza o reprezentare a arborelui de selectie aferent:
```
Inserare 13 -> 13     -> Inserare 70 ->     13      -> 70 > 13 ->   70 ->
                                           /                        /
                                          70                       13

-> Inserare 50 ->           70      -> Inserare 10 ->           70     ->
                           /  \                                /  \
                          13  50                              13  50
                                                             /
                                                            10

-> Inserare 12 ->        70         -> Inserare 40 ->               70       ->
                        /  \                                    /        \
                      13    50                                13          50
                     /  \                                    /  \         /
                    10   12                                 10  12       40

-> Inserare 60 ->           70          -> 60 > 50 ->               70       ->
                        /        \                              /        \
                      13          50                          13          60
                    /    \       /  \                       /    \       /  \
                   10    12     40   60                    10     12    40   50

-> Extragere -> Se interschimba radacina arborerului (70) cu ultimul
element (50), dar nu vom mai reprezenta si ultimul element dupa extragere ->

->                  50      -> 50 > 13 si 50 <= 60 ->           60     -> STOP.
                /       \                                   /        \
              13         60                                13         50
             /  \       /                                 /  \        /
            10   12    40                                10   12     40
```

## 2023:

**[3p.]:**
```
Se considera urmatorul min-heap cu 7 noduri. Min-heap-ul este reprezentat
prin urmatorul vector: 5, 8, 10, 13, 15, 14, 20. Sa se insereze valoarea
3 in heap si apoi sa se realizeze o extragere.
```

*Rezolvare:*
Se poate realiza o reprezentare a arborelui de selectie aferent vectorului dat:
```
            5           -> Inserare 3 ->                    5           ->
        /       \                                       /       \
       8        10                                     8         10
      / \      /  \                                  /   \      /  \
     13 15    14  20                                13   15    14  20
                                                   /
                                                  3

-> 13 >= 3 ->               5           -> 8 >= 3 ->            5            ->
                        /       \                           /       \
                       8         10                        3        10
                      / \       /  \                      / \      /  \
                     3  15    14   20                    8   15   14   20
                    /                                   /
                   13                                  13

-> 5 >= 3 ->                3               -> Extragere ->
                        /       \
                       5        10
                      / \      /  \
                     8   15   14   20
                    /
                   13

->                          13          -> 13 >= 5 si 13 >= 10, dar 5 < 10 ->
                          /    \
                         5      10
                        / \    /  \
                       8  15  14   20

->                          5       -> 13 >= 8 si 13 < 15 ->        5  -> STOP.
                          /   \                                   /   \
                         13   10                                8       10
                        /  \  / \                              /  \    /   \
                       8  15 14  20                           13   15 14   20
```

