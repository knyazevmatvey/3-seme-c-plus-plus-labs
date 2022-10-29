#include<utility>
#include<iostream>


template <typename U>
struct ControlBlock {
    size_t* counter;
    U* ptr;

    ControlBlock() : counter(nullptr), ptr(nullptr) {}
};

template <typename T>
class unique_ptr {
public:
    explicit unique_ptr(T* ptr) : ptr(ptr) { }

    // move constructor (1/5)
    unique_ptr(unique_ptr&& other) noexcept {
        ptr = other.ptr;
        other.ptr = nullptr;
    }

    // move assignment operator (2/5)
    unique_ptr& operator=(unique_ptr&& other) {
        if (&other == this) return *this;
        ptr = other.ptr;
        other.ptr = nullptr;
    }

    // copy constructor (3/5)
    unique_ptr(const unique_ptr<T>&) = delete;

    // copy assignment operator (4/5)
    unique_ptr& operator=(const unique_ptr<T>&) = delete;

    // destructor (5/5)
    ~unique_ptr() {
        delete[] ptr;
    }

    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }


private:
    T* ptr = nullptr;
};

template <typename T, typename... Args>
unique_ptr<T> make_unique(Args&&... args) {
    auto ptr = new T(args...);
    return unique_ptr<T>(ptr);
}



template <typename T>
class shared_ptr {
private:
    ControlBlock<T>* cptr = nullptr;

public:
    shared_ptr<T>(T* ptr) {
        auto cptr = new ControlBlock<T>;
        cptr->counter = new size_t;
        *(cptr->counter) = 1;
        cptr->ptr = ptr;
    }

    // destructor (1/5)
    ~shared_ptr() {
        if (*(cptr->counter) > 1) {
            *(cptr->counter) -= 1;
            cptr->counter = nullptr;
            cptr->ptr = nullptr;
        }
        else {
            delete[] cptr->ptr;
            delete cptr->counter;
        }
        delete cptr;
    }

    // copy constructor (2/5)
    shared_ptr<T>(const shared_ptr<T>& other) {
        auto cptr = new ControlBlock<T>;
        cptr->ptr = (other.cptr)->ptr;
        cptr->counter = (other.cptr)->counter;
        ++(*(cptr->counter));
    }

    // copy assignment operator (3/5)
    shared_ptr<T>& operator=(const shared_ptr<T>& other) {
        this->~shared_ptr();
        cptr = new ControlBlock<T>;
        cptr->ptr = (other.cptr)->ptr;
        cptr->counter = (other.cptr)->counter;
        ++(*(cptr->counter));
    }

    // move constructor (4/5)
    shared_ptr(shared_ptr&& other) {
        cptr = new ControlBlock<T>;
        cptr->ptr = other.cptr->ptr;
        cptr->counter = other.cptr->counter;
        other.cptr->ptr = nullptr;
        other.cptr->counter = nullptr;
    }

    // move assignment operator (5/5)
    shared_ptr<T>& operator=(shared_ptr<T>&& other) {
        if (&other == this) return *this;
        this->~shared_ptr();
        cptr = new ControlBlock<T>;
        cptr->ptr = other.cptr->ptr;
        cptr->counter = other.cptr->counter;
        other.cptr->ptr = nullptr;
        other.cptr->counter = nullptr;
    }

    size_t use_count() const {
        return *(cptr->counter);
    }
};

template <typename T, typename... Args>
shared_ptr<T> make_shared(Args&&... args) {
    auto ptr = new T(args...);
    return shared_ptr<T>(ptr);
}



int main() {
    bool want_to_test_unique = false;
    if (want_to_test_unique) {
        unique_ptr<int> a = make_unique<int>(1);
        std::cout << *a << std::endl;
        std::cout << &a << std::endl;
        unique_ptr<int> b = std::move(a); // move constructor???
        std::cout << *b << std::endl;
        // std::cout << *a << std::endl; // produces an error, as it should

        unique_ptr<int> c = make_unique<int>(3);
        std::cout << "before move:" << std::endl;
        std::cout << *b << std::endl;
        std::cout << *c << std::endl;

        c = std::move(b);
        std::cout << "after move:" << std::endl;
        // std::cout << *b << std::endl; // produces an error, as it should
        std::cout << *c << std::endl;
    }   
}
