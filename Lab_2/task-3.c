#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int main(int argc,char* argv[])
{
    if (argc!=3)
    {
        fprintf(stderr,"Unexpected number of parameters\n.Command format:%s filename line_num\n",argv[0]);
        fprintf(stderr,"filename - name of file to read\n");
        fprintf(stderr,"line_num - count of lines\n");
        return 1;
    }
    char* filename=argv[1];
    FILE* f=fopen(filename,"r");
    if (!f)
    {
        perror("fopen()");
        return 1;
    }
    errno=0;
    char *endptr;
    long line_num=strtol(argv[2],&endptr,10);
    if ((errno == ERANGE && (line_num == LONG_MAX || line_num == LONG_MIN)) || (errno != 0 && line_num == 0)) 
    {
        perror("strtol()");
        exit(EXIT_FAILURE);
    }
    if (endptr == argv[2]) 
    {
        fprintf(stderr, "No digits were found\n");
        exit(EXIT_FAILURE);
    }
    if (line_num<0)
    {
        fprintf(stderr,"Invalid count of lines\n");
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
