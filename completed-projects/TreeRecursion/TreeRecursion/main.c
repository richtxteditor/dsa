//
//  main.c
//  TreeRecursion
//
//  Created by rich on 8/27/24.
//

#include <stdio.h>

void fun(int n)
{
    if (n > 0)
    {
        printf("%d ",n);
        fun(n-1);
        fun(n-1);
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    fun(3);
    return 0;
}
