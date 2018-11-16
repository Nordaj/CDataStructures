#include <stdio.h>
#include <stdlib.h>
#include "CDS/LinkedList.h"
#include "CDS/DynamicArray.h"
#include "CDS/Stack.h"

int main()
{
	Stack *stack = StackCreate(sizeof(int));

	//Push 50 elements, counting
	for (int i = 0; i < 50; i++)
		StackPush(stack, &i);

	//Pop 15 elements
	for (int i = 0; i < 15; i++)
		StackPop(stack);

	//Output all elements
	for (int i = 0; i < stack->size; i++)
		printf("%d: %d\n", i, *(int*)StackGet(stack, i));

	//Free stack
	StackFree(&stack);

	//Keep window up
	puts("Press enter to exit.");
	getchar();

	return 0;
}
