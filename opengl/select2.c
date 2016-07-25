#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

/* セレクションバッファのサイズ */
#define SELECTIONS 100

/* オブジェクトの数 */
#define NOBJECTS 5

/* ディスプレイリストの識別子 */
GLuint objects;

/* オブジェクトの色 */
static GLfloat color[][3] = {
  { 0.1, 0.1, 0.9 },
  { 0.1, 0.9, 0.1 },
  { 0.9, 0.1, 0.1 },
  { 0.1, 0.9, 0.9 },
  { 0.9, 0.1, 0.9 },
  { 0.9, 0.9, 0.1 },
};

/* オブジェクトの配置 */
#define ARRANGEWIDTH	4.0
#define ARRANGECENTER	(ARRANGEWIDTH / 2.0)
#define ARRANGESTEP	(ARRANGEWIDTH / (NOBJECTS - 1))
#define ARRANGEDEPTH	0.0
#define INITIALHEIGHT	0.0
#define INITIALVELOCITY	2.0
#define GRAVITY		-1.0
#define REFRESHRATE	0.01 /* 100Hz */
unsigned long touchtime[NOBJECTS];

/* 光源の位置 */
GLfloat light0pos[] = { 4.0, 8.0, 6.0, 1.0 };

/* カレントフレーム番号 */
unsigned long cframe = 0;

void display(void)
{
  int i;

  /* 時間を計るためにカレントフレーム番号のカウントしておく */
  ++cframe;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  gluLookAt(5.0, 4.0, 5.0, 0.4, 0.0, 0.0, 0.0, 1.0, 0.0);
  glLightfv(GL_LIGHT0, GL_POSITION, light0pos);

  /* シーンの描画 */
  for (i = 0; i < NOBJECTS; i++) {

    /* 各オブジェクトの垂直位置を初期位置に設定する */
    GLdouble h = INITIALHEIGHT;

    /* クリックされた時間が設定されていたら動き出す */
    if (touchtime[i] > 0) {
      double t;

      /* 経過フレーム数から時間を計算（てきとー）*/
      t = (cframe - touchtime[i]) * REFRESHRATE;

      /* 高さの計算（中学か高校の物理で習ったよね）*/
      h += (GRAVITY * t * 0.5 + INITIALVELOCITY) * t;

      /* 地面に落下したら動きを止めるのだ */
      if (h < 0.0) {
	h = INITIALHEIGHT;
	touchtime[i] = 0;
      }
    }

    /* とりあえず色を設定．色はセレクションには関係ないので、
       ディスプレイリストには入れないことにする */
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color[i % 6]);

    /* セレクションのために同じシーンをもう一度描画する必要
       があるので、オブジェクトをディスプレイリストに入れて
       しまう。ただし、ディスプレイリストを削除せずに使い回
       しているので、メモリリークしそうな気がしてちょいと不
       安 */
    glNewList(objects + i, GL_COMPILE_AND_EXECUTE);

    /* 図形の描画 */
    glPushMatrix();
    glTranslated((double)i * ARRANGESTEP - ARRANGECENTER, h, ARRANGEDEPTH);
    glutSolidCube(0.8);
    glPopMatrix();

    glEndList();

  }
  glutSwapBuffers();
}

