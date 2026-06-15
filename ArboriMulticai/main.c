// First child, next sibling.

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

int addChild(Tree parent, Tree child)
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

int main(void)
{
	return 0;
}

