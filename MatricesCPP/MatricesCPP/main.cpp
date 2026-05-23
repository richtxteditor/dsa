//
//  main.cpp
//  MatricesCPP
//
//  Created by richie on 12/8/25.
//

#include <iostream>

#include "lt_matrix.h"

// Lower triangular matrix:
// non-zero when i >= j, zero above the diagonal.
// The demo uses 1-based matrix coordinates so the formulas match textbook
// notation directly.
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

int main()
{
    std::cout << "=== Lower Triangular Matrix: row-major vs column-major demo ===\n";
    DemonstrateLTMatrixLayouts();
    std::cout << "\n=== LowerTriangle interactive demo ===\n";

    int d;
    std::cout << "Enter Dimensions of the square matrix: ";
    if (!(std::cin >> d) || d <= 0) {
        std::cerr << "Invalid matrix dimension.\n";
        return 1;
    }
    
    LowerTriangle lm(d);
    
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
            lm.Set(i,j,x);
        }
    }
    lm.Display();
    return 0;
}
