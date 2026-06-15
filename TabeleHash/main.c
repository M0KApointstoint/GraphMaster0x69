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
}THash;

int main(void)
{
	printf("Hello, world!\n");
	return 0;
}

