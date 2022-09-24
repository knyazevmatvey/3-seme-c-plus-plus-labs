#include <iostream>
#include <vector>
#include <cmath>

struct Point {
	double x = 0;
	double y = 0;

	Point() = default;
	Point(double x, double y) : x(x), y(y) {}

	Point operator+ (const Point& other) {
		x += other.x;
		y += other.y;
	}

	Point operator/ (const int div) {
		x /= div;
		y /= div;
	}
};

struct Vector2d : Point {
	// represents a 2d vector on a plane

	Vector2d(Point begin, Point end) : Point(end.x - begin.x, end.y - begin.y) {} // creates a 2d vector from begin to end

	double length() { // returns length of a vector
		return sqrt(x * x + y * y);
	}
};

double vector_mult(Vector2d a, Vector2d b) {
	// returns oriented area between vectors a and b
	return (a.x * b.y - a.y * b.x);
}

// Abstract class
class Shape {
protected:
	std::vector<Point> storage;  // хранилище угловых точек для фигуры
	// imho можно и по storage найти все эти параметры (вместо того чтобы делать виртуальными)
public:
	virtual double area() = 0;
	virtual double perimeter() = 0;
	virtual Point center() = 0;
};

class Triangle : public Shape {
	Triangle(Point a, Point b, Point c) {
		// Возможно разумнее через список инициализации, но и так сойдет
		storage.clear();
		storage.push_back(a);
		storage.push_back(b);
		storage.push_back(c);
	}

	double area() override {
		Vector2d first(storage[0], storage[1]), second(storage[0], storage[2]);
		return vector_mult(first, second)/2;
	}

	double perimeter() override {
		Vector2d first(storage[0], storage[1]);
		Vector2d second(storage[1], storage[2]);
		Vector2d third(storage[2], storage[0]);
		return first.length() + second.length() + third.length();
	}

	Point center() override {
		return (storage[0] + storage[1] + storage[2]) / 3;
	}

};


class Square : public Shape {
	Square(Point a, Point b, Point c, Point d) {
		storage.clear();
		storage.push_back(a);
		storage.push_back(b);
		storage.push_back(c);
		storage.push_back(d);
	}

	double area() override {
		Vector2d first(storage[0], storage[1]);
		Vector2d second(storage[1], storage[2]);
		return vector_mult(first, second);
	}

	double perimeter() override {
		Vector2d first(storage[0], storage[1]);
		Vector2d second(storage[1], storage[2]);
		return 2 * (first.length() + second.length());
	}

	Point center() override {
		Point ans(0,0);
		for (int i = 0; i < 4; i++) ans = ans + storage[i];
		ans = ans / 4;
		return ans;
	}
};

class Line : public Shape {
	Line(Point a, Point b) {
		storage.clear();
		storage.push_back(a);
		storage.push_back(b);
	}

	double area() override {
		return 0;
	}

	double perimeter() override {
		Vector2d first(storage[0], storage[1]);
		return first.length();
		// P.S. В некотором смысле можно считать что периметр в два раза больше
	}
	
	Point center() override {
		return (storage[0] + storage[1]) / 2;
	}
};