//
//  templateClass.cpp
//  dsa
//
//  Created by rich on 8/20/24.
//
#include <iostream>
#include <stdio.h>

using namespace std;

template<class T>
class Arithmetic
{
private:
    T a;
    T b;
public:
    Arithmetic(T a, T b);
    T add();
    T sub();

    
};

template<class T>
Arithmetic<T>::Arithmetic(T a, T b)
    {
        this->a = a;
        this->b = b;
    }

template<class T>
T Arithmetic<T>::add()
    {
        T c;
        c = a+b;
        return c;
    }

template<class T>
T Arithmetic<T>::sub()
    {
        T c;
        c = a - b;
        return c;
    }


int main()
{
    Arithmetic<char> ar('B', 'A');
    
    cout<<"Add: "<<(int)ar.add()<<endl;
    cout<<"sub: "<<(int)ar.sub()<<endl;

    
    return 0;
}
