#include <stdio.h>
#include <stdlib.h>

typedef struct celula2 {
	int info;
	struct celula2 *pre, *urm;
}TCelula2, *TLista2;

typedef struct {
	TLista2 sf; // Puteam sa aleg "inc" in loc de "sf".
}TCoada;

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

TCoada *InitQ(void)
{
	TCoada *c = malloc(sizeof(TCoada));
	if (!c) {
		return NULL;
	}
	c->sf = NULL;
	return c;
}

int InsQ(TCoada *c, int info)
{
	if (!c) {
		return -1;
	}
	TCelula2 *aux = AlocCelula2(info);
	aux->pre = aux;
	aux->urm = aux;
	if (!aux) {
		return -1;
	}
	if (!c->sf) {
		c->sf = aux;
		return 0;
	}
	aux->pre = c->sf;
	aux->urm = c->sf->urm;
	c->sf->urm->pre = aux;
	c->sf->urm = aux;
	c->sf = aux;
	return 0;
}

int ExtrQ(TCoada *c, int *aX)
{
	if (!c || !aX || !c->sf) {
		return -1;
	}
	*aX = c->sf->urm->info;
	if (c->sf == c->sf->urm) {
		free(c->sf);
		c->sf = NULL;
		return 0;
	}
	TCelula2 *target = c->sf->urm;
	c->sf->urm = target->urm;
	target->urm->pre = c->sf;
	free(target);
	return 0;
}

void ResetQ(TCoada *c)
{
	if (!c || !c->sf) {
		return;
	}
}


int main(void)
{
	return 0;
}

