#include<iostream>
#include<cassert>

template<typename T>
class Array final {
public:
	T* arr_data;

	Array(T* ptr) : arr_data(ptr) { }

	T& operator[] (size_t x_ind) {
		return *(arr_data + x_ind);
	}
};

template<typename T>
class Grid final {
public:
	using size_type = unsigned;
private:
	using value_type = T;
public:
	T* const data;
	size_type const y_size, x_size;

	Grid(T* data, size_type y_size, size_type x_size) : data(data), y_size(y_size), x_size(x_size) {}

	// constructor from one element
	Grid(T const& t) : data(new T), y_size(1), x_size(1) {
		*data = t;
	}

	// constructor that creates a grid filled with default t's
	Grid(size_type y_size, size_type x_size) : data(reinterpret_cast<T*>(malloc(y_size* x_size * sizeof(T)))),
		y_size(y_size), x_size(x_size) {
		T* curr = data;
		T t;
		for (int i = 0; i < y_size * x_size; i++) {
			(*curr) = t;
			curr++;
		}
	}

	// constructor that creates a grid filled with given t
	Grid(size_type y_size, size_type x_size, T const& t) : data(reinterpret_cast<T*>(malloc(y_size* x_size * sizeof(T)))),
		y_size(y_size), x_size(x_size) {
		T* curr = data;
		for (int i = 0; i < y_size * x_size; i++) {
			(*curr) = t;
			curr++;
		}
	}

	// copy constructor (1/5)
	Grid(Grid<T> const& other) : data(reinterpret_cast<T*>(malloc(other.y_size* other.x_size * sizeof(T)))),
		y_size(other.y_size), x_size(other.x_size) {
		std::copy(other.data, other.data + y_size * x_size, data);
	}

	// move constructor (2/5)
	Grid(Grid<T>&& other) = delete;

	// copy assignment operator (3/5)
	Grid<T>& operator=(Grid<T>& other) {
		// checking that dimensions match
		if ((x_size != other.x_size) || (y_size != other.y_size)) {
			std::cout << "Cannot assign an " << other.x_size << "x" << other.y_size << " grid to a " <<
				x_size << "x" << y_size << " array";
			return *this;
		}
		std::copy(other.data, other.data + other.y_size * other.x_size, data);
	};


	// move assignment operator (4/5)
	Grid<T>& operator=(Grid<T>&& other) = delete;

	// destructor (5/5)
	~Grid() {
		if (data != nullptr) free(data);
	}

	// grid[y] returns the pointer to the first element of the y-th row
	// можно попробовать вернуть всю строку (как новый grid nx1), соотв. после второго раза получим стеку 1x1
	// и ее нужно будет неявно преобразовать в просто ссылку
	Array<T> operator[] (size_type y_idx) {
		return Array<T>(data + y_idx * x_size);
	}

	T operator() (size_type y_idx, size_type x_idx) const {
		return data[y_idx * x_size + x_idx];
	}

	T& operator() (size_type y_idx, size_type x_idx) {
		return data[y_idx * x_size + x_idx];
	}


	Grid<T>& operator=(T const& t) {
		for (
			auto it = data, end = data + x_size * y_size;
			it != end; ++it
			) *it = t;
		return *this;
	}


	size_type get_y_size() const { return y_size; };
	size_type get_x_size() const { return x_size; };
};



int main() {
	bool want_to_check_2d = true;
	if (want_to_check_2d) {
		Grid<float> g(3, 2, 0.0f);
		assert(3 == g.get_y_size());
		assert(2 == g.get_x_size());

		using gsize_t = Grid<int>::size_type; // it was the other way around intitially and i had to make it public to access

		for (gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
			for (gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx) {
				assert(0.0f == g[y_idx][x_idx]);
			}

		for (gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
			for (gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx) {
				g[y_idx][x_idx] = 1.0f;
			}

		for (gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
			for (gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx) {
				assert(1.0f == g[y_idx][x_idx]);
			}

		std::cout << "Asserted" << std::endl;
	}
	return 0;

}