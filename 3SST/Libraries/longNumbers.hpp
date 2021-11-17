#ifndef LONGNUMBERS_LIB
#define LONGNUMBERS_LIB

#include <iostream>

#include "list.hpp"
#include "string.hpp"

using UnsignedLongNumber = List2D<uint8_t>;
using UnsignedLongNumber_element = List2D_element<uint8_t>;

/**
 * TODO move all libs to include path
 * TODO add signed number support
 *
 * @brief Long Number class
 */
class LongNumber {
  private:
    uint bufferSize_ = UINT8_MAX;
    uint storageBase_ = 10;
    uint size_ = 0;

    UnsignedLongNumber list_;
    UnsignedLongNumber_element* first_;
    UnsignedLongNumber_element* last_;

    bool positive_ = true;
    bool initialized_ = false;

    UnsignedLongNumber StrToList(const char* str);
    void normalize();

  public:
    LongNumber(UnsignedLongNumber numberList = nullptr);
    LongNumber(const char* cstring);
    LongNumber(int number);
    LongNumber(const LongNumber& longNumber);

    uint getSize() const { return size_; }
    uint isInitialized() const { return initialized_; }

    void print();
    void update();

    LongNumber operator+(const LongNumber& b) const;
    LongNumber operator*(const LongNumber& b) const;
    LongNumber operator-(const LongNumber& b) const;
    bool operator>(const LongNumber& b) const;
    bool operator<(const LongNumber& b) const;

    void operator=(const LongNumber& b);
    void operator*=(const LongNumber& b);

    friend std::istream& operator>>(std::istream& input, LongNumber& number);
    friend std::ostream& operator<<(std::ostream& output,
                                    const LongNumber& number);

    ~LongNumber() {
        if (initialized_)
            deleteList(list_);
    }
};

std::istream& operator>>(std::istream& input, LongNumber& number);
std::ostream& operator<<(std::ostream& output, const LongNumber& number);

LongNumber fact(const int number);

#endif // LONGNUMBERS_LIB
