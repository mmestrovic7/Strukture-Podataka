#ifndef DECLARATIONS_H
#define DECLARATIONS_H
struct treeNode;
typedef struct treeNode* Position;
struct treeNode
{
    int data;
	Position left;
	Position right;
};
Position InsertElement(Position root,int val);
Position CreateNewElement(int val);
int PrintLevel(Position root,int level);
int LevelTracking(Position root);
int InOrderPrint(Position root);
int PreOrderPrint(Position root);
int PostOrderPrint(Position root);

#endif
