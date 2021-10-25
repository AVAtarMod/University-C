#include "longNumbers.hpp"

UnsignedLongNumber LongNumber::StrToList(const char* str) {
    bool isPositive = true;
    const int partSize = getNumberDigits(storageBase_ - 1);
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

LongNumber::LongNumber(UnsignedLongNumber numberList)
    : list_(numberList), first_(nullptr), last_(nullptr) {
    update();
}
LongNumber::LongNumber(const char* cstring) : list_(StrToList(cstring)) {
    update();
}

LongNumber::LongNumber(int number) {
    while (number != 0) {
        pushFront(list_, uint8_t{number % storageBase_});
        number /= storageBase_;
    }
}

void LongNumber::print() {
    if (initialized_) {
        UnsignedLongNumber_element* tmp = last_;
        while (tmp->previous != nullptr) {
            std::cout << int{tmp->data} << " ";
            tmp = tmp->previous;
        }
        std::cout << int{tmp->data};
    }
}

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

    return LongNumber(result);
}

LongNumber LongNumber::operator*(const LongNumber& b) const {
    const LongNumber& a = *this;
    UnsignedLongNumber result = nullptr;
    UnsignedLongNumber tmp = nullptr;

    uint shiftDigits = 0;
    UnsignedLongNumber_element* b_ptr = (b.initialized_) ? *b.list_ : nullptr;
    while (b_ptr) {
        UnsignedLongNumber_element* a_ptr =
            (a.initialized_) ? *a.list_ : nullptr;
        while (a_ptr) {
            uint8_t multiplication = a_ptr->data * b_ptr->data;
            pushBack(tmp, multiplication);
            a_ptr = a_ptr->next;
        }

        ++shiftDigits;
        b_ptr = b_ptr->next;
    }

    return LongNumber(result);
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
