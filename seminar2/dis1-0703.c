/* $Id$ */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LENGTH 10

/*
** [0, max] の間の正の整数の乱数を発生する
*/
int makeRandom(int max)
{
  return (max + 1.0) * rand() / (RAND_MAX + 1.0);
}

/*
** 配列 table の中からランダムに一つ数値を取り出し，そこを詰める
*/
int extractNumber(int table[], int *size)
{
  if (--*size > 0) {
    int r = makeRandom(*size);
    int x = table[r];

    /* r 番目以降を一つずつ詰める */
    for (; r < *size; r++) table[r] = table[r + 1];

    return x;
  }
  else
    return table[0];
}

/*
** 同じ数字を２回以上含まない n 桁 (n <= 10) の数字の列を発生する
*/
void makeNumber(char *string, int n)
{
  int digit[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
  int m = 10;

  if (n > 10) n = 10;

  while (--n >= 0) *string++ = extractNumber(digit, &m);
  *string = '\0';
}

int main()
{
  time_t t;
  char number[LENGTH + 1];

  /* t に現在時刻を得る */
  t = time(0);

  /* 現在時刻を種に使って新しい疑似乱数の系列を設定する */
  srand(t);

  /* 数字の列を作る */
  makeNumber(number, LENGTH);

  printf("%s\n", number);

  return 0;
}
