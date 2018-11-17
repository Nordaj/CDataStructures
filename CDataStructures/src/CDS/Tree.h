#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "DynamicArray.h"

typedef struct TreeNode
{
	void *data;
	struct TreeNode *parent;
	List *children; //TreeNode**
} TreeNode;

typedef struct Tree
{
	int elementSize;
	TreeNode *root;
} Tree;

//Create a tree
inline Tree *TreeCreate(void *rootData, int elementSize)
{
	TreeNode *root = malloc(sizeof(TreeNode));
	root->data = malloc(elementSize);
	memcpy(root->data, rootData, elementSize);
	root->parent = NULL;
	root->children = ListCreate(sizeof(TreeNode*));

	Tree *tree = malloc(sizeof(Tree));
	tree->elementSize = elementSize;
	tree->root = root;

	return tree;
}

//Insert a node into tree
inline TreeNode *TreeInsert(Tree *tree, TreeNode *parent, void *data)
{
	TreeNode *node = malloc(sizeof(TreeNode));
	node->data = malloc(tree->elementSize);
	memcpy(node->data, data, tree->elementSize);
	node->parent = parent;
	node->children = ListCreate(sizeof(TreeNode*));
	ListPushBack(node->parent->children, &node);
	return node;
}

//Remove and deallocate tree node along with all children
inline void *TreeRemove(Tree *tree, TreeNode *node)
{
	//Iterate backwards
	for (int i = 0; i < node->children->size; i++)
		TreeRemove(tree, *(TreeNode**)ListGet(node->children, i));

	//Free data, list, then node itself
	free(node->data);
	ListFree(&node->children);
	free(node);
}

//Free all data on tree
inline void *TreeFree(Tree **tree)
{
	TreeRemove(*(Tree**)tree, (*(Tree**)tree)->root);
	*tree = NULL;
}

//Print value of each node as integers
inline void *TreePrintInt(TreeNode *root)
{
	//Iterate forwards
	printf("===\n%d\n", *(int*)root->data);
	for (int i = 0; i < root->children->size; i++)
		TreePrintInt(*(TreeNode**)ListGet(root->children, i));
}

#endif //TREE_H
