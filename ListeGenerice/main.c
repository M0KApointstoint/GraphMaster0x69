// Coding Style similar cu cel de la curs, stiu...
// Codul pana la main.c este scris integral de mine.
// Codul de checker este scris integral cu Claude Sonnet 4.6.
// Nu am verificat checker-ul in detaliu, functiile seamana cu cele de la curs.

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


// Functia de comparare trebuie sa returneze 1 pentru egalitate.
int CautaLG(TLG l, void *ref, int (*FCmp)(void *, void *))
{
	if (!l || !FCmp) {
		return 0;
	}
	while (l) {
		if (FCmp(l->info, ref)) {
			return 1;
		}
		l = l->urm;
	}
	return 0;
}

int ComparaInt(void *a, void *b)
{
	if (*(int *)a == *(int *)b) {
		return 1;
	}
	return 0;
}

/* ============================================================
   CHECKER - Liste Generice
   Copiaza tot acest bloc si inlocuieste main()-ul tau.
   Scorul final e afisat la sfarsit.
   ============================================================ */

/* ---------- utilitare checker ---------- */
static int _passed = 0;
static int _failed = 0;

#define CHECK(descriere, conditie)                              \
    do {                                                        \
        if (conditie) {                                         \
            printf("  [PASS] %s\n", descriere);                 \
            _passed++;                                          \
        } else {                                                \
            printf("  [FAIL] %s  (linia %d)\n", descriere, __LINE__); \
            _failed++;                                          \
        }                                                       \
    } while (0)

/* ---------- helper: aloca un int pe heap ---------- */
static int *mkint(int val)
{
    int *p = malloc(sizeof(int));
    *p = val;
    return p;
}

/* ============================================================
   TEST 1 – AlocCelulaG
   ============================================================ */
static void test_aloc(void)
{
    printf("\n[TEST 1] AlocCelulaG\n");

    int *v = mkint(42);
    TLG c = AlocCelulaG(v);

    CHECK("celula alocata (non-NULL)",      c != NULL);
    CHECK("info pointeaza corect",          c != NULL && c->info == v);
    CHECK("urm este NULL dupa alocare",     c != NULL && c->urm == NULL);
    CHECK("valoarea info este corecta",     c != NULL && *(int *)c->info == 42);

    /* info NULL => returneaza NULL */
    TLG c2 = AlocCelulaG(NULL);
    CHECK("info=NULL => returneaza NULL",   c2 == NULL);

    /* curatam manual (info-ul NU il eliberam, il vom refolosi) */
    free(c);
    free(v);
}

/* ============================================================
   TEST 2 – InserareLG
   ============================================================ */
static void test_inserare(void)
{
    printf("\n[TEST 2] InserareLG\n");

    TLG l = NULL;

    /* inserare in lista vida */
    int ret = InserareLG(&l, mkint(10));
    CHECK("inserare in lista vida (ret=0)",      ret == 0);
    CHECK("lista non-NULL dupa prima inserare",  l != NULL);
    CHECK("primul element are valoarea 10",      l != NULL && *(int *)l->info == 10);

    /* inserare a doua oara -> noul nod devine capul listei */
    InserareLG(&l, mkint(20));
    CHECK("al doilea insert devine cap (val=20)", *(int *)l->info == 20);
    CHECK("vechiul cap e acum al doilea nod",     *(int *)l->urm->info == 10);

    /* inserare cu pointer NULL la lista */
    ret = InserareLG(NULL, mkint(99));
    CHECK("aL=NULL => returneaza -1",            ret == -1);

    /* inserare cu info NULL */
    ret = InserareLG(&l, NULL);
    CHECK("info=NULL => returneaza -1",          ret == -1);

    /* numaram nodurile: trebuie sa fie exact 2 */
    int cnt = 0;
    TLG tmp = l;
    while (tmp) { cnt++; tmp = tmp->urm; }
    CHECK("lista are exact 2 noduri dupa inserari valide", cnt == 2);

    DistrugeLG(&l, DistrugeInt);
}

/* ============================================================
   TEST 3 – CautaLG
   ============================================================ */
