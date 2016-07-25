#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

/* アニメーションのサイクル */
#define CYCLE 36

/* 曲線の刻み */
#define STEP 100

/* 格子の分割数 */
#define DIVIDE 20

/* 円周率 */
#define PI 3.14159265358979323846264338327950288

/* 表示図形のディスプレイリスト番号 */
static GLuint wave, grid;

/* 視点の位置 */
static GLdouble ex = 0.0, ey = 0.0, ez = 20.0;

/* 目標点の位置 */
static GLdouble tx = 0.0, ty = 0.0, tz = 0.0;

/* ドラッグ開始位置 */
static int cx, cy;

/* マウスの絶対位置→ウィンドウ内での相対位置の換算係数 */
static double sx, sy;

/* マウスの相対位置→回転角の換算係数 */
#define SCALE (2.0 * 3.14159265358979323846)

/* 回転の初期値 (クォータニオン) */
static double cq[4] = { 1.0, 0.0, 0.0, 0.0 };

/* ドラッグ中の回転 (クォータニオン) */
static double tq[4];

/* 回転の変換行列 */
static double rt[16];

/*
** クォータニオンの積 r <- p x q
*/
static void qmul(double r[], const double p[], const double q[])
{
  r[0] = p[0] * q[0] - p[1] * q[1] - p[2] * q[2] - p[3] * q[3];
  r[1] = p[0] * q[1] + p[1] * q[0] + p[2] * q[3] - p[3] * q[2];
  r[2] = p[0] * q[2] - p[1] * q[3] + p[2] * q[0] + p[3] * q[1];
  r[3] = p[0] * q[3] + p[1] * q[2] - p[2] * q[1] + p[3] * q[0];
}

/*
** 回転の変換行列 r <- クォータニオン q
*/
static void qrot(double r[], double q[])
{
  double x2 = q[1] * q[1] * 2.0;
  double y2 = q[2] * q[2] * 2.0;
  double z2 = q[3] * q[3] * 2.0;
  double xy = q[1] * q[2] * 2.0;
  double yz = q[2] * q[3] * 2.0;
  double zx = q[3] * q[1] * 2.0;
  double xw = q[1] * q[0] * 2.0;
  double yw = q[2] * q[0] * 2.0;
  double zw = q[3] * q[0] * 2.0;
  
  r[ 0] = 1.0 - y2 - z2;
  r[ 1] = xy + zw;
  r[ 2] = zx - yw;
  r[ 4] = xy - zw;
  r[ 5] = 1.0 - z2 - x2;
  r[ 6] = yz + xw;
  r[ 8] = zx + yw;
  r[ 9] = yz - xw;
  r[10] = 1.0 - x2 - y2;
  r[ 3] = r[ 7] = r[11] = r[12] = r[13] = r[14] = 0.0;
  r[15] = 1.0;
}

static void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  /* モデルビュー変換行列の初期化 */
  glLoadIdentity();
  
  /* 視点の移動 */
  gluLookAt(ex, ey, ez, tx, ty, tz, 0.0, 1.0, 0.0);
    
  /* 回転 */
  glMultMatrixd(rt);
 
  static int frame = 0;
  double t = (double)frame / (double)CYCLE;
  if (++frame >= CYCLE) frame = 0;

  /* 偏光スクリーン (1) */
  glColor3d(0.0, 0.0, 0.0);
  glPushMatrix();
  glRotated(t * 360.0, 1.0, 0.0, 0.0);
  glTranslated(3.0, 0.0, 0.0);
  glCallList(grid);
  glPopMatrix();

  /* 目に届く光 */
  glColor3d(1.0, 0.0, 0.0);
  glPushMatrix();
  glTranslated(6.0, 0.0, 0.0);
  glScaled(1.0, abs(cos(2.0 * PI * t)), 1.0);
  glCallList(wave);
  glPopMatrix();

  /* 偏光 */
  glCallList(wave);

  /* 自然光の中の偏光成分 */
  glTranslated(-6.0, 0.0, 0.0);
  glCallList(wave);

  /* 偏光スクリーン (2) */
  glPushMatrix();
  glColor3d(0.0, 0.0, 0.0);
  glTranslated(3.0, 0.0, 0.0);
  glCallList(grid);
  glPopMatrix();

  /* 残りの自然光 */
  glColor3d(1.0, 0.6, 0.2);
  for (int i = 0; i < 11; ++i) {
    glRotated(30.0, 1.0, 0.0, 0.0);
    glCallList(wave);
  }

  glutSwapBuffers();
}