void mouse(int button, int state, int x, int y)
{
  GLuint selection[SELECTIONS];  /* セレクションバッファ　　　　　 */
  GLint hits = 0;                /* セレクトされたオブジェクトの数 */

  switch (button) {
  case GLUT_LEFT_BUTTON:
    if (state == GLUT_DOWN) {
      GLuint *ptr;
      GLint vp[4];
      int i;

      /* セレクションに使うバッファの設定．これはセレクショ
         ンモード以外の時（glRenderMode(GL_SELECT) より前）
         に実行する必要がある．セレクションバッファには，入
         るだけのデータが詰め込まれる */
      glSelectBuffer(SELECTIONS, selection);

      /* レンダリングモードをセレクションモードに切替える */
      glRenderMode(GL_SELECT);
      
      /* セレクションバッファを初期化する．これはセレクショ
         ンモードになってないと無視される */
      glInitNames();

      /* ネームスタックの先頭に仮の名前を詰める．ネームスタッ
       * ク自体は複数のオブジェクトが選択できるようにスタッ
       * ク構造になっているが，今回は１個のオブジェクトしか
       * 選択しないので，ネームスタックの先頭の要素だけを取
       * り替えながら描画すればよい．そこで，あらかじめネー
       * ムスタックの先頭に仮の名前 (-1) に詰めておいて，そ
       * こを使い回す． */
      glPushName(-1);

      /* セレクションの処理は視点座標系で行う */
      glMatrixMode(GL_PROJECTION);

      /* 現在の透視変換マトリクスを保存する */
      glPushMatrix();

      /* 透視変換マトリクスを初期化する */
      glLoadIdentity();

      /* 現在のビューポート設定を得る */
      glGetIntegerv(GL_VIEWPORT, vp);

      /* 表示領域がマウスポインタの周囲だけになるように変換
         行列を設定する．マウスの座標系は，スクリーンの座標
         系に対して上下が反転しているので，それを補正する */
      gluPickMatrix(x, vp[3] - y - 1, 1, 1, vp);

      /* 通常の描画と同じ透視変換マトリクスを設定する．ウィ
         ンドウ全体をビューポートにしているので，アスペクト
         比は vp[2] / vp[3] で得られる．*/
      gluPerspective(30.0, (double)vp[2] / (double)vp[3], 1.0, 100.0);

      /* モデルビューマトリクスに切替える */
      glMatrixMode(GL_MODELVIEW);

      /* ここで一旦モデルビューマトリクスに切替えて，ビュー
       * イング変換やモデリング変換の設定をするのだが，直前
       * に描画された図形に対してセレクションを行なうなら，
       * その時に使ったモデルビューマトリクスがそのまま使え
       * る（はず）．だから今は以下の処理 (#if 0 ～ #endif) 
       * を省略しても大丈夫（だと思う）*/

#if 0
      /* モデルビュー変換行列の初期化 */
      glLoadIdentity();

      /* 視点の設定 */
      gluLookAt(5.0, 4.0, 5.0, 0.4, 0.0, 0.0, 0.0, 1.0, 0.0);
#endif

      /* もう一度シーンを描画 */
      for (i = 0; i < NOBJECTS; i++) {
	/* ネームスタックの先頭にこれから描くオブジェクトの
           番号を設定する */
	glLoadName(i);
	/* オブジェクトを描画する（画面には表示されない）*/
	glCallList(objects + i);
      }

      /* 再び透視変換マトリクスに切替える */
      glMatrixMode(GL_PROJECTION);

      /* 透視変換マトリクスを元に戻す */
      glPopMatrix();

      /* モデルビューマトリクスに戻す */
      glMatrixMode(GL_MODELVIEW);

      /* レンダリングモードを元に戻す */
      hits = glRenderMode(GL_RENDER);

      /* セレクションバッファにはいくつのデータが入っている
         のかわからないので，とりあえず先頭のポインタを取り
         出しておく */
      ptr = selection;

      /* hits にはセレクションバッファに格納されたデータの数
         が入る．データがセレクションバッファに入り切らなけ
         れば hits < 0 となる */
      for (i = 0; i < hits; i++) {
	/* セレクションバッファの先頭の要素は、選択されたオ
           ブジェクトの数 */
	unsigned int j, n = ptr[0];

	/* 続く２つの要素は、選択された位置に置ける奥行き値
           の最小値と最大値を符号なし整数で表したもの */
	double near = (double)ptr[1] / (double)0x7fffffff;
	double far  = (double)ptr[2] / (double)0x7fffffff;

	/* セレクションバッファの４つ目の要素（添字＝３）か
           ら選択されたオブジェクトの番号が入っている */
	ptr += 3;
	for (j = 0; j < n; j++) {
	  /* オブジェクトにクリックされた時間を設定する */
	  touchtime[*(ptr++)] = cframe;
	}
      }
    }
    break;
  case GLUT_MIDDLE_BUTTON:
    break;
  case GLUT_RIGHT_BUTTON:
    break;
  default:
    break;
  }
}

void resize(int w, int h)
{
  /* ウィンドウ全体をビューポートにする */
  glViewport(0, 0, w, h);

  /* 透視変換行列を設定する */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);

  /* モデルビュー変換行列を指定しておく */
  glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
  case 'q':
  case 'Q':
  case '\033':
    exit(0);  /* '\033' は ESC の ASCII コード */
  default:
    break;
  }
}

void init(void)
{
  int i;

  /* 初期設定 */
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);

  /* 各オブジェクトのディスプレイリストを作る */
  objects = glGenLists(NOBJECTS);
  if (objects <= 0) {
    fprintf(stderr, "Can't create so many objects: %d.\n", NOBJECTS);
    exit(1);
  }

  /* 各オブジェクトをクリックしたフレーム番号を初期化 */
  for (i = 0; i < NOBJECTS; i++) {
    touchtime[i] = 0;
  }
}

void idle(void)
{
  glutPostRedisplay();
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutMouseFunc(mouse);
  glutReshapeFunc(resize);
  glutKeyboardFunc(keyboard);
  glutIdleFunc(idle);
  init();
  glutMainLoop();
  return 0;
}
