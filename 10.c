#include <stdio.h>
#include <string.h>

int main() {
    char input[100];
    int state = 0;  // Start state = q0
    int i;

    printf("Enter a string (a/b): ");
    scanf("%s", input);

    for (i = 0; i < strlen(input); i++) {
        char symbol = input[i];

        switch (state) {
            case 0: // q0
                if (symbol == 'a')
                    state = 1;
                else if (symbol == 'b')
                    state = 0;
                else {
                    printf("Invalid symbol!\n");
                    return 0;
                }
                break;

            case 1: // q1
                if (symbol == 'a')
                    state = 1;
                else if (symbol == 'b')
                    state = 2;
                else {
                    printf("Invalid symbol!\n");
                    return 0;
                }
                break;

            case 2: // q2
                if (symbol == 'a')
                    state = 1;
                else if (symbol == 'b')
                    state = 0;
                else {
                    printf("Invalid symbol!\n");
                    return 0;
                }
                break;
        }
    }

    if (state == 2)
        printf("✅ String accepted (ends with 'ab')\n");
    else
        printf("❌ String rejected\n");

    return 0;
}
