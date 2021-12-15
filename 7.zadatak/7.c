#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "declarations.h"
#include "functions.c"
int main()
{
    Position head=CreateElement("C:");
    if(!head)
        return -1;
    InputHandle(head);

    return 0;
}
