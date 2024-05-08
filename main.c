#include "include/postfix_evaluation.h"

int main()
{
    char *string = "6 2 3 + - 3 8 2 / + 2 ^ 3 + -";

    int answer = evaulate_postfix(string);

    printf("%d", answer);

    return 0;
}