static void test_cauta(void)
{
    printf("\n[TEST 3] CautaLG\n");

    TLG l = NULL;
    InserareLG(&l, mkint(1));
    InserareLG(&l, mkint(2));
    InserareLG(&l, mkint(3));

    int ref_gasit   = 2;
    int ref_negasit = 99;

    CHECK("cauta element existent (2) => 1",      CautaLG(l, &ref_gasit,   ComparaInt) == 1);
    CHECK("cauta element inexistent (99) => 0",   CautaLG(l, &ref_negasit, ComparaInt) == 0);

    /* cauta primul si ultimul element */
    int prim = 3, ultim = 1;
    CHECK("cauta primul element (3) => 1",        CautaLG(l, &prim,  ComparaInt) == 1);
    CHECK("cauta ultimul element (1) => 1",       CautaLG(l, &ultim, ComparaInt) == 1);

    /* lista vida */
    CHECK("cauta in lista vida => 0",             CautaLG(NULL, &ref_gasit, ComparaInt) == 0);

    /* FCmp NULL */
    CHECK("FCmp=NULL => returneaza 0",            CautaLG(l, &ref_gasit, NULL) == 0);

    DistrugeLG(&l, DistrugeInt);
}

/* ============================================================
   TEST 4 – DistrugeLG
   ============================================================ */
static void test_distruge(void)
{
    printf("\n[TEST 4] DistrugeLG\n");

    TLG l = NULL;
    InserareLG(&l, mkint(5));
    InserareLG(&l, mkint(6));
    InserareLG(&l, mkint(7));

    DistrugeLG(&l, DistrugeInt);
    CHECK("lista devine NULL dupa distrugere",   l == NULL);

    /* distruge lista deja vida - nu trebuie sa crape */
    DistrugeLG(&l, DistrugeInt);
    CHECK("distruge lista vida (fara crash)",    l == NULL);

    /* aL=NULL - nu trebuie sa crape */
    DistrugeLG(NULL, DistrugeInt);
    CHECK("aL=NULL (fara crash)",               1 /* daca am ajuns aici, ok */);

    /* DistrugeInfo=NULL - nu trebuie sa crape */
    TLG l2 = NULL;
    InserareLG(&l2, mkint(8));
    DistrugeLG(&l2, NULL);
    /* l2 nu a fost eliberat (functia face return devreme), curatam manual */
    free(l2->info);
    free(l2);
    CHECK("DistrugeInfo=NULL (fara crash)",     1);
}

/* ============================================================
   TEST 5 – AfisareLG (test vizual)
   ============================================================ */
static void test_afisare(void)
{
    printf("\n[TEST 5] AfisareLG (verificare vizuala)\n");

    TLG l = NULL;
    InserareLG(&l, mkint(10));
    InserareLG(&l, mkint(20));
    InserareLG(&l, mkint(30));

    printf("  Asteptat:  Lista: [ 30 20 10 ]\n");
    printf("  Obtinut:   ");
    AfisareLG(l, AfisareInt);

    /* afisare lista vida - nu trebuie sa crape */
    printf("  Afisare lista vida (fara output): ");
    AfisareLG(NULL, AfisareInt);
    printf("(ok)\n");

    CHECK("AfisareLG ruleaza fara crash", 1);

    DistrugeLG(&l, DistrugeInt);
}

/* ============================================================
   TEST 6 – Inserare multipla + cautare extensiva
   ============================================================ */
static void test_integrat(void)
{
    printf("\n[TEST 6] Test integrat (100 elemente)\n");

    TLG l = NULL;
    int N = 100;

    for (int i = 1; i <= N; i++) {
        InserareLG(&l, mkint(i));
    }

    /* numara nodurile */
    int cnt = 0;
    TLG tmp = l;
    while (tmp) { cnt++; tmp = tmp->urm; }
    CHECK("100 inserari => 100 noduri", cnt == N);

    /* cauta fiecare element */
    int ok = 1;
    for (int i = 1; i <= N; i++) {
        if (!CautaLG(l, &i, ComparaInt)) { ok = 0; break; }
    }
    CHECK("fiecare element din 1..100 se gaseste", ok);

    /* element in afara intervalului */
    int absent = 101;
    CHECK("101 nu se gaseste", CautaLG(l, &absent, ComparaInt) == 0);

    DistrugeLG(&l, DistrugeInt);
    CHECK("distrugere dupa 100 inserari => NULL", l == NULL);
}

/* ============================================================
   MAIN
   ============================================================ */
int main(void)
{
    printf("========================================\n");
    printf("  CHECKER - Liste Generice\n");
    printf("========================================\n");

    test_aloc();
    test_inserare();
    test_cauta();
    test_distruge();
    test_afisare();
    test_integrat();

    printf("\n========================================\n");
    printf("  REZULTAT: %d/%d teste trecute\n", _passed, _passed + _failed);
    if (_failed == 0)
        printf("  Felicitari! Toate testele au trecut.\n");
    else
        printf("  %d teste au picat. Verifica marcajele [FAIL].\n", _failed);
    printf("========================================\n");

    return _failed == 0 ? 0 : 1;
}

