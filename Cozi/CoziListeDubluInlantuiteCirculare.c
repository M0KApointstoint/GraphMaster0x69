#include <stdio.h>
#include <stdlib.h>

typedef struct celula2 {
	int info;
	struct celula *pre, *urm;
}TCelula2, *TLista2;

typedef struct {
	TLista2 sf; // Puteam sa aleg "inc" in loc de "sf".
}TCoada;

TCelula2 *AlocCelula(int info)
{
	TCelula2 *aux = malloc(sizeof(TCelula2));
	if (!aux) {
		return NULL;
	}
	aux->info = info;
	aux->pre = NULL;
	aux->urm = NULL;
	return aux;
}

TCoada *InitQ(void)
{
	TCoada *c = malloc(sizeof(TCoada));
	if (!c) {
		return NULL;
	}
	c->sf = NULL;
	return c;
}

int main(void)
{
	return 0;
}

