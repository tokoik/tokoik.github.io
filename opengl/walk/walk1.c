/*
 * gluLookAt() で視差を与えた立体視のサンプル
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#define PARALLAX 0.1
#define DISTANCE -4.0
#define VIEWANGLE 60.0

int cx, cy;
double speed, angle;
double ex = 0.0, ez = 0.0; 
double r = 0.0; 

GLfloat light0pos[] = { 0.0, 3.0, 5.0, 0.0 };

GLfloat red[] = { 0.8, 0.2, 0.2, 1.0 };
GLfloat blue[] = { 0.2, 0.2, 0.8, 1.0 };
GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat gray[] = { 0.3, 0.3, 0.3, 1.0 };
GLfloat green[] = { 0.3, 0.6, 0.2, 1.0 };

GLfloat line[][3] = {
  { -1.3, -1.0, -100.0 },
  { -1.5, -1.0, -100.0 },
  { -1.5, -1.0,  100.0 },
  { -1.3, -1.0,  100.0 },
  {  1.5, -1.0, -100.0 },
  {  1.3, -1.0, -100.0 },
  {  1.3, -1.0,  100.0 },
  {  1.5, -1.0,  100.0 }
};

GLfloat base[][3] = {
  { -100.0, -1.0, -100.0 },
  { -100.0, -1.0,  100.0 },
  {  100.0, -1.0,  100.0 },
  {  100.0, -1.0, -100.0 }
};

GLfloat normal[] = {
  0.0, 1.0, 0.0
};

#ifdef MULTI
double panangle;
GLint scrWidth, scrHeight;
#endif

void display(void)
{
  ex += speed * sin(-r * 3.1415926536 / 180.0);
  ez += speed * cos(-r * 3.1415926536 / 180.0);
  if (ez > 10.0)
    ez -= 10.0;
  else if (ez < -10.0)
    ez += 10.0;
  r += angle;
  
#ifdef STEREO
#ifdef CRM
  glDrawBuffer(GL_BACK_RIGHT);
#ifdef MULTI
  glViewport(scrWidth, 0, scrWidth, scrHeight);
#endif
#else
  glViewport(0, 0, 1280, 492);
#endif
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  gluLookAt(PARALLAX, 0.0, 0.0, 0.0, 0.0, DISTANCE, 0.0, 1.0, 0.0);
  glRotated(r, 0.0, 1.0, 0.0);
  glTranslated(ex, 0.0, ez);
  glCallList(1);
#ifdef CRM
  glDrawBuffer(GL_BACK_LEFT);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#else
  glViewport(0, 532, 1280, 492);
#endif
  glLoadIdentity();
  gluLookAt(-PARALLAX, 0.0, 0.0, 0.0, 0.0, DISTANCE, 0.0, 1.0, 0.0);
  glRotated(r, 0.0, 1.0, 0.0);
  glTranslated(ex, 0.0, ez);
  glCallList(1);
#else
#ifdef MULTI
  glViewport(scrWidth, 0, scrWidth, scrHeight);
#endif
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glRotated(r, 0.0, 1.0, 0.0);
  glTranslated(ex, 0.0, ez);
  glCallList(1);
#endif

#ifdef MULTI
#ifdef CRM
  glDrawBuffer(GL_BACK);
#endif
  glViewport(0, 0, scrWidth, scrHeight);
  glLoadIdentity();
  glRotated(r - panangle, 0.0, 1.0, 0.0);
  glTranslated(ex, 0.0, ez);
  glCallList(1);
  glViewport(scrWidth + scrWidth, 0, scrWidth, scrHeight);
  glLoadIdentity();
  glRotated(r + panangle, 0.0, 1.0, 0.0);
  glTranslated(ex, 0.0, ez);
  glCallList(1);
#endif

  glutSwapBuffers();
}

void resize(int w, int h)
{
  cx = w / 2;
  cy = h / 2;

#ifdef MULTI
  w /= 3;
#endif

#if (!defined(STEREO) || defined(CRM)) && !defined(MULTI)
  glViewport(0, 0, w, h);
#endif

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(VIEWANGLE, (double)w / (double)h, 1.0, 100.0);
  glMatrixMode(GL_MODELVIEW);

#ifdef MULTI
  panangle = atan(tan(VIEWANGLE * 3.1415926536 / 180.0 / 2.0)
		  * (double)w / (double)h) * 180.0 * 2.0 / 3.1415926536;
  scrWidth = w;
  scrHeight = h;
#endif
}


void motion(int x, int y)
{
  angle = (x - cx) * 0.002;
  speed = (cy - y) * 0.001;
}

void idle(void)
{
  glutPostRedisplay();
}

void scene(void)
{
  int z;

  glNewList(1, GL_COMPILE);
  glDisable(GL_LIGHTING);
  glDisable(GL_DEPTH_TEST);
  glColor3fv(green);
  glBegin(GL_QUADS);
  glVertex3fv(base[0]);
  glVertex3fv(base[1]);
  glVertex3fv(base[2]);
  glVertex3fv(base[3]);
  glEnd();
  glColor3fv(white);
  glBegin(GL_QUADS);
  glVertex3fv(line[0]);
  glVertex3fv(line[1]);
  glVertex3fv(line[2]);
  glVertex3fv(line[3]);
  glVertex3fv(line[4]);
  glVertex3fv(line[5]);
  glVertex3fv(line[6]);
  glVertex3fv(line[7]);
  glEnd();
  glColor3fv(gray);
  glBegin(GL_QUADS);
  glVertex3fv(line[0]);
  glVertex3fv(line[3]);
  glVertex3fv(line[6]);
  glVertex3fv(line[5]);
  glEnd();
  glEnable(GL_LIGHTING);
  glEnable(GL_DEPTH_TEST);
  glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
  for (z = -90; z <= 90; z += 10) {
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, red);
    glPushMatrix();
    glTranslated(-2.0, -1.0, (double)z);
    glRotated(-90.0, 1.0, 0.0, 0.0);
    glutSolidCone(0.5, 2.0, 6, 1);
    glPopMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blue);
    glPushMatrix();
    glTranslated(2.0, -1.0, (double)(z + 5));
    glRotated(-90.0, 1.0, 0.0, 0.0);
    glutSolidCone(0.5, 2.0, 6, 1);
    glPopMatrix();
  }
  glEndList();
}

void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
  case '\033':
#if defined(STEREO) && !defined(CRM)
    system("/usr/gfx/setmon -n 60HZ");
#endif
    exit(0);
    break;
  case '0':
    ex = 0.0;
    ez = -100.0;
    r = angle = 0.0;
    break;
  default:
    break;
  }
}

int main(int argc, char *argv[])
{
#if defined(STEREO) && !defined(CRM)
  system("/usr/gfx/setmon -n STR_RECT");
#endif

  glutInit(&argc, argv);

#ifdef CRM
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE | GLUT_STEREO);
#else
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
#endif
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutIdleFunc(idle);
  glutMotionFunc(motion);
  glutKeyboardFunc(keyboard);
#if defined(STEREO) && !defined(CRM)
  glutFullScreen();
#endif
  scene();
  glClearColor(0.5, 0.7, 0.9, 0.0);
  glEnable(GL_CULL_FACE);
  glEnable(GL_LIGHT0);
  glutMainLoop();
  return 0;
}
