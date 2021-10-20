#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 128
#define MAX_LINE 1024
typedef struct {
	char ime[MAX_SIZE];
	char prezime[MAX_SIZE];
	double bodovi;
}_student;
int BrojRedaka(char* nazivDatoteke)
{
	int br = 0;
	FILE* dat = NULL;
	char buffer[MAX_LINE] = { 0 };
	dat = fopen(nazivDatoteke, "r");
	if (!dat)
	{
		printf("Greska kod otvaranja datoteke!");
		return -1;
	}
	while (!feof(dat))
	{
		fgets(buffer, MAX_LINE, dat);
		br++;
	}
	fclose(dat);
	return br;

}
int main()
{
    int br=0;
    br=BrojRedaka("studenti.txt")-1;


}
