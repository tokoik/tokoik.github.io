#include <math.h>
#include <GL/glut.h>

/* 物体の色 */
GLfloat red[] = { 0.8, 0.2, 0.2, 1.0 };

/* 光源の位置 */
GLfloat pos[] = { 3.0, 4.0, 5.0, 1.0 };

/* 視点の位置 */
GLdouble ex = 0.0, ey = 0.0, ez = 10.0;

/* 目標点の位置 */
GLdouble tx = 0.0, ty = 0.0, tz = 0.0;

/* 回転軸 */
GLdouble ax = 0.0, ay = 1.0;

/* 回転角 */
GLdouble angle = 0.0;

/* 表示図形のディスプレイリスト番号 */
GLuint cube;

/* マウス移動量のスケール */
double sx, sy;
#define SCALE 360.0

/* ドラッグ開始位置 */
int cx, cy;

/* ドラッグ開始時の回転角 */
double ca;

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /* モデルビュー変換行列の初期化 */
  glLoadIdentity();

  /* 視点の移動 */
  gluLookAt(ex, ey, ez, tx, ty, tz, 0.0, 1.0, 0.0);

  /* 光源の位置を設定 */
  glLightfv(GL_LIGHT0, GL_POSITION, pos);

  /* 回転 */
  glRotated(angle, ax, ay, 0.0);

  /* 描画 */
  glCallList(cube);

  glutSwapBuffers();
}

void resize(int w, int h)
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

void idle(void)
{
  glutPostRedisplay();
}

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
    angle = fmod(ca + SCALE * a, 360.0);
    
    /* マウスの変位から回転軸ベクトルを求める */
    ax = dy / a;
    ay = dx / a;
  }
}

void keyboard(unsigned char key, int x, int y)
{
  /* ESC をタイプしたら終了 */
  if (key == '\033') {
    exit(0);
  }
}

void init(void)
{
  /* 初期設定 */
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
}

void scene(void)
{
  /* 表示図形をディスプレイリストに登録 */
  cube = glGenLists(1);

  /* 立方体 */
  glNewList(cube, GL_COMPILE);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
  glutSolidCube(2.0);
  glEndList();
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);
  glutKeyboardFunc(keyboard);
  init();
  scene();
  glutMainLoop();
  return 0;
}
