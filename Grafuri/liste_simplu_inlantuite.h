#ifndef LISTE_SIMPLU_INLANTUITE_H
#define LISTE_SIMPLU_INLANTUITE_H

typedef struct celula{
	int info;
	struct celula *urm;
}TCelula, *TLista;

TLista AlocCelula(int info);

void DistrugeLista(TLista *aL);

#endif

