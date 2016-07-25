#include <GL/glut.h>
#include <stdio.h>

/*
 * エラーハンドラ
 */

static void errCallBack(GLenum errCode)
{
  const GLubyte *estring = gluErrorString(errCode);
  fprintf(stderr, "Quadric Error: %s\n", estring);
  exit(1);
}

/*
 * 円筒を描く
 *   radius: 半径
 *   hole: 穴の半径
 *   height: 高さ
 *   sides: 側面の数（数が多いほど滑らかになる）
 *
 */

void myPipe(double radius, double hole, double height, int sides)
{
  /* quadric object を一つ生成する */
  GLUquadricObj *quad = gluNewQuadric();

  /* 生成したオブジェクトに対するエラーハンドラを登録する */
  gluQuadricCallback(quad, GLU_ERROR, errCallBack);

  /* 面の塗り潰しを指定する（線画ではなく陰影をつけた円柱を描く）*/
  gluQuadricDrawStyle(quad, GLU_FILL);

  /* スムースシェーディングを行うよう設定する */
  gluQuadricNormals(quad, GLU_SMOOTH);

  /* 外側の側面を描く（stacks = 1）*/
  gluCylinder(quad, radius, radius, height, sides, 1);

  /* height の高さに上面を描く */
  glPushMatrix();
  glTranslated(0.0, 0.0, height);
  gluDisk(quad, hole, radius, sides, 1);
  glPopMatrix();

  /* 図形を裏返して描くように設定する */
  gluQuadricOrientation(quad, GLU_INSIDE);

  /* 内側を描く */
  gluCylinder(quad, hole, hole, height, sides, 1);

  /* 下面を描く */
  gluDisk(quad, hole, radius, sides, 1);

  /* 生成した quadlic object を削除する */
  gluDeleteQuadric(quad);
}
