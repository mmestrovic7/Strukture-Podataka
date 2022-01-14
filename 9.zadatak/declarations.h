#ifndef DECLARATIONS_H
#define DECLARATIONS_H
#define MAX_SIZE 100


struct _treeNode;
typedef struct _treeNode* Position;
typedef struct _treeNode {
	int number;
	Position left;
	Position right;
}treeNode;
struct _listNode;
typedef struct _listNode* ListPosition;
typedef struct _listNode {
	int number;
	ListPosition next;
}listNode;
Position InsertElement(Position root,int val)
Position CreateNewElement(int val);
ListPosition CreateNewListElement(int val);
int InsertListElement(ListPosition head, int val);
int TurnTreeIntoList(Position current,ListPosition head);
int Replace(Position current);
int FilePrint(ListPosition beforeReplaceHead,ListPosition afterReplaceHead);
int GetNumber();
int GetRandomNumber();
int Menu(Position root);

#endif
