#ifndef DECLARATIONS_H
#define DECLARATIONS_H
struct _Number;
typedef struct _Number* Position;
typedef struct _Number{
    double number;
    Position next;
}Number;
Position CreateElement(double number);
char* ReadFile(char* fileName);
int InsertAfter(Position head, Position newElement);
int Push(Position head,double number);
int Pop(Position head, double* result);
int ParseStringIntoPostfixAndCalculatePostfix(char* fileName,double* result);
int PopAndPerformOperation(Position head,char operation, double* result);
int CheckStackAndExtractResult(Position head, double* result);
int PrintStack(Position head);

#endif
