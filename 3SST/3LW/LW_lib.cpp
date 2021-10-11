#include "LW_lib.hpp"
#include "functions.hpp"

bool checkBraces(const std::string braces, const std::string strWithBraces)
{
    Stack<uint> openBraces = nullptr;
    bool strIsValid = true;

    const uint bracesLen = braces.size();
    const uint strLen = strWithBraces.size();

    for (uint16_t i = 0; i < strLen && strIsValid; ++i)
    {
        char current = strWithBraces[i];
        const uint braceIdx = braces.find_first_of(current);
        if (braceIdx < bracesLen)
        {
            if (braceIdx % 2 == 0)
                push(openBraces, static_cast<uint>(braceIdx));
            else
            {
                Stack_element<uint> *lastBrace = pop(openBraces);
                bool isError = (lastBrace == nullptr ||
                                lastBrace->data + 1 != braceIdx);
                if (isError)
                    strIsValid = false;
                delete lastBrace;
            }
        }
    }

    if (!isEmpty(openBraces))
    {
        deleteStack(openBraces);
        strIsValid = false;
    }

    return strIsValid;
}

namespace PostfixExpression
{
    std::string operators = "^%*/+-";

    uint indexEndFirstExpression(std::string postfixExpression)
    {
        std::string braces = "()";
        Stack<uint> openBraces = nullptr;
        const uint strLen = postfixExpression.size();
        uint index = 0;

        for (; index < strLen; ++index)
        {
            char current = postfixExpression[index];
            const uint braceIdx = braces.find_first_of(current);
            if (braceIdx < 2)
            {
                if (braceIdx == 0)
                    push(openBraces, static_cast<uint>(index));
                else
                {
                    Stack_element<uint> *tmp = pop(openBraces);
                    if (tmp != nullptr)
                        delete tmp;
                    if (isEmpty(openBraces))
                        break;
                }
            }
        }

        deleteStack(openBraces);
        return index;
    }

} // namespace PostfixExpression

std::string convertToRpnExpression(std::string postfixExpression)
{
    std::string rpnExpression = "";
    Stack<std::string> numbers = nullptr;
    Stack<char> operators = nullptr;
    const uint strLen = postfixExpression.size();

    for (uint index = 0; index < strLen; ++index)
    {
        char current = postfixExpression[index];
        if (current == ' ')
            continue;
        else if (current == '(')
        {
            std::string subExpr = postfixExpression.substr(index);
            subExpr.resize(PostfixExpression::indexEndFirstExpression(subExpr) + 1);
            subExpr.erase(0, 1);
            subExpr.pop_back();
            push(numbers, convertToRpnExpression(subExpr));
            index += subExpr.size() + 1;
        }
        else if (isdigit(current))
        {
            uint endNumberIdx = postfixExpression.find_first_of(' ', index);
            std::string number = postfixExpression.substr(index, endNumberIdx - index);
            push(numbers, number);
            index += number.size() - 1;
        }
        else if (PostfixExpression::operators.find(current) != std::string::npos)
        {
            if (!isEmpty(operators))
            {
                auto prevOperator = pop(operators);
                uint prevOperatorIdx = PostfixExpression::operators.find(prevOperator->data);
                uint currOperatorIdx = PostfixExpression::operators.find(current);

                auto subExpr = postfixExpression.substr(index + 1);
                auto currNumber = pop(numbers);
                auto prevNumber = pop(numbers);
                if (prevNumber == nullptr || currNumber == nullptr)
                    throw std::runtime_error("cannot construct RPN expression");
                if (prevOperatorIdx < currOperatorIdx)
                {
                    rpnExpression +=
                        prevNumber->data +
                        " " +
                        currNumber->data +
                        " " +
                        prevOperator->data +
                        " " +
                        convertToRpnExpression(subExpr) +
                        " " +
                        current;
                }
                else
                {
                    rpnExpression +=
                        prevNumber->data +
                        " " +
                        currNumber->data +
                        " " +
                        convertToRpnExpression(subExpr) +
                        " " +
                        current +
                        " " +
                        prevOperator->data;
                }
                delete prevNumber;
                delete currNumber;
                break;
            }
            else
                push(operators, current);
        }
    }
    if (!isEmpty(operators))
    {
        auto lastOperator = pop(operators);
        auto currNumber = pop(numbers);
        auto prevNumber = pop(numbers);
        if (prevNumber == nullptr || currNumber == nullptr)
            throw std::runtime_error("cannot construct RPN expression");
        rpnExpression +=
            prevNumber->data +
            " " +
            currNumber->data +
            " " +
            lastOperator->data;

        delete lastOperator;
        delete prevNumber;
        delete currNumber;
    }

    if (!isEmpty(numbers))
    {
        auto lastNumber = pop(numbers);
        rpnExpression += lastNumber->data;
        delete lastNumber;
    }

    deleteStack(numbers);
    deleteStack(operators);

    return rpnExpression;
}

namespace RPN_ENGINE
{
    float evalOperator(char operatorChar, Stack<float> &stack)
    {
        Stack_element<float> *A = pop(stack);
        Stack_element<float> *B = pop(stack);
        if (A == nullptr || B == nullptr)
            throw std::runtime_error("evalOperator: A||B nullptr");

        float result;
        switch (operatorChar)
        {
        case '+':
            result = B->data + A->data;
            break;
        case '-':
            result = B->data - A->data;
            break;
        case '*':
            result = B->data * A->data;
            break;
        case '/':
            result = B->data / A->data;
            break;
        default:
            break;
        }
        delete A;
        delete B;
        return result;
    }
} // namespace RPN_ENGINE
