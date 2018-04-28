#include "bitmap.h"
#include <stdlib.h>
#include <stdio.h>

void GrayScale(Image *img);

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

    GrayScale(colorimg);

    if (Write_Bmp(argv[2], colorimg))
    {
        exit(1);
    }

    Free_Image(colorimg);

    return 0;
}

void GrayScale(Image *img)
{
    int i, j;
    unsigned int index;
    unsigned char color;

    for (i = 0; i < img->height; i++)
    {
        for (j = 0; j < img->width; j++)
        {
            index = img->width * i + j;
            color = img->data[index].r * 0.299 + img->data[index].g * 0.587 + img->data[index].b * 0.114;
            img->data[index].r = img->data[index].g = img->data[index].b = color;
        }
    }
}
