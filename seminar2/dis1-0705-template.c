/* $Id$ */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define LENGTH 3

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
  /* 問題7-3で実装したものを用いる */
}

/*
** 二つの数字の列を比較する
*/
void compare(char *s1, char *s2, int *hit, int *blow)
{
  /* 問題7-4で実装したものを用いる */
}

/*
** キーボードから数字の列を入力する
*/
int getNumber(char string[], int length)
{
  /* ここを実装する */
}

int main()
{
  int i;
  time_t t;
  char number1[LENGTH + 1], number2[LENGTH + 1];
  int hit, blow;

  /* t に現在時刻を得る */
  t = time(0);

  /* 現在時刻を種に使って新しい疑似乱数の系列を設定する */
  srand(t);

  /* 数字の列を作る */
  makeNumber(number1, LENGTH);

  printf("私が考えている %d 桁の数字を当てて下さい．\n", LENGTH);

  for (;;) {
    
    /* 数字の列を入力する */
    if (getNumber(number2, LENGTH)) {
      printf("正解は %s でした\n", number1);
      exit(0);
    }
  
    /* 二つの数字の列を比較する */
    compare(number1, number2, &hit, &blow);
    
    if (hit < LENGTH)
      printf("hit=%d, blow=%d\n", hit, blow);
    else {
      printf("正解！\n");
      break;
    }
  }

  return 0;
}
