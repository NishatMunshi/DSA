#pragma once

#include "linked_list_stack.h"

int is_digit(char const _char)
{
    return _char >= '0' && _char <= '9';
}

int is_operator(char const _char)
{
    return _char == '+' ||
           _char == '-' ||
           _char == '*' ||
           _char == '/' ||
           _char == '^';
}

int power(int const _base, unsigned const _exponent)
{
    if (_exponent == 0)
        return 1;
    else
        return _base * power(_base, _exponent - 1);
}

int evaulate_postfix(char const *const _string)
{
    Linked_List_Stack *stack = llstack_create_stack();

    for (unsigned stringIndex = 0; _string[stringIndex] != '\0';)
    {
        char currentCharacter = _string[stringIndex];

        if (is_digit(currentCharacter))
        {
            int toPush = 0;

            for (unsigned lookAheadIndex = stringIndex;; ++lookAheadIndex)
            {
                char lookAheadCharacter = _string[lookAheadIndex];
                if (lookAheadCharacter == '\0')
                    return llstack_pop(stack);

                if (is_digit(lookAheadCharacter))
                {
                    toPush = toPush * 10 + lookAheadCharacter - '0';
                }

                else
                {
                    stringIndex = lookAheadIndex;
                    llstack_push(stack, toPush);
                    break;
                }
            }
        }
        else if (is_operator(currentCharacter))
        {
            stringIndex++;
            int operand2 = llstack_pop(stack);
            int operand1 = llstack_pop(stack);

            int value;
            switch (currentCharacter)
            {
            case '+':
                value = operand1 + operand2;
                break;
            case '-':
                value = operand1 - operand2;
                break;
            case '*':
                value = operand1 * operand2;
                break;
            case '/':
                value = operand1 / operand2;
                break;
            case '^':
                value = power(operand1, operand2);
                break;

            default:
                break;
            }

            llstack_push(stack, value);
            continue;
        }
        else
        {
            stringIndex++;
        }
    }
    return llstack_pop(stack);
}