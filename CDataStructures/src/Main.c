#include <stdio.h>
#include <stdlib.h>
#include "CDS/LinkedList.h"
#include "CDS/DynamicArray.h"

int main()
{
	List *list = ListCreate(sizeof(int));

	int a = 1;
	ListPushBack(list, &a);
	int b = 2;
	ListPushBack(list, &b);
	int c = 3;
	ListPushBack(list, &c);
	int d = 4;
	ListPushBack(list, &d);
	int e = 5;
	ListPushBack(list, &e);

	int f = 6;
	ListInsert(list, 2, &f);

	ListRemove(list, list->size - 1);

	for (int i = 0; i < list->size; i++)
		printf("%d: %d\n", i, *(int*)ListGet(list, i));

	ListFree(&list);

	//Keep window up
	puts("Press enter to exit.");
	getchar();

	return 0;
}
