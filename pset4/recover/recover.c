#include <stdio.h>
#include <stdint.h>
#include <cs50.h>

// use the defined width unsigned
// integer types from stdint to
// define a custom BYTE type, based
// on approach in bmp.h
// we know that we will be reading in blocks of
// 512 bytes. Thus, we need to isolate the in_file's bytes
typedef uint8_t  BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover raw-image\n");
        return 1;
    }

    // remember the in_image name
    char *in_image = argv[1];

    // open input image file to read from
    FILE *inptr = fopen(in_image, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 2;
    }

    // declare bool valid loop variable
    // loop as long as variable is true
    bool reading_card = true;

    int jpeg_counter = 0;

    // initialize a file pointer as pointing to NULL.
    FILE *img = NULL;


    while (reading_card)
    {
        // Define a 'buffer' array with 512
        // 'open spaces' for each BYTE we read in
        BYTE buffer[512];

        // read in one 'element of data' 512 bytes long
        // so one 'block' is 512 bytes long. fread
        // returns the number of elements of data (blocks)
        // 'read in' -> lots of abstraction with File I/O
        int blocks_read = fread(buffer, 512, 1, inptr);

        if (blocks_read != 1)
        {
            // then end of file reached
            // close out the opened out-file.
            // and flip off the reading_card switch
            fclose(img);
            reading_card = false;
        }

        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // identifies a new jpeg file
            // if this isn't the first jpg,
            // then close it so we can open a new one
            if (img != NULL)
            {
                fclose(img);
            }

            // identify the file name of the new jpeg we will start
            char filename[10];
            sprintf(filename, "%03i.jpg", jpeg_counter);

            // open it up, saving to the previously defined file
            // pointer variable 'img.' Increment our counter.
            img = fopen(filename, "w");
            jpeg_counter++;
        }

        // keep the write stream open so long as we have a defined out-file
        // and the reading_card switch is on.
        if (img != NULL && reading_card)
        {
            fwrite(buffer, 512, 1, img);
        }

    }

    // no longer reading from card, end of file was reached and all out files close
    // close out the in_file pointer, no more reading to do. And return 0 from main.
    // no memory was dynamically allocated with malloc, so there's no memory to free.

    fclose(inptr);

    return 0;

}

