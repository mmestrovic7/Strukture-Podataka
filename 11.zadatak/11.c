#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "declarations.h"
#include "functions.c"
int main()
{
    listNode head={.country=0,.root=NULL,.next=NULL };
    hashPointer H=HTInitialization(11);
    PositionList headPointer=&head;
    InputHandle(headPointer);

    return 0;
}

