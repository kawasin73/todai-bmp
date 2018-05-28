#include "bitmap.h"
#include "sobel.h"
#include <stdlib.h>
#include <stdio.h>

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

    if (Write_Bmp(argv[2], colorimg))
    {
        exit(1);
    }

    free(tmpMap);
    Free_Image(colorimg);

    return 0;
}
