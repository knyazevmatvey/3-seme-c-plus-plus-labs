#include <iostream>
using namespace std;

void swap(void* lha, void* rha, int type_size) {
    void* tmp = malloc(type_size);
    memcpy(tmp, lha, type_size);
    memcpy(lha, rha, type_size);
    memcpy(rha, tmp, type_size);
    free(tmp);
}

void* increment(void* begin, int shift, int type_size) {
    // возвращает указатель, сдвинутый на shift
    char* ch_ptr = reinterpret_cast<char*>(begin);
    for (int i = 0; i < shift; i++) ch_ptr += type_size;
    void* ans = reinterpret_cast<void*>(ch_ptr);
    return ans;
}

void qsort(void* arr, int left, int right, int type_size, int (*compare)(void*, void*)) {
    void* pivot = increment(arr, left, type_size);
    int l = left;
    int r = right;

    if (right > left) {
        while (r > l) {
            // moving l and r
            while ((compare(increment(arr, l, type_size), pivot) < 0) && (l < right)) l++; // считая compare(a,b)>0 при a > b
            while ((compare(increment(arr, r, type_size), pivot) >= 0) && (r > left)) r--;

            // swapping if needed
            if (r <= l) break;
            if (r > l) swap(increment(arr, l, type_size), increment(arr, r, type_size), type_size);
        }

        // finding the border where to cut the array
        // (it's probably close to l and r, but I'm not sure
        int index = left;
        while ((compare(increment(arr, index, type_size), pivot) <= 0) && (index < right)) index++;
        qsort(arr, left, index - 1, type_size, compare);
        qsort(arr, index, right, type_size, compare);
    }
}

int int_compare(void* first, void* second) {
    int first_int = *(reinterpret_cast<int*>(first));
    int second_int = *(reinterpret_cast<int*>(second));
    return (first_int - second_int);
}

double double_compare(void* first, void* second) {
    double first_d = *(reinterpret_cast<double*>(first));
    double second_d = *(reinterpret_cast<double*>(second));
    if (first_d > second_d) return 1;
    if (first_d == second_d) return 0;
    if (first_d < second_d) return -1;
}

int main() {
    int n;
    cin >> n;

    // test for int
    int* numbers = new int[n];
    for (int i = 0; i < n; i++) cin >> numbers[i];
    qsort(reinterpret_cast<void*>(numbers), 0, n - 1, sizeof(int), int_compare);
    for (int i = 0; i < n; i++) cout << numbers[i] << " ";
}