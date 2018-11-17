#include <stdio.h>
#include <stdlib.h>
#include "CDS/CDS.h"

int main()
{
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int e = 5;

	Tree *tree = TreeCreate(&a, sizeof(int));

	TreeNode *firstChild = TreeInsert(tree, tree->root, &b);

	TreeInsert(tree, firstChild, &c);
	TreeInsert(tree, firstChild, &d);

	TreeInsert(tree, tree->root, &e);

	TreePrintInt(tree->root);

	TreeFree(&tree);

	//Keep window up
	puts("Press enter to exit.");
	getchar();

	return 0;
}
