#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    FILE *file = fopen(argv[1], "a");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    char input[100];
    //while(True)||
    while (1) {
        printf("Enter a string(-1 to stop!): ");
        fgets(input, 100, stdin);

        if (input[0] == '-'&& input[1] =='1'&& (input[2] == '\n'  || input[2] == '\r')) {
            break;
        }
        fprintf(file, "%s", input);
    }
    fclose(file);
    return 0;
}
