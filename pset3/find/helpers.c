/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

#include "helpers.h"

#define LIMIT 65536

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    int s = 0;
    int e = n - 1;
    
    while(s <= e)
    {
    
        int middle = (e + s) / 2;
    
            if(value == values[middle])
            {
                return true;
            }
            else if(value < values[middle])
            {
                e = middle - 1;
            }
            else if(value > values[middle])
            {
                s = middle + 1;
            }
        
    }

    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n) sorting algorithm
    //max value of a
    int max = 0;
    for(int i = 0; i <= n; i++){
        if(max < values[i]){
            max = values[i];
        }
    }
    //counting array
	int count[max + 1];
	//sorted array
    int build[n + 1];
	int i, j;


    //initialize count[i to max] to zero
    for(i = 0; i <= max; i++){
        count[i] = 0;
    }
    
    //count the frequencount of each element
    for(i = 0; i < n; i++){
        for(j = 1; j <= max; j++){
            if(j == values[i]){
                count[j] = count[j] + 1;
            };
        }
    }

    
    //add current position to previous
    for(i = 1; i < max + 1; i++){
        count[i] = count[i] + count[i - 1];
    }
    
    //place elements into new sorted build array
    for(j = 0; values[j]; j++){
        build[count[values[j]] - 1] = values[j];
        count[values[j]] = count[values[j]] - 1;
    }
    
    //copy build array to array for output
    for(i = 0; values[i]; i++){
        values[i] = build[i];
    }
    
    return;
}
