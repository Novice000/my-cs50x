#include <cs50.h>
#include <stdio.h>

int main(void){
    int x= get_int("what's x? ");
    int y= get_int("what's y> ");

    if(x < y){
        printf("x=%i is less that y=%i \n", x, y);
    }
    else if(x > y){
        printf("x=%i is greater that y=%i\n", x, y);
    }
    else{
        printf("x is equal to y\n");
    }
}
