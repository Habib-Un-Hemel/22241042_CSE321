#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    pid_t a, b, c;
    int count = 1; // for the first parent process
    pid_t initial_pid = getpid(); // store the PID of the initial parent process

    a = fork();
    if (a == 0) {
        exit(0);
    } else if (a > 0) {
        if (a % 2 != 0) {
            if (fork() == 0) exit(0);
            count++;
        }
        count++;
    }

    b = fork();
    if (b == 0) {
        exit(0);
    } else if (b > 0) {
        if (b % 2 != 0) {
            if (fork() == 0) exit(0);
            count++;
        }
        count++;
    }

    c = fork();
    if (c == 0) {
        exit(0);
    } else if (c > 0) {
        if (c % 2 != 0) {
            if (fork() == 0) exit(0);
            count++;
        }
        count++;
    }

    while (wait(NULL) > 0);
    
    if (getpid() == initial_pid) {
        printf("Number of processes created: %d\n", count);
    }

    return 0;
}
