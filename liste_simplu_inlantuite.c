#include <stdlib.h>
#include "liste_simplu_inlantuite.h"

TLista AlocCelula(int info)
{
	TLista aux = malloc(sizeof(TCelula));
	if (!aux) {
		return NULL;
	}
	aux->info = info;
	aux->urm = NULL;
	return aux;
}

