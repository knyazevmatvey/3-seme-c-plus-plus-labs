#include <iostream>
#include <cstring>
#include <string>
using namespace std;

// Я скопировал код из задачи G classwork 8 прошлого семестра,
// так что его не сложно обобщать при добавлении новых операций + можно использовать квадратные скобки [] (как () в обычных выражениях)
// Как следствие, здесь почти везде работа с char* вместо string

const int N = 3;
char operations[N] = { '+', '*', 'n' };

struct Point {
	unsigned long long const x, y;

	Point(unsigned long long x, unsigned long long y) : x(x), y(y) {}

	Point minx(Point const& rha) const {
		return Point(rha.x < x ? rha.x : x, y);
	}

	Point miny(Point const& rha) const {
		return Point(x, rha.y < y ? rha.y : y);
	}

	Point maxx(Point const& rha) const {
		return Point(rha.x > x ? rha.x : x, y);
	}

	Point maxy(Point const& rha) const {
		return Point(x, rha.y > y ? rha.y : y);
	}

	void print() const {
		std::cout << '(' << x << ',' << y << ')';
	}
};

struct Rectangle {
	Point corner; // правый верхний угол

	Rectangle() : corner(0, 0) {}

	Rectangle(Point const& corner) : corner(corner) {}

	Rectangle(int x, int y) : corner(x, y) {}

	Rectangle operator+(Rectangle const& rha) const {
		Point maxed_x = corner.maxx(rha.corner);
		Point maxed_xy = maxed_x.maxy(rha.corner);
		return Rectangle(maxed_xy);
	}

	Rectangle operator*(Rectangle const& rha) const {
		Point mined_x = corner.minx(rha.corner);
		Point mined_xy = mined_x.miny(rha.corner);
		return Rectangle(mined_xy);
	}

	void print() const {
		corner.print();
	}
};


// here operations (including rectangles) will be nodes
struct Node {
	char oper;
	Rectangle rect;
	Node* right;
	Node* left;

	Node() = default; // used to define operations + and * (that do not contain a rectangle)

	Node(int x, int y): rect(x, y) {} // used to define a rectangle
};


struct Heap {
	Node* top;
};

void print_expression(char* math_expression, int left, int right) {
	// this was used to find errors and is no longer needed
	char* current = math_expression;
	current += left;
	for (int i = 0; i <= right - left; i++) {
		cout << *current;
		current++;
	}
}

char first_symbol(char* math_expression, int expr_size) {
	// returns the first symbol, not equal to ' '
	char* current = math_expression;
	while (*current == ' ') {
		current++;
		if (current == nullptr) break;
	}
	if (current != nullptr) return *current;
}

char last_symbol(char* math_expression, int expr_size) {
	// returns the last symbol, not equal to ' '
	// if the string is empty, returns 'w' (i don't remember why)
	char* current = math_expression;
	current += expr_size - 1;
	while (*current == ' ') {
		current--;
		if (current == nullptr) break;
	}
	if (current != nullptr) return *current;
	else return 'w';
}

void skip_to_bracket(char** ptr) {
	// moves the ptr to the end of the bracket clause
	char* current = *ptr;
	current++;
	int counter = 1;

	while (counter != 0) {
		//cout << *ptr;
		if (*current == '[') counter++;
		if (*current == ']') counter--;
		current++;
	}
	*ptr = current;
}


int get_x(std::string str) {
	// from a string "x,y" gets x
	
	// getting x
	int i = 0;
	std::string x_str = "";
	while (str[i] != ',') {
		x_str.append(1, str[i]);
		i++;
	}

	// converting x
	int x = std::stoi(x_str);
	return x;
}

int get_y(std::string str) {
	// from a string "x,y" gets y
	// going to ','
	int i = 0;
	while (str[i] != ',') i++;
	i++;

	// getting y
	std::string y_str = "";
	while (i < str.size()) {
		y_str.append(1, str[i]);
		i++;
	}

	// converting y1
	int y = std::stoi(y_str);
	return y;
}

std::string get_point_string(std::string str) {
	// starting from ind=0 searches str for '(' and ')' and returns the string between them (without brackets)

	// getting to the first character after '('
	int ind = 0;
	while (str[ind] != '(') ind++;
	ind++;

	// getting the answer
	std::string ans = "";
	while (str[ind] != ')') {
		ans.append(1, str[ind]);
		ind++;
	}

	return ans;
}


Rectangle str_to_rect(char* char_expression) {
	// converts a string to a rectangle
	string expression = char_expression;
	string rect_str = get_point_string(expression);
	Rectangle rect = Rectangle(get_x(rect_str), get_y(rect_str));
	return rect;
}

Node* Heapify(char* math_expression, int expr_size) {
	// checking if the whole expression is in brackets
	if ((first_symbol(math_expression, expr_size) == '[') && (last_symbol(math_expression, expr_size) == ']')) {
		char* current = math_expression;
		while (*current != '[') current++;
		char* last = math_expression + expr_size - 1;
		while (*last != ']') last--;
		return Heapify(current + 1, last - current - 1);
	}

	// main case
	else {

		// looking for the last operation to be implemented
		int minimal = 10;
		int border = -1;
		char* end = math_expression + expr_size;
		char* current = math_expression;
		while (current != end) {
			if (*current == '[') {
				skip_to_bracket(&current);
			}
			else {
				for (int j = 0; j < N; j++) {
					if (*current == operations[j]) {
						if (j < minimal) {
							minimal = j;
							border = current - math_expression;
						}
					}
				}
				current++;
			}
		}

		// base of induction (no operations to do)
		if (minimal == 10) {
			// creating a rectangle
			string expression = math_expression;
			string rect_str = get_point_string(expression);
			Node* temp = new Node(get_x(rect_str), get_y(rect_str));
			temp->oper = 'n'; // 'n' for number (originally it was used for numbers, not rectangles)
			temp->right = nullptr;
			temp->left = nullptr;

			return temp;
		}
		// step of induction
		else {
			Node* temp = new Node;
			temp->oper = operations[minimal];
			temp->left = Heapify(math_expression, border);
			temp->right = Heapify(math_expression + border + 1, expr_size - border - 1);
			return temp;
		}
	}
}

Rectangle calculate(Node* top) {
	// returns the result of a calculation represented by a heap
	if (top->oper == 'n') return top->rect;
	if (top->oper == '+') return (calculate(top->left) + calculate(top->right));
	if (top->oper == '*') return (calculate(top->left) * calculate(top->right));
}



int main() {
	// i'm assuming that i work with less than 'big' symbols
	int big = 1000;

	//cout << "Write your expression to calculate: ";

	// input
	int i = 0;
	char* input = new char[big];
	while (true) {
		char temp = cin.get();
		if (temp == '\n') break;
		input[i] = temp;
		i++;
	}
	int size = i;

	calculate(Heapify(input, size)).print();

	return 0;
}