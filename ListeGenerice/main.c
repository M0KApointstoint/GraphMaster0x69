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

void AfisareLG(TLG l, void(*AfisareElem)(void *))
{
	if (!l || !AfisareElem) {
		return;
	}
	printf("Lista: [");
	while (l) {
		AfisareElem(l->info);
		l = l->urm;
	}
	printf("]\n");
}

int main(void)
{
	printf("Hello, World!\n");
	return 0;
}

