#include <stdlib.h>
#include "grafuri.h"

TGraf *InitGraf(int n)
{
	TGraf *g = malloc(sizeof(TGraf));
	if (!g) {
		return NULL;
	}
	g->v = malloc((n + 1) * sizeof(TLista));
	if (!g->v) {
		free(g);
		return NULL;
	}
	for (int i = 0; i < n + 1; ++i) {
		g->v[i] = NULL;
	}
	g->n = n;
	return g;
}

int InserareArc(TGraf *g, int x, int y)
{
	if (!g || x < 1 || x > g->n) {
		return -1;
	}
	TLista p = g->v[x];
	while (p) {
		if (p->info == y) {
			return 1;
		}
		p = p->urm;
	}
	p = g->v[x];
	g->v[x] = AlocCelula(y);
	if (!g->v[x]) {
		return -1;
	}
	g->v[x]->urm = p;
	return 0;
}

