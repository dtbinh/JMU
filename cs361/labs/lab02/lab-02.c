#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    pid_t pid, pid1;

    int number = 15;
    pid = fork();

    switch(pid)
    {
        case -1:    /* fork() failed */
            printf("Fork Failed\n");
            return 1;

        case 0:     /* Child Code */
            pid1 = getpid();
            printf("Inside Child: pid  = %d\n", pid);           /* A */
            printf("Inside Child: pid1 = %d\n", pid1);          /* B */
            number += 5;
            printf("Inside Child: number = %d\n", number);      /* C */
            break;

        default:    /* Parent Code */
            printf("Inside Parent: I will wait till child exits\n");
            wait(NULL) ;
            number += 100;
            pid1 = getpid();
            printf("Inside Parent: pid = %d\n", pid);           /* D */
            printf("Inside Parent: pid1 = %d\n", pid1);         /* E */
            printf("Inside Parent: number = %d\n", number);     /* F */
    }
    
    /* Both parent & child execute any code below this point */
    return 0;
}
