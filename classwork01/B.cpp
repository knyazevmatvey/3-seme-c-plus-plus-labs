#include <iostream>
using namespace std;

void increment(void* &ptr, int n) {
	char* ch_ptr = reinterpret_cast<char*>(ptr);
	for (int i = 0; i < n; i++) ch_ptr++;
	ptr = reinterpret_cast<void*>(ch_ptr);
}

int min(void* arr, int size, int type_size, int (*compare)(void*, void*)) {
	int ans = 0;
	void* min_ptr = arr;
	int curr_ind = 0;
	void* curr = arr;
	for (int i = 0; i < size - 1; i++) {
		increment(curr, type_size);
		curr_ind++;
		if (compare(min_ptr, curr) > 0) {			// я считаю, что compare(a,b) > 0 при a>b
			min_ptr = curr;
			ans = curr_ind;
		}
	}
	return ans;
}

int max(void* arr, int size, int type_size, int (*compare)(void*, void*)) {
	int ans = 0;
	void* max_ptr = arr;
	int curr_ind = 0;
	void* curr = arr;
	for (int i = 0; i < size - 1; i++) {
		increment(curr, type_size);
		curr_ind++;
		if (compare(max_ptr, curr) < 0) {			// я считаю, что compare(a,b) > 0 при a>b
			max_ptr = curr;
			ans = curr_ind;
		}
	}
	return ans;
}

int compare_int(void* first, void* second) {
	int first_int = *reinterpret_cast<int*>(first);
	int second_int = *reinterpret_cast<int*>(second);
	if (first_int - second_int > 0) return 1;
	if (first_int - second_int == 0) return 0;
	if (first_int - second_int < 0) return -1;
}

int main() {
	bool want_to_test = true;
	if (want_to_test) {
		int arr[6] = { 10, 30, 0, 5, -1, 3 };
		cout << "index of min: " << min(arr, 6, 4, compare_int) << endl;
		cout << "index of max: " << max(arr, 6, 4, compare_int) << endl;
	}
}