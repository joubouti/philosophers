#include "philo_three.h"
#include <stdio.h>

int ph_num = 0;

void    ph()
{
    printf("%d\n", ph_num);
}

int main(void)
{
    int i = 0;
    pid_t   pid = 1;

    while (i++ < 10 && pid != 0)
    {
        ph_num++;
        pid = fork();
    }
    if (pid != 0)
    {
        kill(pid, SIGHUP);
        write(1, "EXIT\n", 5);
        // exit(1);
    }
    if (pid == 0)
    {
        kill(0, 9);
        sleep(2);
        ph();
    }
    return (0);
}