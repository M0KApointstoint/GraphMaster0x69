// Coding Style asemanator cu cel de la curs, stiu...
// Cod scris de mana integral.

#include <stdio.h>
#include <stdlib.h>

typedef struct celulag {
	void *info;
	struct celulag *urm;
}TCelulaG, *TListaG;

typedef int (*TFHash)(void *);

typedef struct {
	int m;
	TFHash fh;
	TListaG *v;
}TH;

TH *InitTH(int m, TFHash fh)
{
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

int main(void)
{
	printf("Hello, world!\n");
	return 0;
}

