#include "LW_lib.hpp"
#include "functions.hpp"

bool checkBraces(const std::string braces, const std::string strWithBraces)
{
    Stack<uint> openBraces = nullptr;
    bool strIsValid = true;

    const uint bracesLen = braces.size();
    const uint strLen = strWithBraces.size();

    for (uint16_t i = 0; i < strLen && strIsValid; ++i) {
        char current = strWithBraces[i];
        const uint braceIdx = braces.find_first_of(current);
        if (braceIdx < bracesLen) {
            if (braceIdx % 2 == 0)
                push(openBraces, static_cast<uint>(braceIdx));
            else {
                Stack_element<uint>* lastBrace = pop(openBraces);
                bool isError = (lastBrace == nullptr || lastBrace->data + 1 != braceIdx);
                if (isError)
                    strIsValid = false;
                delete lastBrace;
            }
        }
    }

    if (!isEmpty(openBraces)) {
        deleteStack(openBraces);
        strIsValid = false;
    }

    return strIsValid;
}

namespace PostfixExpression {
const std::string operators = "^%*/+-";

uint indexEndFirstExpression(std::string postfixExpression)
{
    std::string braces = "()";
    Stack<uint> openBraces = nullptr;
    const uint strLen = postfixExpression.size();
    uint index = 0;

    for (; index < strLen; ++index) {
        char current = postfixExpression[index];
        const uint braceIdx = braces.find_first_of(current);
        if (braceIdx < 2) {
            if (braceIdx == 0)
                push(openBraces, static_cast<uint>(index));
            else {
                Stack_element<uint>* tmp = pop(openBraces);
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

    /**
     * @brief This cycle can be rewrited to new
     * function
     */
    for (uint index = 0; index < strLen; ++index) {
        char current = postfixExpression[index];
        char next = postfixExpression[index + 1];
        if (current == ' ')
            continue;
        else if (current == '(') {
            std::string subExpr = postfixExpression.substr(index);
            subExpr.resize(PostfixExpression::indexEndFirstExpression(subExpr) + 1);
            subExpr = subExpr.substr(1, subExpr.size() - 2);
            push(numbers, convertToRpnExpression(subExpr));
            index += subExpr.size() + 1;
        } else if (isdigit(current) || (current == '-' && isdigit(next))) {
            uint endNumberIdx = postfixExpression.find_first_of(' ', index);
            std::string number = postfixExpression.substr(index, endNumberIdx - index);
            push(numbers, number);
            index += number.size() - 1;
        } else if (PostfixExpression::operators.find(current) != std::string::npos) {
            push(operators, current);
            index += 1;
        }
    }

    /**
     * @brief This cycle and "if" above can be rewrited to new
     * function
     */
    uint nextOperatorIdx = PostfixExpression::operators.size() + 1;
    while (!isEmpty(operators)) {
        auto currOperator = pop(operators);
        auto prevOperator = pop(operators);

        uint currOperatorIdx = PostfixExpression::operators.find(currOperator->data);

        auto currNumber = pop(numbers);
        auto prevNumber = pop(numbers);

        if (prevNumber == nullptr || currNumber == nullptr)
            throw std::runtime_error("cannot construct RPN expression");

        if (prevOperator != nullptr) {
            uint prevOperatorIdx = PostfixExpression::operators.find(prevOperator->data);
            nextOperatorIdx = prevOperatorIdx;

            if (prevOperatorIdx < currOperatorIdx)
                rpnExpression = prevNumber->data + " " + prevOperator->data + " " + currNumber->data + " " + currOperator->data + rpnExpression;
            else
                rpnExpression = prevNumber->data + " " + currNumber->data + " " + currOperator->data + " " + prevOperator->data + rpnExpression;

            delete prevOperator;
        } else {

            if (currOperatorIdx < nextOperatorIdx)
                rpnExpression = prevNumber->data + " " + currNumber->data + " " + currOperator->data + " " + rpnExpression;
            else
                rpnExpression = prevNumber->data + " " + currNumber->data + " " + rpnExpression + " " + currOperator->data;
        }

        delete currOperator;

        delete prevNumber;
        delete currNumber;
    }

    if (!isEmpty(numbers)) {
        auto currNumber = pop(numbers);
        rpnExpression = currNumber->data + " " + rpnExpression;
    }

    deleteStack(numbers);
    deleteStack(operators);

    return rpnExpression;
}

namespace RPN_ENGINE {
float evalOperator(char operatorChar, Stack<float>& stack)
{
    Stack_element<float>* A = pop(stack);
    Stack_element<float>* B = pop(stack);
    if (A == nullptr || B == nullptr)
        throw std::runtime_error("evalOperator: A||B nullptr");

    float result;
    switch (operatorChar) {
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
