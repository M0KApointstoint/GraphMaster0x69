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
	TLista2 inc, sf;
}TCoada;

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
	TCelula2 *aux = AlocCelula2(info);
	if (!aux) {
		return -1;
	}
	if (!c->inc) {
		c->inc = aux;
		c->sf = aux;
		return 0;
	}
	aux->pre = c->sf;
	c->sf->urm = aux;
	c->sf = aux;
	return 0;
}

int main(void)
{
	return 0;
}

