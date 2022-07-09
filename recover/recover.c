#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Global variables (& BYTE typedef)
typedef uint8_t BYTE;
BYTE buffer[512];

int count = 0;
char *filename = NULL;
FILE *img = NULL;

// Prototypes
void create_img(void);

int main(int argc, char *argv[])
{
    // Usage check
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Open file + file check
    FILE *file = fopen(argv[1], "r");

    if (!file)
    {
        printf("Image cannot be opened for reading\n");
        return 1;
    }

    // Reading 512 bytes into a buffer until the end of a file
    while (fread(buffer, 1, 512, file) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (count == 0)
            {
                create_img();
            }
            else
            {
                fclose(img);
                free(filename);
                create_img();
            }
        }
        else if (count > 0)
        {
            fwrite(buffer, 1, 512, img);
        }
    }
    free(filename);
    fclose(img);
    fclose(file);
}

// Create a new image file, write current block to it, update count
void create_img(void)
{
    filename = malloc(8);
    sprintf(filename, "%03i.jpg", count);
    img = fopen(filename, "w");
    fwrite(buffer, 1, 512, img);
    count++;
}