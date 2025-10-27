#include <stdio.h>
#include <string.h>

int main()
{
    char icode[10][30];
    char result[10], arg1[10], arg2[10], op;
    int i = 0;

    printf("Enter the set of intermediate code (terminated by 'exit'):\n");

    // Input intermediate code lines
    do
    {
        scanf("%s", icode[i]);
    } while (strcmp(icode[i++], "exit") != 0);

    printf("\nTarget Code Generation");
    printf("\n***********************\n");

    i = 0;
    while (strcmp(icode[i], "exit") != 0)
    {

        // Try to parse instruction with operator (like t1=a+b)
        int count = sscanf(icode[i], "%[^=]=%[^+-*/]%c%s", result, arg1, &op, arg2);

        if (count == 4)
        {
            // Arithmetic operation detected
            char *opr;
            if (op == '+')
                opr = "ADD";
            else if (op == '-')
                opr = "SUB";
            else if (op == '*')
                opr = "MUL";
            else if (op == '/')
                opr = "DIV";
            else
                opr = "UNKNOWN";

            printf("\tMOV R0, %s\n", arg1);
            printf("\t%s R0, %s\n", opr, arg2);
            printf("\tMOV %s, R0\n", result);
        }
        else
        {
            // Assignment without arithmetic (e.g., t1=5 or t1=t2)
            count = sscanf(icode[i], "%[^=]=%s", result, arg1);
            if (count == 2)
            {
                printf("\tMOV %s, %s\n", result, arg1);
            }
            else
            {
                printf("Unsupported instruction format: %s\n", icode[i]);
            }
        }

        i++;
    }

    return 0;
}