static void resize(int w, int h)
{
  /* マウスポインタ位置のウィンドウ内の相対的位置への換算用 */
  sx = 1.0 / (double)w;
  sy = 1.0 / (double)h;
  
  /* ウィンドウ全体をビューポートにする */
  glViewport(0, 0, w, h);
  
  /* 透視変換行列の指定 */
  glMatrixMode(GL_PROJECTION);
  
  /* 透視変換行列の初期化 */
  glLoadIdentity();
  gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);
  
  /* モデルビュー変換行列の指定 */
  glMatrixMode(GL_MODELVIEW);
}

static void idle(void)
{
  glutPostRedisplay();
}

static void mouse(int button, int state, int x, int y)
{
  switch (button) {
    case GLUT_LEFT_BUTTON:
      switch (state) {
        case GLUT_DOWN:
          /* ドラッグ開始点を記録 */
          cx = x;
          cy = y;
          break;
        case GLUT_UP:
          /* 回転の保存 */
          cq[0] = tq[0];
          cq[1] = tq[1];
          cq[2] = tq[2];
          cq[3] = tq[3];
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}

static void motion(int x, int y)
{
  double dx, dy, a;
  
  /* マウスポインタの位置のドラッグ開始位置からの変位 */
  dx = (x - cx) * sx;
  dy = (y - cy) * sy;
  
  /* マウスポインタの位置のドラッグ開始位置からの距離 */
  a = sqrt(dx * dx + dy * dy);
  
  if (a != 0.0) {
    /* マウスのドラッグに伴う回転のクォータニオン dq を求める */
    double ar = a * SCALE * 0.5;
    double as = sin(ar) / a;
    double dq[4] = { cos(ar), dy * as, dx * as, 0.0 };
    
    /* 回転の初期値 cq に dq を掛けて回転を合成 */
    qmul(tq, dq, cq);
    
    /* クォータニオンから回転の変換行列を求める */
    qrot(rt, tq);
  }
}

static void keyboard(unsigned char key, int x, int y)
{
  /* ESC をタイプしたら終了 */
  if (key == '\033') {
    exit(0);
  }
}

static void init(void)
{
  /* 背景色 */
  glClearColor(1.0, 1.0, 1.0, 1.0);

  /* 隠線消去を行う */
  glEnable(GL_DEPTH_TEST);

  /* 線のアンチエリアシングを行う */
  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_BLEND);
  
  /* 回転行列の初期化 */
  qrot(rt, cq);
}

static void scene(void)
{
  /* 波形の図形をディスプレイリストに登録 */
  wave = glGenLists(1);
  glNewList(wave, GL_COMPILE);
  
  glBegin(GL_LINE_STRIP);
  for (int i = 0; i <= STEP; ++i) {
    double t = 3.0 * (double)i / (double)STEP;
    double x = t * 2.0 - 3.0;
    double y = sin(2.0 * PI * t);
    
    glVertex3d(x, y, 0.0);
  }
  glEnd();

  glEndList();

  /* 偏光板の図形をディスプレイリストに登録 */
  grid = glGenLists(1);
  glNewList(grid, GL_COMPILE);
  
  glBegin(GL_LINES);
  for (int i = 0; i < DIVIDE; ++i) {
    double t = 2.0 * (double)(i + 1) / (double)DIVIDE - 1.0;
    double y = t * 1.5;

    glVertex3d(0.0, y, -1.5);
    glVertex3d(0.0, y,  1.5);
  }
  glEnd();

  glEndList();
}

int main(int argc, char *argv[])
{
  glutInitWindowSize(512, 256);
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);
  glutKeyboardFunc(keyboard);
  glutIdleFunc(idle);
  init();
  scene();
  glutMainLoop();
  return 0;
}
