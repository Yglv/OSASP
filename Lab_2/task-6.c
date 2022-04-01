#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

int seenFiles=0;

int CheckDir(char* name,int min,int max,FILE* file)
{
    DIR* curr_dir=opendir(name);
    if (!curr_dir)
    {
        perror("opendir()");
        return 1;
    }
    int name_len=strlen(name);
    struct stat file_stat;
    struct dirent *dir=readdir(curr_dir);
    while (dir!=NULL)
    {
        if (strcmp(dir->d_name,".")==0 || strcmp(dir->d_name,"..")==0)
        {
            dir=readdir(curr_dir);
            continue;
        }
        name[name_len]='/';
        name[name_len+1]='\0';
        strcat(name,dir->d_name);
        if (lstat(name,&file_stat))
        {
            perror("lstat");
            dir=readdir(curr_dir);
            continue;
        }
        if (S_ISDIR(file_stat.st_mode))
        {
            CheckDir(name,min,max,file);
        }
        else
        {
            seenFiles++;
            if (file_stat.st_size>=min && file_stat.st_size<=max)
            {
                fprintf(file,"Path:%s\nName:%s\nSize:%ld\n\n",name,dir->d_name,file_stat.st_size);
            }
        }
        dir=readdir(curr_dir);
    }
    if (closedir(curr_dir))
    {
        perror("closedir()");
        return 1;
    }
    return 0;
}

int main(int argc,char *argv[])
{
    if (argc!=5)
    {
        fprintf(stderr,"Unexpected number of parameters\n");
        return 1;
    }
    int min=strtoll(argv[2],(char**)NULL,10);
    int max=strtoll(argv[3],(char**)NULL,10);
    FILE* f=fopen(argv[4],"w");
    if (!f)
    {
        perror("fopen()");
        return 1;
    }
    char* name=argv[1];
    CheckDir(name,min,max,f);
    printf("Seen files:%d\n",seenFiles);
    if (fclose(f))
    {
        perror("fclose()");
        return 1;
    }
    return 0;
}