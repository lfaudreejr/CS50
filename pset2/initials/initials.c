#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void initial();


int main(void)
{
    string name;
    int length;
    
    //ask user for name input
    
    do {
    name = get_string();
    length = strlen(name);
    }
    while (length <= 0);

    
    //make sure name is a string
    
    if(name != NULL){    
        
        if(name[0] != ' ')
        {
            printf("%c", toupper(name[0]));
        }
        
        //loop through remaining chars
        
        for(int i = 0; i < length; i++)
        {
            //if i'th char is whitespace and the next is not then print the next char
			if(name[i] == ' ' && name[i + 1] != ' ')
			{
			    if(i + 1 < length){
				    printf("%c", toupper(name[i + 1]));
			    }
			}
			
		}
        
        printf("\n");
        return 0;
    }

}