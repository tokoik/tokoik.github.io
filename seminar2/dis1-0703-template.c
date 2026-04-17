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
  /* 問題7-1で実装したものを用いる */
}

/*
** 配列 table の中からランダムに一つ数値を取り出し，そこを詰める
*/
int extractNumber(int table[], int *size)
{
  /* 問題7-2で実装したものを用いる */
}

/*
** 同じ数字を２回以上含まない n 桁 (n <= 10) の数字の列を発生する
*/
void makeNumber(char *string, int n)
{
  /* ここを実装する */
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
