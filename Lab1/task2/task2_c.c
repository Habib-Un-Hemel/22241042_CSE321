#include <stdio.h>
#include <stdbool.h>

int main()
{
    char password[30];
    int d_flag = 0, u_flag = 0, l_flag = 0,s_flag = 0;
    int rules_counter, i = 0;

    printf("Enter password:");
    fgets(password, 30, stdin);

    while (password[i] != '\0')
    {
        if (password[i] >= 'a' && password[i] <= 'z')
        {
            l_flag = 1;
        }
        else if (password[i] >= 'A' && password[i] <= 'Z')
        {
            u_flag = 1;
        }
        else if (password[i] >= '0' && password[i] <= '9')
        {
            d_flag = 1;
        }
        else if (password[i] == '_' || password[i] == '$' || password[i] == '#' ||
        	password[i] == '@')
        {
            s_flag = 1;
        }
        i++;
    }

    rules_counter = 4 - (d_flag + l_flag + u_flag + s_flag);

    if (rules_counter == 0)
    {
        printf("OK");
    }

    else
    {
        if (u_flag == 0)
        {
            printf("Uppercase character missing");
            rules_counter--;

            if (rules_counter != 0)
            {
                printf(", ");
            }
        }

        if (l_flag == 0)
        {
            printf("Lowercase character missing");
            rules_counter--;

            if (rules_counter != 0)
            {
                printf(", ");
            }
        }

        if (d_flag == 0)
        {
            printf("Digit missing");
            rules_counter--;

            if (rules_counter != 0)
            {
                printf(", ");
            }
        }

        if (s_flag == 0)
        {
            printf("Special character missing");
            rules_counter--;

            if (rules_counter != 0)
            {
                printf(", ");
            }
        }
    }
    printf("\n");
    return 0;
}

