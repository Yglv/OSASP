#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <limits.h>
#include <errno.h>

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

long stringToLong(char *num) {
    char *endptr;
    long result= strtol(num, &endptr, 10);

    if ((errno == ERANGE && (res == LONG_MAX || res == LONG_MIN))
        || (errno != 0 && result == 0)) {
        perror("strtol");
        exit(EXIT_FAILURE);
    }

    if (endptr == num) {
        fprintf(stderr, "No digits were found\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

int main(int argc,char *argv[])
{
    if (argc!=5)
    {
        fprintf(stderr,"Unexpected number of parameters\n.Command format:%s dirname min max filename",argv[0]);
        fprintf(stderr,"dirname- name of directory to read\n");
        fprintf(stderr,"min - min size of files\n");
        fprintf(stderr,"max - max size of files\n");
        fprintf(stderr,"filename - name of file to write result\n");
        return 1;
    }
    int min=stringToLong(argv[2]);
    int max=stringToLong(argv[3]);
    FILE* f=fopen(argv[4],"w");
    if (!f)
    {
        perror("fopen()");
        return 1;
    }
    char* name=(char *)malloc(sizeof(char) * PATH_MAX );
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
