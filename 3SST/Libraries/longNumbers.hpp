#ifndef LONGNUMBERS_LIB
#define LONGNUMBERS_LIB

#include <iostream>

#include "list.hpp"
#include "string.hpp"

using UnsignedLongNumber = List2D<uint8_t>;
using UnsignedLongNumber_element = List2D_element<uint8_t>;

/**
 * TODO move all libs to include path
 *
 * @brief Long Number class
 */
class LongNumber {
  private:
    uint bufferSize_ = INT16_MAX;
    uint storageBase_ = 10;
    uint size_ = 0;

    UnsignedLongNumber list_ = nullptr;
    UnsignedLongNumber_element* first_ = nullptr;
    UnsignedLongNumber_element* last_ = nullptr;

    bool positive_ = true;
    bool initialized_ = false;

    UnsignedLongNumber StrToList(const char* str);
    void normalize();
    void appendBegin(const LongNumber& longNumber);

  public:
    LongNumber(UnsignedLongNumber numberList);
    LongNumber(const char* cstring);
    LongNumber(int number);
    LongNumber();

    /**
     * @brief Construct a new Long Number object as @a copy longNumber
     * @note This is copy-constructor
     * @param longNumber object LongNumber
     */
    LongNumber(const LongNumber& longNumber);

    uint getSize() const { return size_; }

    /**
     * @brief Get the subnumber from [start,end)
     * @param indexBegin index of begin of range
     * @param indexEnd index of end of range. Must be > indexStart
     * @return LongNumber subnumber.
     */
    LongNumber getSubNumber(uint indexBegin, uint indexEnd) const;

    bool isInitialized() const { return initialized_; }

    void print();
    void update();

    /**
     * @brief clear LongNumber content.
     */
    void clear();

    /**
     * @brief Cut number from [start,end),
     * @param indexBegin index of begin of range
     * @param indexEnd index of end of range. Must be > indexStart
     * @return LongNumber subnumber.
     */
    LongNumber cut(uint indexStart, uint indexEnd);

    /**
     * @brief Const operators
     */

    LongNumber operator+(const LongNumber& b) const;
    LongNumber operator-(const LongNumber& b) const;
    LongNumber operator*(const LongNumber& b) const;
    LongNumber operator/(const LongNumber& b) const;

    bool operator>(const LongNumber& b) const;
    bool operator<(const LongNumber& b) const;
    bool operator<=(const LongNumber& b) const;
    bool operator>=(const LongNumber& b) const;
    bool operator==(const LongNumber& b) const;
    bool operator!=(const LongNumber& b) const;

    /**
     * @brief Non-const operators
     */

    /**
     * @brief  Assign copy of B to A (where A = B)
     *
     * @param b Value for copying to A
     */
    void operator=(const LongNumber& b);
    void operator+=(const LongNumber& b);
    void operator-=(const LongNumber& b);
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
