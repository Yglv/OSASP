#include <stdio.h>
#include <dirent.h>

int PrintDir(char* name)
{
   DIR* curr_dir=opendir(name);
   if(!curr_dir)
   {
       perror("opendir()");
       return 1;
   }
   struct dirent* dir;
   while (dir=readdir(curr_dir))
   {
       printf("%s\n",dir->d_name);
   }
   if (closedir(curr_dir))
   {
       perror("closedir()");
       return 1;
   }
   return 0;
}

int main(int argc,char* argv[])
{
   printf("Current dir\n------------------\n");
   PrintDir("./");
   printf("Root dir\n--------------------\n");
   PrintDir("/");
   return 0;
}