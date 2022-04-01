#include <stdio.h>
#include <stdlib.h>

int main(int argc,char* argv[])
{
    if (argc!=3)
    {
        fprintf(stderr,"Unexpected number of parameters\n");
        return 1;
    }
    char* filename=argv[1];
    FILE* f=fopen(filename,"r");
    if (!f)
    {
        perror("fopen()");
        return 1;
    }
    int line_num=strtol(argv[2],NULL,10);
    if (line_num<0)
    {
        fprintf(stderr,"The number of lines must be >=0");
        fclose(f);
        return 1;
    }
    int line_counter=0;
    char symbol;
    while ((symbol=fgetc(f))!=EOF)
    {
        if (symbol=='\n')
        {
            line_counter++;
        }
        if (line_counter==line_num && line_num!=0)
        {
            getc(stdin);
            line_counter=0;
        }
        fputc(symbol,stdout);
    }
    if (fclose(f))
    {
        perror("fclose()");
        return 1;
    }
    return 0;
}