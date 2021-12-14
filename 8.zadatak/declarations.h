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
int LevelOrderPrint(Position root);
int InOrderPrint(Position root);
int PreOrderPrint(Position root);
int PostOrderPrint(Position root);
Position FindElement(int val,Position root);
int Menu(Position root);
int GetNumber();


#endif
