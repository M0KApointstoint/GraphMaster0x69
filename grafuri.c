#include <stdio.h>
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

void DistrugeGraf(TGraf **aG)
{
	TGraf *g = *aG;
	for (int i = 0; i < g->n + 1; ++i) {
		DistrugeLista(g->v + i);
	}
	free(g->v);
	free(g);
	*aG = NULL;
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

void DFSRec(TGraf *g, int x, int *vizitati)
{
	if (vizitati[x]) {
		return;
	}
	printf("%d\n", x);
	vizitati[x] = 1;
	TLista p = g->v[x];
	while (p) {
		DFSRec(g, p->info, vizitati);
		p = p->urm;
	}
}

void ParcurgereDFS(TGraf *g, int x)
{
	if (!g || x < 1 || x > g->n) {
		return;
	}
	int *vizitati = malloc((g->n + 1) * sizeof(int));
	if (!vizitati) {
		return;
	}
	for (int i = 0; i < g->n + 1; ++i) {
		vizitati[i] = 0;
	}
	for (int i = 1; i < g->n + 1; ++i) {
		DFSRec(g, i, vizitati);
	}
	free(vizitati);
}

