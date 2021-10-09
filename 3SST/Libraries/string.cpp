#include "string.hpp"

namespace stringLib
{
    std::string erase(char c, const std::string string)
    {
        std::string erased = string;
        uint64_t pos = erased.find_first_of(c);
        while (pos != string.npos)
        {
            erased.erase(pos, 1);
            pos = erased.find_first_of(c);
        }
        return erased;
    }
} // namespace stringLib

namespace conversion
{
} // namespace conversion
