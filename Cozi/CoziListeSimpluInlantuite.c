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

int InsertQ(TCoada *c, int info)
{
	// TODO.
}

