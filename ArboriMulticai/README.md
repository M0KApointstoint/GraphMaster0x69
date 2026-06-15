# Probleme din anii precedenti.

## 2025:

**[3p.]:**
```
Se considera un arbore multicai definit prin tipul de date Tree.
Explicati care este efectul functiei f si care este rezultatul apelului:
int r = f(a, 0), unde a este adresa radacinii arborelui de mai jos.
```

```c
typedef struct node {
    int info;
    struct node *left; /* primul copil */
    struct node *right; /* fratele urmator */
}Node, *Tree;

int f(Tree a, int d)
{
    if (!a) {
        return 0;
    }
    int s = d;
    s += f(a->left, d + 1);
    s += f(a->right, d);
    return s;
}
```

```
            10
         /   |   \
        5    2    15
             |
             3
```

*Rezolvare:*

```
Cu pixul pe hartie se arata ca r = 5.
Functia calculeaza suma adancimilor fiecarui nod din arbore.
```

