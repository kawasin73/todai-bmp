#include "bitmap.h"
#include <stdlib.h>
#include <stdio.h>

void Posterization(Image *img);

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: program <inputfile> <outputfile>\n");
        exit(1);
    }

    Image *colorimg;

    if ((colorimg = Read_Bmp(argv[1])) == NULL)
    {
        exit(1);
    }

    Posterization(colorimg);

    if (Write_Bmp(argv[2], colorimg))
    {
        exit(1);
    }

    Free_Image(colorimg);

    return 0;
}

unsigned char conv(unsigned char v)
{
    if (v < 64)
    {
        return 0;
    }
    else if (v < 128)
    {
        return 85;
    }
    else if (v < 192)
    {
        return 170;
    }
    else
    {
        return 255;
    }
}

void Posterization(Image *img)
{
    int i, j;
    unsigned int index;
    unsigned char gray;

    for (i = 0; i < img->height; i++)
    {
        for (j = 0; j < img->width; j++)
        {
            index = img->width * i + j;
            gray = img->data[index].r * 0.299 + img->data[index].g * 0.587 + img->data[index].b * 0.114;
            img->data[index].r = img->data[index].g = img->data[index].b = conv(gray);
        }
    }
}
