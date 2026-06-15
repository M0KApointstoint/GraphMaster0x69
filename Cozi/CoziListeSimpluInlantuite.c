#include <stdlib.h>

typedef struct celula {
    int info;
    struct celula *urm;
}TCelula, *TLista;

typedef struct coada {
    TLista inc, sf;
}TCoada;

TCelula *AlocCelula(int info)
{
	TCelula *aux = malloc(sizeof(TCelula));
	if (!aux) {
		return NULL;
	}
	aux->info = info;
	aux->urm = NULL;
	return aux;
}

void DistrugeLista(TLista *aL)
{
	if (!aL || !*aL) {
		return;
	}
	TLista l = *aL;
	while (l) {
		TLista target = l;
		l = l->urm;
		free(target);
	}
	*aL = NULL;
}

TCoada *InitQ(void)
{
    TCoada *c = malloc(sizeof(TCoada));
    if (!c) {
        return NULL;
    }
	c->inc = NULL;
	c->sf = NULL;
	return c;
}

int InsQ(TCoada *c, int info)
{
	if (!c) {
		return -1;
	}
	TCelula *aux = AlocCelula(info);
	if (!aux) {
		return -1;
	}
	if (!c->inc) {
		c->inc = aux;
		c->sf = aux;
		return 0;
	}
	c->sf->urm = aux;
	c->sf = aux;
	return 0;
}

int ExtrQ(TCoada *c, int *aX)
{
	if (!c || !aX || !c->inc) {
		return -1;
	}
	*aX = c->inc->info;
	if (c->inc == c->sf) {
		free(c->inc);
		c->inc = NULL
		c->sf = NULL;
		return 0;
	}
	TCelula *target = c->inc;
	c->inc = target->urm;
	free(target);
	return 0;
}

void ResetQ(TCoada *c)
{
	// Verificari facute deja de functie, dar safety matters.
	if (!c || !c->inc) {
		return;
	}
	DistrugeLista(&c->inc);
	// La fel si aici.
	c->inc = NULL;
	c->sf = NULL;
}

void DistrugeQ(TCoada *aC)
{
	if (!aC || !*aC) {
		return;
	}
	ResetQ(*aC);
	free(*aC);
	*aC = NULL;
}

