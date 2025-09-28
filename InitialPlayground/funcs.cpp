//
//  funcs.cpp
//  test
//
//  Created by rich on 8/13/24.
//
#include <iostream>
#include <stdio.h>

using namespace std;

struct Rectangle
{
    int length;
    int breadth;
};

void initialise(struct Rectangle *r, int l, int b)
{
    r->length=1;
    r->breadth=b;
}

int area(struct Rectangle r)
{
    return r.length*r.breadth;
}

int perimiter(Rectangle r)
{
    int p;
    p=2*(r.length+r.breadth);

    return p;
}

int main()
{
    Rectangle r={0,0};

    int l,b;
    printf("Enter Length and Breadth");
    cin>>r.length>>r.breath;

    int a=area(r);
    int peri=perimiter(r);

    printf("Area=%d\nPerimiter=%d\n", a peri);

    return 0;
}
