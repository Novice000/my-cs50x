#include <stdio.h>
#include <cs50.h> // to get plain text
#include <string.h> // for strlen()
#include <ctype.h> // for string operation upper, lower

void substitution_fn(); // for further substitute
void encrypt(char pos, string key);
// to get the alphabet array value of each plain text element (ex:plaintext = h|alphabet array = 8 {a=0, b=1 .....z=26})

int main(int argc, string argv[])
{
    if (argc == 2) // number of commands in terminal
    {
        if (strlen(argv[1]) == 26)
        {
            for (int i = 0; i < strlen(argv[1]) ; i++)
            {

                if (! isalpha(argv[1][i]))
                {
                    printf("Key must contain 26 characters.\n");
                    return 1;
                }

                for (int j = i + 1 ; j < strlen(argv[1]) ; j++)
                {

                    if (toupper(argv[1][j]) == toupper(argv[1][i]))
                    {
                        printf("Key must not contain repeated alphabets.\n");
                        return 1;
                    }
                }
            }

            substitution_fn(argv[1]);

        }
        else
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }

    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    return 0;
}


void substitution_fn(string key)
{
    string p = get_string("plaintext: ");

    printf("ciphertext: ");

    for (int i = 0; i < strlen(p); i++)
    {
        if (isalpha(p[i]))
        {
            if (islower(p[i]))
            {
                encrypt(p[i], key);
            }
            else
            {
                encrypt(p[i], key);
            }

        }
        else
        {
            printf("%c", p[i]);
    }
    }

    printf("\n");

}

void encrypt(char pos, string key)
{
    string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (int i = 0; i < strlen(alpha); i++)
    {
        if (islower(pos))
        {
            if (pos == tolower(alpha[i]))
            {
                printf("%c", tolower(key[i]));
            }
        }
        else
        {
            if (pos == toupper(alpha[i]))
            {
                printf("%c", toupper(key[i]));
            }
        }
    }

}


//     if(argc != 2){
//         printf("Usage: ./substitution KEY\n");
//         return 1;
//     } else if(strlen(argv[1]) != 26){
//         printf("string must contain 26 characters");
//         return 1;
//     }for(int i=0, n= strlen(argv[1]); i<n; i++){
//         if(!isalpha(argv[1][i])){
//             printf("all characters must be alphabets\n");
//             return 1;
//         } }
//     char key[strlen(argv[1])];
//     for(int j=0, m=26; j<m; j++){
//         key[j]= argv[1][j];
//         if(isalpha(key[j]) && islower(key[j])){
//         key[j]=toupper(key[j]); }
//     }

//     char useless[]= key;

//     // for(int g= 0; g<26; g++){
//     //     for(int q= 0; q<26; q++){
//     //         if(key[g] != useless[q]){
//     //             useless[q]=key[g];
//     //         } else if(key[g] == useless[q]){
//     //             printf("Duplicated Text %c and %c", key[g], useless[q]);
//     //             return 1;
//     //         }
//     //     }
//     // }

//     char compareC[]= { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
//     string text= get_string("plaintext: ");

//     int capital_count[strlen(text)];
//     for(int k=0, o=strlen(text);k<o;k++){
//         if(isupper(text[k])){
//             capital_count[k]=1;
//             text[k]= text[k];
//         }else if(islower(text[k]) && isalpha(text[k])){
//             capital_count[k]=0;
//             text[k]=toupper(text[k]);
//         } else{
//             capital_count[k]=0;
//         }
//     }
//     char cipher[strlen(text)];
//     for(int x = 0, y= strlen(text);x<y;x++){
//         for(int z=0;z<26;z++){
//             if(isalpha(text[x]) && text[x]==compareC[z] && capital_count[x]==1){
//                 cipher[x]= key[z];
//             }else if((text[x] == compareC[z]) && isalpha(text[x]) && capital_count[x]==0 ){
//                 cipher[x]= tolower(key[z]);
//             } else if(ispunct(text[x]) || isdigit(text[x]) || isspace(text[x])){
//                 cipher[x]=text[x];
//             }
//         }
//     }
//         printf("ciphertext: %s\n", cipher);
// }
