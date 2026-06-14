# Probleme cu grafuri din anii precedenti

## 2025:

**[3p.]:**
```
Se considera graful orientat cu 6 noduri si urmatoarele arce, descrise sub
forma nod sursa -> destinatie:
1 -> 4, 1 -> 6, 2 -> 1, 2 -> 4, 3 -> 1, 3 -> 4, 5 -> 1, 5 -> 3, 6 -> 3.
Sa se construiasca arborele de parcurgere in adancime (cu marcarea tipurilor
de arce), pornind de la nodul 3.
```

*Solutie:*
Se poate reprezenta graful printr-un desen
(Generat cu AI dar verificat cu scris de mana, pe hartie):
```
Ordinea afisarii: 3, 1, 4, 6, 2, 5.

Mai intai, reprezentarea grafului intreg:

Componenta 1 (radacina 3):
3
└──A──> 1
         ├──A──> 4   (frunza)
         └──A──> 6
                  └──R──> 3   (revenire, ciclu)
3 ──D──> 4   (arc direct, in afara arborelui)

Componenta 2 (radacina 2):
2   (radacina noua, izolata in padurea DFS)
├──T──> 1   (traversare)
└──T──> 4   (traversare)

Componenta 3 (radacina 5):
5   (radacina noua, izolata in padurea DFS)
├──T──> 1   (traversare)
└──T──> 3   (traversare)

Acum, arborele de parcurgere in adancime:

3
└── 1
     ├── 4
     └── 6
```

