#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "declarations.h"


int InputHandle(Position head)
{
    int exitVar=1;
    Position current=head,tempcurrent=NULL;
    Position temphead=head;
    char userInput[MAX_LINE],command[6],directoryName[MAX_LINE];
    _List pathHead= {.name="",.next=NULL};
    PositionList path=&pathHead;
    do
    {
        temphead=head;
        InitialPrint(&pathHead,current);
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
        else if(!strcmp("cd",command))
        {

            tempcurrent=ChangeDirectory(directoryName,temphead,&pathHead);
            if(!tempcurrent)
                printf("The directory doesnt exist\n");
            else
                current=tempcurrent;

        }

        else if(!strcmp("cd dir",command))
        {
            tempcurrent=ChangeDirectory(directoryName,temphead,&pathHead);
            if(!tempcurrent)
                printf("The directory doesnt exist\n");
            else
            {
                current=tempcurrent;
                Dir(current);
            }

        }




    }
    while(exitVar);
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
PositionList CreateListElement(char* name)
{
    PositionList newElement=NULL;
    newElement=(PositionList)malloc(sizeof(_List));
    if(!newElement)
    {
        printf("Couldn't allocate memory!");
        return newElement;
    }
    strcpy(newElement->name,name);
    newElement->next=NULL;

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
int InitialPrint(PositionList path,PositionList current)
{
    int end=0;
    if(path->next==NULL)
        printf("C:");
    while(path->next&&!end)
    {
        path=path->next;
        if(strcmp("C:",path->name))
            printf("\\");
        printf("%s",path->name);
        if(!strcmp(path->name,current->name))
            end=1;
    }

    printf(">");
    return 0;
}
int MakeDir(char* name, Position current)
{
    Position temp=current;
    Position newDirectory=CreateElement(name);
    if(!newDirectory)
        return -1;
    if(!current->child)
    {
        current->child=newDirectory;
        return 0;
    }
    temp=current->child;
    while(temp->sibling)
        temp=temp->sibling;
    temp->sibling=newDirectory;
    return 0;
}
Position ChangeDirectory(char* name,Position temphead,PositionList path)
{
    Position current=NULL;
    if(!strcmp(temphead->name,name))
    {
        if(InsertAfter(path,temphead->name)==-1)
            return NULL;
        return temphead;
    }


    if(temphead->child)
        if((current=ChangeDirectory(name,temphead->child,path))!=NULL)
        {
            if(InsertAfter(path,temphead->name)==-1)
                return NULL;
            return current;
        }

    if(temphead->sibling)
        if((current=ChangeDirectory(name,temphead->sibling,path))!=NULL)
            return current;
    return NULL;
}
int InsertAfter(PositionList head, char* name)
{
    PositionList newElement=CreateListElement(name);
    if(!newElement)
        return -1;
    newElement->next=head->next;
    head->next=newElement;
    return 0;
}

