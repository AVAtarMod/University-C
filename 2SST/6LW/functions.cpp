#include "functions.hpp"

#include <string>
#include <cmath>

bool isFileExist(const char *file);
bool getPowerOf2(int number, int &power)
{
    int a, c = 0;
    while (number != 1)
    {
        a = number % 2;
        if (a != 0)
            return false;
        number /= 2;
        ++c;
    }
    power = c;
    return true;
}

std::string task3(const char *filename)
{
    if (isFileExist(filename))
    {
        std::ifstream in(filename);
        std::string result;
        int k, n, power = 0;
        in >> k >> n;
        if (getPowerOf2(n, power))
        {
            result = std::to_string(k);
            for (int i = 0; i < power; ++i)
            {
                result += "^2";
            }
            result += " = " + std::to_string(power);
            return result;
        }
        else if (getPowerOf2(n - 1, power))
        {
            result = "(" + std::to_string(k);
            for (int i = 0; i < power; ++i)
            {
                result += "^2";
            }
            result += ")*" + std::to_string(k) + " = " + std::to_string(power + 1);
            return result;
        }
        else
        {
            int tN = n;
            while (!getPowerOf2(tN, power))
            {
                --tN;
            }
            if (n == tN + 3)
            {
                int ops = 0;
                result = "(" + std::to_string(k);
                getPowerOf2(tN, power);
                ops += power;
                for (int i = 0; i < power; ++i)
                {
                    result += "^2";
                }
                result += ")*(" + std::to_string(k);
                getPowerOf2(n - tN - 1, power);
                ops += power;
                for (int i = 0; i < power; ++i)
                {
                    result += "^2";
                }
                result += ")*" + std::to_string(k) + " = " + std::to_string(ops + 2);
                return result;
            }
        }
    }
    return 0;
}

// std::string task11(const char *filename)
// {
//     if (isFileExist(filename))
//     {
//         std::ifstream in(filename);
//         std::string result;
//         int k, n;
//         in >> n >> k;
//         if (k == n)
//             return std::to_string(k);
//         else if (k == 1)
//             return std::to_string(n);
//         else if (k > n)
//             return std::to_string(0) + " - Impossible way!";
//         else
//         {
//             int result = 1;
//             bool end = false;
//             while (!end)
//             {
//                 for (unsigned i = 2; i <= k; ++i)
//                 {
//                     for (unsigned numberMaxSteps = 1; numberMaxSteps <= n / i; ++numberMaxSteps)
//                     {
//                         result += n - numberMaxSteps * i;
//                     }
//                 }
//             }
//         }
//     }
//     return "";
// }

bool isFileExist(const char *file)
{
    bool exist = false;

    std::ifstream in(file);
    if (in.good())
    {
        exist = true;
    }
    in.close();

    return exist;
}

int kindsPartitions(int lnFeild, int lnWay)
{
    return lnFeild / lnWay;
}

unsigned maxLayer(unsigned n)
{
    const unsigned nConst = n;
    unsigned layers = 0;
    for (unsigned i = 0; n <= nConst; ++i, n -= i)
        ++layers;
    if (n > nConst)
        --layers;
    return layers;
}

unsigned maxTop(unsigned n, unsigned layers)
{
    unsigned *stairSerialized = new unsigned[layers]{0};
    for (unsigned i = 0; i < layers; ++i)
    {
        stairSerialized[i] = i + 1;
        n -= i + 1;
    }
    while (n > 0)
        for (unsigned i = layers - 1u; i < 0u - 1u && n != 0; --i)
        {
            ++stairSerialized[i];
            --n;
        }

    unsigned result = stairSerialized[0];
    delete[] stairSerialized;
    return result;
}

unsigned getNumberStairs(unsigned n, unsigned layers, unsigned top = 0)
{
    unsigned result = 0;

    if (layers > 2)
    {
        unsigned max_top = maxTop(n, layers);
        for (unsigned i = 1; i <= max_top; ++i)
        {
            result += getNumberStairs(n - i, layers - 1, i);
        }
    }
    else
    {
        unsigned stairSerialized = (top + 1) * 10 + (n - top - 1);
        while (stairSerialized / 10 < stairSerialized % 10)
        {
            ++result;
            stairSerialized += 10;
            --stairSerialized;
        }
    }
    return result;
}

unsigned stairs(unsigned n, unsigned numberLayer = 2, unsigned sum = 0)
{
    if (numberLayer <= maxLayer(n))
        sum += stairs(n, numberLayer + 1, getNumberStairs(n, numberLayer));
    return sum;
}

std::string task12(const char *filename)
{
    if (isFileExist(filename))
    {
        std::ifstream in(filename);
        unsigned n;
        in >> n;
        return std::to_string(stairs(n));
    }
    return "file not exist";
}