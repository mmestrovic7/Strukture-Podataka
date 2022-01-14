#ifndef DECLARATIONS_H
#define DECLARATIONS_H
#define MAX_LINE 1024
struct _treeNode;
typedef struct _treeNode* PositionTree;
typedef struct _treeNode{
    int population;
    char city[MAX_LINE];
    PositionTree left;
    PositionTree right;
}treeNode;
struct _listNode;
typedef struct _listNode* PositionList;
typedef struct _listNode
{
    char country[MAX_LINE];
    PositionTree root;
    PositionList next;
}listNode;
int ReadFromFile(char *fileName, PositionList head);
PositionTree ReadCitiesFromFiles(char* fileName);
int InsertSortedCountriesIntoList(PositionList newElement, PositionList head);
int InsertAfter(PositionList temp, PositionList newElement);
PositionTree InsertSortedCitiesIntoTree(char *name, int population, PositionTree current);
int PrintList(PositionList head);
int InOrderTreePrint(PositionTree current);
int CheckCountriesPopulation(PositionList country, int number, PositionList head);
int FindMax(PositionTree current);
PositionList FindCountry(char* country, PositionList head);
int FindAndPrintCitiesWithLargerPopulation(int number, PositionTree current);
int InputHandle(PositionList head);
int GetNumber();
#endif
