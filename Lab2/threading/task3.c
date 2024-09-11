#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

struct thread_data {
    char *str;
    int *result;
};

int asciiSum(char *str)
{
    int sum = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        sum += str[i];
    }
    return sum;
}

void *thread(void *arg)
{    // allocating memory for the result
    // dereferencing the void pointer and storing the result in the allocated memory
  // returning the pointer to the allocated memory

    char *str = ((struct thread_data*)arg)->str;
    int *result = ((struct thread_data*)arg)->result;
    *result = asciiSum(str);
    pthread_exit(0);
}


int main()
{
    char str1[100], str2[100], str3[100];
    int result1, result2, result3;

    printf("Enter first string: ");
    fgets(str1, 100, stdin);
    printf("Enter second string: ");
    fgets(str2, 100, stdin);
    printf("Enter third string: ");
    fgets(str3, 100, stdin);

    pthread_t thread1, thread2, thread3;
    struct thread_data td1 = {str1, &result1};
    struct thread_data td2 = {str2, &result2};
    struct thread_data td3 = {str3, &result3};


    // passing the address of the string to the thread function and storing it in the thread1 variable.
    pthread_create(&thread1, NULL, thread, &td1);
    pthread_create(&thread2, NULL, thread, &td2);
    pthread_create(&thread3, NULL, thread, &td3);

    // here first pointer used to get the memory address of the returned (result) pointer and second is to store the memory address to this functions result1 variable.

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    // checking if all the three strings have the same ascii sum
    if (result1 == result2 && result2 == result3)
    {
        printf("Youreka\n");
    }
    else if (result1 == result2 || result2 == result3 || result1 == result3)
    {
        printf("Miracle\n");
    }
    else
    {
        printf("Hasta la vista\n");
    }

    return 0;
}
