#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    
    //Do we have 1 argument?
    if(argc != 2){
        printf("Try Again\n");
        return 1;
    }
    
    //variable for our pw input
    string pw;
    
    //User Input
    printf("plaintext:");
    pw = get_string();
    
    //Ciphertext Label
    printf("ciphertext:");    
    
    
    //convert argv[] to an int
    int k = atoi(argv[1]);
 
    
    //iterate over password
    for(int i = 0, n = strlen(pw); i < n; i++)
    {
        //save the ascii of current char
        int curchar = pw[i];
        int cipher = (curchar + k);
        
        
        //convert if a letter bettween a-z or A-Z
        
        if(isalpha(pw[i])){
            
            //lowercase conversion
            
            if(pw[i] <= 90 && cipher > 90){
                
                do
                    {
                        cipher = ((cipher - 91) + 65);
                    }
                    while (cipher > 90);
                
            }
            
            
            //uppercase conversion
            
            if(pw[i] >= 97)
            {
                if(pw[i] <= 122 && cipher > 122)
                {
                    do
                    {
                        cipher = ((cipher - 123) + 97);
                    }
                    while (cipher > 122);
                }
            }
        
        printf("%c", cipher);
        
        } else {printf("%c", pw[i]);}
    
    }
    printf("\n");
    return 0;
}
