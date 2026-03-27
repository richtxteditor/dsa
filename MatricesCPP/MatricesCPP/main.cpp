//
//  main.cpp
//  MatricesCPP
//
//  Created by richie on 12/8/25.
//

// Upper Triangular Matrix
// M[i,j] = if i > j
// M[i,j] = non-zero if i<=j
// non-zero = 5+4+3+2+1
//          = n + n 01 + ... + 3 + 2 + 1 = n(n + 1)/2
// zero = n(n - 1)/ 2



#include <iostream>

class LowerTriangle
{
private:
    int *A;
    int n;
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
    ~LowerTriangle()
    {
        delete []A;
    }
    
    void Set(int i, int j, int x);
    int Get(int i, int j);
    void Display();
    int GetDimension() {return n;}
};

void LowerTriangle::Set(int i, int j, int x)
{
    // non-zeroes will only be present when i >= j
    if(i >= j)
        A[i * (i - 1) / 2 + j - 1] = x;
}

int LowerTriangle::Get(int i, int j)
{
    if (i >= j)
        return A[i * (i - 1) / 2 + j - 1];
    return 0;
}

void LowerTriangle::Display()
{
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            if (i >= j)
                std::cout << A[i * (i - 1) / 2 + j - 1 ] << " ";
            else
                std::cout << "0 ";
        }
        std::cout << std::endl;
    }
}

int main()
{
    int d;
    std::cout << "Enter Dimensions of the square matrix: ";
    std::cin >> d;
    
    LowerTriangle lm(d);
    
    int x;
    std::cout << "Enter all elements below \n";
    
    for(int i = 1; i <= d; i++)
    {
        for(int j = 1; j <= d ; j++)
        {
            std::cin >> x;
            lm.Set(i,j,x);
        }
    }
    lm.Display();
    return 0;
}
