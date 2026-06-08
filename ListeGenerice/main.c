#include <stdio.h>
#include <stdlib.h>

typedef struct celulag{
	void *info;
	struct celulag *urm;
}TCelulaG, *TLG;

TLG AlocCelulaG(void *info)
{
	if (!info) {
		return NULL;
	}
	TLG aux = malloc(sizeof(TCelulaG));
	if (!aux) {
		return NULL;
	}
	aux->info = info;
	aux->urm = NULL;
	return aux;
}

void AfisareLG(TLG l, void(*AfisareInfo)(void *))
{
	if (!l || !AfisareInfo) {
		return;
	}
	printf("Lista: [ ");
	while (l) {
		AfisareInfo(l->info);
		l = l->urm;
	}
	printf("]\n");
}

void AfisareInt(void *info)
{
	printf("%d ", *(int *)info);
}

// Inserare la inceput de lista.
int InserareLG(TLG *aL, void *info)
{
	if (!aL || !info) {
		return -1;
	}
	TLG aux = AlocCelulaG(info);
	if (!aux) {
		return -1;
	}
	// Partea asta este redundanta.
	if (!*aL) {
		*aL = aux;
		return 0;
	}
	// Pana aici.
	aux->urm = *aL;
	*aL = aux;
	return 0;
}

void DistrugeLG(TLG *aL, void (*DistrugeInfo)(void *))
{
	if (!aL || !*aL || !DistrugeInfo) {
		return;
	}
	while (*aL) {
		TLG aux = *aL;
		*aL = (*aL)->urm;
		DistrugeInfo(aux->info);
		free(aux);
	}
}

void DistrugeInt(void *info)
{
	free(info);
}

int main(void)
{
	printf("Hello, World!\n");
	return 0;
}

