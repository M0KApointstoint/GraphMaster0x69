// Coding Style asemanator cu cel de la curs, stiu...
// Cod scris de mana integral.

#include <stdio.h>
#include <stdlib.h>

typedef struct celulag {
	void *info;
	struct celulag *urm;
}TCelulaG, *TListaG;

TCelulaG *AlocCelulaG(void *info)
{
	TCelulaG *aux = malloc(sizeof(TCelulaG));
	if (!aux) {
		return NULL;
	}
	aux->info = info;
	aux->urm = NULL;
	return aux;
}

typedef int (*TFHash)(void *);

typedef void (*TFAfis)(void *);

typedef int (*TFCmp)(void *, void *);

typedef struct {
	int m;
	TFHash fh;
	TListaG *v;
}TH;

TH *InitTH(int m, TFHash fh)
{
	if (!fh) {
		return NULL;
	}
	TH *h = malloc(sizeof(TH));
	if (!h) {
		return NULL;
	}
	h->v = calloc(m, sizeof(TListaG));
	if (!h->v) {
		free(h);
		return NULL;
	}
	h->m = m;
	h->fh = fh;
	return h;
}

void AfisareTH(TH *h, TFAfis f)
{
	if (!h || !f) {
		return;
	}
	for (int i = 0; i < h->m; ++i) {
		printf("[%d]: ", i);
		TListaG l = h->v[i];
		while (l) {
			f(l->info);
			l = l->urm;
		}
		printf("\n");
	}
}

void *ExistaTH(TH *h, void *x, TFCmp f)
{
	if (!h || !x || !f) {
		return NULL;
	}
	int i = h->fh(x);
	TListaG l = h->v[i];
	while (l) {
		if (!f(l->info, x)) {
			return l->info;
		}
		l = l->urm;
	}
	return NULL;
}

int InsTH(TH *h, void *x, TFCmp f)
{
	if (!h || !x || !f) {
		return -1;
	}
	TCelulaG *aux = AlocCelulaG(x);
	if (!aux) {
		return -1;
	}
	int i = h->fh(x);
	TListaG l = h->v[i];
	while (l) {
		if (!f(l->info, x)) {
			return 1;
		}
		l = l->urm;
	}
	aux->urm = h->v[i];
	h->v[i] = aux;
	return 0;
}

int main(void)
{
	printf("Hello, world!\n");
	return 0;
}

