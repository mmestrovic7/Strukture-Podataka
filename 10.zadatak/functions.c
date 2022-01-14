#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "declarations.h"
int ReadFromFile(char *fileName,PositionList head)
{
    char buffer[MAX_LINE]= {0};
    char countryFileName[MAX_LINE]= {0};
    FILE *f;
    f=fopen(fileName,"r");
    PositionList temp=NULL;
    if(!f)
    {
        perror("Couldn't open the file\n");
        return -1;
    }
    while(!feof(f))
    {
        PositionList temp=NULL;
        temp=(PositionList)malloc(sizeof(listNode));
        temp->next=NULL;
        fgets(buffer,MAX_LINE,f);
        if(sscanf(buffer," %s %s", temp->country,countryFileName)==2)
        {
            temp->root=NULL;
            temp->root=ReadCitiesFromFiles(countryFileName);
            InsertSortedCountriesIntoList(temp,head);
        }
    }
    fclose(f);
    return 0;
}
PositionTree ReadCitiesFromFiles(char* fileName)
{
    char buffer[MAX_LINE]= {0};
    char name[MAX_LINE]= {0};
    int population=0;
    FILE *f;
    f=fopen(fileName,"r");
    PositionTree root=NULL;
    if(!f)
    {
        perror("Couldn't open the file\n");
        return NULL;
    }

    while(!feof(f))
    {
        fgets(buffer,MAX_LINE,f);
        if(sscanf(buffer," %s %d",name,&population)==2)
            root=InsertSortedCitiesIntoTree(name,population,root);
    }
    fclose(f);
    return root;
}
int InsertSortedCountriesIntoList(PositionList newElement,PositionList head)
{
    PositionList temp=head;
    while(temp->next!=NULL&&strcmp(temp->next->country,newElement->country)<0)
        temp=temp->next;
    if(temp->next==NULL||strcmp(temp->next->country,newElement->country))
        InsertAfter(temp,newElement);
    else if(!strcmp(temp->next->country,newElement->country))
        return -1;
    return EXIT_SUCCESS;
}
int InsertAfter(PositionList temp,PositionList newElement)
{
    newElement->next=temp->next;
    temp->next=newElement;
}
PositionTree InsertSortedCitiesIntoTree(char *name,int population,PositionTree current)
{
    if(current==NULL)
    {
        current=(PositionTree*)malloc(sizeof(treeNode));
        strcpy(current->city,name);
        current->population=population;
        current->left=NULL;
        current->right=NULL;
    }
    else if(population<current->population)
        current->left=InsertSortedCitiesIntoTree(name,population,current->left);
    else if(population>current->population)
        current->right=InsertSortedCitiesIntoTree(name,population,current->right);
    else if(population==current->population)
    {
        if(strcmp(name,current->city)<0)
            current->left=InsertSortedCitiesIntoTree(name,population,current->left);
        else if(strcmp(name,current->city)>0)
            current->right=InsertSortedCitiesIntoTree(name,population,current->right);
        else
            return current;
    }
    else
        free(current);
    return current;
}
int PrintList(PositionList head)
{
    PositionList temp=head->next;
    while(temp!=NULL)
    {
        printf("\n%s\n",temp->country);
        InOrderTreePrint(temp->root);
        temp=temp->next;
    }
    return 0;
}
int InOrderTreePrint(PositionTree current)
{
    if(current==NULL)
        return 0;
    InOrderTreePrint(current->left);
    printf("\tCITY:%s\t POPULATION:%d\n",current->city,current->population);
    InOrderTreePrint(current->right);
    return 0;
}
int CheckCountriesPopulation(PositionList country,int number,PositionList head)
{
    int max=0;
    max=FindMax(country->root);
    if(number>max)
    {
        printf("There are no cities in %s that have larger population than %d.\n",country,number);
        return -2;
    }
    printf("\nCities in %s with a population larger than %d.\n",country->country,number);
    FindAndPrintCitiesWithLargerPopulation(number,country->root);
    return 0;
}
int FindMax(PositionTree current)
{
    int max=0;
    if(current==NULL)
        return 0;
    if(current->right==NULL)
        return current->population;
    max=FindMax(current->right);
    return max;
}
PositionList FindCountry(char* country,PositionList head)
{
    PositionList temp=head;
    while(temp->next!=NULL&&strcmp(temp->next->country,country))
        temp=temp->next;
    return temp->next;
}
int FindAndPrintCitiesWithLargerPopulation(int number,PositionTree current)
{
    if(current==NULL)
        return 0;
    FindAndPrintCitiesWithLargerPopulation(number,current->left);
    if(current->population >= number)
        printf("\tCITY:%s\t POPULATION:%d\n",current->city,current->population);
    FindAndPrintCitiesWithLargerPopulation(number,current->right);

    return 0;

}
int InputHandle(PositionList head)
{
    char selectedCountry[MAX_LINE]={0};
    int number=0;
    PositionList country=NULL;
    ReadFromFile("drzave.txt", head);
    PrintList(head);
    printf("Choose a country: ");
    scanf("%s",selectedCountry);
    country=FindCountry(selectedCountry,head);
    while(!country)
    {
        printf("Selected country(%s) not found!\nInput another country: ",selectedCountry);
        scanf(" %s",selectedCountry);
        country=FindCountry(selectedCountry,head);

    }
    number=GetNumber();
    CheckCountriesPopulation(country, number, head);
    return 0;
}
int GetNumber()
{
    int number=0,x=1;
    char trash[1024];
    while(x)
    {
        printf("Input a population number: ");
        if(scanf(" %d",&number)!=1)
        {
            printf("That's not a number!\n");
            scanf(" %s",&trash);
        }
        else
            return number;
    }
}
