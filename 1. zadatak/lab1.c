#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 128
#define MAX_LINE 1024
typedef struct
{
    char ime[MAX_SIZE];
    char prezime[MAX_SIZE];
    double bodovi;
} _student;
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
double RelativniBodovi(double bodovi,double maxBodovi)
{
    return bodovi/maxBodovi*100;
}
int main()
{
    int br=0,i=0;
    double maxBodovi=0;
    FILE* dat;
    _student* studenti=NULL;
    dat=fopen("studenti.txt","r");
    br=BrojRedaka("studenti.txt")-1;
    studenti=(_student*)malloc(br*sizeof(_student));

    for(i=0; i<br; i++)
        fscanf(dat,"%s %s %lf",studenti[i].ime,studenti[i].prezime,&studenti[i].bodovi);
    for(i=0; i<br; i++)
        if(maxBodovi<studenti[i].bodovi)
            maxBodovi=studenti[i].bodovi;
    printf("       IME      PREZIME     BODOVI     RELATIVNI BODOVI\n");
    for(i=0; i<br; i++)
        printf("%10s %12s %10.2lf %20.2lf\n",studenti[i].ime,studenti[i].prezime,studenti[i].bodovi,RelativniBodovi(studenti[i].bodovi,maxBodovi));


    fclose(dat);


    return 0;
}
