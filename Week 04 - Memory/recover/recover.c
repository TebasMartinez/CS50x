#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in a FAT
const int FAT = 512;
// Initialize img and filename to NULL
FILE *img = NULL;
char filename[8];
// Initialize file count
int file_count = 0;

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "r");

    // If file not opened properly, tell the user and exit the program
    if (card == NULL)
    {
        printf("File not opened properly\n");
        return 2;
    }

    // Create a buffer for a block of data
    uint8_t buffer[FAT];

    // While there's still data left to read from the memory card
    while (fread(buffer, 1, 512, card) == 512)
    {
        // Create JPEGs from the data
        // If start of new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // If first JPEG
            if (img == NULL)
            {
                // Write
                sprintf(filename, "%03i.jpg", file_count);
                file_count++;
                img = fopen(filename, "w");
                fwrite(buffer, 1, 512, img);
            }
            // If already found a JPEG, close the file already open
            else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", file_count);
                file_count++;
                img = fopen(filename, "w");
                fwrite(buffer, 1, 512, img);
            }
        }
        // If already found a JPEG, keep writing to it
        else
        {
            if (img != NULL)
            {
                fwrite(buffer, 1, 512, img);
            }
        }
    }

    // Close files
    fclose(card);
    fclose(img);
}
