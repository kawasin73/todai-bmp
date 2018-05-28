#include "bitmap.h"
#include "sobel.h"
#include <stdlib.h>
#include <stdio.h>

void Binarization(Image *img);

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: program <inputfile> <outputfile>\n");
        exit(1);
    }

    Image *colorimg;
    double *tmpMap;

    if ((colorimg = Read_Bmp(argv[1])) == NULL)
    {
        exit(1);
    }

    if ((tmpMap = (double *)malloc(sizeof(double) * colorimg->height * colorimg->width)) == NULL)
    {
        fprintf(stderr, "Allocation error\n");
        exit(1);
    }

    Sobel(colorimg, tmpMap);
    Binarization(colorimg);

    if (Write_Bmp(argv[2], colorimg))
    {
        exit(1);
    }

    free(tmpMap);
    Free_Image(colorimg);

    return 0;
}

unsigned char conv(unsigned char v)
{
    if (v < 50)
        return 0;
    else
        return 255;
}

void Binarization(Image *img)
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
