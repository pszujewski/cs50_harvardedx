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
        fprintf(stderr, "Usage: ./copy n infile outfile\n");
        return 1;
    }

    // remember n
    int n = atoi(argv[1]);

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

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    /**
    * Save old values of biWidth and biHeight in BYTE variables.
    * They will be used to iterate over old file
    * Also determine padding of in-file, so you can skip over in loops
    *
    * Multiply bi.biWidth and bi.biHeight by a factor of n
    * These are height and width of the image in pixels
    * Then determine padding using forumla below
    *
    * Get the bi.biSizeImage with following formula
    * res = (sizeof(RGBTRIPLE) * bi.biWidth + padding) * abs(bi.biHeight)
    *
    * Then we need the bf.bfSize which is the total file size in bytes
    * including pixels, padding and headers.
    * res = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    * You can now write the updated headers to the out-file
    *
    * foreach row write each pixel (RGBTRIPLE) to an array new_row n times (horizontal resize)
    * for n times write the array to the outfile and write the out_padding
    * skip over infile padding and repeat
    *
    */

    // Save old values of biWidth and biHeight in BYTE variables.
    // get in-file padding
    LONG in_biWidth = bi.biWidth;
    LONG in_biHeight = bi.biHeight;
    int in_padding = (4 - (in_biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // reset bi.biWidth and bi.biHeight by a factor of n and determine out_padding
    bi.biWidth *= n;
    bi.biHeight *= n;
    int out_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // set the new full image size
    bi.biSizeImage = (sizeof(RGBTRIPLE) * bi.biWidth + out_padding) * abs(bi.biHeight);

    // set the new total file size in bytes (includes headers, pixels and padding)
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, old_in_Height = abs(in_biHeight); i < old_in_Height; i++)
    {
        // array to store the horizontal re-sized row
        RGBTRIPLE new_row[bi.biWidth];
        int curr_idx = 0;

        // iterate over pixels in scanline - foreach row
        for (int j = 0; j < in_biWidth; j++)
        {

            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile - this is one pixel
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            for (int ai = 0; ai < n; ai++)
            {
                // write RGB triple to array n times (horizontal)
                new_row[curr_idx] = triple;
                curr_idx++;
            }

        }

        // for n times write the array to the outfile for vertical resize
        for (int az = 0; az < n; az++)
        {
            for (int bz = 0; bz < bi.biWidth; bz++)
            {
               fwrite(&new_row[bz], sizeof(RGBTRIPLE), 1, outptr);
            }
             // then add the out_padding necessary (if any)
            for (int k = 0; k < out_padding; k++)
            {
                fputc(0x00, outptr);
            }
        }

        // skip over padding, if any
        fseek(inptr, in_padding, SEEK_CUR);

    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
