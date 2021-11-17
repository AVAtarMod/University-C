#include "longNumbers.hpp"

// SERVICE FUNCTIONS
void doDiffRemainder(UnsignedLongNumber_element* current);
bool isNeedPrintSpace(uint count, uint firstSpace);

UnsignedLongNumber LongNumber::StrToList(const char* str) {
    bool isPositive = true;
    UnsignedLongNumber result = nullptr;

    for (uint i = 0; str[i] != '\0'; ++i) {
        if (isPositive && str[i] == '-')
            isPositive = positive_ = false;
        else if (isdigit(str[i])) {
            uint8_t number = conversion::charToInt(str[i]);
            pushFront(result, number);
        }
    }
    return result;
}

void LongNumber::normalize() {
    UnsignedLongNumber_element* last = this->last_;
    while (last && last->data == 0) {
        const UnsignedLongNumber_element* tmp = last;
        last = last->previous;
        last->next = nullptr;
        delete tmp;
    }
    update();
}

LongNumber::LongNumber(UnsignedLongNumber numberList)
    : list_(numberList), first_(nullptr), last_(nullptr) {
    normalize();
}

LongNumber::LongNumber(const char* cstring) : list_(StrToList(cstring)) {
    update();
}

LongNumber::LongNumber(int number) : list_(nullptr) {
    uint uNumber = static_cast<uint>(number);
    while (uNumber != 0) {
        pushBack(list_, static_cast<uint8_t>(uNumber % storageBase_));
        uNumber /= storageBase_;
    }
    update();
}

/**
 * @brief Construct a new Long Number object as @a copy longNumber
 * @note This is copy-constructor
 * @param longNumber object LongNumber
 */
LongNumber::LongNumber(const LongNumber& longNumber) { (*this) = longNumber; }

void LongNumber::print() { std::cout << *this; }

void LongNumber::update() {
    bool isInitialized = isInited(list_);
    uint size = 0;

    initialized_ = isInitialized;
    first_ = (isInitialized) ? *list_ : nullptr;

    UnsignedLongNumber_element* tmp = first_;

    if (tmp != nullptr) {
        while (tmp->next != nullptr) {
            tmp = tmp->next;
            ++size;
        }

        last_ = tmp;
    } else {
        last_ = first_;
    }
    size_ = size + 1;
}

LongNumber LongNumber::operator+(const LongNumber& b) const {
    // TODO Storage base support
    const LongNumber& a = *this;
    UnsignedLongNumber result = nullptr;

    UnsignedLongNumber_element* a_ptr = (a.initialized_) ? *a.list_ : nullptr;
    UnsignedLongNumber_element* b_ptr = (b.initialized_) ? *b.list_ : nullptr;

    uint8_t remainder = 0;
    while (a_ptr || b_ptr) {
        uint currentDataA = (a_ptr) ? a_ptr->data : 0;
        uint currentDataB = (b_ptr) ? b_ptr->data : 0;

        const uint sum = currentDataA + currentDataB + remainder;
        const uint8_t digit = sum % 10;
        remainder = (sum - digit) / 10;

        pushBack(result, digit);

        a_ptr = (a_ptr && a_ptr->next) ? a_ptr->next : nullptr;
        b_ptr = (b_ptr && b_ptr->next) ? b_ptr->next : nullptr;
    }
    if (remainder != 0)
        pushBack(result, remainder);

    return result;
}

LongNumber LongNumber::operator*(const LongNumber& b) const {
    const LongNumber& a = *this;
    LongNumber obResult;

    uint shiftDigits = 0;
    UnsignedLongNumber_element* b_ptr = (b.initialized_) ? *b.list_ : nullptr;
    while (b_ptr) {
        LongNumber tmp;
        UnsignedLongNumber_element* a_ptr =
            (a.initialized_) ? *a.list_ : nullptr;
        uint8_t remainder = 0;
        while (a_ptr) {
            uint8_t multiplication = a_ptr->data * b_ptr->data + remainder;
            pushBack(tmp.list_, static_cast<uint8_t>(multiplication % 10));

            remainder = multiplication / 10;
            a_ptr = a_ptr->next;
        }
        if (remainder != 0)
            pushBack(tmp.list_, remainder);

        for (uint i = 0; i < shiftDigits; ++i) {
            pushFront(tmp.list_, uint8_t{0});
        }

        tmp.update();
        obResult = tmp + obResult;

        ++shiftDigits;
        b_ptr = b_ptr->next;
    }

    return obResult;
}

