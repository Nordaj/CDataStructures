#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdlib.h>
#include <stddef.h>

#define DYNAMIC_ARRAY_INIT_CAPACITY 4
#define DYNAMIC_ARRAY_GROWTH_FACTOR 2

typedef struct List
{
	int size;
	int elementSize;
	int capacity;
	void *data;
} List;

//Create a list, element size is the size of each element in bytes.
inline List *ListCreate(int elementSize)
{
	List *list = malloc(sizeof(List));
	list->size = 0;
	list->elementSize = elementSize;
	list->capacity = DYNAMIC_ARRAY_INIT_CAPACITY;
	list->data = malloc(elementSize * list->capacity);
	return list;
}

//Create a list with advanced options
inline List *ListCreateAdv(int elementSize, int startSize, int capacity)
{
	List *list = malloc(sizeof(List));
	list->size = startSize;
	list->elementSize = elementSize;
	list->capacity = capacity;
	list->data = malloc(elementSize * list->capacity);
	return list;
}

//Get an element from a list
inline void *ListGet(List *list, int index)
{
	if (index < list->size)
		return (char*)list->data + (index * list->elementSize);
	else
		return NULL;
}

//Push to a list
inline void ListPushBack(List *list, void *data)
{
	if (list->size >= list->capacity)
	{
		//Allocate/set new data
		list->capacity *= DYNAMIC_ARRAY_GROWTH_FACTOR;
		void *newLocation = malloc(list->elementSize * list->capacity);
		memcpy(newLocation, list->data, list->elementSize * list->size);
		
		//Free old data
		free(list->data);

		//Set new pointer
		list->data = newLocation;
	}

	//Add to size, and copy element data
	list->size++;
	memcpy(ListGet(list, list->size - 1), data, list->elementSize);
}

//Insert an element into a list at index
inline void ListInsert(List *list, int index, void *data)
{
	//Increase size
	if (list->size >= list->capacity)
	{
		//Allocate/set new data
		list->capacity *= DYNAMIC_ARRAY_GROWTH_FACTOR;
		void *newLocation = malloc(list->elementSize * list->capacity);
		memcpy(newLocation, list->data, list->elementSize * list->size);

		//Free old data
		free(list->data);

		//Set new pointer
		list->data = newLocation;
	}
	list->size++;

	//Copy all elements from after index, over 1
	memcpy(
		(char*)list->data + ((index + 1) * list->elementSize), 	//Destination
		(char*)list->data + ((index)* list->elementSize),		//Source
		(list->size - index) * list->elementSize);				//Size

	//Copy data into index
	memcpy(ListGet(list, index), data, list->elementSize);
}

//Remove an element from a list at index
inline void ListRemove(List *list, int index)
{
	if (index < list->size)
	{
		list->size--;

		//Copy everything back
		memcpy(ListGet(list, index), (char*)ListGet(list, index) + (1 * list->elementSize), (list->size - index) * list->elementSize);
	}
}

//Free all memory of list
inline void ListFree(List **list)
{
	free((*list)->data);
	free(*list);
	*list = NULL;
}

#endif //DYNAMIC_ARRAY_H
