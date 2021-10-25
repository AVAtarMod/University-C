#ifndef LONGNUMBERS_LIB
#define LONGNUMBERS_LIB

#include <iostream>

#include "list.hpp"
#include "string.hpp"

template <class T> using LongNumber_element = List2D_element<T>;

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

  public:
    LongNumber(UnsignedLongNumber numberList = nullptr);
    LongNumber(const char* cstring);
    LongNumber(int number);

    const uint getSize() const { return size_; }
    const uint isInitialized() const { return initialized_; }

    void print();
    void update();

    LongNumber operator+(const LongNumber& b) const;
    LongNumber operator*(const LongNumber& b) const;
    friend std::istream& operator>>(std::istream& input, LongNumber& number);

    ~LongNumber() { deleteList(list_); }
};

LongNumber fact(const LongNumber& a, const LongNumber& b);

#endif // LONGNUMBERS_LIB
