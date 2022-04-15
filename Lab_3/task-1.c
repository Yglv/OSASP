#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int main()
{
    pid_t pid;
    for (int i=0;i<2;i++)
    {
        switch(pid=fork())
        {
            case 0:
            {
                struct timeval time;
                struct tm *today;
                gettimeofday(&time,NULL);
                today=localtime(&time.tv_sec);
                printf("PID:%d\tPPID:%d\tTime:%d:%0d:%0d:%ld\n",
                   getpid(),
                   getppid(),
                   today->tm_hour,
                   today->tm_min,
                   today->tm_sec,
                   time.tv_usec
                );
                exit(EXIT_SUCCESS);
            }
            case -1:
            {
                fprintf(stderr,"Error while creating child process");
                exit(EXIT_FAILURE);
            }
            default:
            {
                break;
            }
        }
    } 
    if (pid>0)
    {
        system("ps -x");
        while (wait(NULL)!=-1);
    }
    return 0;
}