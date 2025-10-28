#include <stdio.h>
#include <string.h>
#include <ctype.h>

char expr[100];
int tempCount = 1;

// Generate temporary variable names: t1, t2, ...
void newTemp(char *temp) {
    sprintf(temp, "t%d", tempCount++);
}

// Find the operator with the highest precedence
int findOperator() {
    // First look for * and /
    for (int i = 0; i < strlen(expr); i++) {
        if (expr[i] == '*' || expr[i] == '/')
            return i;
    }
    // Then look for + and -
    for (int i = 0; i < strlen(expr); i++) {
        if (expr[i] == '+' || expr[i] == '-')
            return i;
    }
    return -1;
}

void generateIntermediateCode() {
    while (1) {
        int pos = findOperator();
        if (pos == -1) break;

        char left[10] = "", right[10] = "", temp[10];
        int i = pos - 1, j = pos + 1;

        // Get left operand (e.g., a or t1)
        while (i >= 0 && (isalnum(expr[i]) || expr[i] == 't'))
            i--;
        strncpy(left, expr + i + 1, pos - (i + 1));
        left[pos - (i + 1)] = '\0';

        // Get right operand (e.g., b or t2)
        while (j < strlen(expr) && (isalnum(expr[j]) || expr[j] == 't'))
            j++;
        strncpy(right, expr + pos + 1, j - (pos + 1));
        right[j - (pos + 1)] = '\0';

        // Generate temp variable and print code
        newTemp(temp);
        printf("%s = %s %c %s\n", temp, left, expr[pos], right);

        // Replace subexpression with temp variable
        char newExpr[100] = "";
        strncpy(newExpr, expr, i + 1);
        newExpr[i + 1] = '\0';
        strcat(newExpr, temp);
        strcat(newExpr, expr + j);

        strcpy(expr, newExpr);
    }

    printf("Final Result: %s\n", expr);
}

int main() {
    printf("Enter expression");
    scanf("%s", expr);

    generateIntermediateCode();
    return 0;
}
