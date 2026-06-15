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

