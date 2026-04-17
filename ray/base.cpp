/*
** GLUT を使った Ray Tracing のベースプログラム
**   ・render() と言う関数を point() を使って作成し，
**   　それをこのプログラムとリンクする
**
**   % c++ base.cpp <render()の入ったソースファイル> -lglut -lGLU -lGL ...
*/

#include <stdlib.h>
#include <GL/glut.h>

#define WIDTH  640	/* 最初に開くウィンドウの幅　 */
#define HEIGHT 480	/* 最初に開くウィンドウの高さ */

static int xw, yw;	/* 開いたウィンドウのサイズ　 */

/*
** Ray Tracing の本体
** 外部プログラムとして定義する
*/
extern void render(int, int);

/*
** (x, y) に色 c を設定する関数
** render() の中で使用する
*/
void point(int x, int y, const float *c)
{
  glColor3fv(c);
  glVertex2i(x, y);
}

/*
** glut を用いた表示プログラム
** display() 内で render() を呼び出している
*/
static void display(void)
{
  glBegin(GL_POINTS);
  render(xw, yw);
  glEnd();
  glFlush();
}

/*
** resise() でウィンドウの幅と高さを得る
** ウィンドウの座標系をビューポート（出力画像）と一致させる
*/
static void resize(int w, int h)
{
  glViewport(0, 0, xw = w, yw = h);
  glLoadIdentity();
  glOrtho(-0.5, (GLdouble)w - 0.5, (GLdouble)h - 0.5, -0.5, -1.0, 1.0);
}

/*
** ESC, q, Q キーで終了する
*/
static void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
  case '\033':
  case 'q':
  case 'Q':
    exit(0);
  default:
    break;
  }
}

/*
** glut/OpenGL の初期化と実行
*/
int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow(argv[0]);
  glutKeyboardFunc(keyboard);
  glutReshapeFunc(resize);
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}
