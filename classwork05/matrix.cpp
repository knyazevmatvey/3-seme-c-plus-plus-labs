#include<iostream>

template<typename Field, size_t M, size_t N>
class Matrix {
public:
	Field mat[M][N];

	Matrix() = default;
	Matrix(Field arr[M * N]) {
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++) {
				mat[i][j] = arr[i * N + j];
			}
	}

	void print() {
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++) std::cout << mat[i][j] << '\t';
			std::cout << std::endl;
		}
	}
};

template<typename Field, size_t M, size_t N, size_t K>
Matrix<Field, M, K> operator*(const Matrix<Field, M, N>& lha, const Matrix<Field, N, K>& rha) {
	Matrix<Field, M, K> ans;
	for (int i = 0; i < M; i++)
		for (int j = 0; j < K; j++) {
			ans.mat[i][j] = 0;
			for (int k = 0; k < N; k++) ans.mat[i][j] += lha.mat[i][k] * rha.mat[k][j];
		}
	return ans;
}

template<typename Field, size_t M, size_t N>
Matrix<Field, M, N> operator+(const Matrix<Field, M, N>& lha, const Matrix<Field, M, N>& rha) {
	Matrix<Field, M, N> ans;
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++) {
			ans.mat[i][j] = lha.mat[i][j] + rha.mat[i][j];
		}
	return ans;
}

template<typename Field, size_t M, size_t N>
Matrix<Field, M, N> operator-(const Matrix<Field, M, N>& lha, const Matrix<Field, M, N>& rha) {
	Matrix<Field, M, N> ans;
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++) {
			ans.mat[i][j] = lha.mat[i][j] - rha.mat[i][j];
		}
	return ans;
}

int main() {

	bool want_to_check_sum = false;
	if (want_to_check_sum) {
		int first_arr[3 * 5] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
		Matrix<int, 3, 5> first(first_arr);
		std::cout << "first:" << '\n';
		first.print();

		int second_arr[3 * 5] = { 5, 1, 3, 6, 2, 3, 5, 4, 3, 6, 2, 5, 7, 3, 0 };
		Matrix<int, 3, 5> second(second_arr);
		std::cout << '\n' << "second:" << '\n';
		second.print();

		Matrix<int, 3, 5> sum = first + second;
		Matrix<int, 3, 5> diff = first - second;
		std::cout << '\n' << "sum:" << '\n';
		sum.print();
		std::cout << '\n' << "diff:" << '\n';
		diff.print();
	}

	bool want_to_check_product = false;
	if (want_to_check_product) {
		int first_arr[2 * 3] = { 6, 1, 3, 2, 5, 2 };
		Matrix<int, 2, 3> first(first_arr);

		int second_arr[3 * 4] = { 5, 1, 7, 2, 5, 7, 2, 4, 3, 1, 7, 6 };
		Matrix<int, 3, 4> second(second_arr);

		Matrix<int, 2, 4> product = first * second;

		std::cout << "first:" << '\n';
		first.print();
		std::cout << '\n' << "second:" << '\n';
		second.print();
		std::cout << '\n' << "product:" << '\n';
		product.print();
	}
}