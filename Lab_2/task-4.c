#include <stdio.h>
#include <sys/stat.h>

int main(int argc,char* argv[])
{
    if (argc!=3)
    {
        fprintf(stderr,"Unexpected number of parameters\n.Comman format:Command format:%s filename_1 filename_2 \n",argv[0]);
        fprintf(stderr,"filename_1 - name of file to read\n");
        fprintf(stderr,"filename_2 - name of file to write\n");
        return 1;
    }
    char* filename_1=argv[1];
    char* filename_2=argv[2];
    FILE* f1=fopen(filename_1,"r");
    if (!f1)
    {
        perror("fopen()");
        return 1;
    }
    FILE* f2=fopen(filename_2,"w");
    if (!f2)
    {
        perror("fopen()");
        fclose(f1);
        return 1;
    }
    struct stat copy_stat;
    if (stat(argv[1],&copy_stat))
    {
       perror("stat()");
       fclose(f1);
       fclose(f2);
       return 1;
    }
    if (chmod(argv[2],copy_stat.st_mode))
    {
        fprintf(stderr,"chmod()");
        fclose(f1);
        fclose(f2);
        return 1;
    }
    char symb;
    while ((symb=getc(f1))!=EOF)
    {
        putc(symb,f2);
    }
    if (fclose(f1))
    {
        perror("fclose()");
        return 1;
    }
    if (fclose(f2))
    {
        perror("fclose()");
        return 1;
    }
    return 0;
}
