// Coding Style asemanator cu cel de la curs, stiu...
// Cod scris de mana integral, pana la partea de checker.
// Partea de checker este scrisa complet cu AI.
// Nu am verificat checker-ul, functiile seamana cu cele de la curs.

#include <stdio.h>
#include <stdlib.h>

typedef struct celulag {
	void *info;
	struct celulag *urm;
}TCelulaG, *TListaG;

typedef void (*TFDistr)(void *);

TCelulaG *AlocCelulaG(void *info)
{
	TCelulaG *aux = malloc(sizeof(TCelulaG));
	if (!aux) {
		return NULL;
	}
	aux->info = info;
	aux->urm = NULL;
	return aux;
}

void DistrugeLG(TListaG *aL, TFDistr f)
{
	if (!aL || !*aL) {
		return;
	}
	while (*aL) {
		TListaG target = *aL;
		*aL = (*aL)->urm;
		f(target->info);
		free(target);
	}
}

typedef int (*TFHash)(void *);

typedef void (*TFAfis)(void *);

typedef int (*TFCmp)(void *, void *);

typedef struct {
	int m;
	TFHash fh;
	TListaG *v;
}TH;

TH *InitTH(int m, TFHash fh)
{
	if (!fh) {
		return NULL;
	}
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

void AfisareTH(TH *h, TFAfis f)
{
	if (!h || !f) {
		return;
	}
	for (int i = 0; i < h->m; ++i) {
		printf("[%d]: ", i);
		TListaG l = h->v[i];
		while (l) {
			f(l->info);
			l = l->urm;
		}
		printf("\n");
	}
}

void *ExistaTH(TH *h, void *x, TFCmp f)
{
	if (!h || !x || !f) {
		return NULL;
	}
	int i = h->fh(x);
	TListaG l = h->v[i];
	while (l) {
		if (!f(l->info, x)) {
			return l->info;
		}
		l = l->urm;
	}
	return NULL;
}

int InsTH(TH *h, void *x, TFCmp f)
{
	if (!h || !x || !f) {
		return -1;
	}
	int i = h->fh(x);
	TListaG l = h->v[i];
	while (l) {
		if (!f(l->info, x)) {
			return 1;
		}
		l = l->urm;
	}
	TCelulaG *aux = AlocCelulaG(x);
	if (!aux) {
		return -1;
	}
	aux->urm = h->v[i];
	h->v[i] = aux;
	return 0;
}

void DistrugeTH(TH **aH, TFDistr f)
{
	if (!aH || !*aH) {
		return;
	}
	TH *h = *aH;
	for (int i = 0; i < h->m; ++i) {
		if (h->v[i]) { // Nu este necesar, dar siguranta este siguranta.
			DistrugeLG(h->v + i, f);
		}
	}
	free(h->v);
	free(h);
	*aH = NULL;
}

#include <string.h>

// Culori pentru terminal
#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"

// ============================================================================
//               PARTEA DE CHECKER (DATE DE TEST)
// ============================================================================

// --- TEST 1: Tipul de date INT ---
int hash_int(void *key) {
	return (*(int *)key) % 5; // M = 5 buckets
}

int cmp_int(void *a, void *b) {
	return (*(int *)a) - (*(int *)b);
}

void distr_int(void *a) {
	free(a);
}

// --- TEST 2: Tipul de date STRUCT (Student) ---
typedef struct {
	char nume[50];
	int nota;
} TStudent;

int hash_stud(void *key) {
	TStudent *s = (TStudent *)key;
	int sum = 0;
	for (int i = 0; s->nume[i] != '\0'; i++) {
		sum += s->nume[i];
	}
	return sum % 3; // M = 3 buckets
}

int cmp_stud(void *a, void *b) {
	return strcmp(((TStudent *)a)->nume, ((TStudent *)b)->nume);
}

void distr_stud(void *a) {
	free(a);
}

// --- Utilitare Testare ---
void print_verdict(const char *test_name, int condition) {
	if (condition) {
		printf("[ " GREEN "PASSED" RESET " ] %s\n", test_name);
	} else {
		printf("[ " RED "FAILED" RESET " ] %s\n", test_name);
	}
}

// --- Main Checker ---
int main(void)
{
	printf(YELLOW "=== STARTING HASH TABLE CHECKER ===\n\n" RESET);

	// ------------------------------------------------------------------------
	// SECTIUNEA 1: Testare cu Intregi (Genericitate primitiva & Coliziuni)
	// ------------------------------------------------------------------------
	printf("--- Rulare Teste Integers (M = 5) ---\n");
	TH *h_int = InitTH(5, hash_int);
	print_verdict("Initializare tabela hash (Int)", h_int != NULL);

	int *v1 = malloc(sizeof(int)); *v1 = 10; // Hash: 10 % 5 = 0
	int *v2 = malloc(sizeof(int)); *v2 = 5;  // Hash: 5 % 5 = 0 -> Coliziune!
	int *v3 = malloc(sizeof(int)); *v3 = 12; // Hash: 12 % 5 = 2
	int *v4 = malloc(sizeof(int)); *v4 = 10; // Duplicat pentru v1

	print_verdict("Inserare element normal (10)", InsTH(h_int, v1, cmp_int) == 0);
	print_verdict("Inserare element coliziune pe bucket 0 (5)", InsTH(h_int, v2, cmp_int) == 0);
	print_verdict("Inserare element pe bucket diferit (12)", InsTH(h_int, v3, cmp_int) == 0);

	int res_dup = InsTH(h_int, v4, cmp_int);
	print_verdict("Inserare element duplicat (trebuie sa intoarca 1)", res_dup == 1);
	if (res_dup == 1) free(v4); // Nu s-a inserat, eliberam copia

	// Test Cautare (ExistaTH)
	int cautat_exista = 5;
	int cautat_nu_exista = 99;
	print_verdict("Cautare element existent (5)", ExistaTH(h_int, &cautat_exista, cmp_int) != NULL);
	print_verdict("Cautare element inexistent (99)", ExistaTH(h_int, &cautat_nu_exista, cmp_int) == NULL);

	DistrugeTH(&h_int, distr_int);
	print_verdict("Distrugere tabela si eliberare (Int)", h_int == NULL);

	printf("\n");

	// ------------------------------------------------------------------------
	// SECTIUNEA 2: Testare cu Structuri Complexe (Studenti)
	// ------------------------------------------------------------------------
	printf("--- Rulare Teste Structs/Students (M = 3) ---\n");
	TH *h_stud = InitTH(3, hash_stud);
	print_verdict("Initializare tabela hash (Studenti)", h_stud != NULL);

	TStudent *s1 = malloc(sizeof(TStudent)); strcpy(s1->nume, "Alice"); s1->nota = 10;
	TStudent *s2 = malloc(sizeof(TStudent)); strcpy(s2->nume, "Bob");   s2->nota = 9;

	print_verdict("Inserare Student 1 (Alice)", InsTH(h_stud, s1, cmp_stud) == 0);
	print_verdict("Inserare Student 2 (Bob)", InsTH(h_stud, s2, cmp_stud) == 0);

	// Verificare cautare structura
	TStudent criteriu_cautare;
	strcpy(criteriu_cautare.nume, "Alice");
	TStudent *gasit = (TStudent*)ExistaTH(h_stud, &criteriu_cautare, cmp_stud);
	print_verdict("Cautare Student dupa nume (Alice)", gasit != NULL && gasit->nota == 10);

	DistrugeTH(&h_stud, distr_stud);
	print_verdict("Distrugere tabela si eliberare (Studenti)", h_stud == NULL);

	printf(YELLOW "\n=== FINISHED HASH TABLE CHECKER ===\n" RESET);
	return 0;
}

