**1.) [10p.]:**
```
a.) Specificati diferenta dintre un arbore AVL si un arbore binar de cautare.
Dati cate un exemplu pentru fiecare tip de arbore. [3p.]

b.) Construiti treap-ul (folosind min-heap) prin inserarea succesiva a cheilor,
de forma (cheie, prioritate): (1, 6), (0, 9), (4, 14), (9, 17), (5, 11),
(3, 1), (2, 80), (8, 39), (7, 22). Reprezentati treap-ul dupa fiecare
operatie de inserare. [3p.]

c.) Se considera urmatorul arbore. Sa se construiasca arborele prin eliminarea
nodului 5. Explicati cum se realizeaza aceasta eliminare.

        10
       /  \
      3    15
       \     \
        7   20
       / \
      6   8
           \
            9

d.) Se considera vectorul v cu elementele: 1, 2, 5, 10, 16, 12, 8, 9. Poate
acesta sa reprezinte un min-heap?. Explicati.
```

*Rezolvare:*
```
a.) AVL-ul este un are arbore binar de cautare mereu echilibrat, ABC-ul nu
este mereu echilibrat. Exemple:

    2               4
   / \             / \
  1   3           3   5
                       \
                        6
                         \
                          7

b.) Reprezentari generate cu AI, dar verificate de mine, pe foaie:

1. Inserăm (1,6)
1(6)
2. Inserăm (0,9)

BST: 0 < 1 ⇒ stânga.

    1(6)
   /
0(9)

Heap-ul este respectat deoarece:

6 < 9
3. Inserăm (4,14)

BST: 4 > 1 ⇒ dreapta.

    1(6)
   /   \
0(9)  4(14)

Heap-ul este respectat.

4. Inserăm (9,17)

BST:

9 > 1
9 > 4
      1(6)
     /    \
  0(9)   4(14)
             \
             9(17)

Heap-ul este respectat.

5. Inserăm (5,11)

Inserare BST:

      1(6)
     /    \
  0(9)   4(14)
             \
             9(17)
            /
         5(11)

Nodul 5 are prioritate mai mică decât 9:

11 < 17

Rotim dreapta în jurul lui 9:

      1(6)
     /    \
  0(9)   4(14)
             \
            5(11)
                \
                9(17)

Acum:

11 < 14

Rotim stânga în jurul lui 4:

       1(6)
      /    \
   0(9)   5(11)
          /   \
      4(14)  9(17)

Heap-ul este acum respectat.

6. Inserăm (3,1)

Inserare BST:

          1(6)
         /    \
      0(9)   5(11)
             /   \
         4(14)  9(17)
         /
      3(1)

Prioritatea lui 3 este mai mică decât a lui 4:

1 < 14

Rotire dreapta la 4:

          1(6)
         /    \
      0(9)   5(11)
             /   \
          3(1)  9(17)
             \
             4(14)

Acum:

1 < 11

Rotire dreapta la 5:

          1(6)
         /    \
      0(9)   3(1)
               \
               5(11)
              /   \
          4(14)  9(17)

Acum:

1 < 6

Rotire stânga la 1:

            3(1)
           /    \
        1(6)   5(11)
       /       /   \
    0(9)    4(14) 9(17)
7. Inserăm (2,80)

Inserare BST:

            3(1)
           /    \
        1(6)   5(11)
       /  \    /   \
    0(9) 2(80)4(14)9(17)

Heap-ul este deja respectat.

8. Inserăm (8,39)

Inserare BST:

            3(1)
           /    \
        1(6)   5(11)
       /  \    /   \
    0(9) 2(80)4(14)9(17)
                    /
                 8(39)

Prioritățile:

39 > 17

Nu sunt necesare rotații.

9. Inserăm (7,22)

Inserare BST:

            3(1)
           /    \
        1(6)   5(11)
       /  \    /   \
    0(9) 2(80)4(14)9(17)
                    /
                 8(39)
                 /
              7(22)

Verificăm heap-ul:

22 < 39

Rotire dreapta la 8:

            3(1)
           /    \
        1(6)   5(11)
       /  \    /   \
    0(9) 2(80)4(14)9(17)
                    /
                 7(22)
                     \
                     8(39)

Acum:

22 > 17

Ne oprim.

Treap-ul final
                3(1)
               /    \
            1(6)   5(11)
           /  \    /    \
        0(9) 2(80)4(14) 9(17)
                          /
                       7(22)
                           \
                           8(39)

c.) Se alege cea mai mare valoare (cea mai din dreapta) din subarborele
stang al nodului cu valoarea 5, se face interschimbarea si se elimina frunza
cu valoarea 5:

        10
       /  \
      3    15
     /      \
    7       20
   / \
  6   8
       \
        9

d.) Dupa reprezentarea arborelui de selectie aferent vectorului v se constata
ca nodul cu valoarea 10 este parinte al nodului cu valoarea 9, dar 10 > 9, deci
vectorul v NU poate reprezenta un min-heap.
```

