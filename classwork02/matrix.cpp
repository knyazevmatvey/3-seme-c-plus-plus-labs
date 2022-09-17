#include<iostream>
using namespace std;

class Matrix {
public:
    Matrix(int height, int width, int* arr) : height(height), width(width) {
        // I assume that arr has the right size (height*width) without checking
        mat = new int* [height];
        for (int i = 0; i < height; i++) mat[i] = new int[width];
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++) {
                mat[i][j] = arr[i * width + j];
            }
    }
    Matrix(int dim, int* arr) : Matrix(dim, dim, arr) {}

    Matrix(): Matrix(1, (size_t)1) {// Определить конструктор по умолчанию, как матрицу размера 1 с элементом равным 1
    }

    Matrix(int element, size_t n_elements): height(n_elements), width(n_elements) { // Заполнение матрицы элементом element; n_elements -- количество элементов
        // Я предполагаю, что n_elements значит матрица n x n, а не sqrt(n) x sqrt(n), ибо давать на вход квадрат числа было бы странно
        mat = new int* [n_elements];
        for (unsigned int i = 0; i < n_elements; i++) mat[i] = new int[n_elements];
        for (unsigned int i = 0; i < n_elements; i++)
            for (unsigned int j = 0; j < n_elements; j++) {
                mat[i][j] = element;
            }
    }

    Matrix(const Matrix& other) {
        this->height = other.height;
        this->width = other.width;
        this->mat = new int* [height];
        for (int i = 0; i < height; i++) mat[i] = new int[width];
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++) {
                mat[i][j] = other.mat[i][j];
            }
    }

    void printMatrix() const {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) cout << mat[i][j] << " ";
            cout << endl;
        }
    }

    int calcDeterminant() { // Возвращает детерминант, но с плохой асимптотикой (не по Гауссу, в лоб по индукции)
        if (height != width) {
            cout << "Can't calculate determinant for a non-square matrix" << endl;
            return 0;
        }
        if (height == 1) return mat[0][0];
        else {
            int ans = 0;
            for (int i = 0; i < height; i++) {
                // creating a new matrix (by crossing out the first row and the i-th column)
                int* arr = new int[(height - 1) * (height - 1)];
                int count = 0;
                for (int row = 1; row < height; row++)
                    for (int col = 0; col < height; col++) {
                        if (col != i) {
                            arr[count] = mat[row][col];
                            count++;
                        }
                    }
                Matrix minor(height - 1, arr);
                delete[] arr;
                //minor.printMatrix();
                //cout << "det of this minor = " << minor.calcDeterminant() << endl;
                int adj = minor.calcDeterminant();
                if (i % 2 != 0) adj = -adj;
                ans += adj*mat[0][i];
            }
            return ans;
        }
    }

    Matrix multiplyByMatrix(const Matrix& other) const {
        if (this->width != other.height) {
            cout << "Can't multiply these matrices (wrong dimensions)" << endl;
        }
        else {
            // creating a new matrix
            int new_height = this->height;
            int new_width = other.width;
            int* arr = new int[new_height * new_width];
            for (int i = 0; i < new_height * new_width; i++) arr[i] = 0;
            Matrix product(new_height, new_width, arr);
            delete[] arr;

            // filling it with right values
            for (int i = 0; i < new_height; i++)
                for (int j = 0; j < new_width; j++) {
                    product.mat[i][j] = 0;
                    for (int k = 0; k < this->width; k++) product.mat[i][j] += this->mat[i][k] * other.mat[k][j];
                }

            return product;
        }
    }

    void calcSquare() {
        if (width != height) {
            cout << "Can't square a non-square matrix";
        }
        else {
            Matrix temp = (*this).multiplyByMatrix(*this);
            for (int i = 0; i < this->height; i++)
                for (int j = 0; j < this->width; j++) {
                    this->mat[i][j] = temp.mat[i][j];
                }
        }
    }

    void matTranspose() {// Осуществляет транспонирование матрицы, результат сохраняется тут же
        // storing data in a linear array
        int* arr = new int[width * height];
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++) {
                arr[i * height + j] = mat[i][j];
            }

        // changing dimensiona
        int temp = height;
        height = width;
        width = height;

        // deleting old mat and creating a new one
        for (int i = 0; i < width; i++) delete[] mat[i];    // width = old height
        delete[] mat;
        mat = new int* [height];
        for (int i = 0; i < height; i++) mat[i] = new int[width];
        
        // filling mat with right values
        for (int i = 0; i < width; i++) 
            for (int j = 0; j < height; j++) {
                mat[j][i] = arr[i * width + j];
            }
        delete[] arr;

    }

    ~Matrix() {
        for (int i = 0; i < height; i++) delete[] mat[i];
        delete[] mat;
    }

private:
    int** mat;
    int width;
    int height;
};

int main() {
}