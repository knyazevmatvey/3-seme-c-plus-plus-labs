#include <iostream>

class Fraction {
public:
    friend std::ostream& operator<<(std::ostream& out, const Fraction& obj);  // Оператор вывода << "числитель знаминатель"
    friend std::istream& operator>>(std::istream& is, Fraction& obj);  // Оператор ввода >> числитель >> знаминатель

    Fraction& operator+=(const Fraction& other) {
        this->numerator = this->numerator * other.denominator + this->denominator * other.numerator;
        this->denominator = this->denominator * other.denominator;
        return *this;
    }
    Fraction& operator-=(const Fraction& other) {
        this->numerator = this->numerator * other.denominator - this->denominator * other.numerator;
        this->denominator = this->denominator * other.denominator;
        return *this;
    }
    Fraction& operator*=(const Fraction& other) {
        this->numerator *= other.numerator;
        this->denominator *= other.denominator;
        return *this;
    }

    // Я удалил friend, ибо зачем он нужен
    Fraction operator+(const Fraction& other) const {
        Fraction sum(other);
        sum += (*this);
        return sum;
    }
    Fraction operator-(const Fraction& other) const {
        Fraction diff(other);
        diff -= (*this);
        return diff;
    };
    Fraction operator*(const Fraction& other) const {
        Fraction product(other);
        product *= (*this);
        return product;
    }

    Fraction& operator++() {
        *this += 1;
        return *this;
    }
    Fraction operator++(int) {
        Fraction res(*this);
        ++(*this);
        return res;
    }
    Fraction& operator--() {
        *this -= 1;
        return *this;
    }
    Fraction operator--(int) {
        Fraction res(*this);
        --(*this);
        return res;
    }

    Fraction(int numerator, int denominator) : numerator(numerator), denominator(denominator) {}
    Fraction(int numerator) : Fraction(numerator, 1) {} // Делигирующий конструктор
    Fraction() = delete; // Конструктор по умолчанию должен быть удален
    Fraction(const Fraction& other) : numerator(other.numerator), denominator(other.denominator) {} // Конструктор копирования

    void fracSimplify() { // Сокращает дробь по возможности
        for (int div = 2; div < denominator; div++) {
            while ((denominator % div == 0) && (numerator % div == 0)) {
                denominator = denominator / div;
                numerator = numerator / div;
            }
        }
    }

    double calc() {  // Возвращает значение дроби в десятичном виде
        double num_d = (double)numerator;
        double den_d = (double)denominator;
        return (num_d / den_d);
    }

    int getNumerator() {  // Возвращает значение числителя
        return numerator;
    }

    int getDenominator() {  // Возвращает знамечение знаменателя
        return denominator;
    }

private:
    int numerator;
    int denominator;
};

std::ostream& operator<<(std::ostream& os, const Fraction& obj)
{
    os << obj.numerator << " " << obj.denominator;
    return os;
}

std::istream& operator>>(std::istream& is, Fraction& obj)
{
    int num, den;
    is >> num >> den;
    obj.numerator = num;
    obj.denominator = den;
    return is;
}