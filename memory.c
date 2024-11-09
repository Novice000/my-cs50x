#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main (void)
{
    int n= 8;
    int* integer= &n;
    printf("%p", integer);
}
