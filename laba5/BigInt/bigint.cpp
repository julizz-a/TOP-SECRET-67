#include "bigint.h"
#include <cmath>
#include <stdexcept>

namespace mt {

void BigInt::removeZeros() { // удаляет нули в начале числа
    while (numbers.size() > 1 && numbers.back() == 0) {
        numbers.pop_back();
    }
    if (numbers.size() == 1 && numbers[0] == 0) {
        isNegative = false;
    }
}

bool BigInt::isLessThan(const BigInt& other) const { //сравнение абсолютного значения (<)
    if (numbers.size() != other.numbers.size()) {
        return numbers.size() < other.numbers.size();
    }
    for (int i = numbers.size() - 1; i >= 0; --i) {
        if (numbers[i] != other.numbers[i]) {
            return numbers[i] < other.numbers[i];
        }
    }
    return false;
}

void BigInt::addAbsolute(const BigInt& other) { // сумма абсолютного значения
    int c = 0;
    size_t maxSize = std::max(numbers.size(), other.numbers.size());
    numbers.resize(maxSize, 0);

    for (size_t i = 0; i < maxSize; ++i) {
        int sum = numbers[i] + (i < other.numbers.size() ? other.numbers[i] : 0) + c; // условие ? значение_если_истина : значение_если_ложь
        numbers[i] = sum % 10;
        c = sum / 10;
    }

    if (c > 0) {
        numbers.push_back(c);
    }
}

void BigInt::subtractAbsolute(const BigInt& other) { // разность абсолютного значения
    int c = 0;
    for (size_t i = 0; i < numbers.size(); ++i) {
        int sub = (i < other.numbers.size() ? other.numbers[i] : 0) + c; // условие ? значение_если_истина : значение_если_ложь
        if (numbers[i] < sub) {
            c = 1;
        } else {
            numbers[i] -= sub;
            c = 0;
        }
    }
    removeZeros();
}

std::string BigInt::toString() const {
    if (this->isZero()) {
        return "0";
    }
    std::string result;
    if (isNegative) {
        result += '-';
    }
    for (int i = numbers.size() - 1; i >= 0; --i) {
        result += char(numbers[i] + '0');
    }

    return result;
}

BigInt::BigInt() : numbers(1, 0), isNegative(false) { }

BigInt::BigInt(const std::string& numStr) {
    if (numStr.empty()) {
        numbers.push_back(0);
        isNegative = false;
        return;
    }
    int start = 0;
    if (numStr[0] == '-') {
        isNegative = true;
        start = 1;
    } else {
        isNegative = false;
    }
    numbers.clear();
    for (int i = numStr.length() - 1; i >= static_cast<int>(start); --i) {
        numbers.push_back(numStr[i] - '0');
    }
    removeZeros();
}

BigInt::BigInt(const BigInt& other) : numbers(other.numbers), isNegative(other.isNegative) {}

BigInt::BigInt(long long num) {
    isNegative = num < 0;
    long long absNum = std::llabs(num);

    if (absNum == 0) {
        numbers.push_back(0);
    } else {
        while (absNum > 0) {
            numbers.push_back(absNum % 10);
            absNum /= 10;
        }
    }
}

BigInt& BigInt::operator=(const BigInt& other) {
    if (this != &other) {
        numbers = other.numbers;
        isNegative = other.isNegative;
    }
    return *this;
}

BigInt::~BigInt() {}

BigInt BigInt::operator+(const BigInt& other) const {
    BigInt result = *this;
    result += other;
    return result;
}

BigInt& BigInt::operator+=(const BigInt& other) {
    if (isNegative == other.isNegative) {
        addAbsolute(other);
    } else {
        if (this->isLessThan(other)) {
            BigInt temp = other;
            temp.subtractAbsolute(*this);
            *this = temp;
        } else {
            subtractAbsolute(other);
        }
    }
    return *this;
}

BigInt& BigInt::operator++() {
    *this += BigInt(1);
    return *this;
}

BigInt BigInt::operator++(int) {
    BigInt temp = *this;
    ++(*this);
    return temp;
}

BigInt BigInt::operator-(const BigInt& other) const {
    BigInt result = *this;
    result -= other;
    return result;
}


BigInt& BigInt::operator-=(const BigInt& other) {
    if (isNegative != other.isNegative) {
        addAbsolute(other);
    } else {
        if (isLessThan(other)) {
            BigInt temp = other;
            temp.subtractAbsolute(*this);
            *this = temp;
            isNegative = !isNegative;
        } else {
            subtractAbsolute(other);
        }
    }
    return *this;
}

BigInt BigInt::operator*(const BigInt& other) const {
    BigInt result;
    result.numbers.resize(numbers.size() + other.numbers.size(), 0);
    for (size_t i = 0; i < numbers.size(); ++i) {
        int carry = 0;
        for (size_t j = 0; j < other.numbers.size(); ++j) {
            int prod = result.numbers[i + j] + numbers[i] * other.numbers[j] + carry;
            result.numbers[i + j] = prod % 10;
            carry = prod / 10;
        }
        if (carry > 0) {
            result.numbers[i + other.numbers.size()] += carry;
        }
    }
    result.isNegative = isNegative != other.isNegative;
    result.removeZeros();

    return result;
}

BigInt& BigInt::operator*=(const BigInt& other) {
    *this = *this * other;
    return *this;
}

bool BigInt::operator==(const BigInt& other) const {
    return isNegative == other.isNegative && numbers == other.numbers;
}

bool BigInt::operator!=(const BigInt& other) const {
    return !(*this == other);
}

bool BigInt::operator<(const BigInt& other) const {
    if (isNegative != other.isNegative) {
        return isNegative;
    }
    if (isNegative) {
        return !isLessThan(other);
    }
    return isLessThan(other);
}

bool BigInt::operator>(const BigInt& other) const {
    return other < *this;
}

bool BigInt::operator<=(const BigInt& other) const {
    return !(*this > other);
}

bool BigInt::operator>=(const BigInt& other) const {
    return !(*this < other);
}

BigInt BigInt::operator/(const BigInt& other) const {
    if (other.isZero()) {
        throw std::runtime_error("Делить на ноль нельзя");
    }

    BigInt dividend = *this;
    BigInt divisor = other;
    dividend.isNegative = false;
    divisor.isNegative = false;

    if (dividend < divisor) {
        return BigInt(0);
    }

    BigInt quotient;
    BigInt current;

    for (int i = dividend.numbers.size() - 1; i >= 0; --i) {
        current.numbers.insert(current.numbers.begin(), dividend.numbers[i]);
        current.removeZeros();

        int numbersQuotient = 0;
        int left = 0, right = 9;

        while (left <= right) {
            int mid = (left + right) / 2;
            BigInt test = divisor * BigInt(mid);

            if (test <= current) {
                numbersQuotient = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        quotient.numbers.insert(quotient.numbers.begin(), numbersQuotient);
        current -= divisor * BigInt(numbersQuotient);
    }

    quotient.removeZeros();
    quotient.isNegative = isNegative != other.isNegative;
    return quotient;
}

BigInt& BigInt::operator/=(const BigInt& other) {
    *this = *this / other;
    return *this;
}

BigInt BigInt::operator%(const BigInt& other) const {
    BigInt quotient = *this / other;
    BigInt product = quotient * other;
    return *this - product;
}

BigInt& BigInt::operator%=(const BigInt& other) {
    *this = *this % other;
    return *this;
}

BigInt BigInt::pow(int exponent) const {
    if (exponent < 0) {
        throw std::invalid_argument("Отрицательный показатель степени не поддерживается");
    }
    BigInt result(1);
    BigInt base = *this;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result *= base;
        }
        base *= base;
        exponent /= 2;
    }
    return result;
}

BigInt BigInt::sqrt() const {
    if (isNegative) {
        throw std::invalid_argument("Квадратный корень из отрицательного числа");
    }

    if (isZero()) {
        return BigInt(0);
    }

    BigInt left(1);
    BigInt right = *this;
    BigInt result(0);


    while (left <= right) {
        BigInt mid = (left + right) / BigInt(2);
        BigInt square = mid * mid;

        if (square == *this) {
            return mid;
        } else if (square < *this) {
            result = mid;
            left = mid + BigInt(1);
        } else {
            right = mid - BigInt(1);
        }
    }
    return result;
}

BigInt BigInt::nRoot(int n) const {
    if (n <= 0) {
        throw std::invalid_argument("Степень корня должна быть положительной");
    }
    if (isNegative) {
        if (n % 2 == 0) {
            throw std::invalid_argument("Чётный корень из отрицательного числа не является действительным числом");
        }
        BigInt absResult = (-(*this)).nRoot(n);
        return -absResult;
    }
    if (isZero()) {
        return BigInt(0);
    }
    if (n == 1) {
        return *this;
    }
    if (n == 2) {
        return this->sqrt();
    }
    BigInt left(1);
    BigInt right = *this;
    BigInt result(0);
    while (left <= right) {
        BigInt mid = (left + right) / BigInt(2);
        BigInt power = mid.pow(n);
        if (power == *this) {
            return mid;
        } else if (power < *this) {
            result = mid;
            left = mid + BigInt(1);
        } else {
            right = mid - BigInt(1);
        }
    }
    return result;
}

std::ostream& operator<<(std::ostream& os, const BigInt& num) {
    os << num.toString();
    return os;
}

std::istream& operator>>(std::istream& is, BigInt& num) {
    std::string str;
    is >> str;
    num = BigInt(str);
    return is;
}

BigInt BigInt::operator-() const {
    BigInt result = *this;
    if (!result.isZero()) {
        result.isNegative = !result.isNegative;
    }
    return result;
}

}
