#include <fstream>
#include <array>
#include <string>

#include "algorithms.hpp"
#include "useful.hpp"
#include "TextTable.hpp"
#include "files.hpp"

#define cast static_cast
#define PATH "/home/grigory/Programming/C++/Laboratory/2SST/LABW2/files/table.txt"

int main()
{
    if (isFileExist(PATH))
    {
        std::ofstream out(PATH);
        {
            bool debug = false;
            std::string example1("abcbcacabbac");
            std::string substr1("bac");
            std::array<std::string, 8> row0 = {
                "#",
                "EXAMPLE",
                "Linear",
                "Linear+",
                "Boyer-Moor's",
                "Knuth-Morris-Prath's",
                "Karph-Rabin's"};
            std::array<std::string, 8> row1 = {
                "1",
                example1 + " " + substr1,
                linear(example1.c_str(), substr1.c_str()), linearAccelerated(example1.c_str(), substr1.c_str()),
                boyerMoor(example1.c_str(), substr1.c_str()),
                knuthMorisPratt(example1.c_str(), substr1.c_str()),
                rabinKarp(example1.c_str(), substr1.c_str())};
            TextTable table;
            table.addRow(row0);
            table.addRow(row1);

            if (!debug)
            {
                std::string example2("abcbcacabbac");
                std::string example3("limonlimonlimonlimom");
                std::string example4("version Reverse");
                std::string example5("sssssssssssssssssssssss");
                std::string example6("aaaaaaaaaab");
                std::string example7("kmpkmpkmpkmp");
                std::string example8("aaaaaasearchaa");
                std::string example9("a;enfwl;efnwjek");
                std::string example10("jeknrfeakjrf");

                std::string substr2("bac");
                std::string substr3("limom");
                std::string substr4("notFound");
                std::string substr5("lsssssssss");
                std::string substr6("aaab");
                std::string substr7("setkmp");
                std::string substr8("search");
                std::string substr9(";");
                std::string substr10("f");
                std::array<std::string, 8> row2 = {
                    "2",
                    example2 + " " + substr2,
                    linear(example2.c_str(), substr2.c_str()), linearAccelerated(example2.c_str(), substr2.c_str()),
                    boyerMoor(example2.c_str(), substr2.c_str()),
                    knuthMorisPratt(example2.c_str(), substr2.c_str()),
                    rabinKarp(example2.c_str(), substr2.c_str())};

                std::array<std::string, 8> row3 = {
                    "3",
                    example3 + " " + substr3,
                    linear(example3.c_str(), substr3.c_str()), linearAccelerated(example3.c_str(), substr3.c_str()),
                    boyerMoor(example3.c_str(), substr3.c_str()),
                    knuthMorisPratt(example3.c_str(), substr3.c_str()),
                    rabinKarp(example3.c_str(), substr3.c_str())};

                std::array<std::string, 8> row4 = {
                    "4",
                    example4 + " " + substr4,
                    linear(example4.c_str(), substr4.c_str()), linearAccelerated(example4.c_str(), substr4.c_str()),
                    boyerMoor(example4.c_str(), substr4.c_str()),
                    knuthMorisPratt(example4.c_str(), substr4.c_str()),
                    rabinKarp(example4.c_str(), substr4.c_str())};

                std::array<std::string, 8> row5 = {
                    "5",
                    example5 + " " + substr5,
                    linear(example5.c_str(), substr5.c_str()), linearAccelerated(example5.c_str(), substr5.c_str()),
                    boyerMoor(example5.c_str(), substr5.c_str()),
                    knuthMorisPratt(example5.c_str(), substr5.c_str()),
                    rabinKarp(example5.c_str(), substr5.c_str())};

                std::array<std::string, 8> row6 = {
                    "6",
                    example6 + " " + substr6,
                    linear(example6.c_str(), substr6.c_str()), linearAccelerated(example6.c_str(), substr6.c_str()),
                    boyerMoor(example6.c_str(), substr6.c_str()),
                    knuthMorisPratt(example6.c_str(), substr6.c_str()),
                    rabinKarp(example6.c_str(), substr6.c_str())};

                std::array<std::string, 8> row7 = {
                    "7",
                    example8 + " " + substr8,
                    linear(example8.c_str(), substr8.c_str()), linearAccelerated(example8.c_str(), substr8.c_str()),
                    boyerMoor(example8.c_str(), substr8.c_str()),
                    knuthMorisPratt(example8.c_str(), substr8.c_str()),
                    rabinKarp(example8.c_str(), substr8.c_str())};

                std::array<std::string, 8> row8 = {
                    "8",
                    example8 + " " + substr8,
                    linear(example8.c_str(), substr8.c_str()), linearAccelerated(example8.c_str(), substr8.c_str()),
                    boyerMoor(example8.c_str(), substr8.c_str()),
                    knuthMorisPratt(example8.c_str(), substr8.c_str()),
                    rabinKarp(example8.c_str(), substr8.c_str())};
                std::array<std::string, 8> row9 = {
                    "9",
                    example9 + " " + substr9,
                    linear(example9.c_str(), substr9.c_str()), linearAccelerated(example9.c_str(), substr9.c_str()),
                    boyerMoor(example9.c_str(), substr9.c_str()),
                    knuthMorisPratt(example9.c_str(), substr9.c_str()),
                    rabinKarp(example9.c_str(), substr9.c_str())};

                std::array<std::string, 8> row10 = {
                    "10",
                    example10 + " " + substr10,
                    linear(example10.c_str(), substr10.c_str()), linearAccelerated(example10.c_str(), substr10.c_str()),
                    boyerMoor(example10.c_str(), substr10.c_str()),
                    knuthMorisPratt(example10.c_str(), substr10.c_str()),
                    rabinKarp(example10.c_str(), substr10.c_str())};
                table.addRow(row2);
                table.addRow(row3);
                table.addRow(row4);
                table.addRow(row5);
                table.addRow(row6);
                table.addRow(row7);
                table.addRow(row8);
                table.addRow(row9);
                table.addRow(row10);
            }

            out << table;
        }
        out.close();
        if (!out.fail())
            std::cout << fgBrightGreen << "Work successfuly complete."
                      << "\nSee " << PATH << " for results\n"
                      << reset  ;
    }
    else
        std::cerr << "File not exist!\n";

    return 0;
}
