#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <cs50.h>

int main (int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover infile\n");
        return 1;
    }

    //1:  OPEN MEM CARD FILE
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 2;
    }

    //Buffer
    uint8_t buffer[512];
    
    //output file pointer
    FILE *outptr;
    // hold new file name [[RELEASE]]
    char *filename = malloc(8 * sizeof(char));
    if (filename == NULL)
    {
        fprintf(stderr, "Error -- out of memory.\n");
        return 4;
    }
    
    // track filenames
    int count = 0;
    //when jpeg is found set to true to start writing
    char ready = false;
    
    
    
    //2. REPEAT UNTIL EOF / 3. READ 512 BYTES TO BUFFER
    while (fread(&buffer, 1, 512, inptr) > 0)
    {


        //4. START A NEW JPEG?
        // does the first 4 bytes resemble a jpeg struct
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
                
                //we have found a jpeg set ready to true to start writing to file
                ready = true;
            
                //if we are already working on a JPEG close it
                if(count > 0)
                {
                    
                    //close any open files
                    fclose(outptr);
                    

                }
                
                // Start a new JPEG
                
                // print new filname
                sprintf(filename, "%03d.jpg", count);
                
                //open new file
                outptr = fopen(filename, "w");
                if (outptr == NULL)
                {
                    fprintf(stderr, "Could not open %s.\n", filename);
                    return 5;
                }
                
                // increase count to track filenames
                
                count++;

                
        }

        if(ready == true)
        {
            
            //7. WRITE 512 BYTES UNTIL COMPLETE OR NEW JPEG
            fwrite(buffer, 1, 512, outptr);
    
        }

    }
    
    
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);
    
    
    
    //release mallocs
    free(filename);
    
    
    return 0;
}


/* TODO:
    -open memory card file
        -fopen !check return for NULL
        
    -find beginning of JPEG
        -first 3 bytes: 0xff 0xd8 0xff
        -last byte: 0xe0, 0xe1, 0xe2, ...., 0xef
        -if (buffer[0] == 0xff &&
             buffer[1] == 0xd8 &&
             buffer[2] == 0xff &&
             (buffer[3] & 0xf0) == 0xe0)
        
    -open a new JPEG
        -fread(data, size, number, inptr)
            -fread(buffer, 1, 512, raw_file)
            -fread(buffer, 512, 1, raw_file) <<use
            -create a new file name:
                -sprintf(filename, "%000.jpg", 2)
                -filename: char array to store the result string
            -FILE *img = fopen(filename, "W")
        
    -write 512 bytes until new JPEG is found
        -fwrite(data, size, number, outptr)
        
    -detect end of file
        -read in 512 bytes at a time until EOF
        -we will get something shorter than 512 at EOF
    
    PSUEDOCODE:
        -open card file
        -repeat until end of card
            -read 512 bytes into a buffer
            -start of a new JPEG?
                -yes: ask if we already found a JPEG
                -no: continue
            -already found a JPEG?
                -no: open new file
                -yes: close prev file and open new file
        -close any remaining files
*/
    