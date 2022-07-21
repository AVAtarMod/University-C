// Taken from https://stackoverflow.com/questions/13445688/how-to-generate-a-random-number-in-c and liitle edited
//  Code written by Serge Dundich

#include <chrono>
#include <random>
namespace hqrandom {
int engine()
{
    std::random_device rd;
    // seed value is designed specifically to make initialization
    // parameters of std::mt19937 (instance of std::mersenne_twister_engine<>)
    // different across executions of application
    std::mt19937::result_type seed = rd() ^ ((std::mt19937::result_type)std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count() + (std::mt19937::result_type)std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());

    std::mt19937 gen(seed);

    /* ^^^Yes. Generating single pseudo-random number makes no sense
    even if you use std::mersenne_twister_engine instead of rand()
    and even when your seed quality is much better than time(NULL) */
    std::mt19937::result_type n;
    // reject readings that would make n%6 non-uniformly distributed
    while ((n = gen()) > std::mt19937::max() - (std::mt19937::max() - 5) % 6) { /* bad value retrieved so get next one */
    }

    return n;
}

} // namespace hqrandom