#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE (50)
struct _Person;
typedef struct _Person* Position;
typedef struct _Person
{
    char name[MAX_SIZE];
    char surname[MAX_SIZE];
    int birthYear;
    Position next;
} Person;

int PrependList(Position head);
Position InputAndCreatePerson();
int PrintList(Position first);
int InsertAfter(Position position, Position newPerson);
int main()
{
    int x=1;
    while(x==1)
    {
    Person head = { .next = NULL, .name = {0}, .surname = {0}, .birthYear = 0 };

    Position p = &head;
    PrependList(p);
    PrintList(p->next);
    }

}
int PrependList(Position head)
{
    Position newPerson = NULL;

    newPerson = InputAndCreatePerson();
    if (!newPerson)
    {

        return -1;
    }

    InsertAfter(head, newPerson);


    return EXIT_SUCCESS;
}

int PrintList(Position first)
{
    Position temp = first;

    while (temp)
    {
        printf("Ime: %s, prezime: %s, godina rodenja: %d\n", temp->name, temp->surname, temp->birthYear);
        temp = temp->next;
    }

    return EXIT_SUCCESS;
}

Position InputAndCreatePerson()
{
    Position newPerson = NULL;
    char* name = (char*)malloc(MAX_SIZE*sizeof(char));
    char* surname = (char*)malloc(MAX_SIZE*sizeof(char));
    int birthYear = 0;

    newPerson = (Position)malloc(sizeof(Position));
    if (!newPerson)
    {
        perror("Can't allocate memory!\n");
        return NULL;
    }
    printf("Unesite ime: ");
    scanf(" %s", name);
    printf("Unesite prezime: ");
    scanf(" %s", surname);
    printf("Unesite godinu rodenja: ");
    scanf(" %d", &birthYear);

    strcpy(newPerson->name, name);
    strcpy(newPerson->surname, surname);
    newPerson->birthYear=birthYear;
    newPerson->next=NULL;



    return newPerson;
}

int InsertAfter(Position position, Position newPerson)
{
    newPerson->next = position->next;
    position->next = newPerson;

    return EXIT_SUCCESS;
}
