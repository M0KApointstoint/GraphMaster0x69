// Cozi implementate cu liste dublu inlantuite.
// Coding Style asemanator cu cel de la curs, stiu...
// Codul este scris de mana integral, pana la partea de checker.
// Partea de checker este scris integral cu AI.
// Nu am verificat checker-ul, functiile sunt asemanatoare cu cele de curs.

#include <stdio.h>
#include <stdlib.h>

typedef struct celula2 {
	int info;
	struct celula2 *pre, *urm;
}TCelula2, *TLista2;

TCelula2 *AlocCelula2(int info)
{
	TCelula2 *aux = malloc(sizeof(TCelula2));
	if (!aux) {
		return NULL;
	}
	aux->info = info;
	aux->pre = NULL;
	aux->urm = NULL;
	return aux;
}

void DistrugeL2(TLista2 *aL)
{
	if (!aL || !*aL) {
		return;
	}
	while (*aL) {
		TLista2 target = *aL;
		*aL = target->urm;
		free(target);
	}
}

typedef struct {
	TLista2 inc, sf;
}TCoada;

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
	TCelula2 *aux = AlocCelula2(info);
	if (!aux) {
		return -1;
	}
	if (!c->inc) {
		c->inc = aux;
		c->sf = aux;
		return 0;
	}
	aux->pre = c->sf;
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
	TCelula2 *target = c->inc;
	c->inc = target->urm;
	free(target);
	c->inc->pre = NULL;
	return 0;
}

void ResetQ(TCoada *c)
{
	if (!c || !c->inc) {
		return;
	}
	DistrugeL2(&c->inc);
	c->inc = NULL; // For safety.
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

// Checker generat complet cu AI.

int CheckIntegrity(TCoada *c)
{
    if (!c)
        return 0;

    if (!c->inc && !c->sf)
        return 1;

    if (!c->inc || !c->sf)
        return 0;

    if (c->inc->pre != NULL)
        return 0;

    if (c->sf->urm != NULL)
        return 0;

    int cnt_forward = 0;
    int cnt_backward = 0;

    TLista2 p = c->inc;
    TLista2 last = NULL;

    while (p) {
        if (p->urm && p->urm->pre != p)
            return 0;

        last = p;
        p = p->urm;
        cnt_forward++;

        if (cnt_forward > 100000)
            return 0;
    }

    if (last != c->sf)
        return 0;

    p = c->sf;

    while (p) {
        if (p->pre && p->pre->urm != p)
            return 0;

        p = p->pre;
        cnt_backward++;

        if (cnt_backward > 100000)
            return 0;
    }

    return cnt_forward == cnt_backward;
}

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
    printf("TEST COADA - LISTA DUBLU INLANTUITA\n");
    printf("=====================================\n\n");

    /* AlocCelula2 */

    TCelula2 *cel = AlocCelula2(123);

    CHECK(cel != NULL,
          "AlocCelula2 aloca memorie");

    CHECK(cel &&
          cel->info == 123 &&
          cel->pre == NULL &&
          cel->urm == NULL,
          "AlocCelula2 initializeaza campurile");

    free(cel);

    /* InitQ */

    TCoada *c = InitQ();

    CHECK(c != NULL,
          "InitQ aloca structura");

    CHECK(c &&
          c->inc == NULL &&
          c->sf == NULL,
          "InitQ initializeaza coada vida");

    CHECK(CheckIntegrity(c),
          "Integritate coada vida");

    /* InsQ invalid */

    CHECK(InsQ(NULL, 10) == -1,
          "InsQ refuza coada NULL");

    /* Prima inserare */

    CHECK(InsQ(c, 10) == 0,
          "Inserare primul element");

    CHECK(c->inc == c->sf,
          "Primul element: inc == sf");

    CHECK(c->inc->info == 10,
          "Valoarea primului element");

    CHECK(c->inc->pre == NULL,
          "Primul element are pre NULL");

    CHECK(c->sf->urm == NULL,
          "Ultimul element are urm NULL");

    CHECK(CheckIntegrity(c),
          "Integritate dupa prima inserare");

    /* Inserari multiple */

    CHECK(InsQ(c, 20) == 0,
          "Inserare al doilea element");

    CHECK(InsQ(c, 30) == 0,
          "Inserare al treilea element");

    CHECK(c->inc->info == 10,
          "inc ramane primul element");

    CHECK(c->sf->info == 30,
          "sf devine ultimul element");

    CHECK(c->sf->pre->info == 20,
          "Legatura pre este corecta");

    CHECK(CheckIntegrity(c),
          "Integritate dupa inserari multiple");

    /* ExtrQ invalid */

    int x;

    CHECK(ExtrQ(NULL, &x) == -1,
          "ExtrQ refuza coada NULL");

    CHECK(ExtrQ(c, NULL) == -1,
          "ExtrQ refuza parametru NULL");

    /* FIFO */

    CHECK(ExtrQ(c, &x) == 0 && x == 10,
          "FIFO: extrage 10");

    CHECK(CheckIntegrity(c),
          "Integritate dupa extragere 10");

    CHECK(c->inc->pre == NULL,
          "Noul inceput are pre NULL");

    CHECK(ExtrQ(c, &x) == 0 && x == 20,
          "FIFO: extrage 20");

    CHECK(CheckIntegrity(c),
          "Integritate dupa extragere 20");

    CHECK(ExtrQ(c, &x) == 0 && x == 30,
          "FIFO: extrage 30");

    CHECK(c->inc == NULL && c->sf == NULL,
          "Coada devine vida");

    CHECK(CheckIntegrity(c),
          "Integritate dupa golire");

    /* Extragere din coada vida */

    CHECK(ExtrQ(c, &x) == -1,
          "Extragere din coada vida");

    /* Element unic */

    CHECK(InsQ(c, 777) == 0,
          "Inserare element unic");

    CHECK(CheckIntegrity(c),
          "Integritate element unic");

    CHECK(ExtrQ(c, &x) == 0 && x == 777,
          "Extragere element unic");

    CHECK(c->inc == NULL &&
          c->sf == NULL,
          "Coada vida dupa element unic");

    /* ResetQ */

    InsQ(c, 1);
    InsQ(c, 2);
    InsQ(c, 3);
    InsQ(c, 4);
    InsQ(c, 5);

    CHECK(CheckIntegrity(c),
          "Integritate inainte de ResetQ");

    ResetQ(c);

    CHECK(c->inc == NULL &&
          c->sf == NULL,
          "ResetQ goleste coada");

    CHECK(CheckIntegrity(c),
          "Integritate dupa ResetQ");

    /* DistrugeL2 */

    TLista2 L = AlocCelula2(1);

    L->urm = AlocCelula2(2);
    L->urm->pre = L;

    L->urm->urm = AlocCelula2(3);
    L->urm->urm->pre = L->urm;

    DistrugeL2(&L);

    CHECK(L == NULL,
          "DistrugeL2 seteaza lista la NULL");

    /* DistrugeQ */

    InsQ(c, 100);
    InsQ(c, 200);

    DistrugeQ(&c);

    CHECK(c == NULL,
          "DistrugeQ seteaza pointerul la NULL");

    /* DistrugeQ(NULL) */

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
        printf("\nEXISTA TESTE PICATE\n");

    return failed ? 1 : 0;
}

