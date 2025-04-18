#include <math.h>
#include <GL/glut.h>

/* 物体の色 */
GLfloat red[] = { 0.8, 0.2, 0.2, 1.0 };
GLfloat blue[] = { 0.2, 0.2, 0.8, 1.0 };
GLfloat yellow[] = { 0.8, 0.8, 0.2, 1.0 };

/* 光源の位置 */
GLfloat pos[] = { 3.0, 2.0, 5.0, 1.0 };

/* 視点の位置 */
GLdouble ex = 3.0, ey = 4.0, ez = 5.0;

/* 目標点の位置 */
GLdouble tx = 0.0, ty = 0.0, tz = 0.0;

/* 回転軸 */
GLdouble ax = 0.0, ay = 1.0;

/* 回転角 */
GLdouble angle = 0.0;

/* クリップ面 */
GLdouble clip[] = { 0.0, 0.0, -1.0, 0.0 };

/* 表示図形のディスプレイリスト番号 */
GLuint cube, dodeca, plane;

/* マウス移動量のスケール */
double sx, sy;
#define SCALE 360.0

/* ドラッグ開始位置 */
int cx, cy;

/* ドラッグ開始時の回転角 */
double ca;

void display(void)
{
  double dx = tx - ex, dy = ty - ey, dz = tz - ez;
  double d = sqrt(dx * dx + dy * dy + dz * dz);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  /* クリップ面の設定 */
  glLoadIdentity();
  glTranslated(0.0, 0.0, -d);
  glRotated(angle, ax, ay, 0.0);
  glClipPlane(GL_CLIP_PLANE0, clip);

  /* モデルビュー変換行列の初期化 */
  glLoadIdentity();

  /* 視点の移動 */
  gluLookAt(ex, ey, ez, tx, ty, tz, 0.0, 1.0, 0.0);

  /* 光源の位置を設定 */
  glLightfv(GL_LIGHT0, GL_POSITION, pos);

  /* ステンシルバッファの使用開始 */
  glEnable(GL_STENCIL_TEST);

  /* ステンシルバッファへ書きこむように設定 */
  glStencilFunc(GL_ALWAYS, 0x0, 0xffffffff);

  /* 外側のクリップされる１２面体を描画 */
  glEnable(GL_CLIP_PLANE0);
  glCallList(dodeca);
  glDisable(GL_CLIP_PLANE0);

  /* ステンシルを参照して描画するように設定 */
  glStencilFunc(GL_NOTEQUAL, 0x0, 0xffffffff);

  /* キャップをクリップ面と同様に回転して描画 ～ クリップ面
   の座標変換の結果を glGetFloatv(GL_MODELVIEW_MATRIX, ..) 
   して、それを glLoadMatrixf(..) してもいいと思うけど… */
  glPushMatrix();
  glLoadIdentity();
  glTranslated(0.0, 0.0, -d);
  glRotated(angle, ax, ay, 0.0);
  glCallList(plane);
  glPopMatrix();

  /* ステンシルバッファの使用終了 */
  glDisable(GL_STENCIL_TEST);

  /* 内側のクリップされない立方体を描画 */
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
  switch (key) {
  case '\033':
    /* ESC をタイプしたら終了 */
    exit(0);
  case 'x':
    ex += 0.5;
    break;
  case 'X':
    ex -= 0.5;
    break;
  case 'y':
    ey += 0.5;
    break;
  case 'Y':
    ey -= 0.5;
    break;
  case 'z':
    ez += 0.5;
    break;
  case 'Z':
    ez -= 0.5;
    break;
  default:
    break;
  }
  glutPostRedisplay();
}

void init(void)
{
  /* 初期設定 */
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  /* ステンシルバッファに書きこむたびにステンシルバッファのビットを反転 */
  glStencilOp(GL_INVERT, GL_INVERT, GL_INVERT);

  /* 図形が「閉じた立体」（かつ glCullFace() を使わない）な
     ら、画素のステンシルバッファへの書き込み回数は偶数回に
     なる。ところが、クリップされて物体に穴が開いてしまうと、
     その部分（そこからは裏側の面が見える）に対する書き込み
     回数は奇数回になる。したがって、ステンシルバッファの書
     き込みが行われる度にステンシルバッファのビットを反転す
     れば、奇数回書き込みが行われた部分、すなわち穴の部分の
     画素のステンシルバッファだけ値がセットされることになる。*/

}

void scene(void)
{
  /* 表示図形をディスプレイリストに登録 */
  int l = glGenLists(3);

  /* 内側の立方体 */
  cube = l;
  glNewList(cube, GL_COMPILE);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
  glutSolidCube(2.0);
  glEndList();

  /* 外側の１２面体 */
  dodeca = l + 1;
  glNewList(dodeca, GL_COMPILE);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blue);
  glutSolidDodecahedron();
  glEndList();

  /* クリップされた部分のキャップ */
  plane = l + 2;
  glNewList(plane, GL_COMPILE);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, yellow);
  glNormal3d(0.0, 0.0, 1.0);
  glBegin(GL_QUADS);
  glVertex3d(2.0, 2.0, 0.0);
  glVertex3d(-2.0, 2.0, 0.0);
  glVertex3d(-2.0, -2.0, 0.0);
  glVertex3d(2.0, -2.0, 0.0);
  glEnd();
  glEndList();
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);
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
