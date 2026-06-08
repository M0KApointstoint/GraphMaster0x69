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

int main(void)
{
	printf("Hello, World!\n");
	return 0;
}

