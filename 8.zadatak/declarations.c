#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "declarations.h"

Position InsertElement(Position root,int val)
{
    if(root==NULL)
        return CreateNewElement(val);
    if(root->data<val)
        root->right=InsertElement(root->right,val);
    else if(root->data>val)
        root->left=InsertElement(root->left,val);
    return root;
}
Position CreateNewElement(int val)
{
    Position newNode=(Position)malloc(sizeof(struct treeNode));
	if (!newNode)
	{
	    printf("Unsuccesful memory allocation!\n");
		return newNode;
	}
	newNode->data=val;
	newNode->left=NULL;
	newNode->right=NULL;
	return newNode;
}
int PrintLevel(Position root,int level)
{
    int left=0,right=0;
    if(root==NULL)
        return 0;
    if (level==1)
    {
        printf("%d ",root->data);
        return 1;
    }
    left=PrintLevel(root->left,level-1);
    right=PrintLevel(root->right,level-1);
    return left||right;
}

int LevelTracking(Position root)
{
    int level=1;
    while (PrintLevel(root, level))
        level++;
    return 0;
}
int InOrderPrint(Position root)
{
	if (root)
	{
		InOrderPrint(root->left);
		printf("%d ", root->data);
		InOrderPrint(root->right);
	}
	return 0;
}
int PreOrderPrint(Position root)
{
	if (root)
	{
	    printf("%d ", root->data);
		PreOrderPrint(root->left);
		PreOrderPrint(root->right);
	}
    return 0;
}
int PostOrderPrint(Position root)
{
	if (root)
	{
	    PostOrderPrint(root->left);
		PostOrderPrint(root->right);
		printf("%d", root->data);
	}
    return 0;
}