**2.) [10p.]:**
```
a.) Se considera graful orientat cu 6 noduri si urmatoarele arce, descrise sub
forma nod sursa -> nod destinatie: 1 -> 4, 1 -> 6, 2 -> 1, 2 -> 4, 3 -> 1,
3 -> 4, 5 -> 1, 5 -> 3, 6 -> 3. Sa se construiasca arborele de parcurgere in
adancime (cu marcarea tipurilor de arce), pornind de la nodul 5. [3p.]

b.) Explicati care este rolul arcelor de adancime intr-un graf orientat. [2p.]

c.) Scrieti functia care primeste ca parametri un graf orientat reprezentat
prin liste de adiancenta (conform decalaratiei de tip de mai jos) si indicele
unui nod din graf (s) si intoarce numarul de arce de adancime obtinute prin
parcurgerea in adancime a grafului pornind de la nodul s. Indicii nodurilor
in graf sunt numerotati de la 1.
```

```c
typedef struct celar {
    int d; /* destinatie arc */
    struct celarc *urm; /* adresa urmatorului adiacent */
}TCelArc, *AArc;

typedef struct {
    int n; /* numar noduri *./
    AArc *x; / * vector adrese liste arce */
}TGrafL;
```

*Rezolvare:*
```
a.) Reprezentarea este facuta cu AI, dar verificat de mine, pe foaie.

(5,1) -> A
(1,4) -> A
(1,6) -> A
(6,3) -> A
(3,1) -> R
(3,4) -> T
(5,3) -> D
(2,1) -> T
(2,4) -> T

Arborele doar cu arce de adancime:

5
└── 1
     ├── 4
     └── 6
          └── 3

b.) AI.

c.) AI.
```
**4.) [5p.]:**
```
Se considera declaratia de tip pentru lsita dublu inlantuita circulara cu
santinela cu elemente intregi. Sa se scrie declaratia de tip pentru coada
cu elemente intregi implementata folosind acest tip de lista. Sa se
implementeze functia de eliminare element din coada.
```

```c
typedef struct celula2 {
    int info;
    struct celula2 *pre, *urm;
}TCelula2, *TLista2;
```

**6.) [3p.]:**
```
Se considera un sistem de gestionare a rezervarilor si comenzilor intr-un
restaurant, unde fiecare comanda are urmatoarele elemente: cod unic al
comenzii, momentul plasarii, prioritatea (de exemplu: rezervare la masa /
livrare rapida / comanda normala), masa sau clientul asociat. Sistemul
trebuie sa permita: a.) preluarea rapida a comenzii cu cea mai mare prioritate
si b.) cautarea si actualizarea rapida a unei comenzi pe baza codului unic
(de exemplu, anularea unei comenzi deja plasate). Sa se indice structura /
structurile de date alese penru o implementare eficienta.
```

*Rezolvare:*
```
Se poate implementa un treap care foloseste pe post de valoare codul unic
pentru comenzi si ca prioritate prioritatea comenzii.

SAU (generat cu AI):

Se poate implementa folosind două structuri de date: un hash map care
folosește drept cheie codul unic al comenzii și permite
căutarea/actualizarea rapidă a unei comenzi, respectiv un heap
(coadă de priorități) care ordonează comenzile după prioritate și
permite preluarea rapidă a comenzii cu prioritatea cea mai mare.
Astfel, căutarea după cod se face în O(1) în medie, iar accesul la
comanda cu prioritatea maximă în O(1).
Dacă anulezi o comandă:
map.remove("C103")
ea rămâne în heap dacă nu faci ceva suplimentar. Ai două variante:

Varianta 1: ștergere directă din heap
Trebuie să găsești nodul în heap și să-l elimini.
Problema este că un heap obișnuit nu știe unde se află elementul
cu codul C103, deci căutarea lui costă O(n). Asta strică avantajul.

Varianta 2: lazy deletion
Se marchează comanda drept anulată:
C103.cancelled = true
și se șterge din HashMap.
Când ajunge în vârful heap-ului:
while heap.top().cancelled:
    heap.pop()
o elimini atunci.
Asta este soluția folosită frecvent.
```

**7.) [6p.]:**
```
Se considera declaratia de tip pentru lista generica simplu inlantuita.
```

```c
typedef struct celulag {
    void *info;
    struct celulag *urm;
}TCelulaG, *TLG;
```

```
a.) Sa se scrie functia care construieste o noua lista prin copierea
elementelor care indeplinesc o anumita conditie(Nu se cunosc: tipul elementelor
din lista, precum si conditia pentru copiere). [2p.]

b.) Se va scrie apelul functiei pentru cazul in care lista generica contine
elemente intregi, iar functia va trebui sa elimine toate elementele pare din
lista. [1p.]

c.) Specificati care sunt modificarile in cazul in care elementele din lista
generica reprezinta liste simplu inlantuite cu elemente intregi. [3p.]
```

