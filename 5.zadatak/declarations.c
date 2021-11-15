#define _CRT_SECURE_NO_WARNINGS
#include "declarations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* ReadFile(char* fileName)
{
    FILE* file;
    int fileLength=0;
    char* buffer=NULL;
    file=fopen(fileName,"rb");
    if(!file)
    {
        perror("Can't open file/file might not exist!\n");
        return NULL;
    }
    fseek(file,0,SEEK_END);
    fileLength=ftell(file);
    buffer=(char*)calloc(fileLength+1,sizeof(char));
    if (!buffer)
    {
        perror("Unsuccesful memory allocation\n");
        return NULL;
    }
    rewind(file);
    fread(buffer,sizeof(char),fileLength,file);
    printf("%s\n",buffer);
    fclose(file);

    return buffer;
}
Position CreateElement(double number)
{
    Position newElement=NULL;
    newElement=(Position)malloc(sizeof(Number));
    if(!newElement)
    {
        perror("Unsuccesful memory allocation\n");
        return NULL;
    }
    newElement->number=number;
    newElement->next=NULL;
    return newElement;

}
int InsertAfter(Position head, Position newElement)
{
    newElement->next=head->next;
    head->next=newElement;
    PrintStack(head->next);
    return EXIT_SUCCESS;
}
int Push(Position head,double number)
{
    Position newElement=NULL;
    newElement=CreateElement(number);
    if(!newElement)
        return -1;
    InsertAfter(head,newElement);
    return EXIT_SUCCESS;
}
int Pop(Position head, double* result)
{
    Position toDelete=NULL;

    toDelete=head->next;
    if (!toDelete)
    {
        perror("Stack is empty! Nothing to pop!\n");
        return -1;
    }
    head->next=toDelete->next;
    *result=toDelete->number;
    free(toDelete);

    return EXIT_SUCCESS;
}
int ParseStringIntoPostfixAndCalculatePostfix(char* fileName,double* result)
{
    Number head={.number=0,.next=NULL};

    char* buffer=NULL,currentBuffer=NULL;
    double number=0.0;
    int numBytes=0,status=0;
    char operation='\0';
    buffer=ReadFile(fileName);
    if(!buffer)
        return EXIT_FAILURE;
    for(currentBuffer=buffer;strlen(currentBuffer)>0;currentBuffer+=numBytes)
    {
        status=sscanf(currentBuffer," %lf %n",&number,&numBytes);
        if(status!=1)
        {
            sscanf(currentBuffer," %c %n",&operation,&numBytes);
            status=PopAndPerformOperation(&head,operation,result);
            if (status!=EXIT_SUCCESS)
                return EXIT_FAILURE;
            number=*result;

        }
        if(Push(&head,number)!=EXIT_SUCCESS)
            return EXIT_FAILURE;



    }
    return CheckStackAndExtractResult(&head,result);

}
int PopAndPerformOperation(Position head,char operation, double* result)
{
    double firstNumber=0.0,secondNumber=0.0;
    if(Pop(head,&firstNumber)!=EXIT_SUCCESS)
        return EXIT_FAILURE;
    if(Pop(head,&secondNumber)!=EXIT_SUCCESS)
        return EXIT_FAILURE;
    switch (operation)
    {
    case '+':
        *result=secondNumber+firstNumber;
        break;
    case '-':
        *result=secondNumber-firstNumber;
        break;
    case '*':
        *result=secondNumber*firstNumber;
        break;
    case '/':
        *result=secondNumber/firstNumber;
        break;
    default:
        printf("Operation %c not supported yet!\r\n", operation);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
int CheckStackAndExtractResult(Position head, double* result)
{
    int status=EXIT_SUCCESS;

    status=Pop(head, result);
    if (status!=EXIT_SUCCESS)
        return status;
    if (head->next)
    {
        printf("Invalid postfix, please check the file!\r\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
int PrintStack(Position head)
{
    Position temp=head;

    while(temp)
    {
        printf("%0.1lf", temp->number);
        temp=temp->next;
    }
    printf("\n");

    return EXIT_SUCCESS;
}
