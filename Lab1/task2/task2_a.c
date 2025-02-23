#include <stdio.h>
#include <stdlib.h>

float addition(float a, float b)
{
    return a + b;
}

float subtraction(float a, float b)
{
    return a - b;
}

float multiplication(float a, float b)
{
    return a * b;
}

int main()
{
    float f_num, s_num;
    char operator;

    printf("First Number: ");
    scanf("%f", &f_num);

    printf("Second Number: ");
    scanf("%f", &s_num);

    if (f_num > s_num)
    {
        printf("Result is: %.2f\n", subtraction(f_num, s_num));
    }
    else if (f_num < s_num)
    {
        printf("Result is: %.2f\n", addition(f_num, s_num));
    }
    else
    {
        printf("Result is: %.2f\n", multiplication(f_num, s_num));
    }

    return 0;
}

