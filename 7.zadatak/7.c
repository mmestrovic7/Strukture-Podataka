#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "declarations.h"
#include "functions.c"
int main()
{
    _Directory head={.name="C:",.child=NULL,.sibling=NULL};
    InputHandle(&head);

    return 0;
}
