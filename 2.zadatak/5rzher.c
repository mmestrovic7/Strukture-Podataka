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

int PrependList(Position head,char *name,char *surname,int *birthYear);
int PrintList(Position first);
void InputPersonInfo(char *name,char *surname,int *birthYear);
Position CreatePerson(char *name,char *surname,int birthYear);
int InsertAfter(Position position, Position newPerson);
Position FindLast(Position head);
int AppendList(Position head,char *name,char *surname,int *birthYear);
Position FindPerson(Position first, char* surname);
void Menu(Position p);
void DeletePerson(Position head, char* surname);

int main(int argc, char** argv)
{
    Person head = { .next = NULL, .name = {0}, .surname = {0}, .birthYear = 0 };

    Position p = &head;
    Menu(p);



    return EXIT_SUCCESS;
}
void Menu(Position p)
{
    char choice='0';
    int error=0;
    char search[MAX_SIZE] = "";
    char* name = (char*)malloc(MAX_SIZE*sizeof(char));
    char* surname = (char*)malloc(MAX_SIZE*sizeof(char));
    int birthYear = 0;
    Position searchPosition = NULL;

    do
    {
        printf("Unosom broja odaberite zelite li:\n"
               "1. Dodati novi element na pocetak liste\n"
               "2. Ispisati listu\n"
               "3. Dodati novi element na kraj liste\n"
               "4. Pronaci element u listi (po prezimenu)\n"
               "5. Izbrisati odredeni element iz liste(po prezimenu)\n"
               "0. Izaci iz programa\n");
        scanf(" %c", &choice);

        switch (choice)
        {
        case '1':
            InputPersonInfo(name,surname, &birthYear);
            error = PrependList(p,name,surname,birthYear);
            if (error == -1)
                printf("Neuspjesno dodavanje osobe!\n");
            else
                printf("Uspjesno ste dodali osobu!\n");
            break;

        case '2':
            if (p->next == NULL)
            {
                printf("U listi nema ljudi\n");
                break;
            }

            PrintList(p->next);
            break;

        case '3':
            InputPersonInfo(name,surname,&birthYear);
            error = AppendList(p,name,surname,birthYear);
            if (error == -1)

                printf("Neuspjesno dodavanje osobe");

            else

                printf("Uspjesno ste dodali osobu\n");

            break;

        case '4':
            if (p->next == NULL)
            {
                printf("U listi nema ljudi\n");
                break;
            }
            printf("Unesite prezime: ");
            scanf("%s", search);
            searchPosition = FindPerson(p->next, search);
            if(!searchPosition)
                printf("Ne postoji osoba s tim prezimenom.\n");
            else
                printf("%s %s, birth year: %d\n", searchPosition->name, searchPosition->surname, searchPosition->birthYear);
            break;

        case '5':
            if (p->next == NULL)
            {
                printf("U listi nema ljudi\n");
                break;
            }
            printf("Unesite prezime: ");
            scanf("%s", search);
            DeletePerson(p,search);

            break;
        case '0':
            break;
        default:
            printf("Krivi unos\n");
            break;

        }
    }
    while(choice!='0');


}

int PrependList(Position head,char *name,char *surname,int *birthYear)
{
    Position newPerson = NULL;

    newPerson = CreatePerson(name,surname,birthYear);

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
void InputPersonInfo(char *name,char *surname,int *birthYear)
{
     printf("Unesite ime: ");
    scanf(" %s", name);
    printf("Unesite prezime: ");
    scanf(" %s", surname);
    printf("Unesite godinu rodenja: ");
    scanf(" %d", birthYear);
}

Position CreatePerson(char *name,char *surname,int birthYear)
{
    Position newPerson = NULL;


    newPerson = (Position*)malloc(sizeof(Position));
    if (!newPerson)
    {
        perror("Can't allocate memory!\n");
        return NULL;
    }


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

Position FindLast(Position head)
{
    Position temp = head;

    while (temp->next)
    {
        temp = temp->next;
    }

    return temp;
}

int AppendList(Position head,char *name,char *surname,int *birthYear)
{
    Position newPerson = NULL;
    Position last = NULL;

    newPerson = CreatePerson(name,surname,birthYear);
    if (!newPerson)
    {
        return -1;
    }

    last=FindLast(head);
    InsertAfter(last, newPerson);

    return EXIT_SUCCESS;
}

Position FindPerson(Position first, char* surname)
{
    Position temp = first;

    while (temp)
    {
        if (strcmp(temp->surname, surname) == 0)
        {
            return temp;
        }

        temp = temp->next;
    }

    return temp;
}
void DeletePerson(Position head, char* surname)
{
    int i=1;
    Position temp=head;
    Position toDelete=NULL;
    while(i)
    {

        if (strcmp(temp->next->surname, surname) == 0)
        {
            toDelete=temp->next;
            temp->next=toDelete->next;
            free(toDelete);
            printf("Izbrisali ste osobu\n");

        }
        if(temp->next==NULL)
            break;
        temp=temp->next;

    }




}
