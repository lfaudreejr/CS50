//================================================================//
//=========					CS50 : CRACK			==============//
//=========			PASSWORD ENCRYPTION CRACK		==============//
//================================================================//

#define _XOPEN_SOURCE
#include <unistd.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

//=======================MAIN PROGRAM=============================//

int main(int argc, string argv[])
{
	//Make sure that only 2 arguments are passed
    if(argc != 2){
        printf("Error\n");
        return 1;
    }
    
    //Store the users input as ciphertext
    string ciphertext; 
    ciphertext = argv[1];
    
    //Set character list for out generator
    const char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    
    //Our generated plaintext
    char plaintext[5];
    plaintext[4] = '\0';
    
	//The hash after encrytion
    string hash;
    
	
    //Gnerate the first letter in our plaintext
    for(int i = 0; i < 52; i++){
        
		//Set our i'th letter into our plaintext
        plaintext[0] = letters[i];
        
        //Encrypt our plaintext
        hash = crypt(plaintext, "50");
        
        //Compare our encrypted hash and the input ciphertext
        if (strcmp(hash, ciphertext) == 0){
            //did we find it?
            printf("%s\n", plaintext);
        break;
        
        }
        
        else { 
            
        
            //Generate our second plaintext
            for(int j = 0; j < 52; j++){
                
				//Set our j'th letter into our plaintext
                plaintext[1] = letters[j];
            
                //Encrypt our plaintext
                hash = crypt(plaintext, "50");
                
                //Compare our encrypted hash and the input ciphertext
                if(strcmp(hash, ciphertext) == 0){
                    printf("%s\n", plaintext);
                    return 1;
                }
                
                else {
                    
                    //Generate our third plaintext
                    for(int k = 0; k < 52; k++){
                        
                        //Set our k'th letter into our plaintext
                        plaintext[2] = letters[k];
                        
                        //Encrypt our plaintext
                        hash = crypt(plaintext, "50");
                        
                        //Compare our encrypted hash and the input ciphertext
                        if(strcmp(hash, ciphertext) == 0){
                            printf("%s\n", plaintext);
                            return 1;
                        }
                    
                        else {
                            //Generate our fourth plaintext
                            for(int l = 0; l < 52; l++){
                        
                                //set the 4th letter of our hash
                                plaintext[3] = letters[l];
                                
                                //Encrypt our plaintext
                                hash = crypt(plaintext, "50");
                                
                                //Compare our encrypted hash and the input ciphertext
                                if(strcmp(hash, ciphertext) == 0){
                                    printf("%s\n", plaintext);
                                    return 1;
                                }
                            }
                        
                        }
                    }
                }
            }
        }
    }

    //End Program if password not found
    return 0;
    
}