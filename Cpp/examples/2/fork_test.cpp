#include <stdio.h>   /* printf, stderr, fprintf */
#include <sys/types.h> /* pid_t */
#include <unistd.h>  /* _exit, fork */
#include <stdlib.h>  /* exit */
#include <errno.h>   /* errno */

int main(void)
{
    pid_t  pid;

    pid = fork();

    if (pid == -1)
    {
        fprintf(stderr, "can't fork, error %d\n", errno);
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        int  j;
        for (j = 0; j < 10; j++)
        {
            printf("child: %d\n", j);
            int* pi = (int*)0x11;
            *pi = 3;
            sleep(1);
        }
        _exit(0);  /* Note that we do not use exit() */
    }
    else
    {
        int  i;
        for (i = 0; i < 10; i++)
        {
            printf("parent: %d\n", i);
            sleep(1);
        }
        exit(0);
    }
    return 0;
}

