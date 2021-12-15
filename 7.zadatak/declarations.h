#ifndef DECLARATIONS_H
#define DECLARATIONS_H
#define MAX_LINE 1024

struct Directory;
typedef struct Directory* Position;
typedef struct Directory
{
    char name[MAX_LINE];
    Position sibling;
    Position child;
}_Directory;
int InputHandle(Position head);
Position CreateElement(char* name);
Position Exit(Position current);
int InitialPrint(Position head,Position current);
int Dir(Position current);
int MakeDir(char* name, Position current);


#endif


