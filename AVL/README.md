# Probleme din anii precedenti cu AVL

## 2025:

**[3p.]:**
```
Fie secventa 45, 31, 13, 80, 40, 90, 20, 38, 85, 82.
Construiti arborele binar de cautare prin inserarea succesiva a cheilor.
Transformati arborele in arbore AVL.
```

*Rezolvare:*
**La examen se vor face si pasii intermediari pentru ABC in detaliu!**
Se poate reprezenta printr-un desen arborele in urma operatiilor aferente
(generat de AI, dar verificat cu desenul facut de mana, pe foaie):
```
                45
              /    \
            31      80
           /  \       \
         13    40      90
           \   /       /
           20 38      85
                      /
                     82

Se aplica o rotatie dreapta asupra lui 90:

                45
              /    \
            31      80
           /  \       \
         13    40      85
           \   /       /  \
           20 38      82   90

Se aplica o rotatie stanga asupra lui 80:

                45
              /     \
            31       85
           /  \      /  \
         13    40   80    90
           \   /      \
           20 38       82
```

## 2024:

**[4p.]:**
```
Fie secventa 70, 35, 45, 20, 50, 90, 60. Construiti arborele binar de cautare
prin inserarea succesiva a cheilor. Arborele construit este AVL?. Explicati.
In cazul in care arborele nu este AVL, aratati cum poate fi tranformat
in arbore AVL.
```
*Rezolvare:*
**La examen se vor face si pasii intermediari pentru ABC in detaliu!**
Se poate reprezenta printr-un desen arborele in urma operatiilor aferente
(generat de AI, dar verificat cu desenul facut de mana, pe foaie):
```

                70
              /    \
            35      90
           /  \
         20    45
                 \
                  50
                   \
                    60

Arborele dat nu este AVL, deoarece nu este echilibrat, exista noduri care au
factori de echilibru mai mari decat 1 si mai mici decat -1.

Se aplica o rotatie stanga in jurul lui 45:

                70
              /    \
            35      90
           /  \
         20    50
              /  \
            45    60

Se aplica o rotatie dreapta in jurul lui 70:

                50
              /    \
            35      70
           /  \    /  \
         20   45  60   90

```

