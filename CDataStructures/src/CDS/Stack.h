#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stddef.h>

#define DYNAMIC_ARRAY_INIT_CAPACITY 4
#define DYNAMIC_ARRAY_GROWTH_FACTOR 2

typedef struct Stack
{
	int size;
	int elementSize;
	int capacity;
	void *data;
} Stack;

//Creates a stack
inline Stack *StackCreate(int elementSize)
{
	Stack *stack = malloc(sizeof(Stack));
	stack->size = 0;
	stack->elementSize = elementSize;
	stack->capacity = DYNAMIC_ARRAY_INIT_CAPACITY;
	stack->data = malloc(elementSize * stack->capacity);
	return stack;
}

//Get an element from stack of index
inline void *StackGet(Stack *stack, int index)
{
	if (index < stack->size)
		return (char*)stack->data + (index * stack->elementSize);
	else
		return NULL;
}

//Push an element to a stack
inline void StackPush(Stack *stack, void *data)
{
	if (stack->size >= stack->capacity)
	{
		//Allocate/set new data
		stack->capacity *= DYNAMIC_ARRAY_GROWTH_FACTOR;
		void *newLocation = malloc(stack->elementSize * stack->capacity);
		memcpy(newLocation, stack->data, stack->elementSize * stack->size);

		//Free old data
		free(stack->data);

		//Set new pointer
		stack->data = newLocation;
	}

	//Add to size, and copy element data
	stack->size++;
	memcpy(StackGet(stack, stack->size - 1), data, stack->elementSize);
}

//Pop an element from a stack
inline void StackPop(Stack *stack)
{
	stack->size--;
}

//Free all memory of stack
inline void StackFree(Stack **stack)
{
	free((*stack)->data);
	free(*stack);
	*stack = NULL;
}

#endif //STACK_H
