#include <stdio.h>
#include <string.h>
#include <ctype.h>

char input[100];
int tempCount = 1;

void generateIntermediateCode(char expr[])
{
    char op, left[10], right[10], temp[5];
    char lOp[3], rOp[3];
    int i, j, k;

    // Handle multiplication or division first (* /)
    for (i = 0; i < strlen(expr); i++)
    {
        if (expr[i] == '*' || expr[i] == '/')
        {
            op = expr[i];

            // Get left operand
            j = i - 1;
            while (j >= 0 && expr[j] == ' ')
                j--;
            left[0] = expr[j];
            left[1] = '\0';

            // Get right operand
            k = i + 1;
            while (expr[k] == ' ')
                k++;
            right[0] = expr[k];
            right[1] = '\0';

            sprintf(temp, "t%d", tempCount++);

            // Prepare operands with t prefix if they are temp variables
            if (left[0] >= '1' && left[0] <= '9')
                sprintf(lOp, "t%c", left[0]);
            else
                sprintf(lOp, "%c", left[0]);

            if (right[0] >= '1' && right[0] <= '9')
                sprintf(rOp, "t%c", right[0]);
            else
                sprintf(rOp, "%c", right[0]);

            printf("%s = %s %c %s\n", temp, lOp, op, rOp);

            // Replace expression part with temp variable
            expr[j] = temp[1]; // store temp number for next use
            expr[i] = ' ';
            expr[k] = ' ';
        }
    }

    // Handle addition or subtraction (+ -)
    for (i = 0; i < strlen(expr); i++)
    {
        if (expr[i] == '+' || expr[i] == '-')
        {
            op = expr[i];

            j = i - 1;
            while (j >= 0 && expr[j] == ' ')
                j--;
            left[0] = expr[j];
            left[1] = '\0';

            k = i + 1;
            while (expr[k] == ' ')
                k++;
            right[0] = expr[k];
            right[1] = '\0';

            sprintf(temp, "t%d", tempCount++);

            // Prepare operands with t prefix if they are temp variables
            if (left[0] >= '1' && left[0] <= '9')
                sprintf(lOp, "t%c", left[0]);
            else
                sprintf(lOp, "%c", left[0]);

            if (right[0] >= '1' && right[0] <= '9')
                sprintf(rOp, "t%c", right[0]);
            else
                sprintf(rOp, "%c", right[0]);

            printf("%s = %s %c %s\n", temp, lOp, op, rOp);

            expr[j] = temp[1]; // store temp number for next use
            expr[i] = ' ';
            expr[k] = ' ';
        }
    }
}

int main()
{
    char lhs[10], rhs[100];

    printf("Enter expression (e.g. a=b+c*d): ");
    scanf("%s", input);

    sscanf(input, "%[^=]=%s", lhs, rhs);

    printf("\n--- Intermediate Code ---\n");
    generateIntermediateCode(rhs);
    printf("%s = t%d\n", lhs, tempCount - 1);

    return 0;
}
