#if defined(_WIN32)
#define PLATFORM_NAME 0
#include <fcntl.h>
#include <io.h>
#elif defined(__linux__)
#define PLATFORM_NAME 1
#include <locale>
#endif

#include <iostream>

int main(int argc, char const* argv[])
{
    std::cout << "Hello from ";

#if PLATFORM_NAME == 0
    std::cout << "Windows!";
    _setmode(_fileno(stdout), _O_U8TEXT);
#elif PLATFORM_NAME != 0
    std::cout << "Non-windows!";
    setlocale(LC_CTYPE, "");
    #if PLATFORM_NAME == 1 || PLATFORM_NAME == 2
        std::cout << " Linux or unknown OS!";
        setlocale(LC_CTYPE, "");
    #endif
#endif

    return 0;
}
