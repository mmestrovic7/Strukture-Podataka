#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#define MAX_LINE 1024
#define MAX_SIZE 50

struct _Polynomial;
typedef struct _Polynomial* Position;
typedef struct _Polynomial
{
	int coefficient;
	int exponent;
	Position next;
}Polynomial;
int ReadFile(char *file, Position head1, Position head2);
Position CreateElement(int coefficient,int exponent);
int ParseStringToList(char *buffer,Position head);
int InsertSorted(Position head,Position newElement);
int InsertAfter(Position head,Position newElement);
int DeleteAfter(Position previousElement);
int AddPoly(Position resultPoly,Position head1,Position head2);
void PrintPoly(char *print,Position poly);


#endif
