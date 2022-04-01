#include <stdio.h>

int main(int argc,char *argv[])
{
    if (argc!=2)
    {
       fprintf(stderr,"Unexpected number of parameters\n");
       return 1;
    }
    char* filename=argv[1];
    FILE* f=fopen(filename,"w");
    if (!f)
    {
        perror("fopen()");
        return 1;
    } 
    char symbol;
    while ((symbol=getc(stdin))!=6)
    {
        fputc(symbol,f);
    }
    if (fclose(f))
    {
        perror("fclose()");
        return 1;
    }
    return 0;
}