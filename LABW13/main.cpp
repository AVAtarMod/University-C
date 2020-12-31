#include <iostream>
#include <fstream>
#include <string>

#include "files.h"
#include "arrays2d.h"
#include "useful.h"

void task1();
void task2();
void task3();
void task4();
void task6();
void task7();

int main(int argc, char const *argv[])
{
    bool noData = false;
    if (argc == 1)
    {
        printf("Введите программу для запуска: ");
        argc++;
        noData = true;
    }
    for (int i = 1; i < argc; i++)
    {
        int choice;
        if (noData)
        {
            scanf("%d", &choice);
            std::cin.ignore(32767, '\n');
        }
        else
        {
            choice = std::stoi(argv[i]);
        }

        switch (choice)
        {
        case 1:
            printf("Задание №1 #");
            task1();
            break;
        case 2:
            printf("Задание №2 #");
            task2();
            break;
        case 3:
            printf("Задание №3 #");
            task3();
            break;
        case 4:
            printf("Задание №4 #");
            task4();
            break;
        case 6:
            printf("Задание №6 #");
            task6();
            break;
        case 7:
            printf("Задание №7 #");
            task7();
            break;
        default:
            printf("Номер задачи введен не верно либо не удалось конвертировать введенные данные\n");
            break;
        }
    }
}

void task1()
{
    int *range = array2d::getRangeRandom(-100, 100);
    int *size = array2d::getSizeRandom();
    int **array = array2d::init(size[0], size[1]);
    array2d::fillRandom(array, range[0], range[1], size[0], size[1]);

    printArray(array, size[0], size[1], "files/array_task1.txt");

    array2d::delete_(array, size[0]);
    std::cout << "Выполнено\n";
}
void task2()
{
    std::ifstream in("files/array.txt");
    std::ofstream out("files/new_array.txt");
    if (!in || !out)
    {
        std::cout << "Incorrect filename\n";
        in.close();
        out.close();
    }
    else
    {
        int num;
        int count = 0;
        while (!in.eof())
        {
            in >> num;
            if (count % 2 == 0)
            {
                out << num << " ";
            }
            ++count;
        }
        out.close();
        in.close();
    }
}
void task3()
{
    // char file[255];
    // getFileAdressUser(file, 255);
    // std::ifstream in1(file);
    // getFileAdressUser(file, 255);
    // std::ifstream in2(file);
    // getFileAdressUser(file, 255);
    // std::fstream out(file);
    std::ifstream in1("files/1.txt");
    std::ifstream in2("files/2.txt");
    std::fstream out("files/3.txt");

    if (in1.good() && in2.good() && out.good())
    {
        int number1txt = 0;
        int number2txt = 0;
        int numberFromOut;

        while (!in1.eof() && out.good())
        {
            in1 >> number1txt;
            out << ' ' << number1txt;
        }

        out.seekg(0, out.beg);
        out.seekp(0, out.beg);
        while (!in2.eof())
        {
            in2 >> number2txt;
            bool matchExist = false;
            while (!out.eof() && !matchExist)
            {
                out >> numberFromOut;
                if (numberFromOut == number2txt)
                    matchExist = true;
            }
            if (!matchExist)
                out << ' ' << number2txt;
            out.seekg(0, out.beg);
            out.seekp(0, out.beg);
        }
        out.close();
        in1.close();
        in2.close();
    }
    else
        std::cout << "Incorrect filename\n";
    in1.close();
    in2.close();
    out.close();
}
void task4()
{
    char choice[255];
    getFileAdressUser(choice, 255);
    std::ifstream in(choice);
    if (in.good())
    {
        std::string expression;
        getline(in, expression);
        int result[2] = {0, 0};
        uint32_t pos = 0;
        while (expression.find('(', pos) != expression.npos)
        {
            pos = expression.find('(', pos) + 1;
            result[0]++;
        }

        pos = 0;
        while (expression.find(')', pos) != expression.npos)
        {
            pos = expression.find(')', pos) + 1;
            result[1]++;
        }
        if (result[0] == result[1])
        {
            std::cout << "Expression correct\n";
        }
        else
            std::cout << "Expression \x1B[31mincorrect!\033[0m Lacks " << abs(result[0] - result[1]) << ((result[0] > result[1]) ? " ')' " : " '(' ") << "brackets\n";
    }
    else
        std::cout << "Incorrect file\n";
    in.close();
}
void task6()
{
    std::ifstream in("files/text.in");
    if (!in.good())
    {
        std::cout << "Incorrect filename\n";
        in.close();
    }
    else
    {
        std::string max;
        std::string current;
        int lnMax = 0;

        while (in.good() && !in.eof())
        {
            getline(in, current);
            int lnCurrent = current.size();
            if (lnCurrent > lnMax)
            {
                max = current;
                lnMax = lnCurrent;
            }
        }
        in.close();

        std::cout << "\n\nMax line: " << max << "\n";
    }
}
void task7()
{
    std::string word;
    std::cout << "Enter word: ";
    std::cin >> word;
    std::ifstream in("files/text.in");
    if (!in.good())
        in.open("/home/grigory/Programming/C++/Laboratory/LABW13/files/text.in");
    if (in.good())
    {
        bool wordIsFound = false;
        while (in.good() && !wordIsFound)
        {
            std::string line;
            getline(in, line);

            int lengthWord = word.size();
            int indexStr = line.find(word);

            if (line.find(word) != line.npos)
            {
                bool isEndAlpha = isalpha(line[uint32_t(indexStr + lengthWord)]);
                bool isFirstWord = (indexStr == 0) ? true : false;
                bool isEndAlphaFirst = (isFirstWord && !isEndAlpha) ? true : false;
                bool isPrevCharAlpha = false;

                if (!isFirstWord)
                    isPrevCharAlpha = isalpha(line[uint32_t(indexStr - 1)]);

                bool isWord = (isEndAlphaFirst || (!isEndAlpha && !isPrevCharAlpha));
                if (isWord)
                {
                    wordIsFound = true;
                }
            }
        }

        std::string isfound = word + fgGreen + " was found " + reset;
        std::string notfound = word + fgRed + " was not found" + reset;
        std::cout << ((wordIsFound) ? isfound : notfound) << "\n";
    }
    else
    {
        std::cout << "File not exist\n";
    }
    in.close();
}