#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void){
    string player_one= get_string("Player 1: ");
    string player_two=  get_string("Player 2: ");


    //player ones word sum
    int player1_sum=0;
    for(int i=0, n= strlen(player_one); i<n; i++){
        if(toupper(player_one[i])== 'A'|| toupper(player_one[i])=='E' || toupper(player_one[i])== 'I' || toupper(player_one[i])== 'L' || toupper(player_one[i])== 'N' || toupper(player_one[i])== 'O' || toupper(player_one[i])== 'R' || toupper(player_one[i])== 'U'|| toupper(player_one[i])== 'S' || toupper(player_one[i])== 'T'){
            player1_sum= player1_sum+1;
        }
        else if (toupper(player_one[i])== 'B' || toupper(player_one[i])== 'C' || toupper(player_one[i])== 'M' || toupper(player_one[i])== 'P'){
            player1_sum= player1_sum + 3;
        }
        else if(toupper(player_one[i])=='D' || toupper(player_one[i])== 'G'){
            player1_sum= player1_sum + 2;
        }
        else if(toupper(player_one[i])=='F' || toupper(player_one[i])== 'H' || toupper(player_one[i])== 'V' || toupper(player_one[i])== 'W' || toupper(player_one[i])== 'Y'){
            player1_sum= player1_sum + 4;
        }
        else if(toupper(player_one[i])== 'J'){
            player1_sum= player1_sum + 8;
        }
        else if(toupper(player_one[i])=='K' || toupper(player_one[i])== 'X'){
            player1_sum=  player1_sum + 5;
        }
        else if(toupper(player_one[i])== 'Q' || toupper(player_one[i])=='Z') {
            player1_sum = player1_sum + 10;
        }else{
            player1_sum = player1_sum + 0;
        }
    }

    //player two word sum
    int player2_sum= 0;

    for(int i=0, n= strlen(player_two); i<n; i++){
        if(toupper(player_two[i])== 'A'|| toupper(player_two[i])=='E' || toupper(player_two[i])== 'I' || toupper(player_two[i])== 'L' || toupper(player_two[i])== 'N' || toupper(player_two[i])== 'O' || toupper(player_two[i])== 'R' || toupper(player_two[i])== 'U'|| toupper(player_two[i])== 'S' || toupper(player_two[i])== 'T'){
            player2_sum= player2_sum+1;
        }
        else if (toupper(player_two[i])== 'B' || toupper(player_two[i])== 'C' || toupper(player_two[i])== 'M' || toupper(player_two[i])== 'P'){
            player2_sum= player2_sum + 3;
        }
        else if(toupper(player_two[i])=='D' || toupper(player_two[i])== 'G'){
            player2_sum= player2_sum + 2;
        }
        else if(toupper(player_two[i])=='F' || toupper(player_two[i])== 'H' || toupper(player_two[i])== 'V' || toupper(player_two[i])== 'W' || toupper(player_two[i])== 'Y'){
            player2_sum= player2_sum + 4;
        }
        else if(toupper(player_two[i])== 'J'){
            player2_sum= player2_sum + 8;
        }
        else if(toupper(player_two[i])=='K' || toupper(player_two[i])== 'X'){
            player2_sum=  player2_sum + 5;
        }else if(toupper(player_two[i])== 'Q' || toupper(player_two[i])=='Z') {
            player2_sum = player2_sum + 10;
        } else{
            player2_sum = player2_sum + 0;
        }
    }

    //comparing sums
    if(player2_sum > player1_sum){
        printf("Player 2 wins!\n");
    } else if(player1_sum > player2_sum){
        printf("Player 1 wins\n");
    } else {
        printf("Tie\n");
    }
}
