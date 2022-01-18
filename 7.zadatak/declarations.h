#ifndef DECLARATIONS_H
#define DECLARATIONS_H
#define MAX_LINE 1024

struct Directory;
struct List;
typedef struct Directory* Position;
typedef struct List* PositionList;
typedef struct Directory
{
    char name[MAX_LINE];
    Position sibling;
    Position child;
}_Directory;
typedef struct List
{
    char name[MAX_LINE];
    PositionList next;
}_List;
int InputHandle(Position head);
Position CreateElement(char* name);
Position Exit(Position current);
int InitialPrint(PositionList path);
int Dir(Position current);
int MakeDir(char* name, Position current);
Position ChangeDirectory(char* name,Position temphead,PositionList path);
int InsertAfter(PositionList head, char* name);

#endif


