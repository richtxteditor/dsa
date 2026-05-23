#include <iostream>
#include "lt_matrix.h"
 
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
    void Display(bool row=true) const;
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
 
void LTMatrix::Display(bool row) const {
    for (int i=1; i<=n; i++){
        for (int j=1; j<=n; j++){
            if (i >= j){
                if (row){
                    std::cout << getRowMajor(i, j) << " ";
                } else {
                    std::cout << getColMajor(i, j) << " ";
                }
            } else {
                std::cout << 0 << " ";
            }
        }
        std::cout << std::endl;
    }
}
 
void DemonstrateLTMatrixLayouts() {
 
    LTMatrix rm(4);
    rm.setRowMajor(1, 1, 1);
    rm.setRowMajor(2, 1, 2);
    rm.setRowMajor(2, 2, 3);
    rm.setRowMajor(3, 1, 4);
    rm.setRowMajor(3, 2, 5);
    rm.setRowMajor(3, 3, 6);
    rm.setRowMajor(4, 1, 7);
    rm.setRowMajor(4, 2, 8);
    rm.setRowMajor(4, 3, 9);
    rm.setRowMajor(4, 4, 10);
 
    rm.Display();
    std::cout << std::endl;
 
    LTMatrix cm(4);
    cm.setColMajor(1, 1, 1);
    cm.setColMajor(2, 1, 2);
    cm.setColMajor(2, 2, 3);
    cm.setColMajor(3, 1, 4);
    cm.setColMajor(3, 2, 5);
    cm.setColMajor(3, 3, 6);
    cm.setColMajor(4, 1, 7);
    cm.setColMajor(4, 2, 8);
    cm.setColMajor(4, 3, 9);
    cm.setColMajor(4, 4, 10);
 
    cm.Display(false);
}
