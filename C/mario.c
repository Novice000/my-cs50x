#include <stdio.h>
#include <cs50.h>
void spaces(int counter, int height, int row);
void rh(int n, int row);
void lh(int n, int row);

int main(void){
    int height;
    do{
    height= get_int("input desire height ");
    } while(height<1);
    for(int i=1; i<=height;i++){
            int counter= 0;
            int lc= 0;
            int rc= 0;
            spaces(counter, height, i);
            lh(lc,i);
            spaces(0,3,1);
            rh(rc,i);
            printf("\n");
        }
    }

void spaces(int counter, int height, int row){
  while(counter < height-row){
        printf(" ");
        counter++;
}
}

void lh(int n, int row){
    while(n < row){
    printf("#");
    n++;
            }
}

void rh(int n, int row){
    while(n < row){
    printf("#");
    n++;
            }
}
