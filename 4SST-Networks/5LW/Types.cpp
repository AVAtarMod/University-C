#include "Types.hpp"

bool operator==(const sockaddr& a, const sockaddr& b)
{
    return strcmp(a.sa_data, b.sa_data) == 0 && a.sa_family == b.sa_family;
}

bool operator<(const sockaddr& a, const sockaddr& b)
{
    return strcmp(a.sa_data, b.sa_data) < 0 && a.sa_family == b.sa_family;
}
