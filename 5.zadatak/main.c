#define _CRT_SECURE_NO_WARNINGS
#include "declarations.h"
#include "declarations.c"
#include <stdio.h>
#include<stdlib.h>


int main(int argc, char* argv[])
{
    double result=0.0;
    if(ParseStringIntoPostfixAndCalculatePostfix("postfix.txt",&result)!=EXIT_SUCCESS)
        return EXIT_FAILURE;
    printf("%lf ",result);

}