LongNumber LongNumber::operator-(const LongNumber& b) const {
    // TODO Storage base support
    LongNumber first, second;
    bool resultIsPositive = true;
    if (*this > b) {
        first = *this;
        second = b;
    } else {
        first = b;
        second = *this;
        resultIsPositive = false;
    }

    UnsignedLongNumber result = nullptr;

    UnsignedLongNumber_element* a_ptr =
        (first.initialized_) ? *first.list_ : nullptr;
    UnsignedLongNumber_element* b_ptr =
        (second.initialized_) ? *second.list_ : nullptr;

    uint8_t remainder = 0;
    while (a_ptr || b_ptr) {
        const bool aNull = (a_ptr == nullptr);
        const bool bNull = (b_ptr == nullptr);

        if (remainder == 1)
            doDiffRemainder(a_ptr);
        uint dataA = (aNull) ? 0 : a_ptr->data;
        uint dataB = (bNull) ? 0 : b_ptr->data;

        remainder = (dataA < dataB) ? 1 : 0;

        const uint8_t diff = dataA + (remainder * 10) - dataB;

        pushBack(result, diff);

        a_ptr = (aNull) ? nullptr : a_ptr->next;
        b_ptr = (bNull) ? nullptr : b_ptr->next;
    }

    LongNumber obResult(result);
    obResult.positive_ = resultIsPositive;
    obResult.normalize();
    return obResult;
}

bool LongNumber::operator>(const LongNumber& b) const {
    const LongNumber& a = *this;
    if (a.size_ > b.size_)
        return true;
    else if (a.size_ < b.size_)
        return false;

    UnsignedLongNumber_element* a_ptr = (a.initialized_) ? a.last_ : nullptr;
    UnsignedLongNumber_element* b_ptr = (b.initialized_) ? b.last_ : nullptr;
    while (a_ptr && b_ptr) {
        if (a_ptr->data > b_ptr->data)
            return true;
        else if (a_ptr->data < b_ptr->data)
            return false;
        a_ptr = (a_ptr) ? a_ptr->previous : nullptr;
        b_ptr = (b_ptr) ? b_ptr->previous : nullptr;
    }
    return false;
}
bool LongNumber::operator<(const LongNumber& b) const { return !(*this > b); }

/**
 * @brief  Assign copy of B to A (where A = B)
 *
 * @param b Value for copying to A
 */
void LongNumber::operator=(const LongNumber& b) {
    LongNumber& a = *this;
    a.~LongNumber();

    a.bufferSize_ = b.bufferSize_;
    a.storageBase_ = b.storageBase_;
    a.positive_ = b.positive_;
    a.list_ = copy(b.list_);
    a.update();
}

void LongNumber::operator*=(const LongNumber& b) {
    LongNumber& a = *this;
    a = a * b;
}

std::istream& operator>>(std::istream& input, LongNumber& number) {
    char* buffer = new char[number.bufferSize_];
    input.getline(buffer, number.bufferSize_);
    number.list_ = number.StrToList(buffer);

    number.update();
    delete[] buffer;
    input.clear();
    return input;
}

std::ostream& operator<<(std::ostream& output, const LongNumber& number) {
    if (number.initialized_) {
        UnsignedLongNumber_element* tmp = number.last_;
        uint count = 0;
        uint firstSpace = number.size_ % 3;
        if (!number.positive_)
            output << '-';
        while (tmp->previous != nullptr) {
            output << static_cast<int>(tmp->data);
            tmp = tmp->previous;
            ++count;
            if (isNeedPrintSpace(count, firstSpace))
                output << " ";
        }
        output << static_cast<int>(tmp->data);
    }
    return output;
}

LongNumber fact(const int number) {
    LongNumber result(1);
    for (int i = 2; i <= number; i++) {
        result *= LongNumber(i);
    }
    return result;
}

// SERVICE FUNCTIONS

void doDiffRemainder(UnsignedLongNumber_element* current) {
    while (current != nullptr && current->data == 0) {
        current->data = 9;
        current = current->next;
    }
    if (current != nullptr)
        --current->data;
}

bool isNeedPrintSpace(uint count, uint firstSpace) {
    if (count == firstSpace)
        return true;
    else if (count > firstSpace && (count - firstSpace) % 3 == 0)
        return true;
    return false;
}
