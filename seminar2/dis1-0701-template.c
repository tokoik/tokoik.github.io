/* $Id$ */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 9

#define LOOPS 10000000

/*
** [0, max] の間の正の整数の乱数を発生する
*/
int makeRandom(int max)
{
  /* ここを実装する */
}

int main()
{
  int i;
  time_t t;
  static int hist[MAX + 1];

  /* t に現在時刻を得る */
  t = time(0);

  /* 現在時刻を種に使って新しい疑似乱数の系列を設定する */
  srand(t);

  for (i = 0; i < LOOPS; i++) {
    int r;

    /* 0～9の乱数を得る */
    r = makeRandom(MAX);

    /* その乱数の発生頻度を数える */
    hist[r]++;
  }

  for (i = 0; i <= MAX; i++) {

    /* 各乱数の発生頻度の割合を表示する */
    printf("%3d:%6.2f%%\n", i, (double)hist[i] * 100.0 / (double)LOOPS);
  }

  return 0;
}
