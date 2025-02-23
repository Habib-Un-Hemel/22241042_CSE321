#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>

struct shared {
    char sel[100];
    int b;
};

int main() {
    struct shared obj;
    char buff[] = "Thank you for using";
    int fd[2];
    pipe(fd);
    char input;

    printf("Provide Your Input From Given Options:\n");
    printf("1. Type 'a' to Add Money\n");
    printf("2. Type 'w' to Withdraw Money\n");
    printf("3. Type 'c' to Check Balance\n");
    scanf(" %c", &input);
    printf("Your selection : %c\n", input);
    
    obj.sel[0] = input;
    obj.sel[1] = '\0';
    obj.b = 1000;
    
    void *s_m;
    int sm_id = shmget((key_t)101, sizeof(struct shared), 0666 | IPC_CREAT);
    s_m = shmat(sm_id, NULL, 0);
    memcpy(s_m, &obj, sizeof(struct shared));
    
    pid_t pid = fork();
    
    if (pid == 0) {
        struct shared *received_obj = (struct shared *)s_m;
        
        if (received_obj->sel[0] == 'a') {
            printf("Enter amount to be added: \n");
            int amount;
            scanf("%d", &amount);
            
            if (amount > 0) {
                received_obj->b += amount;
                printf("Balance added successfully\n");
                printf("Updated balance after addition: %d\n", received_obj->b);
            } else {
                printf("Adding failed, Invalid amount.\n");
            }
        } else if (received_obj->sel[0] == 'w') {
            printf("Enter amount to be withdrawn: \n");
            int amount;
            scanf("%d", &amount);
            
            if (amount > 0 && amount <= received_obj->b) {
                received_obj->b -= amount;
                printf("Balance withdrawn successfully\n");
                printf("Updated balance after withdrawal: %d\n", received_obj->b);
            } else {
                printf("Withdrawal failed, Invalid amount.\n");
            }
        } else if (received_obj->sel[0] == 'c') {
            printf("Your current balance is: %d\n", received_obj->b);
        } else {
            printf("Invalid selection\n");
        }
        
        close(fd[0]);
        write(fd[1], buff, sizeof(buff));
        close(fd[1]);
    } else {
        wait(NULL);
        close(fd[1]);
        read(fd[0], buff, sizeof(buff)); 
        printf("%s\n", buff);
        close(fd[0]);
        shmctl(sm_id, IPC_RMID, NULL); 
    }

    return 0;
}

