#include <stdio.h>
#include <stdlib.h>

typedef struct celula2 {
	int info;
	struct celula *pre, *urm;
}TCelula2, *TLista2;

typedef struct {
	TLista2 sf; // Puteam sa aleg "inc" in loc de "sf".
}TCoada;

int main(void)
{
	return 0;
}

