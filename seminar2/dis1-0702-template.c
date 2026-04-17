/* $Id$ */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 19

/*
** [0, max] の間の正の整数の乱数を発生する
*/
int makeRandom(int max)
{
  /* 問題7-1で実装したものを用いる */
}

/*
** 配列の中からランダムに数値を取り出し，そこを詰める
*/
int extractNumber(int table[], int *size)
{
  /* ここを実装する */
}

int main()
{
  int i;
  time_t t;
  int table[MAX + 1], n = MAX + 1;

  /* t に現在時刻を得る */
  t = time(0);

  /* 現在時刻を種に使って新しい疑似乱数の系列を設定する */
  srand(t);

  /* 配列 table に出力する数値を入れておく */
  for (i = 0; i <= MAX; i++) {
    table[i] = i;
  }

  while (n > 0) {
    int s;

    /* 配列 table の中から数値を一つ取り出す */
    s = extractNumber(table, &n);
    printf("%d\n", s);
  }

  return 0;
}
