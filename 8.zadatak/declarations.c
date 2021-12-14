#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "declarations.h"

Position InsertElement(Position root,int val)
{
    if(root==NULL)
        return CreateNewElement(val);
    if(root->data<val)
        root->right=InsertElement(root->right,val);
    else if(root->data>val)
        root->left=InsertElement(root->left,val);
    return root;
}
Position CreateNewElement(int val)
{
    Position newNode=(Position)malloc(sizeof(struct treeNode));
    if (!newNode)
    {
        printf("Unsuccesful memory allocation!\n");
        return newNode;
    }
    newNode->data=val;
    newNode->left=NULL;
    newNode->right=NULL;
    return newNode;
}
int PrintLevel(Position root,int level)
{
    int left=0,right=0;
    if(root==NULL)
        return 0;
    if (level==1)
    {
        printf("%d\n",root->data);
        return 1;
    }
    left=PrintLevel(root->left,level-1);
    right=PrintLevel(root->right,level-1);
    return left||right;
}
int LevelOrderPrint(Position root)
{
    int level=1;
    while (PrintLevel(root, level))
        level++;
    return 0;
}
int InOrderPrint(Position root)
{
    if (root)
    {
        InOrderPrint(root->left);
        printf("%d\n", root->data);
        InOrderPrint(root->right);
    }
    return 0;
}
int PreOrderPrint(Position root)
{
    if (root)
    {
        printf("%d\n", root->data);
        PreOrderPrint(root->left);
        PreOrderPrint(root->right);
    }
    return 0;
}
int PostOrderPrint(Position root)
{
    if (root)
    {
        PostOrderPrint(root->left);
        PostOrderPrint(root->right);
        printf("%d\n", root->data);
    }
    return 0;
}
Position FindElement(int val,Position root)
{
    if (!root)
        return root;
    else if (val<root->data)
        return FindElement(val,root->left);
    else if (val>root->data)
        return FindElement(val,root->right);
    else
        return root;
}
int Menu(Position root)
{
    int number=0;
    char option[1024]="0";
    Position element=NULL;
    do
    {

        printf("Choose an option:\n"
               "1)Input an element(number)\n"
               "2)Inorder printing\n"
               "3)Preorder printing\n"
               "4)Postorder printing\n"
               "5)Level order printing\n"
               "6)Find an element(number)\n"
               "8)Clear screen(except menu)\n"
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
            InOrderPrint(root);
            break;
        case '3':
            PreOrderPrint(root);
            break;
        case '4':
            PostOrderPrint(root);
            break;
        case '5':
            LevelOrderPrint(root);
            break;
        case '6':
            number=GetNumber();
            element=FindElement(number,root);
            if(element)
                printf("Element is found. The adress of the element:",element);
            break;
        case '7':
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
