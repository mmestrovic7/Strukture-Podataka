#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "declarations.h"
Position InsertElement(Position root,int val)
{
    if(root==NULL)
        return CreateNewElement(val);
    if(root->number<val)
        root->right=InsertElement(root->right,val);
    else if(root->number>val)
        root->left=InsertElement(root->left,val);
    return root;
}
Position CreateNewElement(int val)
{
    Position newNode=(Position)malloc(sizeof(treeNode));
    if(!newNode)
    {
        perror("Unsuccesful memory allocation!\n");
        return newNode;
    }
    newNode->number=val;
    newNode->left=NULL;
    newNode->right=NULL;
    return newNode;
}
ListPosition CreateNewListElement(int val)
{
    ListPosition newNode=NULL;
    newNode=(ListPosition)malloc(sizeof(listNode));
    if(!newElement)
    {
        perror("Unsuccesful memory allocation!\n");
        return NULL;
    }
    newNode->number=nodeNumber;
    newNode->next=NULL;
    return newNode;
}
int InsertListElement(ListPosition head,int val)
{
    ListPosition temp=head;
    ListPosition newElement=NULL;
    newElement=CreateNewListElement(val);
    if(!newElement)
        return EXIT_FAILURE;
    while (temp->next)
        temp=temp->next;
    newElement->next=temp->next;
    temp->next=newElement;
    return EXIT_SUCCESS;
}
int TurnTreeIntoList(Position current,ListPosition head)
{
    Position temp=current;
    if(temp&&temp->left)
        TurnTreeIntoList(temp->left,head);
    if(temp&&temp->right)
        TurnTreeIntoList(temp->right,head);
    if(temp)
        InsertListElement(head,temp->number);
    return EXIT_SUCCESS;
}
int Replace(Position current)
{
    int temp=0;
    if(!(current->left||current->right))
    {
        temp=current->number;
        current->number=0;
        return temp;
    }
    else if(current->left&&current->right)
    {
        temp=current->number;
        current->number=Replace(current->left)+Replace(current->right);
        temp+=current->number;
        return temp;
    }
    else if(current->left&&!current->right)
    {
        temp=current->number;
        current->number=Replace(current->left);
        temp+=current->number;
        return temp;
    }
    else
    {
        temp=current->number;
        current->number=Replace(current->right);
        temp+=current->number;
        return temp;
    }
    return current->number;
}
int GetRandomNumber()
{
    time_t t;
    int number=0;
    srand((unsigned)time(&t));
    number=(rand()%(89-11+1))+10;
    printf("Random element is %d\n",number);
    return number;

}
int GetNumber()
{
    int number=0,x=1;
    char trash[1024];
    while(x)
    {
        printf("Input a number: ");
        if(scanf(" %d",&number)!=1)
        {
            printf("That's not a number!\n");
            scanf(" %s",&trash);
        }
        else
            return number;
    }
}
int FilePrint(ListPosition beforeReplaceHead,ListPosition afterReplaceHead)
{
    FILE* file=NULL;
    ListPosition temp1=beforeReplaceHead->next;
    ListPosition temp2=afterReplaceHead->next;
    file=fopen("file.txt","w");
    if (!file)
    {
        perror("Couldn't open the file\n");
        return EXIT_FAILURE;
    }
    fprintf(file,"Binary tree before performing Replace function:\n");
    while (temp1)
    {
        fprintf(file,"%d ",temp1->number);
        temp1=temp1->next;
    }
    fprintf(file,"\nBinary tree after performing Replace function:\n");
    if(!temp2)
        fprintf(file,"You haven't performed the function yet!\n");
    else
        while (temp2)
        {
            fprintf(file,"%d ",temp2->number);
            temp2=temp2->next;
        }
    fclose(file);
    return EXIT_SUCCESS;
}
int Menu(Position root)
{
    int number=0;
    char option[1024]="0";
    ListPosition beforeReplaceHead=NULL;
    ListPosition afterReplaceHead=NULL;
    listNode head1= {.number=0,.next=NULL };
    beforeReplaceHead=&head1;
    listNode head2= {.number=0,.next=NULL };
    afterReplaceHead=&head2;
    do
    {
        printf("Choose an option:\n"
               "1)Insert an element(number)\n"
               "2)Insert a random number\n"
               "3)Replace every node with the sum of its children\n"
               "4)Inorder print into a file\n"
               "5)Clear screen(except menu)\n"
               "X)Exit\n");
        printf("Input a character: ");
        scanf(" %s",&option);
        if(option[1]!='\0')
        {
            printf("Too many characters! ");
            option[0]='0';
        }

        switch(option[0])
        {
        case '1':
            number=GetNumber();
            root=InsertElement(root,number);
            break;
        case '2':
            number=GetRandomNumber();
            root=InsertElement(root,number);
            break;
        case '3':
            TurnTreeIntoList(root,beforeReplaceHead);
            Replace(root);
            TurnTreeIntoList(root,afterReplaceHead);
            break;
        case '4':
            if(!afterReplaceHead->next)
                TurnTreeIntoList(root,beforeReplaceHead);
            FilePrint(beforeReplaceHead afterReplaceHead);
            break;
        case '5':
            system("cls");
            break;
        case 'x':
        case 'X':
            break;
        default:
            printf("Invalid input\n");
            break;

        }

    }
    while(option[0]!='X'&&option[0]!='x');

    return 0;
}
