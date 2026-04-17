/*
** BMP ファイルを作成する Ray Tracing のベースプログラム
**   ・render() と言う関数を point() を使って作成し，
**   　それをこのプログラムとリンクする
**
** 注：IRIX と Linux でしか試していない
** 　　（Windows では正常に動かない）
**
**   % cc bmp.c <render()の入ったソースファイル>
*/

#include <stdio.h>
#include <stdlib.h>

/* BMP/DIB ファイルのヘッダ定義 */
static struct biHeader {
  unsigned char bfType[2];
  unsigned char bfSize[4];
  unsigned char bfReserved1[2];
  unsigned char bfReserved2[2];
  unsigned char bfOffBits[4];
  unsigned char biSize[4];
  unsigned char biWidth[4];
  unsigned char biHeight[4];
  unsigned char biPlanes[2];
  unsigned char biBitCount[2];
  unsigned char biCompression[4];
  unsigned char biSizeImage[4];
  unsigned char biXPelsPerMeter[4];
  unsigned char biYPelsPerMeter[4];
  unsigned char biClrUsed[4];
  unsigned char biClrImportant[4];
} header;

/* 画像を格納するメモリの先頭ポインタと大きさ */
static unsigned char *image;
static int size;

/* デフォルトの出力ファイル名 */
static char filename[] = "outfile.bmp";

/* デフォルトの出力サイズ */
static int xw = 640, yw = 480;

/* 画像解像度 2835 pixel/meter ≒ 72dpi */
#define XRESOLUTION 2835
#define YRESOLUTION 2835

/*
** Ray Tracing の本体
** 外部プログラムとして定義する
*/
extern void render(int, int);

/*
** (x, y) に色 c を設定する関数
** render() の中で使用する
** 色は 0 ～ 1 に収める
*/
void point(int x, int y, const float *c)
{
  int offset = (y * xw + x) * 3;

  image[offset + 0] =
    (c[2] <= 0.0) ? 0 : ((c[2] >= 1.0) ? 255 : (unsigned char)(c[2] * 255.0));
  image[offset + 1] =
    (c[1] <= 0.0) ? 0 : ((c[1] >= 1.0) ? 255 : (unsigned char)(c[1] * 255.0));
  image[offset + 2] =
    (c[0] <= 0.0) ? 0 : ((c[0] >= 1.0) ? 255 : (unsigned char)(c[0] * 255.0));
}

/*
** メインプログラム
*/
int main(void)
{
  FILE *fp;
  int status = 0;

  image = malloc(size = xw * yw * 3);
  if (image == 0) {
    fprintf(stderr, "Can't allocate memory.\n");
    status = 1;
  }
  else {
    render(xw, yw);

    fp = fopen(filename, "wb");
    if (fp == 0) {
      fprintf(stderr, "Can't open file %s,\n", filename);
      status = 1;
    }
    else {
      long temp;

/*
** BMP は Little Endian なので
** 使用マシンの Endian に依存しないように
** 1 byte ずつ設定する
*/

      header.bfType[0] = 'B';
      header.bfType[1] = 'M';

      temp = size + 54;
      header.bfSize[0] = (unsigned char)(temp & 0xff);
      temp >>= 8;
      header.bfSize[1] = (unsigned char)(temp & 0xff);
      temp >>= 8;
      header.bfSize[2] = (unsigned char)(temp & 0xff);
      temp >>= 8;
      header.bfSize[3] = (unsigned char)(temp & 0xff);

      header.bfReserved1[0] = 0;
      header.bfReserved1[1] = 0;
      header.bfReserved2[0] = 0;
      header.bfReserved2[1] = 0;

      header.bfOffBits[0] = 54;
      header.bfOffBits[1] = 0;
      header.bfOffBits[2] = 0;
      header.bfOffBits[3] = 0;

      header.biSize[0] = 40;
      header.biSize[1] = 0;
      header.biSize[2] = 0;
      header.biSize[3] = 0;

      temp = xw;
      header.biWidth[0] = (unsigned char)(temp & 0xff);
      temp >>= 8;
      header.biWidth[1] = (unsigned char)(temp & 0xff);
      temp >>= 8;
      header.biWidth[2] = (unsigned char)(temp & 0xff);
      temp >>= 8;
      header.biWidth[3] = (unsigned char)(temp & 0xff);

      temp = yw;
      header.biHeight[0] = (unsigned char)(temp & 0xff);
      temp >>= 8;
      header.biHeight[1] = (unsigned char)(temp & 0xff);
      temp >>= 8;
      header.biHeight[2] = (unsigned char)(temp & 0xff);
      temp >>= 8;
      header.biHeight[3] = (unsigned char)(temp & 0xff);

      header.biPlanes[0] = 1;
      header.biPlanes[1] = 0;

      header.biBitCount[0] = 24;
      header.biBitCount[1] = 0;

      header.biCompression[0] = 0;
      header.biCompression[1] = 0;
      header.biCompression[2] = 0;
      header.biCompression[3] = 0;

      temp = size;
      header.biSizeImage[0] = (unsigned char)(temp & 0xff);
      temp >>= 8;
      header.biSizeImage[1] = (unsigned char)(temp & 0xff);
      temp >>= 8;
      header.biSizeImage[2] = (unsigned char)(temp & 0xff);
      temp >>= 8;
      header.biSizeImage[3] = (unsigned char)(temp & 0xff);

      temp = XRESOLUTION;
      header.biXPelsPerMeter[0] = (unsigned char)(temp & 0xff);
      temp >>= 8;
      header.biXPelsPerMeter[1] = (unsigned char)(temp & 0xff);
      temp >>= 8;
      header.biXPelsPerMeter[2] = (unsigned char)(temp & 0xff);
      temp >>= 8;
      header.biXPelsPerMeter[3] = (unsigned char)(temp & 0xff);

      temp = YRESOLUTION;
      header.biYPelsPerMeter[0] = (unsigned char)(temp & 0xff);
      temp >>= 8;
      header.biYPelsPerMeter[1] = (unsigned char)(temp & 0xff);
      temp >>= 8;
      header.biYPelsPerMeter[2] = (unsigned char)(temp & 0xff);
      temp >>= 8;
      header.biYPelsPerMeter[3] = (unsigned char)(temp & 0xff);

      header.biClrUsed[0] = 0;
      header.biClrUsed[1] = 0;
      header.biClrUsed[2] = 0;
      header.biClrUsed[3] = 0;

      header.biClrImportant[0] = 0;
      header.biClrImportant[1] = 0;
      header.biClrImportant[2] = 0;
      header.biClrImportant[3] = 0;

      fwrite(&header, sizeof header, 1, fp);
      fwrite(image, size, 1, fp);
      
      fclose(fp);
    }
  }

  return status;
}
