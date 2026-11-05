
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

// Matrix class
class Matrix {
private:
    int size;
    int* data;

public:
    // Constructor
    Matrix(int n) {
        size = n;
        data = new int[size * size]();
    }

    // Copy constructor
    Matrix(const Matrix& other) {
        size = other.size;
        data = new int[size * size];

        for (int i = 0; i < size * size; i++) {
            data[i] = other.data[i];
        }
    }

    // Destructor
    ~Matrix() {
        delete[] data;
    }

    // Assignment operator
    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            delete[] data;

            size = other.size;
            data = new int[size * size];

            for (int i = 0; i < size * size; i++) {
                data[i] = other.data[i];
            }
        }

        return *this;
    }

    // Read matrix values from file
    void readFromFile(std::ifstream& file) {
        for (int i = 0; i < size * size; i++) {
            file >> data[i];
        }
    }

    // Display matrix
    void display() const {
        for (int row = 0; row < size; row++) {
            for (int col = 0; col < size; col++) {
                std::cout << std::setw(4)
                          << data[row * size + col];
            }

            std::cout << std::endl;
        }
    }

    // Get an element
    int getElement(int row, int col) const {
        return data[row * size + col];
    }

    // Update an element
    void setElement(int row, int col, int value) {
        data[row * size + col] = value;
    }

    // Get matrix size
    int getSize() const {
        return size;
    }

    // Addition operator
    Matrix operator+(const Matrix& other) const {
        Matrix result(size);

        for (int i = 0; i < size * size; i++) {
            result.data[i] = data[i] + other.data[i];
        }

        return result;
    }

    // Multiplication operator
    Matrix operator*(const Matrix& other) const {
        Matrix result(size);

        for (int row = 0; row < size; row++) {
            for (int col = 0; col < size; col++) {

                result.data[row * size + col] = 0;

                for (int k = 0; k < size; k++) {
                    result.data[row * size + col] +=
                        data[row * size + k] *
                        other.data[k * size + col];
                }
            }
        }

        return result;
    }

    // Main diagonal sum
    int mainDiagonalSum() const {
        int sum = 0;

        for (int i = 0; i < size; i++) {
            sum += data[i * size + i];
        }

        return sum;
    }

    // Secondary diagonal sum
    int secondaryDiagonalSum() const {
        int sum = 0;

        for (int i = 0; i < size; i++) {
            sum += data[i * size + (size - 1 - i)];
        }

        return sum;
    }
};

// Practice 5 - Swap rows
void swapRows(Matrix matrix, int row1 = 0, int row2 = 1) {

    if (row1 < 0 || row2 < 0 ||
        row1 >= matrix.getSize() ||
        row2 >= matrix.getSize()) {

        std::cout << "Invalid row indices." << std::endl;
        return;
    }

    for (int col = 0; col < matrix.getSize(); col++) {

        int temp = matrix.getElement(row1, col);

        matrix.setElement(
            row1, col, matrix.getElement(row2, col));

        matrix.setElement(row2, col, temp);
    }

    matrix.display();
}

// Practice 6 - Swap columns
void swapColumns(Matrix matrix, int col1 = 0, int col2 = 1) {

    if (col1 < 0 || col2 < 0 ||
        col1 >= matrix.getSize() ||
        col2 >= matrix.getSize()) {

        std::cout << "Invalid column indices." << std::endl;
        return;
    }

    for (int row = 0; row < matrix.getSize(); row++) {

        int temp = matrix.getElement(row, col1);

        matrix.setElement(
            row, col1, matrix.getElement(row, col2));

        matrix.setElement(row, col2, temp);
    }

    matrix.display();
}

// Practice 7 - Update matrix element
void updateMatrix(Matrix matrix, int row = 0,
                  int col = 0, int value = 100) {

    if (row < 0 || col < 0 ||
        row >= matrix.getSize() ||
        col >= matrix.getSize()) {

        std::cout << "Invalid indices." << std::endl;
        return;
    }

    matrix.setElement(row, col, value);

    matrix.display();
}

// Main function
int main() {

    std::string filename;

    // Ask for input filename
    std::cout << "Enter input filename: ";
    std::cin >> filename;

    // Open input file
    std::ifstream file(filename);

    if (!file) {
        std::cout << "Unable to open file." << std::endl;
        return 1;
    }

    // Read matrix size
    int n;
    file >> n;

    // Create two matrices
    Matrix A(n);
    Matrix B(n);

    // Read matrix values
    A.readFromFile(file);
    B.readFromFile(file);

    // Display Matrix A
    std::cout << "\nMatrix A:" << std::endl;
    A.display();

    // Display Matrix B
    std::cout << "\nMatrix B:" << std::endl;
    B.display();

    // Practice 2 - Addition
    Matrix sum = A + B;

    std::cout << "\nA + B:" << std::endl;
    sum.display();

    // Practice 3 - Multiplication
    Matrix product = A * B;

    std::cout << "\nA * B:" << std::endl;
    product.display();

    // Practice 4 - Diagonal sums
    std::cout << "\nDiagonal sums for Matrix A:" << std::endl;

    std::cout << "Main diagonal sum: "
              << A.mainDiagonalSum() << std::endl;

    std::cout << "Secondary diagonal sum: "
              << A.secondaryDiagonalSum() << std::endl;

    // Practice 5 - Swap rows
    std::cout << "\nProblem 5 - Rows 0 and 2 swapped:"
              << std::endl;

    swapRows(A, 0, 2);

    // Practice 6 - Swap columns
    std::cout << "\nProblem 6 - Columns 0 and 2 swapped:"
              << std::endl;

    swapColumns(A, 0, 2);

    // Practice 7 - Update element
    std::cout << "\nProblem 7 - Updated matrix:"
              << std::endl;

    updateMatrix(A, 1, 2, 99);

    file.close();

    return 0;
}
