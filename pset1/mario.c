#include <cs50.h>
#include <stdio.h>

int main(void)
{
    
    int height;  //Stores height of pyramid
    
    
    //Prompt the user for valid input between 0 and 23:
    do{
        printf("Enter a Height: ");
        height = get_int();  //Get height from the user
    }
    while (height < 0 || height > 23);
    
    //iterate the height
    for(int i = 1; i <= height; i++){
        
        int space = height - i;   //Stores number of space in front of first half of pyramid
        int hashes = height - space;  //number of hashes per line
        
        //determine how many spaces to use
        for(int j = 0; j < space; j++){
            printf(" ");
        }
        //determine the number of hashes to use
        for(int k = 0; k < hashes; k++){
                printf("#");
        }
        //print the gap
        printf("  ");
        //print remaining hashes
        for(int k = 0; k < hashes; k++){
                printf("#");
        }
        
        
        printf("\n"); 
        
        
    }
}

