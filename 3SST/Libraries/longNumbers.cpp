#include "longNumbers.hpp"

// SERVICE FUNCTIONS
void doDiffRemainder(UnsignedLongNumber_element* current);
bool isNeedPrintSpace(uint count, uint firstSpace);
/**
 * @brief check indexBegin and indexEnd in range [0, length)
 */
inline bool isCorrectRange(uint indexBegin, uint indexEnd, uint length);

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

void LongNumber::appendBegin(const LongNumber& longNumber) {
    UnsignedLongNumber copyLongNumber = copy(longNumber.list_);
    if (size_ > 0) {
        last_->next = *copyLongNumber;
        last_->next->previous = last_;
    } else
        list_ = copyLongNumber;
    delete copyLongNumber;
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
    do {
        pushBack(list_, static_cast<uint8_t>(uNumber % storageBase_));
        uNumber /= storageBase_;
    } while (uNumber != 0);
    update();
}

LongNumber::LongNumber() {}

LongNumber::LongNumber(const LongNumber& longNumber) { (*this) = longNumber; }

LongNumber LongNumber::getSubNumber(uint start, uint end) const {
    LongNumber result = 0;

    if (isCorrectRange(start, end, size_)) {
        result.clear();

        uint index = 0;
        UnsignedLongNumber_element* tmp = last_;

        while (index < end) {
            if (index >= start)
                pushFront(result.list_, tmp->data);
            tmp = tmp->previous;
            ++index;
        }
        result.update();
    } else {
        throw std::runtime_error("Incorrect range for getSubNumber: [" +
                                 std::to_string(start) + ", " +
                                 std::to_string(end) + "), must be in [0, " +
                                 std::to_string(size_) + ")");
    }

    return result;
}

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
        ++size;
    } else {
        last_ = first_;
    }
    size_ = size;
}

void LongNumber::clear() {
    LongNumber& obThis = *this;
    obThis.~LongNumber();
    obThis.update();
}

LongNumber LongNumber::cut(uint start, uint end) {
    if (isCorrectRange(start, end, size_)) {
        uint index = 0;
        UnsignedLongNumber_element* tmp = last_;
        // * Можно сделать функцию split
        // * А здесь нужно сделать выборку отрезка целиком, а не поэлементно
        while (index < start) {
            tmp = tmp->previous;
            ++index;
        }
        UnsignedLongNumber_element* beginCut = tmp;
        while (index < end - 1) {
            tmp = tmp->previous;
            ++index;
        }

        UnsignedLongNumber_element* endCut = tmp;
        bool isBeginExist = true, isEndExist = true;
        if (beginCut->next)
            beginCut->next->previous = endCut->previous;
        else
            isBeginExist = false;
        if (endCut->previous)
            endCut->previous->next = beginCut->next;
        else
            isEndExist = false;
        if (!isBeginExist && !isEndExist)
            list_ = nullptr;

        beginCut->next = nullptr;
        endCut->previous = nullptr;

        UnsignedLongNumber result = nullptr;
        initBySequence(result, endCut);
        LongNumber obResult(result);

        obResult.update();
        update();

        return obResult;
    } else {
        throw std::runtime_error("Incorrect range for cut: [" +
                                 std::to_string(start) + ", " +
                                 std::to_string(end) + "), must be in " +
                                 "[0, " + std::to_string(size_) + ")");
    }
    return 0;
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

LongNumber LongNumber::operator-(const LongNumber& b) const {
    LongNumber first, second;
    bool resultIsPositive = true;
    if (*this == b)
        return 0;
    else if (*this > b) {
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

LongNumber LongNumber::operator/(const LongNumber& b) const {
    LongNumber a(*this);
    const uint fullLength = a.size_;
    //TODO:fix memory corruption!
    if (a < b || b == 0)
        return 0;

    LongNumber result;
    for (uint i = 0; i < fullLength;) {
        LongNumber subNumber;
        uint lengthSubNumber = 0;
        do {
            ++lengthSubNumber;
            subNumber = a.getSubNumber(0, lengthSubNumber);
        } while (subNumber < b);

        LongNumber multipliedB = 0;
        uint8_t multiplier = 0;
        do {
            ++multiplier;
            multipliedB += b;
        } while (multipliedB < subNumber && multiplier < 10);
        if (multipliedB > subNumber) {
            --multiplier;
            multipliedB -= b;
        }

        pushFront(result.list_, multiplier);
        subNumber -= multipliedB;

        a.update();
        a.cut(0, lengthSubNumber);

        if (subNumber != 0)
            a.appendBegin(subNumber);

        i += lengthSubNumber;
    }

    a.update();
    result.update();
    return result;
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

bool LongNumber::operator<(const LongNumber& b) const {
    const LongNumber& a = *this;
    if (a.size_ < b.size_)
        return true;
    else if (a.size_ > b.size_)
        return false;

    UnsignedLongNumber_element* a_ptr = (a.initialized_) ? a.last_ : nullptr;
    UnsignedLongNumber_element* b_ptr = (b.initialized_) ? b.last_ : nullptr;
    while (a_ptr && b_ptr) {
        if (a_ptr->data < b_ptr->data)
            return true;
        else if (a_ptr->data > b_ptr->data)
            return false;
        a_ptr = (a_ptr) ? a_ptr->previous : nullptr;
        b_ptr = (b_ptr) ? b_ptr->previous : nullptr;
    }
    return false;
}

bool LongNumber::operator<=(const LongNumber& b) const { return !(*this > b); }

bool LongNumber::operator>=(const LongNumber& b) const { return !(*this < b); }

bool LongNumber::operator==(const LongNumber& b) const {
    const LongNumber& a = *this;
    if (a.size_ != b.size_)
        return false;

    return isEqual(a.list_, b.list_);
}

bool LongNumber::operator!=(const LongNumber& b) const { return !(*this == b); }

void LongNumber::operator=(const LongNumber& b) {
    LongNumber& a = *this;
    a.~LongNumber();
    a.bufferSize_ = b.bufferSize_;
    a.storageBase_ = b.storageBase_;
    a.positive_ = b.positive_;
    a.list_ = copy(b.list_);
    a.update();
}

void LongNumber::operator+=(const LongNumber& b) {
    LongNumber& a = *this;
    a = a + b;
}

void LongNumber::operator-=(const LongNumber& b) {
    LongNumber& a = *this;
    a = a - b;
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

inline bool isCorrectRange(uint indexBegin, uint indexEnd, uint length) {
    return (indexBegin < indexEnd && indexBegin < length && indexEnd <= length);
}
