/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

//track words in dictionary
int wordCount = 0;
//nodes
struct node *root;
struct node *newNode;
//returns a new node
struct node *getNode(void)
{
    struct node *newNode = NULL;
    
    newNode = (struct node *)malloc(sizeof(struct node));
    
    if (newNode)
    {
        int i;
 
        newNode->isWord = false;
 
        for (i = 0; i < ALPHABET; i++)
            newNode->child[i] = NULL;
    }
    
    return newNode;
}


/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // TODO
    newNode = root;

        //iterate over each word being read
        for(int i = 0, length = strlen(word); i < length ; i++)
        {   
            char INDEX = word[i];

            //check if apostrophe
            if(INDEX == '\'')
            {
                //123 - 'a' = 26 = last rootNode
                INDEX = 123;
            }
            else
            {
                INDEX = tolower(word[i]);
            }
            
            if (!newNode->child[INDEX - INDEXONE])
                return false;
 
            newNode = newNode->child[INDEX - INDEXONE];
        }
 
        return (newNode != NULL && newNode->isWord);

}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    // TODO
    // open dictionary
    FILE *fp;
    fp = fopen(dictionary, "r");
    if(fp == NULL)
    {
        printf("Error, could not open %s.\n", dictionary);
        unload();
        return 1;
    }

    root = getNode();
    
    //word buffer
    char s[45];
    //iterate through dictionary words
    while(fscanf(fp, "%s", s) != EOF)
    {
        newNode = root;
        //iterate over each word being read
        for(int i = 0, length = strlen(s); i < length ; i++)
        {   
            char INDEX = s[i];

            //check if apostrophe
            if(INDEX == '\'')
            {
                //123 - 'a' = 26 = last rootNode
                INDEX = 123;
            }
            else
            {
                INDEX = tolower(s[i]);
            }

            if (!newNode->child[INDEX - INDEXONE])
                newNode->child[INDEX - INDEXONE] = getNode();
    
            newNode = newNode->child[INDEX - INDEXONE];

        }

        // //track word count && set isWord to true
        newNode->isWord = true;
        wordCount++;
    }
    
    //if EOF return true "dictionary read"
    if(EOF)
    {
        return true;
    }
    
    
    //close dictionary
    fclose(fp);
    return false;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    if(wordCount > 0){
        return wordCount;
    }
    
    return 0;
}

void clear(node* ptr)
{
    for (int i = 0; i < ALPHABET; i++)
    {
        if (ptr->child[i] != NULL)
            clear(ptr->child[i]);
    }
 
    free(ptr);
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{

    clear(root);
    return true;
}
