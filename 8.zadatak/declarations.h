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
void LevelTracking(Position root);
#endif
