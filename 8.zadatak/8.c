#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include "declarations.h"
#include "declarations.c"

int main()
{
    int number=0;
    char option='\0',trash='\0';
    Position root=NULL;
    do
    {
        printf("Do you want to insert a number(y/n): ");
        scanf(" %c",&option);
        option=tolower(option);
        if(option=='y')
        {
            printf("Input the number you'd like to insert: ");
            if(scanf(" %d",&number)!=1)
            {
                printf("That's not a number!\n");
                scanf(" %c",&trash);
                }
            else
            root=InsertElement(root,number);
        }
        if(option!='y'&&option!='n')
            printf("Invalid input, please input either y or n!\n");
    }while(option!='n');
    LevelTracking(root);
    return 0;
}
