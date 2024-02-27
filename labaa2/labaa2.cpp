#include <iostream>
#include <cstdlib>

class Matrix {
private:
    int** data;
    unsigned int m;
    unsigned int n;
public:
    Matrix(unsigned int m, unsigned int n) {
        this->m = m;
        this->n = n;

        // Выделение памяти для двумерного массива
        data = new int* [m];
        for (int i = 0; i < m; i++) {
            data[i] = new int[n];
        }
    }

    ~Matrix() {
        // Освобождение памяти
        for (int i = 0; i < m; i++) {
            delete[] data[i];
        }
        delete[] data;
    }

    int* operator[](unsigned int index) {
        return data[index];
    }

    void fillRandom() {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                data[i][j] = rand() % 10;
            }
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
        for (int i = 0; i < matrix.m; i++) {
            for (int j = 0; j < matrix.n; j++) {
                os << matrix.data[i][j] << " ";
            }
            os << std::endl;
        }
        return os;
    }

    Matrix& operator+=(const Matrix& matrix) {
        if (m != matrix.m || n != matrix.n) {
            throw std::runtime_error("Invalid matrix dimensions");
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                data[i][j] += matrix.data[i][j];
            }
        }
        return *this;
    }

    Matrix operator+(const Matrix& matrix) const {
        if (m != matrix.m || n != matrix.n) {
            throw std::runtime_error("Invalid matrix dimensions");
        }

        Matrix result(m, n);

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                result.data[i][j] = data[i][j] + matrix.data[i][j];
            }
        }
        return result;
    }

    Matrix& operator-=(const Matrix& matrix) {
        if (m != matrix.m || n != matrix.n) {
            throw std::runtime_error("Invalid matrix dimensions");
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                data[i][j] -= matrix.data[i][j];
            }
        }
        return *this;
    }

    Matrix operator-(const Matrix& matrix) const {
        if (m != matrix.m || n != matrix.n) {
            throw std::runtime_error("Invalid matrix dimensions");
        }

        Matrix result(m, n);

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                result.data[i][j] = data[i][j] - matrix.data[i][j];
            }
        }
        return result;
    }

    Matrix operator*(const Matrix& matrix) const {
        if (n != matrix.m) {
            throw std::runtime_error("Invalid matrix dimensions");
        }

        Matrix result(m, matrix.n);

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < matrix.n; j++) {
                result.data[i][j] = 0;
                for (int k = 0; k < n; k++) {
                    result.data[i][j] += data[i][k] * matrix.data[k][j];
                }
            }
        }
        return result;
    }

    bool operator==(const Matrix& matrix) const {
        if (m != matrix.m || n != matrix.n) {
            return false;
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (data[i][j] != matrix.data[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator!=(const Matrix& matrix) const {
        return !(*this == matrix);
    }
};

int main() {
    Matrix A(3, 3);
    A.fillRandom();
    std::cout << "A:\n" << A << std::endl;

    Matrix B(3, 3);
    B.fillRandom();
    std::cout << "B:\n" << B << std::endl;

    Matrix C = A + B;
    std::cout << "C:\n" << C << std::endl;

    Matrix D = A * B;
    std::cout << "D:\n" << D << std::endl;

    return 0;
}