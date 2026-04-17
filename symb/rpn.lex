%{
#define SIZE 100  /* スタックのサイズ */
int st[SIZE];     /* スタック         */
int sp = 0;       /* スタックポインタ */
extern void push(int), operator(char), print(void), reset(void);
%}

%%
[0-9]+	push(atoi(yytext));
[-+*/]	operator(*yytext);
p	print();
r	reset();
.|\n	;
%%

/*
 * x をスタックに入れる
 */
void push(int x)
{
  if (sp >= SIZE) {
    fprintf(stderr, "stack overflow\n");
    exit(1);
  }
  st[sp++] = x;
}

/*
 * スタックトップの値を取り出す
 */
int pop(void)
{
  if (sp <= 0) {
    fprintf(stderr, "stack underflow\n");
    exit(1);
  }
  return st[--sp];
}

/*
 * 演算子の処理
 */
void operator(char op)
{
  int x, y, z;

  y = pop();
  x = pop();

  switch(op) {
  case '+':
    z = x + y;
    break;
  case '-':
    z = x - y;
    break;
  case '*':
    z = x * y;
    break;
  case '/':
    if (y == 0) {
      fprintf(stderr, "division by zero\n");
      exit(1);
    }
    z = x / y;
    break;
  }
  push(z);
}

/*
 * スタックトップの値を表示
 */
void print(void)
{
  if (sp > 0)
    fprintf(yyout, "%d\n", st[sp - 1]);
  else
    fprintf(stderr, "stack is empty\n");
}

/*
 * スタックをリセット
 */
void reset(void)
{
  sp = 0;
}
