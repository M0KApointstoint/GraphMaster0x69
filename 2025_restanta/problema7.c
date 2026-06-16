#include <stdlib.h>

typedef struct celulag {
	void *info;
	struct celulag *urm;
}TCelulaG, *TLG;

// Rezolvare.
// Subpunctul a.)
// Returneaza 0 daca nu se respecta conditia.
typedef int (*TFCond)(void *);

typedef void *(*TFCopie)(void *);

typedef void (*TFDistr)(void *);

TLG AlocCelulaG(void *info);

void DistrugeL(TLG *aL, TFDistr f);

TLG Constr(TLG src, TFCond f, TFCopie g, TFDistr h)
{
	TLG dst = NULL;
	if (!src || !f || !g || !h) {
		return dst;
	}
	TLG CapDst = dst;
	while (src) {
		if (f(src->info)) {
			void *InfoCopie = g(src->info);
			if (!InfoCopie) {
				DistrugeL(&CapDst, h);
				return CapDst; // Adica tot NULL.
			}
			TLG aux = AlocCelulaG(InfoCopie);
			if (!aux) {
				h(InfoCopie);
				DistrugeL(&CapDst, h);
				return CapDst; // Adica tot NULL.
			}
			if (!dst) {
				dst = aux;
				CapDst = aux;
			} else {
				dst->urm = aux;
				dst = aux;
			}
		}
		src = src->urm;
	}
	return CapDst;
}

// Subpunctul b.)

int EsteImpar(void *x)
{
	int n = *(int *)x;
	if (n % 2) {
		return 1;
	}
	return 0;
}

void *CopieInt(void *x)
{
	void *copie = malloc(sizeof(int));
	if (!copie) {
		return NULL;
	}
	*(int *)copie = *(int *)x;
	return copie;
}

void DistrugeInt(void *x)
{
	free(x);
}


int main(void)
{
	TLG l = NULL; // Nu este corect, dar nu asta conteaza.
	TLG copie = Constr(l, EsteImpar, CopieInt, DistrugeInt);
	// De aici verificari si tot asa.
	// Pentru subpunctul c.), AI.
	return 0;
}

