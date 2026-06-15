// First child, next sibling.
// Cod scris integral de mine, pana la partea de Checker.
// Partea de checker este scrisa complet cu AI.
// Nu am mai verificat checker-ul, functiie seamana cu cele de curs.
// Coding Style de curs, stiu...

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int info;
	struct node *left, *right;
} Node, *Tree;

Tree CreateNode(int info)
{
	Tree aux = malloc(sizeof(Node));
	if (!aux) {
		return NULL;
	}
	aux->info = info;
	aux->left = NULL;
	aux->right = NULL;
	return aux;
}

int AddChild(Tree parent, Tree child)
{
	if (!parent) {
		return -1;
	}
	if (!parent->left) {
		parent->left = child;
		return 0;
	}
	Tree aux = parent->left;
	while (aux->right) {
		aux = aux->right;
	}
	aux->right = child;
	return 0;
}

void Preorder(Tree root)
{
	if (!root) {
		return;
	}
	printf("%d\n", root->info);
	Preorder(root->left);
	Preorder(root->right);
}

#include <string.h>

// ---------------- Checker scris de AI ----------------

#define MAX_BUF 4096

static char g_buf[MAX_BUF];
static int g_len;

// Versiune de Preorder care scrie intr-un buffer, pentru verificare automata.
void PreorderBuf(Tree root)
{
	if (!root) {
		return;
	}
	int written = snprintf(g_buf + g_len, MAX_BUF - g_len, "%d ", root->info);
	if (written > 0 && g_len + written < MAX_BUF) {
		g_len += written;
	}
	PreorderBuf(root->left);
	PreorderBuf(root->right);
}

// Numara nodurile dintr-un arbore FCNS.
int CountNodes(Tree root)
{
	if (!root) {
		return 0;
	}
	return 1 + CountNodes(root->left) + CountNodes(root->right);
}

// Numara copiii directi ai unui nod (lantul de "right" de la "left").
int CountChildren(Tree parent)
{
	if (!parent || !parent->left) {
		return 0;
	}
	int cnt = 0;
	Tree aux = parent->left;
	while (aux) {
		cnt++;
		aux = aux->right;
	}
	return cnt;
}

// Elibereaza recursiv un arbore FCNS.
void FreeTree(Tree root)
{
	if (!root) {
		return;
	}
	FreeTree(root->left);
	FreeTree(root->right);
	free(root);
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
	printf("TEST ARBORE MULTICAI (FCNS)\n");
	printf("=====================================\n\n");

	/* CreateNode */

	Tree n = CreateNode(42);

	CHECK(n != NULL,
		  "CreateNode aloca memorie");

	CHECK(n &&
		  n->info == 42 &&
		  n->left == NULL &&
		  n->right == NULL,
		  "CreateNode initializeaza campurile corect");

	free(n);

	/* AddChild pe parinte NULL */

	Tree tmp = CreateNode(99);

	CHECK(AddChild(NULL, tmp) == -1,
		  "AddChild refuza parinte NULL");

	free(tmp);

	/* AddChild - primul copil */

	Tree root = CreateNode(1);
	Tree child1 = CreateNode(2);

	CHECK(AddChild(root, child1) == 0,
		  "AddChild adauga primul copil");

	CHECK(root->left == child1,
		  "Primul copil devine root->left");

	CHECK(child1->right == NULL,
		  "Primul copil nu are frate (right == NULL)");

	CHECK(CountChildren(root) == 1,
		  "Numarul de copii este 1 dupa primul AddChild");

	/* AddChild - copii multipli (lant de frati) */

	Tree child2 = CreateNode(3);
	Tree child3 = CreateNode(4);

	CHECK(AddChild(root, child2) == 0,
		  "AddChild adauga al doilea copil");

	CHECK(AddChild(root, child3) == 0,
		  "AddChild adauga al treilea copil");

	CHECK(root->left == child1 &&
		  child1->right == child2 &&
		  child2->right == child3 &&
		  child3->right == NULL,
		  "Lantul de frati (right) este corect format");

	CHECK(CountChildren(root) == 3,
		  "Numarul de copii este 3 dupa cele 3 AddChild");

	/* Adaugare copil pe al doilea nivel (nepot) */

	Tree grandchild = CreateNode(5);

	CHECK(AddChild(child1, grandchild) == 0,
		  "AddChild adauga un nepot (copil al lui child1)");

	CHECK(child1->left == grandchild,
		  "Nepotul devine child1->left");

	CHECK(CountChildren(child1) == 1,
		  "child1 are exact 1 copil");

	CHECK(CountChildren(root) == 3,
		  "root inca are 3 copii (nepotul nu modifica numarul copiilor lui root)");

	/* CountNodes */

	CHECK(CountNodes(root) == 5,
		  "CountNodes numara corect toate cele 5 noduri din arbore");

	CHECK(CountNodes(NULL) == 0,
		  "CountNodes pe arbore vid returneaza 0");

	/* Preorder - verificare automata prin buffer */

	g_len = 0;
	g_buf[0] = '\0';

	PreorderBuf(root);

	// Arborele este:
	//   1
	//   |- 2
	//   |   |- 5
	//   |- 3
	//   |- 4
	// Preordine: 1 2 5 3 4

	CHECK(strcmp(g_buf, "1 2 5 3 4 ") == 0,
		  "Preorder produce secventa corecta 1 2 5 3 4");

	/* Preorder pe arbore vid nu trebuie sa scrie nimic */

	g_len = 0;
	g_buf[0] = '\0';

	PreorderBuf(NULL);

	CHECK(g_buf[0] == '\0',
		  "Preorder pe arbore NULL nu produce output");

	/* Afisare reala cu Preorder (cea din enunt) */

	printf("\nAfisare Preorder (functia originala):\n");
	Preorder(root);
	printf("\n");

	/* Eliberare */

	FreeTree(root);

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

