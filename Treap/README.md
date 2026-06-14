# Probleme din anii precedenti cu Treap

## 2025:

**[3p.]:**
```
Construiti treap-ul (folosind max-heap) prin inserarea succesiva a cheilor,
de forma (cheie, prioritate): (9, 17), (3, 10), (2, 8), (4, 14), (5, 17),
(17, 15), (12, 20), (15, 18), (16, 13). Reprezentati treap-ul dupa fiecare
operatie de inserare. In treap-ul construit sa se elimine nodul (17, 15).
```

*Rezolvare:*
Se poate realiza o reprezentare grafica a operatiilor realizate
(Generat de AI, dar desen verificat pe foaie, scris de mana):
```
- Inserare (9, 17):

(9,17)

- Inserare (3, 10):

    (9,17)
    /
(3,10)

- Inserare (2, 8):

      (9,17)
      /
   (3,10)
   /
(2,8)

- Inserare (4, 14):

        (9,17)
        /
     (3,10)
     /    \
  (2,8) (4,14)

14 > 10 => Rotatie stanga in jurul lui (3, 10):

        (9,17)
        /
     (4,14)
     /
  (3,10)
  /
(2,8)

- Inserare (5, 17):

        (9,17)
        /
     (4,14)
     /    \
  (3,10) (5,17)
  /
(2,8)

17 > 14 => Rotatie stanga in jurul lui (4, 14):

        (9,17)
        /
     (5,17)
     /
  (4,14)
  /
(3,10)
/
(2,8)

- Inserare (17, 15):

          (9,17)
         /      \
     (5,17)   (17,15)
      /
   (4,14)
   /
(3,10)
/
(2,8)

- Inserare (12, 20):

          (9,17)
         /      \
     (5,17)   (17,15)
      /        /
   (4,14)  (12,20)
   /
(3,10)
/
(2,8)

20 > 15 => Rotatie dreapta in jurul lui (17, 15):

          (9,17)
         /      \
     (5,17)   (12,20)
      /           \
   (4,14)       (17, 15)
   /
(3,10)
/
(2,8)

20 > 17 => Rotatie dreapta in jurul lui (9, 17):

              (12,20)
             /       \
         (9,17)    (17,15)
         /
      (5,17)
      /
   (4,14)
   /
(3,10)
/
(2,8)

- Inserare (15, 18):

              (12,20)
             /       \
         (9,17)    (17,15)
         /         /
      (5,17)   (15,18)
      /
   (4,14)
   /
(3,10)
/
(2,8)

18 > 15 => Rotatie stanga in jurul lui (17, 15):

              (12,20)
             /       \
         (9,17)    (15,18)
         /              \
      (5,17)          (17, 15)
      /
   (4,14)
   /
(3,10)
/
(2,8)

- Inserare (16, 13):

                 (12,20)
                /       \
            (9,17)    (15,18)
            /              \
        (5,17)           (17,15)
        /                /
     (4,14)          (16,13)
     /
  (3,10)
  /
(2,8)

- Eliminare (17, 15):

Se face o rotatie stanga in jurul lui (17, 15), care devine frunza apoi se
sterge din arbore:

                 (12,20)
                /       \
            (9,17)    (15,18)
            /              \
        (5,17)           (16,13)
        /
     (4,14)
     /
  (3,10)
  /
(2,8)
```

