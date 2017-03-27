#include <cs50.h>
#include <stdio.h>
#include <math.h>

void strip(long long card, int cclength);

int main(void)
{
    //check if card is valid
    //if card is valid test the type and return the type
    //AMEX starts with 34 or 37
    //VISA starts with 4
    //Mastercard starts with 51, 52, 53, 54, 55
    
    //to test validitity - start at second to last number multiply every other number by 2 then add the the single digits
    //then add the sum to sum of digits not multiplied
    //then if last digit of sum is 0 = valid
    
    //GLOBAL VARIABLES//
    
    long long ccnumber;                         //card number
    int cardlen;                                //card length
    
    
    //GET USER INPUT//
    
    
    printf("Card number:");
    ccnumber = get_long_long();                 //store user input
    
    cardlen = floor(log10(ccnumber)) + 1;       //get the number of digits in cc card
    
    
    //DETERMINE VALID OR INVALID
    
    
    strip(ccnumber, cardlen);                   //call strip function to determine validity
    
    

    return 0;
}


void strip(long long card, int cclength ){
    long long cc_copy = card;
    long long cardnum = card;
    int everyother = 0;                         //holder for everyother digit starting from last digit
    int testdouble = 0;                         //hold for double digit for splitting and sum
    int everydouble = 0;                        //double every other digit starting second from the last
    int nextlast;                               //next to last number
    int sumsum = 0;                             //sum of everyother and everydouble
    
    
    //iterate over cc number
    
    
    for(int i = 0; i < cclength; i++){
        
        long long cc = card;
        
        int last = cc % 10;                     //hold the last cc digit
        
        card = card / 100;                      //skip every other digit
        
        everyother = everyother + last;         //add everyother digit
        
    }
    
    
    //iterate starting from the second to last digit
    
    
    for(int j = 0; j < cclength; j++){
        //take off the last digit
        cc_copy = (cc_copy / 10);               //take off the last digit
        nextlast = (cc_copy % 10);              //save the second to last digit
        cc_copy = (cc_copy / 10);               //take off another digit to skip over
        
        testdouble = nextlast * 2;              //double the digit that is grabbed
        
        
        //test if greater than 9
        if(testdouble > 9) {
            testdouble = testdouble - 9;
        };
        
        everydouble = everydouble + testdouble; //sum of everother digit doubled
        
        
        testdouble = 0;                         //reset test to zero
        
        }
    
    
    
    sumsum = everyother + everydouble;          //sum of all digits pulled

    
    //check validity//
    
    if(sumsum % 10 == 0){
        //int lenMinusOne = floor(cardnum / ( pow(10, cclength)));
        int firstTwoDigits = floor(cardnum / ( pow(10, cclength - 2)));
        
        
            switch(firstTwoDigits){
            
                case 34:
                case 37:
                    printf("AMEX\n");
                    break;
                    
                case 40:
                case 41:
                case 42:
                case 43:
                case 44:
                case 45:
                case 46:
                case 47:
                case 48:
                case 49:
                    printf("VISA\n");
                    break;
                    
                case 51:
                case 52:
                case 53:
                case 54:
                case 55:
                    printf("MASTERCARD\n");
                    break;
                    
                default:
                    printf("INVALID CARD\n");
                    break;
            }
            
        
    } else { printf("INVALID\n");}
    
}
