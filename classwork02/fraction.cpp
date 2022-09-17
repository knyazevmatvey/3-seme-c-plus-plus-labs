#include<iostream>
using namespace std;

class Fraction {
public:
    Fraction(int numerator, int denominator) : numerator(numerator), denominator(denominator) {}

    Fraction(int numerator) : Fraction(numerator, 1) {} // Делигирующий конструктор
    Fraction() = delete; // Конструктор по умолчанию должен быть удален

    Fraction(const Fraction& other) {
        numerator = other.numerator;
        denominator = other.denominator;
    } // Конструктор копирования

    void printFraction() {  // Выводит дробь в формате 'numerator / denominator'
        std::cout << numerator << "/" << denominator;
    }

    void fracReverse() {  // Перевернуть дробь, знаменатель<->числитель
        int tmp = numerator;
        numerator = denominator;
        denominator = tmp;
    }

    void fracSimplify() { // Сокращает дробь по возможности
        for (int div = 2; div < denominator; div++) {
            while ((denominator % div == 0) && (numerator % div == 0)) {
                denominator = denominator / div;
                numerator = numerator / div;
            }
        }
    }

    void multByNumber(int value) { // Умножить дробь на число
        numerator *= value;
    }

    void multByFrac(const Fraction& other) {
        numerator *= other.numerator;  // Умножить дробь на другую дробь, результат оставить в вызывающей (в this)
        denominator *= other.denominator;
    }

    Fraction multByFracReturn(const Fraction& other) const {
        return Fraction(numerator * other.numerator, denominator * other.denominator);  // умножает дроби и возвращает результат в третью
    }

    void sumFrac(const Fraction& other) {  // Просуммировать дробь на другую дробь, результат оставить в вызывающей (в this)
        numerator = numerator * other.denominator + denominator * other.numerator;
        denominator *= other.denominator;
    }

    Fraction sumFracReturn(const Fraction& other) const { // просуммировать дроби и вернуть результат в третью
        return Fraction(numerator * other.denominator + denominator * other.numerator, denominator * other.denominator);
    }

    void diffFrac(const Fraction& other) {
        Fraction negative_other = other; // Взять разность дробей, результат оставить в вызывающей (в this)
        negative_other.multByNumber(-1);
        this->sumFrac(negative_other);
    }

    Fraction diffFracReturn(const Fraction& other) const {
        Fraction negative_other = other;  // Взять разность дробей, результат в третью
        negative_other.multByNumber(-1);
        return this->sumFracReturn(negative_other);
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

int main() {
}