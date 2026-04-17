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
** 二つの数字の列を比較する
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

/*
** キーボードから数字の列を入力する
*/
int getNumber(char string[], int length)
{
  int i = 0, digit[10];

  for (;;) {
    int c;

    if (i < 0) {

      /* \n まで読み飛ばす */
      do
	if ((c = getchar()) == EOF) return 1;
      while (c != '\n');
      i = 0;
    }

    if (i == 0) {
      int j;

      /* 使った数字を記録する配列を初期化 */
      for (j = 0; j < 10; j++) digit[j] = 0;
    }

    if ((c = getchar()) == EOF)
      return 1;
    if (c == '\n') {
      if (i == length) {
	string[i] = '\0';
	return 0;
      }
      printf("数字が短過ぎます．%d 文字入れて下さい．\n", length);
      i = 0;
    }
    else if (i >= length) {
      printf("数字が長過ぎます．%d 文字入れて下さい．\n", length);
      i = -1;
    }
    else if (!isdigit(c)) {
      printf("%c は数字ではありません．\n", c);
      i = -1;
    }
    else if (digit[c - '0']) {
      printf("同じ数字は２回以上使えません．\n");
      i = -1;
    }
    else {
      digit[c - '0'] = 1;
      string[i++] = c;
    }
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
