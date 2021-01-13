#ifndef STRUCT
#define STRUCT

#include <memory>
#include <cstring>

#define STR_SIZE 255
#define BUFFER_SIZE 1032 /** @def BUFFER_SIZE 1032 @brief 1032 bytes*/

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
        char ageBuf[sizeof(age)]{0};
        char phoneNumberBuf[sizeof(phoneNumber)]{0};
        strncpy(ageBuf,(char *)(&age),sizeof(age));
        strncpy(phoneNumberBuf,(char *)(&phoneNumber),sizeof(phoneNumber));

        auto buffer = std::make_unique<char[]>(BUFFER_SIZE);
        char *ptrCopy = buffer.get();

        /**
         * @brief Filling main buffer from Member
         */
        memcpy(ptrCopy            , fullName, STR_SIZE);
        memcpy(ptrCopy += STR_SIZE, country, STR_SIZE);
        memcpy(ptrCopy += STR_SIZE, city, STR_SIZE);
        memcpy(ptrCopy += STR_SIZE, work, STR_SIZE);
        memcpy(ptrCopy += STR_SIZE, ageBuf, sizeof(age));
        memcpy(ptrCopy += sizeof(age),phoneNumberBuf,
        sizeof(phoneNumber));

        return buffer;
    }

    /**
     * @brief Default constructor with support user values
     */
    Member(const char fn[STR_SIZE] = "",const char cn[STR_SIZE] = "",
           const char ct[STR_SIZE] = "",const char wk[STR_SIZE] = "",
           uint32_t ag = 0,uint64_t pN = 0)
           {
               strncpy(fullName,fn,STR_SIZE);
               strncpy(country,ct,STR_SIZE);
               strncpy(city,cn,STR_SIZE);
               strncpy(work,wk,STR_SIZE);
               age = ag;
               phoneNumber = pN;
           }

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


std::unique_ptr<char[]> getLastName(Member member);
static bool sortFullnameA_Z(const Member &left, const Member &right)
{
    return (strcoll(getLastName(left.fullName).get(), getLastName(right.fullName).get()) < 0);
}

static bool sortFullnameZ_A(const Member &left, const Member &right)
{
    return (strcoll(getLastName(left.fullName).get(), getLastName(right.fullName).get()) > 0);
}

std::istream &operator>>(std::istream &input, Member &member);
std::ostream &operator<<(std::ostream &output, Member &member);

bool binWriteMember(std::ofstream &output, Member &member);
bool binReadMember(std::ifstream &input, Member &member);

bool searchText(const char *source, const char *text);
void editMember(Member &member);

#endif