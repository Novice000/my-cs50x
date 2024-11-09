#include <stdio.h>
void meow(int n);

int main(void){
    int i=0;
    while(i<3){
        printf("meow\n");
        i++;
    };

    for(int ii=0; ii < 3; ii++){
        printf("efemena\n");
    }
    meow(3);
};

void meow(int n){
    for(int i=0;i<=n;i++){
    printf("meow");
    }
}
