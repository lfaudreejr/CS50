/**
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./copy infile outfile\n");
        return 1;
    }
    
    //remember argv1
    float f = atof(argv[1]);


    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    
    //Make outfile BITMAPFILEHEADER
    BITMAPFILEHEADER bfout;
    bfout = bf;
    //Make outfile BITMAPINFOHEADER
    BITMAPINFOHEADER biout;
    biout = bi;
    
    //setting new width, height, and size
    biout.biWidth = bi.biWidth * f;
    biout.biHeight = bi.biHeight * f;
    
    // determine padding for scanlines
    int out_padding = (4 - (biout.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    //outfile size
    biout.biSizeImage = (((biout.biWidth * 3) + out_padding) * abs(biout.biHeight));
    bfout.bfSize = (sizeof(biout) + sizeof(bfout)) + biout.biSizeImage; 
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bfout, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&biout, sizeof(BITMAPINFOHEADER), 1, outptr);

    

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

 
    // temporary storage
    RGBTRIPLE triple;
    
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        
        for (int v = 0; v < f; v++)
        {
            
             // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                
                for (int r = 0; r < f; r++)
                {
                    // write RGB to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr); 
                }

                
            }
            
            //add padding
            for (int k = 0; k < out_padding; k++)
            {
                fputc(0x00, outptr);
            }
            
            //reset if at end
            if(v < f-1){
                long offset = (bi.biWidth * sizeof(RGBTRIPLE));
                fseek(inptr, -(offset), SEEK_CUR);
            }
        }   
        
        // skip over padding
        fseek(inptr, padding, SEEK_CUR);
        
    }



    
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
