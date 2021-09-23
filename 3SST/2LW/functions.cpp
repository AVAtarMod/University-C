#include <iostream>
#include <random>
#include <chrono>

int getRandomNumber(int from, int to)
{
    try
    {
        if (from > to)
            throw "Incorrect couple 'from - to' for generating random numbers";
    }
    catch (const char *message)
    {
        std::cerr << message << '\n';
        exit(1);
    }

    unsigned int now = static_cast<unsigned>(std::chrono::high_resolution_clock::now().time_since_epoch().count() % 10000);
    std::mt19937 engine(now);
    std::uniform_int_distribution<int> random(from, to);

    return random(engine);
}
