//
//  cppClassesPractice.cpp
//  dsa
//
//  Created by rich on 8/20/24.
//

#include <iostream>
#include <stdio.h>

using namespace std;

class Rectangle
{
    
private:

    int length;
    int breadth;
    
public:
   
    Rectangle()
    {
        length = 0;
        breadth = 0;
    }

    Rectangle(int l, int b)
    {
        length = l;
        breadth = b;
    }

    void initialise(int l, int b)
    {
        length = l;
        breadth = b;
    }
    
    
    void setLength(int l)
    {
        length = l;
    }
    
    void setBreadth(int b)
    {
        breadth = b;
    }
    
    int getLength()
    {
        return length;
    }
    
    int getBreadth()
    {
        return breadth;
    }
    
    int area()
    {
        return length * breadth;
    }
    
    int perimiter()
    {
        int p;
        p= 2 * (length + breadth);
        
        return p;
    }
    ~Rectangle()
    {
        cout<<"Rectangle destructor destroyed itself\n";
    }
};


int main(int argc, const char * argv[]) {
    std::cout << "Hello, World!\n";
    
    Rectangle r(2,2);
    
    cout<<"Area: "<<r.area()<<endl;
    cout<<"Perimeter: "<<r.perimiter()<<endl;
    
    
    return 0;
}
