# Probleme cu liste generice din anii precedenti

## 2025:

**[3p.]:**
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
Sa se scrie functia care elimina din lista elementele care indeplinesc
o anumita conditie (Nu se cunosc: tipul elementelor din lista, precum si
conditia pentru eliminare).

Sa se scrie apelul functiei pentru cazul in care lista generica contine
elemente intregi, iar functia va trebui sa elimine toate elementele impare din
lista.
```

