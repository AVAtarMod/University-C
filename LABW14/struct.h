#ifndef STRUCT
#define STRUCT

#include <memory>
#include <cstring>
#define STR_SIZE 255
#define BUFFER_SIZE 1032 /** @def BUFFER_SIZE 1032 @brief 1032 bytes*/

template <class T>
std::unique_ptr<char[]> numberBinary(T number)
{
    //TODO Строка результата больше предпологаемого размера;
    auto bin = std::make_unique<char[]>(sizeof(number));
    strncpy(bin.get(), std::to_string(number).c_str(), sizeof(number));
    return bin;
}

template <class T>
T numberDecimal(char* numberBinary)
{
    return static_cast<T>(atoll(numberBinary));
}

struct Member
{
    char fullName[STR_SIZE];
    char country[STR_SIZE];
    char city[STR_SIZE];
    char work[STR_SIZE];
    uint32_t age;
    uint64_t phoneNumber;

    /**
     * @brief Convert structure to char* buffer BUFFER_SIZE bytes
     * @return smart pointer to char*
     */
    operator std::unique_ptr<char[]>()
    {
        auto ageBuf = numberBinary(age);
        auto phoneNumberBuf = numberBinary(phoneNumber);

        auto buffer = std::make_unique<char[]>(BUFFER_SIZE);
        char *ptrCopy = buffer.get();

        /**
         * @brief Filling main buffer from Member
         */
        memcpy(ptrCopy            , fullName, STR_SIZE);
        memcpy(ptrCopy += STR_SIZE, country, STR_SIZE);
        memcpy(ptrCopy += STR_SIZE, city, STR_SIZE);
        memcpy(ptrCopy += STR_SIZE, work, STR_SIZE);
        memcpy(ptrCopy += STR_SIZE, (char *)(&age), sizeof(age));
        memcpy(ptrCopy += sizeof(age),(char *)(&phoneNumber),
        sizeof(phoneNumber));

        return buffer;
    }

    /**
     * @brief Default constructor
     */
    Member(){}

    /**
     * @brief Construct from buffer
     * @param buffer[1032] extracted from binary file or other place;
     */
    Member(char buffer[BUFFER_SIZE])
    {
        char *ptrBuffer = buffer;
        char ageBuff[sizeof(age)];
        char numberPhoneBuff[sizeof(phoneNumber)];
        strncpy(fullName,       ptrBuffer, STR_SIZE);
        strncpy(country,        ptrBuffer+=STR_SIZE, STR_SIZE);
        strncpy(city,           ptrBuffer+=STR_SIZE, STR_SIZE);
        strncpy(work,           ptrBuffer+=STR_SIZE, STR_SIZE);
        strncpy(ageBuff,        ptrBuffer+=STR_SIZE, sizeof(age));
        strncpy(numberPhoneBuff,ptrBuffer+=sizeof(age), sizeof(phoneNumber));
        age = *((uint32_t *)(ageBuff));
        phoneNumber = *((uint64_t *)(numberPhoneBuff));
    }
};

std::istream &operator>>(std::istream &input, Member &member);
std::ostream &operator<<(std::ostream &output, Member &member);

bool binWriteMember(std::ofstream &output, Member &member);
bool binReadMember(std::ifstream &input, Member &member);

#endif