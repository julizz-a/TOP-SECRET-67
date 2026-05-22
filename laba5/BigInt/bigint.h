# pragma once
#include <iostream>
#include <vector>


namespace mt {
class BigInt {
private:
    std::vector<char> numbers;
    bool isNegative;

    void removeZeros();
    bool isLessThan(const BigInt& other) const;
    void addAbsolute(const BigInt& other);
    void subtractAbsolute(const BigInt& other);

public:
    BigInt();
    BigInt(long long num);
    BigInt(const std::string& numStr);
    BigInt(const BigInt& other);
    BigInt& operator=(const BigInt& other);
    ~BigInt();

    BigInt operator+(const BigInt& other) const;
    BigInt& operator+=(const BigInt& other);
    BigInt& operator++();      // префиксный
    BigInt operator++(int);    // постфиксный

    BigInt operator-(const BigInt& other) const;
    BigInt& operator-=(const BigInt& other);

    BigInt operator*(const BigInt& other) const;
    BigInt& operator*=(const BigInt& other);

    bool operator==(const BigInt& other) const;
    bool operator!=(const BigInt& other) const;
    bool operator<(const BigInt& other) const;
    bool operator>(const BigInt& other) const;
    bool operator<=(const BigInt& other) const;
    bool operator>=(const BigInt& other) const;

    BigInt operator/(const BigInt& other) const;
    BigInt& operator/=(const BigInt& other);
    BigInt operator%(const BigInt& other) const;
    BigInt& operator%=(const BigInt& other);

    BigInt pow(int exponent) const;
    BigInt sqrt() const;
    BigInt nRoot(int n) const;

    friend std::ostream& operator<<(std::ostream& os, const BigInt& num);
    friend std::istream& operator>>(std::istream& is, BigInt& num);

    BigInt operator-() const;
    std::string toString() const;
    int length() const { return numbers.size(); }
    bool isZero() const { return numbers.empty() || (numbers.size() == 1 && numbers[0] == 0); }
};
}

