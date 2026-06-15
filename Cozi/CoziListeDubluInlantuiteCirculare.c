// Cozi implementate cu liste dublu inlantuite circulare, fara santinela.
// Coding Style ca la curs, stiu...
// Codul este scris de mana integral de mine, asemanator cu ce e la curs.
// Partea de Checker este generata complet cu AI.
// Nu am verificat checker-ul, functiile sunt asemanatoare cu cele de curs.

#include <stdio.h>
#include <stdlib.h>

typedef struct celula2 {
	int info;
	struct celula2 *pre, *urm;
}TCelula2, *TLista2;

typedef struct {
	TLista2 sf; // Puteam sa aleg "inc" in loc de "sf".
}TCoada;

TCelula2 *AlocCelula2(int info)
{
	TCelula2 *aux = malloc(sizeof(TCelula2));
	if (!aux) {
		return NULL;
	}
	aux->info = info;
	aux->pre = aux;
	aux->urm = aux;
	return aux;
}

TCoada *InitQ(void)
{
	TCoada *c = malloc(sizeof(TCoada));
	if (!c) {
		return NULL;
	}
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
	if (!c->sf) {
		c->sf = aux;
		return 0;
	}
	aux->pre = c->sf;
	aux->urm = c->sf->urm;
	c->sf->urm->pre = aux;
	c->sf->urm = aux;
	c->sf = aux;
	return 0;
}

int ExtrQ(TCoada *c, int *aX)
{
	if (!c || !aX || !c->sf) {
		return -1;
	}
	*aX = c->sf->urm->info;
	if (c->sf == c->sf->urm) {
		free(c->sf);
		c->sf = NULL;
		return 0;
	}
	TCelula2 *target = c->sf->urm;
	c->sf->urm = target->urm;
	target->urm->pre = c->sf;
	free(target);
	return 0;
}

// Checker generat cu AI.

int CheckIntegrity(TCoada *c)
{
    if (!c)
        return 0;

    if (!c->sf)
        return 1;

    TLista2 start = c->sf->urm;
    TLista2 p = start;

    int count = 0;

    do {
        if (!p)
            return 0;

        if (!p->urm)
            return 0;

        if (!p->pre)
            return 0;

        if (p->urm->pre != p)
            return 0;

        if (p->pre->urm != p)
            return 0;

        p = p->urm;
        count++;

        if (count > 100000)
            return 0;

    } while (p != start);

    return 1;
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
    printf("COADA - LISTA DUBLU CIRCULARA\n");
    printf("=====================================\n\n");

    TCoada *c = InitQ();

    CHECK(c != NULL,
          "InitQ aloca structura");

    CHECK(c->sf == NULL,
          "Coada initial vida");

    CHECK(CheckIntegrity(c),
          "Integritate coada vida");

    CHECK(InsQ(NULL, 10) == -1,
          "InsQ refuza coada NULL");

    CHECK(InsQ(c, 10) == 0,
          "Inserare primul element");

    CHECK(c->sf != NULL,
          "sf actualizat");

    CHECK(c->sf->info == 10,
          "Valoare corecta");

    CHECK(c->sf->urm == c->sf,
          "Ciclu element unic (urm)");

    CHECK(c->sf->pre == c->sf,
          "Ciclu element unic (pre)");

    CHECK(CheckIntegrity(c),
          "Integritate element unic");

    CHECK(InsQ(c, 20) == 0,
          "Inserare al doilea element");

    CHECK(InsQ(c, 30) == 0,
          "Inserare al treilea element");

    CHECK(InsQ(c, 40) == 0,
          "Inserare al patrulea element");

    CHECK(c->sf->info == 40,
          "sf pointeaza ultimul element");

    CHECK(c->sf->urm->info == 10,
          "inceputul este primul inserat");

    CHECK(CheckIntegrity(c),
          "Integritate dupa inserari");

    int x;

    CHECK(ExtrQ(NULL, &x) == -1,
          "ExtrQ refuza coada NULL");

    CHECK(ExtrQ(c, NULL) == -1,
          "ExtrQ refuza rezultat NULL");

    CHECK(ExtrQ(c, &x) == 0 && x == 10,
          "FIFO: extrage 10");

    CHECK(CheckIntegrity(c),
          "Integritate dupa extragere 10");

    CHECK(ExtrQ(c, &x) == 0 && x == 20,
          "FIFO: extrage 20");

    CHECK(CheckIntegrity(c),
          "Integritate dupa extragere 20");

    CHECK(ExtrQ(c, &x) == 0 && x == 30,
          "FIFO: extrage 30");

    CHECK(CheckIntegrity(c),
          "Integritate dupa extragere 30");

    CHECK(ExtrQ(c, &x) == 0 && x == 40,
          "FIFO: extrage 40");

    CHECK(c->sf == NULL,
          "Coada devine vida");

    CHECK(CheckIntegrity(c),
          "Integritate dupa golire");

    CHECK(ExtrQ(c, &x) == -1,
          "Extragere din coada vida");

    free(c);

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

