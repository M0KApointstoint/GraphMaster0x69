#include <stdio.h>
#include <stdlib.h>

typedef struct celula2 {
	int info;
	struct celula2 *pre, *urm;
}TCelula2, *TLista2;

TCelula2 *AlocCelula2(int info)
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

typedef struct {
	TLista sf; // Puteam sa aleg "inc" in loc de "sf".
}TCoada; // Puteam nici sa nu definesc structura asta.

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

