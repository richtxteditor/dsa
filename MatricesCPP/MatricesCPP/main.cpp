//
//  main.cpp
//  MatricesCPP
//
//  Created by richie on 12/8/25.
//

#include <iostream>

// Lower triangular matrix:
// non-zero when i >= j, zero above the diagonal.
// The demo uses 1-based matrix coordinates so the formulas match textbook
// notation directly.

/*
class LowerTriangle
{
private:
    int *A;
    int n;
    
    int rowMajorIndex(int i, int j) const;
public:
    LowerTriangle()
    {
        n = 2;
        A = new int[2 * (2 + 1) / 2];
    }
    LowerTriangle(int n)
    {
        this->n = n;
        A = new int[n * (n + 1) / 2];
    }
    // Raw arrays have single ownership here; deleting copy prevents shallow
    // copies that would try to delete the same buffer twice.
    LowerTriangle(const LowerTriangle&) = delete;
    LowerTriangle& operator=(const LowerTriangle&) = delete;
    ~LowerTriangle()
    {
        delete []A;
    }
    
    void Set(int i, int j, int x);
    int Get(int i, int j) const;
    void Display() const;
    int GetDimension() const {return n;}
};

int LowerTriangle::rowMajorIndex(int i, int j) const
{
    // Count all stored values before row i, then offset j within that row.
    return i * (i - 1) / 2 + j - 1;
}

void LowerTriangle::Set(int i, int j, int x)
{
    // non-zeroes will only be present when i >= j
    if(i >= j)
        A[rowMajorIndex(i, j)] = x;
}

int LowerTriangle::Get(int i, int j) const
{
    if (i >= j)
        return A[rowMajorIndex(i, j)];
    return 0;
}

void LowerTriangle::Display() const
{
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            if (i >= j)
                std::cout << A[rowMajorIndex(i, j)] << " ";
            else
                std::cout << "0 ";
        }
        std::cout << std::endl;
    }
}
*/

class LTMatrix{
private:
    int n;
    int* A;

    int rowMajorIndex(int i, int j) const;
    int colMajorIndex(int i, int j) const;
public:
    explicit LTMatrix(int n) : n(n), A(new int[n * (n + 1) / 2]) {}
    // Raw-array ownership is intentionally visible for this lesson. Deleted
    // copy operations prevent accidental shallow copies and double deletes.
    LTMatrix(const LTMatrix&) = delete;
    LTMatrix& operator=(const LTMatrix&) = delete;
    ~LTMatrix(){ delete[] A; }
    void displayRowMajor() const;
    void displayColMajor() const;
    void setRowMajor(int i, int j, int x);
    void setColMajor(int i, int j, int x);
    int getRowMajor(int i, int j) const;
    int getColMajor(int i, int j) const;
    int getN() const { return n; }

};

int LTMatrix::rowMajorIndex(int i, int j) const {
    // Row-major stores each lower-triangle row contiguously.
    return ((i * (i - 1)) / 2) + j - 1;
}

int LTMatrix::colMajorIndex(int i, int j) const {
    // Column-major stores each lower-triangle column contiguously.
    return (n * (j - 1) - (((j - 2) * (j - 1)) / 2)) + (i - j);
}

void LTMatrix::setRowMajor(int i, int j, int x) {
    if (i >= j){
        A[rowMajorIndex(i, j)] = x;
    }
}

void LTMatrix::setColMajor(int i, int j, int x) {
    if (i >= j){
        A[colMajorIndex(i, j)] = x;
    }
}

int LTMatrix::getRowMajor(int i, int j) const {
    if (i >= j){
        return A[rowMajorIndex(i, j)];
    } else {
        return 0;
    }
}

int LTMatrix::getColMajor(int i, int j) const {
    if (i >= j){
        return A[colMajorIndex(i, j)];
    } else {
        return 0;
    }
}

void LTMatrix::displayRowMajor() const {
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            if (i >= j){
                std::cout << getRowMajor(i, j) << " ";
            } else {
                std::cout << 0 << " ";
                }
            }
        std::cout << std::endl;
    }
}

void LTMatrix::displayColMajor() const {
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            if (i >= j){
                std::cout << getColMajor(i, j) << " ";
            } else {
                std::cout << 0 << " ";
                }
            }
        std::cout << std::endl;
    }
}

int main()
{
    int d;
    std::cout << "Enter Dimensions of the square matrix: ";

    if (!(std::cin >> d) || d <= 0) {
        std::cerr << "Invalid matrix dimension.\n";
        return 1;
    }
    
    // LowerTriangle lm(d);
    LTMatrix rowMatrix(d);
    LTMatrix colMatrix(d);

    int x;
    std::cout << "Enter all elements below \n";
    
    for(int i = 1; i <= d; i++)
    {
        for(int j = 1; j <= d ; j++)
        {
            if (!(std::cin >> x)) {
                std::cerr << "Invalid matrix element.\n";
                return 1;
            }
            // lm.Set(i,j,x);
            rowMatrix.setRowMajor(i, j, x);
            colMatrix.setColMajor(i, j, x);
        }
    }
    // lm.Display();
    std::cout << "\nMatrix using row-major storage:\n";
    rowMatrix.displayRowMajor();
    std::cout << "\nValue at row 3, column 2: " << rowMatrix.getRowMajor(3, 2) << "\n";

    std::cout << "\nMatrix using column-major storage:\n";
    colMatrix.displayColMajor();
    std::cout << "\nValue at row 2, column 1: " << colMatrix.getColMajor(2, 1) << "\n";

    return 0;
}
