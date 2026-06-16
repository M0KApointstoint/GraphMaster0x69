#include <stdio.h>
#include <stdlib.h>

typedef struct celula2 {
	int info;
	struct celula2 *pre, *urm;
}TCelula2, *TLista2;

// Rezolvare.
typedef struct coada {
	TLista2 inc; // Puteam sa aleg si "sf" in loc de "inc".
}TCoada;

int ExtrQ(TCoada *c, int *x)
{
	if (!c || !x || ||!c->inc || c->inc == c->inc->urm) {
		return -1;
	}
	TLista2 aux = c->inc->urm;
	*x = aux->info;
	aux->urm->pre = c->inc;
	c->inc->urm = aux->urm;
	free(aux);
	return 0;
}
