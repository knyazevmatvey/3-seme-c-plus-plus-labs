#include<iostream>
#include<limits>
using namespace std;

int main() {
	cout << "type: sizeof, min, max" << endl;
	cout << "char: " << sizeof(char) << ", " << numeric_limits<char>::min() << ", " << numeric_limits<char>::max() << endl;
	cout << "short int: " << sizeof(short int) << ", " << numeric_limits<short int>::min() << ", " << numeric_limits<short int>::max() << endl;
	cout << "int: " << sizeof(int) << ", " << numeric_limits<int>::min() << ", " << numeric_limits<int>::max() << endl;
	cout << "long int: " << sizeof(long int) << ", " << numeric_limits<long int>::min() << ", " << numeric_limits<long int>::max() << endl;
	cout << "float: " << sizeof(float) << ", " << numeric_limits<float>::min() << ", " << numeric_limits<float>::max() << endl;
	cout << "double: " << sizeof(double) << ", " << numeric_limits<double>::min() << ", " << numeric_limits<double>::max() << endl;
}