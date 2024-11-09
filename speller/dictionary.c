// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 997;

int count;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    if(table[hash(word)] != NULL){
        for(node* ptr= table[hash(word)]; ptr != NULL; ptr= ptr->next)
        {
            if(strcasecmp(word,ptr->word)==0)
            {
                return true;
            }
            else
            {
                continue;
            }
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int length= strlen(word);
    unsigned int char_sum=0;
    // TODO: Improve this hash function
    for(int i=0; i < length; i++)
    {
        if(isalpha(word[i]))
        {
            if(islower(word[i]))
            {
                char_sum += toupper(word[i]);
            }
            else
            {
            char_sum += word[i];
            }
        }
         else
        {
            char_sum += word[i];
        }
    }

    return ((char_sum-64) % N);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    count= 0;
    char buffer[46];
    FILE* source= fopen(dictionary, "r");
    if(source==NULL)
    {
        printf("Invalid file source");
        return 1;
    }
    while(fscanf(source, "%s", buffer) != EOF)
    {
        node *new_node= malloc(sizeof(node));
        if(new_node == NULL)
        {
            return 1;
        }

        strcpy(new_node->word, buffer);

        new_node->next = NULL;
        unsigned int index= hash(buffer);
        if(table[index] == NULL)
        {
            table[index] = new_node;
            count+=1;
        }
        else if(table[index] != NULL)
        {
            new_node->next= table[index];
            table[index]= new_node;
            count += 1;
        }
        else
        {
            return false;
        }

    }

    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for(int i=0; i<N; i++)
    {
        if(table[i]==NULL)
        {
            continue;
        }
        else
        {
            node* ptr= table[i];
            while(ptr != NULL)
            {
                node* temp= ptr->next;
                free(ptr);
                ptr = temp;
            }
        }
    }
    return true;
}

// char* lowercase(char* word)
// {
//     int length= strlen(word);
//     for(int i=0; i<length; i++)
//     {
//         if(isalpha(word[i]) && isupper(word[i]))
//         {
//             word[i]= tolower(word[i]);
//         }
//     }
// }
