#include<iostream>
#include<cstring>

struct vector_exception {
	virtual std::string what() = 0;
};

struct out_of_range_exception final : vector_exception {
	std::string what() override { return std::string("Vector index is out of range\n"); }
};

struct empty_pop_exception final : vector_exception {
	std::string what() override { return std::string("Can not pop an empty vector\n"); }
};

template <typename T>
class Vector {
private:
	size_t cap = 0;
	size_t size = 0;
	T* buffer = nullptr;

public:
	Vector() = default;

	// copy constructor (1/5)
	Vector(Vector const& vec) : size(vec.size), cap(vec.cap), buffer(new T[vec.cap]) {
		std::memcpy(buffer, vec.buffer, cap*sizeof(T));
	}

	// move constructor (2/5)
	Vector(Vector&& vec) noexcept : size(vec.size), cap(vec.cap), buffer(vec.buffer) {
		vec.buffer = nullptr;
	}

	// copy assignment (3/5)
	Vector& operator=(Vector const& vec) {
		Vector tmp(vec);
		std::swap(buffer, tmp.buffer);
		std::swap(cap, tmp.cap);
		std::swap(size, tmp.size);
	}

	// move assignment (4/5)
	Vector& operator=(Vector&& vec) {
		Vector tmp(std::move(vec));
		std::swap(buffer, tmp.buffer);
		std::swap(cap, tmp.cap);
		std::swap(size, tmp.size);
	}

	void add_memory() {
		// increases cap twice

		if (buffer == nullptr) {
			buffer = new T[1];
			cap = 1;
		}
		else {
			T* new_buffer = new T[cap * 2];
			std::memcpy(new_buffer, buffer, cap*sizeof(T));
			delete[] buffer;
			buffer = new_buffer;
			cap *= 2;
		}
	}

	void push_back(const T& value) {
		if (size == cap) add_memory();
		T* after_last = buffer + size;
		*after_last = value;
		size++;
	}

	T& top() {
		return *(buffer + size - 1);
	}

	void pop() {
		if (this->is_empty()) throw empty_pop_exception();

		// a possbible error may occcur when deleting the buffer
		size--;
	}

	bool is_empty() const {
		return buffer == nullptr;
	};

	size_t capacity() const { return cap; }

	T& at(size_t index) {
		if (index < size) return *(buffer + index);
		else throw out_of_range_exception();
	}

	T& operator[](size_t index) { return *(buffer + index); }

	// destructor (5/5)
	~Vector() {
		delete[] buffer;
	}
};

int main() {
	Vector<int> vec;
	vec.push_back(1);
	vec.push_back(2);
	std::cout << vec[0] << " " << vec[1];
	vec.pop();
}