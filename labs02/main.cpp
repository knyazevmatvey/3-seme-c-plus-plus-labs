#include <iostream>
#include <set>
#include <random>
#include <fstream>

// Базовый класс: по сути, State определяется функцией, которая говорить, лежит ли s в State
// Я очень сильно надеюсь, что никто не будет объявлять State напрямую, но писать contains=0 (делая класс абстрактным)
// я не буду, ибо это приведет к огромным страданиям
class State {
public:
    virtual bool contains(int s) const { return false; };
};

class SumState : public State {
private:
    State& first;
    State& second;

public:
    SumState(State& first, State& second) : first(first), second(second) {}
    bool contains(int s) const override {
        return first.contains(s) || second.contains(s);
    }
};

class IntersectionState : public State {
private:
    State& first;
    State& second;

public:
    IntersectionState(State& first, State& second) : first(first), second(second) {}
    bool contains(int s) const override {
        return first.contains(s) && second.contains(s);
    }
};

class DiffState : public State {
private:
    State& first;
    State& second;

public:
    // Конструктор вычитает second из first (не наоборот)
    DiffState(State& first, State& second): first(first), second(second) {}
    bool contains(int s) const override {
        return first.contains(s) && !second.contains(s);
    }
};

class DiscreteState: public State {
private:
    int const state;

public:
    DiscreteState(int state) : state(state) { }

    bool contains(int s) const override {
        return s == state;
    }
};

class SegmentState: public State {
private:
    int const beg, end;

public:
    SegmentState() : beg(0), end(-1) { }
    SegmentState(int beg, int end) : beg(beg), end(end) { }

    bool contains(int s) const override {
        return s >= beg && s <= end;
    }
};

class SetState: public State {
private:
    std::set<int> const states;

public:
    SetState() : states() { }
    SetState(std::set<int> const& src) : states(src) { }

    bool contains(int s) const override {
        return states.count(s) > 0;
    }
};

class SegmentWithHoles : public State {
private:
    SegmentState segment;
    SetState holes;

public:
    SegmentWithHoles(int beg, int end, std::set<int> const& src) : segment(beg, end), holes(src) { }
    bool contains(int s) const override {
        return (segment.contains(s) && !holes.contains(s));
    }
};

class SegmentWithAdditions : public State {
private:
    SegmentState segment;
    SetState additions;

public:
    SegmentWithAdditions(int beg, int end, std::set<int> const& src) : segment(beg, end), additions(src) {}
    bool contains(int s) const override {
        return (segment.contains(s) || additions.contains(s));
    }
};


class ProbabilityTest {
private:
    unsigned seed;
    int test_min, test_max;
    unsigned test_count;

public:
    ProbabilityTest(unsigned seed, int test_min, int test_max, unsigned test_count) : seed(seed), test_min(test_min), test_max(test_max), test_count(test_count) { }

    float operator()(State const& s) const {
        std::default_random_engine rng(seed);
        std::uniform_int_distribution<int> dstr(test_min, test_max);
        unsigned good = 0;
        for (unsigned cnt = 0; cnt != test_count; ++cnt)
            if (s.contains(dstr(rng))) ++good;

        return static_cast<float>(good) / static_cast<float>(test_count);
    }
};

void print(State& st) {
    for (int i = -1000; i<1000; i++) {
        if (st.contains(i)) std::cout << i << " ";
    }
}

int main(int argc, const char* argv[]) {
    
    SegmentState s(1, 10);
    SetState ss({ 1, 3, 5, 7, 23, 48, 57, 60, 90, 99 });
    

    std::ofstream file;
    file.open("temp.txt");

    bool calc_first = true;
    if (calc_first) {
        int num_of_seeds = 10;
        for (int N = 100; N < 50000; N += 100) {
            float ans = 0;
            for (int seed = 0; seed < num_of_seeds; seed++) {
                ProbabilityTest pt(seed, 0, 100, N);
                ans += pt(s) / num_of_seeds;
            }
            file << N << " " << ans << " " << std::endl;
            std::cout << N << std::endl;
        }
        file.close();
    }

    bool want_to_test_operations = false;
    if (want_to_test_operations) {
        SegmentState a(0, 6);
        SegmentState b(4, 10);
        SumState sum(a, b);
        IntersectionState intersection(a, b);
        DiffState diff(a, b);

        std::cout << "a: ";
        print(a);
        std::cout << std::endl;

        std::cout << "b: ";
        print(b);
        std::cout << std::endl;

        std::cout << "sum: ";
        print(sum);
        std::cout << std::endl;

        std::cout << "inter: ";
        print(intersection);
        std::cout << std::endl;

        std::cout << "diff: ";
        print(diff);
        std::cout << std::endl;
    }

    return 0;
}
