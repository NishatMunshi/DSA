#include <stack>
#include <string>
#include <iostream>

inline bool is_operator(char const _char)
{
    return _char == '+' or
           _char == '-' or
           _char == '*' or
           _char == '/' or
           _char == '^';
}
inline bool is_operand(char const _char)
{
    return isalnum(_char);
}

std::string infix_to_postfix(std::string const &_infix)
{
    std::string postfix;

    std::stack<std::string> stack;

    for (const auto character : _infix)
    {
        if (is_operand(character))
        {
            postfix.append(std::string(1, character));
        }
        else if (is_operator(character))
        {
            while (not stack.empty())
            {
                postfix.append(stack.top());
                stack.pop();
            }

            stack.push(std::string(1, character));
        }
    }
    while (not stack.empty())
    {
        postfix.append(stack.top());
        stack.pop();
    }
    return postfix;
}

std::string postfix_to_infix(std::string const &_postfix)
{
    std::stack<std::string> stack;

    for (const auto character : _postfix)
    {
        if (is_operand(character))
        {
            stack.push(std::string(1, character));
        }
        else if (is_operator(character))
        {
            auto const operand2 = stack.top();
            stack.pop();

            auto const operand1 = stack.top();
            stack.pop();

            auto const infix = operand1 + std::string(1, character) + operand2;
            stack.push(infix);
        }
    }

    return stack.top();
}

std::string prefix_to_infix(std::string const &_prefix)
{
    std::stack<std::string> stack;

    for (auto iterator = _prefix.crbegin(); iterator < _prefix.crend(); iterator++)
    {
        auto const character = *iterator;
        if (is_operand(character))
        {
            stack.push(std::string(1, character));
        }
        else if (is_operator(character))
        {
            auto const operand1 = stack.top();
            stack.pop();

            auto const operand2 = stack.top();
            stack.pop();

            auto const infix = operand1 + std::string(1, character) + operand2;
            stack.push(infix);
        }
    }

    return stack.top();
}

int main(void)
{

    std::string infixExp = "a+b-c+d+e";
    auto const postfixExp = infix_to_postfix(infixExp);
    std::cout << postfixExp << std::endl;

    // std::string prefixExp = "-+abc";
    // auto const infixExp = prefix_to_infix(prefixExp);
    // std::cout << infixExp << std::endl;

    // std::string postfixExp = "ab+c-";

    // auto const infix = postfix_to_infix(postfixExp);
    // std::cout << infix << std::endl;

    return 0;
}