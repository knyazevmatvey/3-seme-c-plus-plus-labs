#include<iostream>

template<typename T>
struct Comparator {
	virtual bool operator() (T const&, T const&) const = 0;
};

struct IntComparator final : Comparator<int> {
    bool operator() (int const& lha, int const& rha) const override {
        return lha < rha;
    }
};

struct DoubleComparator final : Comparator<double> {
    bool operator() (double const& lha, double const& rha) const override {
        return lha < rha;
    }
};

template<typename T>
void quicksort(T arr[], int left, int right, Comparator<T>& comp) {
    T pivot = arr[left];
    int l = left;
    int r = right;

    if (right > left) {
        while (comp(l, r)) {
            // moving l and r
            while (comp(arr[l], pivot) && (l < right)) l++;
            while (!comp(arr[r], pivot) && (r > left)) r--;

            // swapping if needed
            if (r <= l) break;
            if (r > l) {
                T temp = arr[r];
                arr[r] = arr[l];
                arr[l] = temp;
            }
        }

        // finding the border where to cut the array
        // (it's probably close to l and r, but I'm not sure
        int index = left;
        while (!comp(pivot, arr[index]) && (index < right)) index++;
        quicksort<T>(arr, left, index - 1, comp);
        quicksort<T>(arr, index, right, comp);
    }
}

int main() {
    bool want_to_test = true;
    if (want_to_test) {
        IntComparator comp_int;
        int arr_int[] = { 1, 4, 6, 2, 3, 5, 4, 9, 3, 5 };
        quicksort(arr_int, 0, sizeof(arr_int) / sizeof(int) - 1, comp_int);
        for (int i = 0; i < sizeof(arr_int) / sizeof(int); i++) std::cout << arr_int[i] << " ";
        std::cout << '\n';

        DoubleComparator comp_double;
        double arr_double[] = { 1, 5, 2, -8, 4, 3, 6.5, 4, 9, 3, 5 };
        quicksort(arr_double, 0, sizeof(arr_double) / sizeof(double) - 1, comp_double);
        for (int i = 0; i < sizeof(arr_double) / sizeof(double); i++) std::cout << arr_double[i] << " ";
    }
}
