#include "matrix.h"

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(0));

    Matrix<int> mat1(3, 3);
    Matrix<int> mat2(3, 3);
    mat1.fillFromKeyboard();
    mat2.fillWithRandom();
    cout << "Matrix 1:" << endl;
    mat1.print();
    cout << "Matrix 2:" << endl;
    mat2.print();
    Matrix<int> matSum = mat1 + mat2;
    cout << "Sum of matrices:" << endl;
    matSum.print();
    Matrix<int> matDifference = mat1 - mat2;
    cout << "Difference of matrices:" << endl;

    matDifference.print();
    try {
        Matrix<int> matProduct = mat1 * mat2;
        cout << "Product of matrices:" << endl;
        matProduct.print();
    }
    catch (const invalid_argument& e) {
        cout << e.what() << endl;
    }
    try {
        Matrix<int> matQuotient = mat1 / mat2;
        cout << "Quotient of matrices:" << endl;
        matQuotient.print();
    }
    catch (const invalid_argument& e) {
        cout << e.what() << endl;
    }

    cout << "Maximum element in matrix 1: " << mat1.findMax() << endl;
    cout << "Minimum element in matrix 1: " << mat1.findMin() << endl;

    return 0;
}
