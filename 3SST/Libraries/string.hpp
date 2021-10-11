#ifndef STRING_LIB
#define STRING_LIB

#include <string>

namespace stringLib
{
    std::string erase(char c, const std::string string);
} // namespace string

namespace conversion
{
    template <class T>
    T strToType(std::string str)
    {
        if (std::is_same_v<T, float>)
            return std::stof(str);
        else if (std::is_same_v<T, int>)
            return std::stoi(str);
        else if (std::is_same_v<T, long>)
            return std::stol(str);
        else if (std::is_same_v<T, uint>)
            return static_cast<uint>(std::stol(str));
        else
            return 0;
    }

} // namespace conversion

#endif //STRING_LIB
