#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Polynomial.h"
int main()
{
    Polynomial head1= {.coefficient=0,.exponent=0,.next=NULL};
    Polynomial head2= {.coefficient=0,.exponent=0,.next=NULL};
    Polynomial resultPoly1= {.coefficient=0,.exponent=0,.next=NULL};
    Polynomial resultPoly2= {.coefficient=0,.exponent=0,.next=NULL};
    Position p1=&head1;
    Position p2=&head2;
    Position p3=&resultPoly1;
    Position p4=&resultPoly2;
    if(ReadFile("polynomial.txt",p1,p2)!=EXIT_SUCCESS)
        return EXIT_FAILURE;
    PrintPoly("First polynomial: ",p1);
    PrintPoly("Second polynomial: ",p2);
    if(AddPoly(p3,p1,p2)!=EXIT_SUCCESS)
        return EXIT_FAILURE;
    PrintPoly("Result of addition: ",p3);
    if(MultiplyPoly(p4,p1,p2)!=EXIT_SUCCESS)
        return EXIT_FAILURE;
    PrintPoly("Result of multiplication: ",p4);


    return EXIT_SUCCESS;

}
int ReadFile(char *fileName, Position head1, Position head2)
{
    FILE *file=NULL;
    int status=0;
    char buffer[MAX_LINE]= {0};
    file=fopen(fileName,"r");
    if(!file)
    {
        perror("Can't open file!\n");
        return -1;
    }
    fgets(buffer,MAX_LINE,file);

    status=ParseStringToList(buffer,head1);
    if (status!=EXIT_SUCCESS)
    {
        return EXIT_FAILURE;
    }
    fgets(buffer, MAX_LINE, file);

    status=ParseStringToList(buffer,head2);
    if (status!=EXIT_SUCCESS)
    {
        return EXIT_FAILURE;
    }
    fclose(file);
    return EXIT_SUCCESS;



}
int ParseStringToList(char *buffer,Position head)
{
    char *currentBuffer=buffer;
    int coefficient=0;
    int exponent=0;
    int numBytes=0;
    int status=0;
    Position newElement=NULL;
    while (strlen(currentBuffer)>0)
    {
        status=sscanf(currentBuffer, " %d %d %n", &coefficient, &exponent, &numBytes);
        if (status!=2)
        {
            printf("Invalid coefficient/exponent!\n");
            return EXIT_FAILURE;
        }


        newElement=CreateElement(coefficient, exponent);

        if (!newElement)
        {
            return EXIT_FAILURE;
        }


        InsertSorted(head, newElement);
        currentBuffer+=numBytes;
    }

    return EXIT_SUCCESS;
}
Position CreateElement(int coefficient,int exponent)
{
    Position newElement=NULL;
    newElement=(Position)malloc(sizeof(Polynomial));
    if (!newElement)
    {
        printf("Unsuccessful memory allocation\n");
        return newElement;
    }

    newElement->coefficient=coefficient;
    newElement->exponent=exponent;
    return newElement;

}
int InsertSorted(Position head,Position newElement)
{
    Position temp=head;
    if(newElement->coefficient!=0)
    {
        if(temp->next==NULL)
            return InsertAfter(temp,newElement);
        while(temp)
        {

            if(temp->next->exponent<newElement->exponent)
                return InsertAfter(temp,newElement);
            if(temp->next->exponent==newElement->exponent)
            {
                if(temp->next->coefficient==-(newElement->coefficient))
                    return DeleteAfter(temp);
                temp->next->coefficient+=newElement->coefficient;
                return EXIT_SUCCESS;

            }
            if((temp->next->next==NULL)&&(temp->next->exponent>newElement->exponent))
                return InsertAfter(temp->next,newElement);

            temp=temp->next;
        }
    }
   return EXIT_SUCCESS;
}
int InsertAfter(Position head,Position newElement)
{
    newElement->next=head->next;
    head->next=newElement;
    return EXIT_SUCCESS;
}
int DeleteAfter(Position previousElement)
{
    Position toDelete=NULL;
    toDelete=previousElement->next;
    previousElement->next=previousElement->next->next;
    free(toDelete);
    return EXIT_SUCCESS;
}
int AddPoly(Position resultPoly,Position head1,Position head2)
{
    Position newElement=NULL;
    head1=head1->next;
    head2=head2->next;
    while(head1)
    {
        newElement=CreateElement(head1->coefficient,head1->exponent);
        if (!newElement)
            return EXIT_FAILURE;
        InsertSorted(resultPoly, newElement);
        head1=head1->next;

    }
    while(head2)
    {
        newElement=CreateElement(head2->coefficient,head2->exponent);
        if (!newElement)
            return EXIT_FAILURE;
        InsertSorted(resultPoly, newElement);
        head2=head2->next;

    }
    return EXIT_SUCCESS;

}
int MultiplyPoly(Position resultPoly,Position head1,Position head2)
{
    int coefficient=0,exponent=0;;
    Position i=NULL,j=NULL;
    Position newElement=NULL;
    if(head1->next==NULL||head2->next==NULL)
        return EXIT_SUCCESS;
    for(i=head1->next; i; i=i->next)
        for(j=head2->next; j; j=j->next)
        {
            coefficient=i->coefficient*j->coefficient;
            exponent=i->exponent+j->exponent;
            newElement=CreateElement(coefficient, exponent);

            if (!newElement)
            {
                return EXIT_FAILURE;
            }
            InsertSorted(resultPoly, newElement);

        }
    return EXIT_SUCCESS;

}
void PrintPoly(char *print,Position poly)
{
    Position i=NULL;
    printf("%s",print);
    if(poly->next==NULL)
        printf("0");
    for(i=poly->next; i!=NULL; i=i->next)
    {
        if(i->coefficient!=1||i->exponent==0)
            printf("%d",i->coefficient);
        if(i->exponent<0)
            printf("x^(%d)",i->exponent);
        if(i->exponent>0)
            printf("x^%d",i->exponent);
        if(i->next!=NULL)
            printf(" + ");
    }
    printf("\n");


}
