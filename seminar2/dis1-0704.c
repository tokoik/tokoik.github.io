/* $Id$ */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LENGTH 5

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
  int m = 10; /* 配列 digit の要素数 */

  if (n > 10) n = 10;

  while (--n >= 0) *string++ = extractNumber(digit, &m);
  *string = '\0';
}

/*
** 二つの数字だけからなる文字列 s1 と s2 を比較する
*/
void compare(char *s1, char *s2, int *hit, int *blow)
{
  int i, digit[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

  *hit = *blow = 0;

  for (i = 0; s1[i] && s2[i]; i++) {
    if (s1[i] == s2[i])
      ++*hit;  /* 同じ桁に同じ数字があればヒット */
    else
      digit[s1[i] - '0'] = 1;  /* s1 に現れた数字を記録 */
  }

  for (i = 0; s2[i]; i++) {
    if (digit[s2[i] - '0'])
      ++*blow;  /* s2 に現れた数字が記録されていたらブロー */
  }
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

  /* 同じ長さの数字の列を二つ作る */
  makeNumber(number1, LENGTH);
  makeNumber(number2, LENGTH);

  /* 二つの数字の列を比較する */
  compare(number1, number2, &hit, &blow);

  printf("s1=%s, s2=%s -> *hit=%d, *blow=%d\n", number1, number2, hit, blow);

  return 0;
}
