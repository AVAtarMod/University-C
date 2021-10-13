#ifndef LW_LIB
#define LW_LIB

#include "stack.hpp"
#include "queue.hpp"
#include "string.hpp"
#include "useful.hpp"

#include <sstream>
#include <stdexcept>

bool checkBraces(const std::string braces, const std::string strWithBraces);

namespace RPN_ENGINE
{
    template <class T>
    T evalOperator(char operatorChar, Stack<T> &stack)
    {
        Stack_element<T> *A = pop(stack);
        Stack_element<T> *B = pop(stack);
        if (A == nullptr || B == nullptr)
            throw std::runtime_error("evalOperator: A||B nullptr");

        T result;
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
        case '%':
            result = B->data % A->data;
            break;
        case '^':
            if (A->data < 0)
                throw std::runtime_error("power must be >= 0");
            result = pow(B->data, static_cast<uint>(A->data));
            break;
        default:
            break;
        }
        delete A;
        delete B;
        return result;
    }

    float evalOperator(char operatorChar, Stack<float> &stack);

    enum TYPE_RPN_DATA
    {
        TRPN_NO_DATA,
        TRPN_OPERATOR,
        TRPN_NUMBER,
    };

    template <class T>
    TYPE_RPN_DATA recognizeAction(std::stringstream &source, char &operatorRpn, T &operand)
    {
        std::string operators = "+-*/%^";
        std::string buffer;
        source >> buffer;
        if (buffer.size() == 1 && operators.find(buffer[0]) != operators.npos)
        {
            operatorRpn = buffer[0];
            if (std::is_same_v<T, float>)
            {
                if (operatorRpn == '%')
                    throw std::runtime_error("recognizeAction: recognized %, but type float");
                else if (operatorRpn == '^')
                    throw std::runtime_error("recognizeAction: recognized ^, but type float");
            }
            return TYPE_RPN_DATA::TRPN_OPERATOR;
        }
        else
        {
            try
            {
                operand = conversion::strToType<T>(buffer);
                return TYPE_RPN_DATA::TRPN_NUMBER;
            }
            catch (std::invalid_argument const &ex)
            {
                operand = 0;
                std::cerr << fgBrightRed << "Error: " << reset << ex.what() << '\n';
            }
            catch (std::out_of_range const &ex)
            {
                operand = 0;
                std::cerr << fgBrightRed << "Error: " << reset << ex.what() << '\n';
            }
        }
        return TRPN_NO_DATA;
    }

    template <class T>
    T evalRpnExpressionEngine(std::string expression)
    {
        std::stringstream streamData;
        streamData.str(expression);
        Stack<T> numbers = nullptr;

        while (!streamData.eof())
        {
            char operatorRpn;
            T number;
            try
            {
                TYPE_RPN_DATA result = recognizeAction(streamData, operatorRpn, number);
                if (result == TRPN_NUMBER)
                    push(numbers, number);
                else
                    push(numbers, evalOperator(operatorRpn, numbers));
            }
            catch (const std::exception &ex)
            {
                std::cerr << fgBrightRed << "Error: " << reset << ex.what() << '\n';
            }
        }

        Stack_element<T> *last = pop(numbers);
        T result = last->data;
        delete last;
        deleteStack(numbers);
        return result;
    }
} // namespace RPN_ENGINE

template <class T>
T evalRpnExpression(const std::string expression)
{
    bool isSupportedT = (std::is_same_v<T, float> ||
                         std::is_same_v<T, int> ||
                         std::is_same_v<T, long>);
    if (isSupportedT)
        return RPN_ENGINE::evalRpnExpressionEngine<T>(expression);
    else
        throw std::runtime_error("evalRpnExpression: Unsupported type RPN expression.");
    return 0;
}

std::string convertToRpnExpression(std::string postfixExpression);

#endif //LW_LIB
