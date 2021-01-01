#ifndef STRUCT
#define STRUCT

struct Member
{
    std::string fullName;
    std::string country;
    std::string city;
    std::string work;
    uint32_t age;
    uint64_t phoneNumber;
    explicit operator const char*()
    {
        std::string result = fullName + country + city + work + std::to_string(age) + std::to_string(phoneNumber);
        return result.c_str();
    }
};

std::istream &operator>>(std::istream &input, Member &member);
std::ostream &operator<<(std::ostream &output, Member &member);

#endif