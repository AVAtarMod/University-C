#include <iostream>
#include <vector>

#include "functions.hpp"

void task1()
{
    std::cout << "Magick square\n";
    unsigned **task1 = magickSquare();
    for (int i = 0; i < 3; ++i)
    {
        for (int ii = 0; ii < 3; ++ii)
        {
            std::cout << task1[i][ii] << " ";
        }
        std::cout << "\n";
    }
    array2d::delete_(task1, 3);
}

void task2()
{
    std::cout << "Enter N boxes: ";
    int numberBoxes;
    std::cin >> numberBoxes;

    const int amountNumbers = numberBoxes, amountOperators = numberBoxes - 1;

    int *array = new int[numberBoxes + numberBoxes - 1];
    std::cout << "Enter operators and then numbers:\n ";
    for (int i = 0; i < amountNumbers + amountOperators; ++i)
    {
        std::string temp;
        std::cin >> temp;
            std::cout << temp;
        if (i > amountNumbers)
        {
            array[i] = temp[0];
            try
            {
                if (array[i] != '<' || array[i] != '>')
                    throw temp[0] + " cannot handle";
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
        }
        else
            array[i] = atoi(temp.c_str());
    }

    delete[] array;
}
void task3()
{
}
void task4()
{
}
void task5()
{
    int ar[13] = {1,3,5,2,12,15,11,53,13,10,9,43,4};

}
void task6()
{
}

int main()
{
    task1();
    // task2();
    task3();
    task4();
    task5();
    task6();
    return 0;
}
