#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *threads(void *num)
{
    int thread_num = *(int *)num;  
    int start_value = thread_num * 5 + 1;  // Calculate the starting value 
    for (int i = 0; i < 5; i++)
    {
        printf("Thread %d prints %d\n", thread_num, start_value + i);
    }
    return NULL;
}

int main()
{
    pthread_t number[5];  
    int thread_args[5];  

    // Create 5 
    for (int i = 0; i < 5; i++)
    {
        thread_args[i] = i;  
        pthread_create(&number[i], NULL, threads, &thread_args[i]);
    }

    for (int i = 0; i < 5; i++)
    {
        pthread_join(number[i], NULL);
    }

    return 0;
}

// Thread 4 prints 21
// Thread 4 prints 22
// Thread 4 prints 23
// Thread 4 prints 24
// Thread 4 prints 25