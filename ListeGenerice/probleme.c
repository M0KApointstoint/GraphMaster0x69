#include <stdio.h>
#include <stdlib.h>

typedef struct celulag {
	void *info;
	struct celulag *urm;
} TCelulaG, *TLG;

// Pentru subpunctul a.).
typedef int (*TFCond)(void *);

typedef void (*TFElib)(void *);

// Presupunem ca functia returneaza 0 daca nu se respecta conditia.
void ElimCond(TLG *aL, TFCond f, TFElib g)
{
	if (!aL || !f) {
		return;
	}
	TLG pre = NULL;
	TLG l = *aL;
	while (l) {
		if (f(l->info)) {
			if (!pre) {
				*aL = (*aL)->urm;
			} else {
				pre->urm = l->urm;
			}
			TLG aux = l;
			l = l->urm;
			g(aux->info);
			free(aux);
			continue;
		}
		pre = l;
		l = l->urm;
	}
}

// Pentru subpunctul b.).
void ElimInt(void *info)
{
	free(info);
}

int EsteImpar(void *info)
{
	int x = *(int *)info;
	if (x % 2) {
		return 1;
	}
	return 0;
}

int main(void)
{
	TLG L = NULL; // Stiu ca nu este corect aici, dar nu asta conteaza.
	ElimCond(&L, EsteImpar, ElimInt);
	return 0;
}

