#ifndef GRAFURI_H
#define GRAFURI_H

#include "liste_simplu_inlantuite.h"

typedef struct {
	int n;
	TLista *v;
}TGraf;

TGraf *InitGraf(int n);

int InserareArc(TGraf *g, int x, int y);

#endif

