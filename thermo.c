#include "bitmap.h"
#include <stdlib.h>
#include <stdio.h>

void ThermoScale(Image *img);

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

    ThermoScale(colorimg);

    if (Write_Bmp(argv[2], colorimg))
    {
        exit(1);
    }

    Free_Image(colorimg);

    return 0;
}

unsigned char thermoR(unsigned char v)
{
    if (v < 128)
    {
        return 0;
    }
    else if (v < 192)
    {
        return (v - 128) * 4;
    }
    else
    {
        return 255;
    }
}

unsigned char thermoG(unsigned char v)
{
    if (v < 64)
    {
        return (v - 64) * 4;
    }
    else if (v < 192)
    {
        return 255;
    }
    else
    {
        return (255 - v) * 4;
    }
}

unsigned char thermoB(unsigned char v)
{
    if (v <= 64)
    {
        return 255;
    }
    else if (v < 128)
    {
        return (127 - v) * 4;
    }
    else
    {
        return 0;
    }
}

void ThermoScale(Image *img)
{
    int i, j;
    unsigned int index;
    unsigned char gray;
    for (i = 0; i < img->height; i++)
    {
        for (j = 0; j < img->width; j++)
        {
            index = i * img->width + j;
            gray = img->data[index].r * 0.299 + img->data[index].g * 0.587 + img->data[index].b * 0.114;

            img->data[index].r = thermoR(gray);
            img->data[index].g = thermoG(gray);
            img->data[index].b = thermoB(gray);
        }
    }
}
