#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

/* セレクションバッファのサイズ */
#define SELECTIONS 100

/* オブジェクトの数 */
#define NOBJECTS 5

/* ディスプレイリストの識別子 */
GLuint objects;

/* 各オブジェクトの色 */
GLfloat *color[NOBJECTS];

/* 色データ */
GLfloat gray[] = { 0.7, 0.7, 0.7 };
GLfloat blue[] = { 0.1, 0.1, 0.9 };

void display(void)
{
  int i;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

  /* 一旦シーンを描画する */
  for (i = 0; i < NOBJECTS; i++) {
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color[i]);
    glCallList(objects + i);
  }

  glFlush();
}

void mouse(int button, int state, int x, int y)
{
  static GLuint selection[SELECTIONS];  /* セレクションバッファ　　　　　 */
  static GLint hits = 0;                /* セレクトされたオブジェクトの数 */

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
      
      /* セレクションバッファの初期化，これはセレクションモー
         ドになってないと無視される */
      glInitNames();

      /* ネームスタックの先頭に仮の名前を詰めておく．ネーム
         スタック自体は複数のオブジェクトが選択できるように
         スタック構造になっているが，今回は１個のオブジェク
         トしか選択しないので，ネームスタックの先頭の要素だ
         けを取り替えながら描画すればよい．そこで，あらかじ
         めネームスタックの先頭に仮の名前 (-1) に詰めておい
         て，そこを使い回す． */
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
         イング変換やモデリング変換の設定をするのだが，直前
         に描画された図形に対してセレクションを行なうなら，
         その時に使ったモデルビューマトリクスがそのまま使え
         る（はず）．だから今は以下の処理 (#if 0 ～ #endif) 
         を省略しても大丈夫（だと思う）*/

#if 0
      /* モデルビュー変換行列の初期化 */
      glLoadIdentity();

      /* 視点の設定 */
      gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
#endif

      /* もう一度シーンを描画する */
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
	  color[*(ptr++)] = blue; /* オブジェクトの色を青にする */
	}
      }
    }
    else {
      GLuint *ptr = selection;
      int i;

      /* selection[] の内容はマウスの左ボタンをクリックした
         時にしか変更されないはずだから，まだ残っているはず */
      for (i = 0; i < hits; i++) {
	unsigned int j, n = ptr[0];
	
	ptr += 3;
	for (j = 0; j < n; j++) {
	  color[*(ptr++)] = gray;
	}
      }
    }

    /* 画面を書き換えてみる */
    glutPostRedisplay();
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

  /* 各オブジェクトの色を初期化 */
  for (i = 0; i < NOBJECTS; i++) {
    color[i] = gray;
  }
}

void scene(void)
{
  const GLdouble width = 4.0;
  const GLdouble center = width / 2.0;
  const GLdouble step = width / (NOBJECTS - 1);
  int i;

  /* セレクションの対象になるオブジェクトを生成して，ディス
     プレイリストを作っておく*/
  for (i = 0; i < NOBJECTS; i++) {

    /* 図形をディスプレイリストに登録 */
    glNewList(objects + i, GL_COMPILE);

    /* 球を描く */
    glPushMatrix();
    glTranslated((double)i * step - center, ((i & 1) * 2 - 1) * step, 0.0);
    glutSolidSphere(0.5, 10, 5);
    glPopMatrix();

    glEndList();
  }
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutMouseFunc(mouse);
  glutReshapeFunc(resize);
  glutKeyboardFunc(keyboard);
  init();
  scene();
  glutMainLoop();
  return 0;
}
