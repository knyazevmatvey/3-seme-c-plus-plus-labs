#include<iostream>

struct base_exception {
    virtual std::string what() = 0;
};

struct math_exception final : base_exception{
    std::string what() override { return std::string("Division by zero (or other mathematiclal error)\n"); }
};

struct invalid_argument final : base_exception{
    std::string what() override { return std::string("Invalid argument\n"); }
};

double inverse(double x) {
    if (x == 0)
        throw math_exception();
    return 1. / x;
}

double root(double x) {
    if (x < 0)
        throw invalid_argument();
    return std::sqrt(x);
}


int main() {
    try {
        std::cout << root(4.0) << '\n';
    }
    catch (base_exception& err) {
        std::cout << err.what();
    }

    try {
        std::cout << root(0.0) << '\n';
    }
    catch (base_exception& err) {
        std::cout << err.what();
    }

    try {
        std::cout << root(-1.0) << '\n';
    }
    catch (base_exception& err) {
        std::cout << err.what();
    }

    try {
        std::cout << inverse(1) << '\n';
    }
    catch (base_exception& err) {
        std::cout << err.what();
    }

    try {
        std::cout << inverse(0) << '\n';
    }
    catch (base_exception& err) {
        std::cout << err.what();
    }
}