#include<iostream>
using namespace std;

class Fraction {
public:
    Fraction(int numerator, int denominator) : numerator(numerator), denominator(denominator) {}

    Fraction(int numerator) : Fraction(numerator, 1) {} // ������������ �����������
    Fraction() = delete; // ����������� �� ��������� ������ ���� ������

    Fraction(const Fraction& other) {
        numerator = other.numerator;
        denominator = other.denominator;
    } // ����������� �����������

    void printFraction() {  // ������� ����� � ������� 'numerator / denominator'
        std::cout << numerator << "/" << denominator;
    }

    void fracReverse() {  // ����������� �����, �����������<->���������
        int tmp = numerator;
        numerator = denominator;
        denominator = tmp;
    }

    void fracSimplify() { // ��������� ����� �� �����������
        for (int div = 2; div < denominator; div++) {
            while ((denominator % div == 0) && (numerator % div == 0)) {
                denominator = denominator / div;
                numerator = numerator / div;
            }
        }
    }

    void multByNumber(int value) { // �������� ����� �� �����
        numerator *= value;
    }

    void multByFrac(const Fraction& other) {
        numerator *= other.numerator;  // �������� ����� �� ������ �����, ��������� �������� � ���������� (� this)
        denominator *= other.denominator;
    }

    Fraction multByFracReturn(const Fraction& other) const {
        return Fraction(numerator * other.numerator, denominator * other.denominator);  // �������� ����� � ���������� ��������� � ������
    }

    void sumFrac(const Fraction& other) {  // �������������� ����� �� ������ �����, ��������� �������� � ���������� (� this)
        numerator = numerator * other.denominator + denominator * other.numerator;
        denominator *= other.denominator;
    }

    Fraction sumFracReturn(const Fraction& other) const { // �������������� ����� � ������� ��������� � ������
        return Fraction(numerator * other.denominator + denominator * other.numerator, denominator * other.denominator);
    }

    void diffFrac(const Fraction& other) {
        Fraction negative_other = other; // ����� �������� ������, ��������� �������� � ���������� (� this)
        negative_other.multByNumber(-1);
        this->sumFrac(negative_other);
    }

    Fraction diffFracReturn(const Fraction& other) const {
        Fraction negative_other = other;  // ����� �������� ������, ��������� � ������
        negative_other.multByNumber(-1);
        return this->sumFracReturn(negative_other);
    }

    double calc() {  // ���������� �������� ����� � ���������� ����
        double num_d = (double)numerator;
        double den_d = (double)denominator;
        return (num_d / den_d);
    }

    int getNumerator() {  // ���������� �������� ���������
        return numerator;
    }

    int getDenominator() {  // ���������� ���������� �����������
        return denominator;
    }

private:
    int numerator;
    int denominator;
};

int main() {
}