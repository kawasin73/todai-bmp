//  Copied from http://hooktail.org/computer/index.php?Bitmap%A5%D5%A5%A1%A5%A4%A5%EB%A4%F2%C6%FE%BD%D0%CE%CF%A4%B7%A4%C6%A4%DF%A4%EB
#include"bitmap.h"
#include<stdlib.h>
#include<stdio.h>

int main(int argc, char *argv[])
{
    if(argc != 3){
        fprintf(stderr, "Usage: program <inputfile> <outputfile>\n");
        exit(1);
    }

    Image *colorimg;

    if((colorimg = Read_Bmp(argv[1])) == NULL){
        exit(1);
    }

    if(Write_Bmp(argv[2], colorimg)){
        exit(1);
    }

    Free_Image(colorimg);

    return 0;
}


