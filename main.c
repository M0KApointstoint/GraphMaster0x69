#include <stdio.h>
#include "liste_simplu_inlantuite.h"
#include "grafuri.h"

TGraf *CitireGraf(FILE *f)
{
	if (!f) {
		return NULL;
	}
	int n = 0;
	fscanf(f, "%d", &n);
	TGraf *g = InitGraf(n);
	if (!g) {
		return NULL;
	}
	int x = 0;
	int y = 0;
	while (fscanf(f, "%d %d", &x, &y) == 2) {
		if (InserareArc(g, x, y) == -1) {
			DistrugeGraf(&g);
			return NULL;
		}
	}
	return g;
}

int main(void)
{
	FILE *f = fopen("graf.txt", "r");
	if (!f) {
		return -1;
	}
	TGraf *g = CitireGraf(f);
	if (!g) {
		fclose(f);
		return -1;
	}
	ParcurgereDFS(g, 1);
	DistrugeGraf(&g);
	fclose(f);
	return 0;
}

