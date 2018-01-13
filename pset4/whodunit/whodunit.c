/**
 * Copies a BMP piece by piece, just because.
 */

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 3)
    {
        fprintf(stderr, "Usage: ./copy infile outfile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[1];
    char *outfile = argv[2];

    // open input file for reading using file I/O
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file for writing using file I/O
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    // Defines bf as 'type' BITMAPFILEHEADER
    // inptr is a 'file stream.' It reads all along the stream for a sizeof BITMAPFILEHEADER
    // Save the pointer (see below for more details)
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    // defines bi as 'type' BITMAPINFOHEADER
    // Continue along the inptr stream to read the INFOHEADER. It knows when to stop because we give the size of the header.
    // save the pointer for the bi variable of type BITMAPINFORHEADER. Because that is the type, the memory is statically
    // allocated at compile time (we know how large the INFOHEADER is).
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    /**
    * After we read from the inptr above, we can access the properties on the structures. For example, the bits of the
    * BITMAPFILEHEADER are all saved starting at memory address &bf. Remember the size of the overall structure is
    * defined, as is the size of each of its properties.
    * bi and bf are not pointers, so to access their properties, we don't need to dereference them.
    * The first argument to fread is a pointer to a struct that will contain the bytes we're reading. So it reads from the
    * stream and saves it in the struct. Each property points to its own address in memory since they all have defined sizes
    */

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    // 0x4d42 is the 'magic number' that identifies a bitmap file.
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // write outfile's BITMAPFILEHEADER
    // starting at the memory address of bf, write the copy to the 'write' stream given at outptr
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    // scanline is one row of the bmp
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    // each iteration is a new scanline (row)
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        // biWidth is number of pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            // use the RGBTRIPLE 'type' (which defines a struct) to define variable 'triple'
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // change all white to blue
            if (triple.rgbtRed == 0xff && triple.rgbtBlue == 0xff && triple.rgbtGreen == 0xff)
            {
                triple.rgbtRed = 0x00;
                triple.rgbtBlue = 0xff;
                triple.rgbtGreen = 0x00;
            }

            // change all red to white.
            if (triple.rgbtRed == 0xff && triple.rgbtBlue == 0x00 && triple.rgbtGreen == 0x00)
            {
                //triple.rgbtRed = 0x;
                triple.rgbtBlue = 0xff;
                triple.rgbtGreen = 0xff;
            }

            // write RGB triple to outfile
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }

        // skip over padding, if any
        // padding would always be at the end, after the rgbtriple.
        fseek(inptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
