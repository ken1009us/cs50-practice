#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    else
    {
        // open memory card
        char* input_file_name = argv[1];
        FILE* input_file = fopen(input_file_name, "r");

        if (input_file == NULL)
        {
            printf("Cannot open this file.\n");
            return 2;
        }

        // set variables
        BYTE buffer[512];
        // track the number of images
        int count = 0;
        // each of the JPEG's name
        char filename[8];
        // write to new image
        FILE* new_image = NULL;

        //read files
        while (fread(&buffer, 512, 1, input_file) == 1)
        {
            //check if starts of JPEG file
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
            {
                //if not the first JPEG image, close
                if (!(count == 0))
                {
                    fclose(new_image);
                }

                //set the file
                sprintf(filename, "%03i.jpg", count);
                new_image = fopen(filename, "w");
                count ++;
            }

            // write to the new image file
            if (!(count == 0))
            {
                fwrite(&buffer, 512, 1, new_image);
            }
        }

        //close the file
        fclose(input_file);
        fclose(new_image);

        return 0;
    }
}
