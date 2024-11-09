#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

int main(void){
    string text= get_string("Text: ");
    int letter_count= 0;
    int word_count= 1;
    int sentence_count= 0;

    for(int i=0; text[i] != '\0'; i++){
        if(!isspace(text[i]) && (!ispunct(text[i]))){
            letter_count= letter_count+1;
        }
        else if(isspace(text[i])){
            word_count=word_count+1;
        } else if(text[i]=='!' || text[i]=='.' || text[i] == '?'){
            sentence_count= sentence_count +1;
        }
    }
    // printf("letters: %i\n", letter_count);
    // printf("words: %i\n", word_count);
    // printf("sentence: %i\n", sentence_count);

    float letter_per_words= ((float)letter_count/ (float) word_count)* 100;
    float sentence_per_words= ((float)sentence_count/(float) word_count)*100;
    int coleman= round(0.0588*letter_per_words - 0.296* sentence_per_words - 15.8);
    // printf("coleman: %i", coleman);
    if(coleman < 1 ){
        printf("Before Grade 1\n");
    } else if(coleman > 16){
        printf("Grade 16+\n");
    } else{
        printf("Grade %i\n", coleman);
    }
}
