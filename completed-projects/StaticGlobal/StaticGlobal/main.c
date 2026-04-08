//
//  main.c
//  StaticGlobal
//
//  Created by rich on 8/27/24.
//

#include <stdio.h>
int x=0;

int fun(int n)
{
    if(n>0)
    {
        x++;
        return fun(n-1)+x;
    }
    return 0;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    int r;
    r=fun(5);
    printf("Hello, World!\n");
    printf("%d\n",r);
    
    r=fun(5);
    printf("Hello, again!\n");
    printf("%d\n",r);

    return 0;
}
