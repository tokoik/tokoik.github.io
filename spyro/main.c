/*
 *   position() と言う関数を作成し，このプログラムとリンクする
 *
 *   % cc main.c <position()の入ったソースファイル> -lglut -lGLU -lGL ...
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

/*
 * t における位置 x, y を計算する関数
 */
extern void position(double, double []);

/* 回転軸 */
static GLdouble ax = 0.0, ay = 1.0, az = 0.0;

/* 回転角 */
static GLdouble angle = 0.0;

/* マウス移動量のスケール */
#define SCALE 360.0
static double sx, sy;

/* ドラッグ開始位置 */
static int cx, cy;

/* ドラッグ開始時の回転角 */
static double ca;

/*
 * glut を用いた表示プログラム
 * display() 内で trace() を呼び出している
 */
static void display(void)
{
  int i;

  glClear(GL_COLOR_BUFFER_BIT);
  glPushMatrix();
  glRotated(angle, ax, ay, az);

  glBegin(GL_LINE_LOOP);
  for (i = 0; i <= LOOPS; i++) {
    double t = 6.28318530717958647692 * (double)i / (double)LOOPS, p[3];

    glColor3d(cos(t) * 0.5 + 0.5, 0.0, (p[2] = sin(t)) * 0.5 + 0.5);
    position(t, p);
    glVertex3dv(p);
  }
  glEnd();

  glPopMatrix();
  glutSwapBuffers();
}

/*
 * resise() でウィンドウの幅と高さを得る
 * ウィンドウの座標系をビューポート（出力画像）と一致させる
 */
static void resize(int w, int h)
{
  /* マウスポインタ位置のウィンドウ内の相対的位置への換算用 */
  sx = 1.0 / (double)w;
  sy = 1.0 / (double)h;

  glViewport(0, 0, w, h);
  glLoadIdentity();
  glOrtho(-2.5, 2.5, -2.5, 2.5, -2.5, 2.5);
}

/*
 * 画面の再描画
 */
void idle(void)
{
  glutPostRedisplay();
}

/*
 * ドラッグ開始点の処理
 */
void mouse(int button, int state, int x, int y)
{
  switch (button) {
  case GLUT_LEFT_BUTTON:
    switch (state) {
    case GLUT_DOWN:
      /* アニメーション開始 */
      glutIdleFunc(idle);
      /* ドラッグ開始点を記録 */
      cx = x;
      cy = y;
      /* ドラッグ開始時の回転角を記録 */
      ca = angle;
      break;
    case GLUT_UP:
      /* アニメーション終了 */
      glutIdleFunc(0);
      break;
    default:
      break;
    }
    break;
  default:
    break;
  }
}

/*
 * ドラッグ位置から回転軸と回転角を算出する
 */
void motion(int x, int y)
{
  double dx, dy, a;

  /* マウスポインタの位置のドラッグ開始位置からの変位 */
  dx = (x - cx) * sx;
  dy = (y - cy) * sy;

  /* マウスポインタの位置のドラッグ開始位置からの距離 */
  a = sqrt(dx * dx + dy * dy);

  if (a != 0.0) {
    /* 距離を角度に換算してドラッグ開始時の回転角に加算 */
    angle = ca + SCALE * a;

    /* マウスの変位から回転軸ベクトルを求める */
    ax = dy / a;
    ay = dx / a;
    az = 0.0;
  }
}

/*
 * ESC キーで終了する
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
 * glut/OpenGL の初期化と実行
 */
int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow(argv[0]);
  glutReshapeFunc(resize);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);
  glutKeyboardFunc(keyboard);
  glutDisplayFunc(display);
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glutMainLoop();
  return 0;
}
