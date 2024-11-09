#include <stdio.h>
#include <cs50.h>

int main(void){
    int x= get_int("type an integer for x, ");
    int y= get_int("type an integer for y, ");

    float z= (float) x/ (float) y;
    printf("%.5f", z);
}
