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

void DFSRec(TGraf *g, int x, int *vizitat)
{
	vizitat[x] = vizitat[0]++;
	TLista p = g->v[x];
	while (p) {
		printf("%d -> %d\n", x, p->info);
		if (vizitat[p->info] > 0) {
			printf("Arcul este de tip revenire.\n");
		} else if (vizitat[p->info] < 0 && -vizitat[p->info] > vizitat[x]) {
			printf("Arcul este de tip destinatie.\n");
		} else if (vizitat[p->info] < 0 && -vizitat[p->info] < vizitat[x]) {
			printf("Arcul este de tip Traversare.\n");
		}
		if (!vizitat[p->info]) {
			printf("Arcul este de tip adancime.\n");
			DFSRec(g, p->info, vizitat);
		}
		p = p->urm;
	}
	vizitat[x] *= -1;
}

void ParcurgereDFS(TGraf *g, int x)
{
	if (!g || x < 1 || x > g->n) {
		return;
	}
	int *vizitat = malloc((g->n + 1) * sizeof(int));
	if (!vizitat) {
		return;
	}
	vizitat[0] = 1;
	for (int i = 1; i < g->n + 1; ++i) {
		vizitat[i] = 0;
	}
	for (int i = 1; i < g->n + 1; ++i) {
		if (!vizitat[i]) {
			DFSRec(g, i, vizitat);
		}
	}
	free(vizitat);
}

int AciclicRec(TGraf *g, int i, int *vizitat)
{
	if (vizitat[i]) {
		return 1;
	}
	vizitat[i] = vizitat[0]++;
	TLista p = g->v[i];
	int cod = 1;
	while (p) {
		if (vizitat[p->info] > 0) {
			return 0;
		}
		cod = AciclicRec(g, p->info, vizitat);
		if (!cod) {
			return 0;
		}
		p = p->urm;
	}
	vizitat[i] *= -1;
	return cod;
}

int Aciclic(TGraf *g)
{
	if (!g) {
		return 1;
	}
	int *vizitat = malloc((g->n + 1) * sizeof(int));
	if (!vizitat) {
		return 1;
	}
	vizitat[0] = 1;
	for (int i = 1; i < g->n + 1; ++i) {
		vizitat[i] = 0;
	}
	for (int i = 1; i < g->n + 1; ++i) {
		if (!AciclicRec(g, i, vizitat)) {
			free(vizitat);
			return 0;
		}
	}
	free(vizitat);
	return 1;
}

