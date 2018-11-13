#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>
#include <stddef.h>

typedef struct LLNode
{
	void *data;
	struct LLNode *next;
} LLNode;

//Create list
inline LLNode *LLCreate(void *data)
{
	//Create new node with data
	LLNode *newNode = malloc(sizeof(LLNode));
	newNode->data = data;
	newNode->next = NULL;
}

//Inserts the data after node
inline LLNode *LLInsertAfter(LLNode *node, void *data)
{
	//Create new node, insert it into list
	LLNode *newNode = LLCreate(data);
	newNode->next = node->next;
	node->next = newNode;

	return newNode;
}

//Inserts the data at the end of the list
inline LLNode *LLInsertEnd(LLNode *list, void *data)
{
	//Find the end
	LLNode *end = list;
	for (; end->next; end = end->next) {}

	//Create and add new node
	LLNode *newNode = LLCreate(data);
	end->next = newNode;
	return newNode;
}

//Inserts the data at the beginning of the list
inline LLNode *LLInsertBeginning(LLNode **list, void *data)
{
	//Create new node
	LLNode *newNode = LLCreate(data);
	newNode->next = *list;

	//Make list start at beginning
	(*list) = newNode;

	return newNode;
}

//Frees all memory in the list
inline void LLFree(LLNode **list)
{
	LLNode *current = *list;
	for (; current != NULL;)
	{
		LLNode *n = current;
		current = current->next;
		free(n);
	}
	*list = NULL;
}

//Finds the first node matching the data given
inline LLNode *LLFindByData(LLNode *list, void *data)
{
	for (; list != NULL; list = list->next)
		if (list->data == data) return list;
}

//Removes node from list
inline void LLRemove(LLNode **list, LLNode *node)
{
	//Just free if in beginning
	if (*list == node)
	{
		*list = (*list)->next;
		free(node);
		return;
	}

	//Find previous node
	LLNode *prev = *list;
	for (; prev->next != node; prev = prev->next) {}
	if (prev == NULL) return; //Error check

							  //Connect previous to the node being pointed to unless at end
	if (node->next)
		prev->next = node->next;
	else
		prev->next = NULL;

	//Remove node, does not free the nodes data
	free(node);
}

//Removes first node with matching data
inline void LLRemoveByData(LLNode **list, void *data)
{
	LLRemove(list, LLFindByData(*list, data));
}

#endif //LINKED_LIST_H
