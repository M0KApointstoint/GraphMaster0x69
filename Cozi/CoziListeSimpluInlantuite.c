// Implementare structura de coada cu liste simplu inlantuite.
// Coding Style asemanator cu cel de curs, stiu...
// Codul este scris de mana pana la functia main de checker, scrisa full AI.
// Nu am verificat checker-ul integral, functiile seamana cu cele de la curs.

#include <stdio.h>
#include <stdlib.h>

typedef struct celula {
	int info;
	struct celula *urm;
}TCelula, *TLista;

typedef struct coada {
	TLista inc, sf;
}TCoada;

TCelula *AlocCelula(int info)
{
	TCelula *aux = malloc(sizeof(TCelula));
	if (!aux) {
		return NULL;
	}
	aux->info = info;
	aux->urm = NULL;
	return aux;
}

void DistrugeLista(TLista *aL)
{
	if (!aL || !*aL) {
		return;
	}
	TLista l = *aL;
	while (l) {
		TLista target = l;
		l = l->urm;
		free(target);
	}
	*aL = NULL;
}

TCoada *InitQ(void)
{
	TCoada *c = malloc(sizeof(TCoada));
	if (!c) {
		return NULL;
	}
	c->inc = NULL;
	c->sf = NULL;
	return c;
}

int InsQ(TCoada *c, int info)
{
	if (!c) {
		return -1;
	}
	TCelula *aux = AlocCelula(info);
	if (!aux) {
		return -1;
	}
	if (!c->inc) {
		c->inc = aux;
		c->sf = aux;
		return 0;
	}
	c->sf->urm = aux;
	c->sf = aux;
	return 0;
}

int ExtrQ(TCoada *c, int *aX)
{
	if (!c || !aX || !c->inc) {
		return -1;
	}
	*aX = c->inc->info;
	if (c->inc == c->sf) {
		free(c->inc);
		c->inc = NULL;
		c->sf = NULL;
		return 0;
	}
	TCelula *target = c->inc;
	c->inc = target->urm;
	free(target);
	return 0;
}

void ResetQ(TCoada *c)
{
	// Verificari facute deja de functie, dar safety matters.
	if (!c || !c->inc) {
		return;
	}
	DistrugeLista(&c->inc);
	// La fel si aici.
	c->inc = NULL;
	c->sf = NULL;
}

void DistrugeQ(TCoada **aC)
{
	if (!aC || !*aC) {
		return;
	}
	ResetQ(*aC);
	free(*aC);
	*aC = NULL;
}

// Testing generat de ChatGPT!

int main(void)
{
	int passed = 0;
	int failed = 0;

#define PASS(msg) \
	do { \
		printf("[PASS] %s\n", msg); \
		passed++; \
	} while (0)

#define FAIL(msg) \
	do { \
		printf("[FAIL] %s (line %d)\n", msg, __LINE__); \
		failed++; \
	} while (0)

#define CHECK(cond, msg) \
	do { \
		if (cond) \
			PASS(msg); \
		else \
			FAIL(msg); \
	} while (0)

	printf("=====================================\n");
	printf("TESTARE IMPLEMENTARE COADA FIFO\n");
	printf("=====================================\n\n");

	/* InitQ */

	TCoada *c = InitQ();

	CHECK(c != NULL,
		  "InitQ aloca structura");

	CHECK(c && c->inc == NULL && c->sf == NULL,
		  "InitQ initializeaza coada vida");

	/* InsQ pe NULL */

	CHECK(InsQ(NULL, 10) == -1,
		  "InsQ refuza coada NULL");

	/* Inserare primul element */

	CHECK(InsQ(c, 10) == 0,
		  "InsQ insereaza primul element");

	CHECK(c->inc != NULL &&
		  c->sf != NULL &&
		  c->inc == c->sf &&
		  c->inc->info == 10,
		  "Primul element actualizeaza corect inc/sf");

	/* Inserari multiple */

	CHECK(InsQ(c, 20) == 0,
		  "InsQ insereaza al doilea element");

	CHECK(InsQ(c, 30) == 0,
		  "InsQ insereaza al treilea element");

	CHECK(c->inc->info == 10,
		  "Inserarea nu modifica inceputul cozii");

	CHECK(c->sf->info == 30,
		  "Inserarea actualizeaza sfarsitul cozii");

	/* ExtrQ parametri invalizi */

	int x;

	CHECK(ExtrQ(NULL, &x) == -1,
		  "ExtrQ refuza coada NULL");

	CHECK(ExtrQ(c, NULL) == -1,
		  "ExtrQ refuza rezultat NULL");

	/* FIFO */

	CHECK(ExtrQ(c, &x) == 0 && x == 10,
		  "FIFO: primul extras este 10");

	CHECK(ExtrQ(c, &x) == 0 && x == 20,
		  "FIFO: al doilea extras este 20");

	CHECK(ExtrQ(c, &x) == 0 && x == 30,
		  "FIFO: al treilea extras este 30");

	CHECK(c->inc == NULL && c->sf == NULL,
		  "Coada devine vida dupa extragerea tuturor elementelor");

	/* Extragere din coada vida */

	CHECK(ExtrQ(c, &x) == -1,
		  "ExtrQ refuza extragerea din coada vida");

	/* Test un singur element */

	CHECK(InsQ(c, 777) == 0,
		  "Inserare element unic");

	CHECK(ExtrQ(c, &x) == 0 && x == 777,
		  "Extragere element unic");

	CHECK(c->inc == NULL && c->sf == NULL,
		  "inc si sf devin NULL dupa ultimul element");

	/* ResetQ */

	InsQ(c, 1);
	InsQ(c, 2);
	InsQ(c, 3);

	ResetQ(c);

	CHECK(c->inc == NULL && c->sf == NULL,
		  "ResetQ goleste coada");

	CHECK(ExtrQ(c, &x) == -1,
		  "Dupa ResetQ coada este vida");

	/* ResetQ pe coada vida */

	ResetQ(c);

	CHECK(c->inc == NULL && c->sf == NULL,
		  "ResetQ pe coada vida nu produce efecte adverse");

	/* DistrugeLista */

	TLista L = NULL;

	CHECK(AlocCelula(1) != NULL,
		  "AlocCelula aloca memorie");

	L = AlocCelula(100);
	L->urm = AlocCelula(200);
	L->urm->urm = AlocCelula(300);

	DistrugeLista(&L);

	CHECK(L == NULL,
		  "DistrugeLista seteaza lista la NULL");

	/* DistrugeQ */

	InsQ(c, 10);
	InsQ(c, 20);

	DistrugeQ(&c);

	CHECK(c == NULL,
		  "DistrugeQ elibereaza si seteaza pointerul la NULL");

	/* DistrugeQ pe NULL */

	DistrugeQ(NULL);

	PASS("DistrugeQ(NULL) nu produce crash");

	printf("\n=====================================\n");
	printf("REZULTAT FINAL\n");
	printf("=====================================\n");
	printf("PASS : %d\n", passed);
	printf("FAIL : %d\n", failed);

	if (failed == 0)
		printf("\nTOATE TESTELE AU TRECUT\n");
	else
		printf("\nEXISTA TESTE PICAte\n");

	return failed ? 1 : 0;
}

