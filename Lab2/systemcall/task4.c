#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("Fork failed");
        exit(1);
    }
    else if (pid == 0)
    {
        execvp("./sort", argv);
    }
    else
    {
        wait(NULL);
        execvp("./oddeven", argv);
    }

    return 0;
}

