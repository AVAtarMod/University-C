#ifndef Data_module
#define Data_module

#include <sstream>
#include <vector>

class Data {
public:
    uint32_t replaces;
    uint32_t comparisons;

    Data(uint32_t nReplaces = 0,
         uint32_t nComparisons = 0)
    {
        replaces = nReplaces,
        comparisons = nComparisons;
    }

    operator std::string()
    {
        std::ostringstream stream;
        stream << this->replaces
               << " "
               << this->comparisons;
        return stream.str();
    }
};

inline std::ostream& operator<<(std::ostream& out, Data data)
{
    out << "number comparisons: " << data.comparisons
        << " number replaces: " << data.replaces
        << std::endl;
    return out;
}

#endif