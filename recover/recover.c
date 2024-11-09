#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Usage:  ./recover\n");
        return 1;
    }

    FILE *mem_card= fopen(argv[1], "rb");
    if(mem_card == NULL)
    {
        printf("file not found");
        return 1;
    }

    char filename[8];
    uint8_t* buffer=  malloc(512);
    int image_count=0;
    FILE *img = NULL;

    while(fread(buffer, 1, 512, mem_card) == 512)
    {
        if(buffer[0]==0xff && buffer[1]==0xd8 && buffer[2]==0xff && (buffer[3]&0xf0) == 0xe0)
        {
            sprintf(filename, "%03i.jpg", image_count);
            if(image_count == 0)
            {
                img = fopen(filename, "wb");
                fwrite(buffer , 1, 512 ,img);
            }
            else
            {
                fclose(img);
                img = fopen(filename, "wb");
                fwrite(buffer , 1, 512 ,img);
            }
                image_count++;
        }
        else
        {
            if(img != NULL)
            {
                fwrite(buffer,1,512,img);
            }
            else
            {
                continue;
            }
        }
    }

    free(buffer);
    fclose(mem_card);
    fclose(img);
}
