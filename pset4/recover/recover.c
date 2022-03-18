#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int main(int argc, char *argv[])
{
   if(argc != 2)
    {
        printf("Usage: ./recover 'your file'\n");
        return 1;
    }
    FILE *argc1 = fopen(argv[1], "r");
    if(argc1 == NULL)
    {
        printf("Unable to open file.\n");
        return 2;
    }
    FILE *image = NULL;
    int counter = 0;
    unsigned char buffer[512];
    bool found = false;
    for(;fread(buffer, 512, 1, argc1) == true;)
    {
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xe0) == 0xe0)
        {
            if(found == true)
            {
                fclose(image);
            }
            else
            {
                found = true;
            }
            char filename[8];
            sprintf(filename, "%03d.jpg", counter);
            image = fopen(filename, "a");
            if(found == true)
            {
                counter++;
            }
        }
        if(found == true)
        {
            fwrite(&buffer, 512, 1, image);
        }
    }
    fclose(argc1);
    fclose(image);
    return 0;
}