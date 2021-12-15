#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "declarations.h"


int InputHandle(Position head)
{
    int exitVar=1;
    Position current=head;
    char userInput[MAX_LINE],command[6],directoryName[MAX_LINE];
    do
    {
        InitialPrint(head,current);
        fgets(userInput,MAX_LINE,stdin);
        sscanf(userInput,"%s %s",command,directoryName);
        if(!strcmp("exit",command))
        {
            Exit(head);
            exitVar=0;
        }
        else if(!strcmp("dir",command))
            Dir(current);
        else if(!strcmp("md",command))
            MakeDir(directoryName,current);


    }while(exitVar);
    return 0;
}
Position CreateElement(char* name)
{
    Position newElement=NULL;
    newElement=(Position)malloc(sizeof(_Directory));
    if(!newElement)
    {
        printf("Couldn't allocate memory!");
        return newElement;
    }
    strcpy(newElement->name,name);
    newElement->child=NULL;
    newElement->sibling=NULL;

}
Position Exit(Position current)
{
    if(current->child==NULL&&current->sibling==NULL)
    {
        free(current);
        return NULL;
    }
    if(current->sibling!=NULL)
        current->sibling=Exit(current->sibling);
    current->child=Exit(current->child);
    free(current);
    return NULL;
}
int Dir(Position current)
{
    Position temp=current;
    if(!temp->child)
    {
        printf("No directories in this directory\n");
        return 0;
    }
    printf("<%s>\t%s\n",current->name,temp->child);
    temp=temp->child;
    while(temp->sibling)
    {
        printf("<%s>\t%s\n",current->name,temp->sibling);
        temp=temp->sibling;
    }

   return 0;
}
int InitialPrint(Position head,Position current)
{
        Position temp=head;
        printf("%s",head->name);
        while(temp!=head)
        {
            printf("\\");
            printf("%s",temp->name);
            temp=temp->child;
        }
        printf(">");
        return 0;
}
int MakeDir(char* name, Position current)
{
    Position newDirectory=CreateElement(name);
    if(!newDirectory)
        return -1;
    if(!current->child)
    {
        current->child=newDirectory;
        return 0;
    }
    while(current->child->sibling)
        current=current->sibling;
    current->child->sibling=newDirectory;
    return 0;
}
