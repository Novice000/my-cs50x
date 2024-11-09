#include <cs50.h>
#include <stdio.h>

int  calculate_pennies(int cents);
int  calculate_nickel(int cents);
int  calculate_dime(int cents);
int calculate_quarters(int cents);
int sum(int pennies, int dime, int nickel, int quarter);

int main (void){
    int cents;
    do{
        cents= get_int("input change owed ");
    } while(cents<1);

    int quarter= calculate_quarters(cents);
    int cents_one=cents-(quarter*25);
    int dimes= calculate_dime(cents_one);
    int cents_two = cents_one-(dimes*10);
    int nickel= calculate_nickel(cents_two);
    int cents_three=cents_two - (nickel*5);
    int pennies= calculate_pennies(cents_three);
    int cents_four=cents_three-(pennies*1);
    int total_coins = sum(quarter,dimes, nickel, pennies);
    printf("%i\n", total_coins);
}

int calculate_quarters(int cents){
    int q= cents/25;
    return q;
}

int  calculate_dime(int cents){
    int d= cents/10;
    return d;
}

int  calculate_nickel(int cents){
    int n= cents/5;
    return n;
}

int calculate_pennies(int cents){
    int p= cents/1;
    return p;
}

int sum(int pennies, int dime, int nickel, int quarter){
    int number= pennies + dime + nickel + quarter;
    return  number;
}
