#include <iostream>
using namespace std;

void swap(void* &first_ptr, void* &second_ptr) {
	// ������ �������� �������� ����� ptr
	void* inter = first_ptr;
	first_ptr = second_ptr;
	second_ptr = inter;
}

int main() {
	// example
	int a = 1;
	int b = 2;
	char first = 'A';
	char second = 'B';
	double pi = 3.14;
	double e = 2.78;
	void* ptr_a = &a;
	void* ptr_b = &b;
	cout << "before swapping pointers: " << *reinterpret_cast<int*>(ptr_a) << " " << *reinterpret_cast<int*>(ptr_b) << endl;
	swap(ptr_a, ptr_b);
	cout << "after swapping pointers: " << *reinterpret_cast<int*>(ptr_a) << " " << *reinterpret_cast<int*>(ptr_b) << endl;
	//swap(a, b);
	//cout << a << b << endl;
	//swap(first, second);
	//cout << first << second;
	//swap(pi, e);
	//cout << pi << e;

	// ����, ��� ���� �������� a � b �� �������� (���� ���������� ���������), �� � �� ���� ��� ��� ����� ������� �� ������� ������������ void*
	// ������, �����-�� ���������� ��� �������, swap(a,b) ���� ��������, ���� ����� ��� �� ��������� (�� ������� ���� �� ���� ����� ��������� ��� 
	// char'��, int'�� � double'��
}