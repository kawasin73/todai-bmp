# 課題2レポート

この課題のソースコードは[https://github.com/kawasin73/todai-bmp](https://github.com/kawasin73/todai-bmp)にアップロードしています。

以下の2つのソースコードは、[物理のかぎしっぽ](http://hooktail.org/computer/index.php?Bitmap%A5%D5%A5%A1%A5%A4%A5%EB%A4%F2%C6%FE%BD%D0%CE%CF%A4%B7%A4%C6%A4%DF%A4%EB)から引用しました。

- `bitmap.h`
- `bitmap.c`

`bitmap.h`と`bitmap.c` は、以下の機能を提供しています。

- Bitmap画像ファイルの読み込み(`Read_Bmp`)
- Bitmap画像のファイルへの書き込み(`Write_Bmp`)
- Bitmap画像を表す`Image`構造体の定義

このソースコードはダウンロードしたものをそのまま利用しているため解説は省略します。

## ソースコード

勾配画像の書き出しは以下の`sobel.c` と `sobel-binary.c`のソースコードで実現します。

`sobel.c` については、課題１で解説しているため省略します。

### sobel-binary.c

```c:sobel-binary.c
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

```

`void Binarization(Image *img)` で、2値化しています。最初は、`127` を基準にして2値化していましたが、我が家の玄関のエッジがうまく現れなかったため、`50`を基準値にしています。

グレースケールの値は、勾配画像の計算ですでに算出され、R,G,B に同じ値が設定されているため、そのうちの1つをグレースケールの値として使えばよかったのですが、`Binarization`関数に汎用性を持たせるために、あえて`img->data[index].r * 0.299 + img->data[index].g * 0.587 + img->data[index].b * 0.114`を使っています。

### 結果

元画像はこれです。

![元画像](./sample.bmp)

変換されたエッジの画像はこれです。

![エッジ画像](./edge.bmp)
