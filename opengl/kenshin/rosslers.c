#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

#define PARALLAX 0.2
#define DISTANCE 8.0

#define DATA_SIZE 3000
#define DISPLAY_DATA_SIZE 50

static double de_sol[DATA_SIZE][3];    /* 解曲線 */
static double de_n[DATA_SIZE][3];      /* 解曲線のattractiveな方向 */
static double de_a[DATA_SIZE][3];      /* 解曲線のexpandingな方向 */

static int repeat=1;                   /* デモの反復(スイッチ) */
static int sws=0;                      /* 視点の位置(スイッチ) */
static int altrj=1;                    /* 軌道の全体/部分表示(スイッチ) */
static int time=DISPLAY_DATA_SIZE;     /* 解曲線の始点の位置 */
static double spos=2.5;                /* 視点の高さ */
static int zoom=8;                     /* 拡大率 */

static int vp,vh,zm;             /* menu ID's */

void quit(void)
{
#if defined(STEREO) && !defined(CRM)
  system("/usr/gfx/setmon -n 60HZ");
#endif
  exit(0);
}

void solv_de()
{
  double  v1[3], v2[3];
  double  u1[3], u2[3];
  double  vn[3], va[3];
  double  ra, rn;
  double  dt;
  int  h,i;

  dt = 0.01 ;			/* 時間間隔 */

  v1[0]= 5.0;			/* 初期値 */
  v1[1]= 5.0;
  v1[2]= 0.0;
  u1[0]= 5.0;
  u1[1]= 5.1;
  u1[2]= 0.0;

  /* 差分方程式の繰り返し計算 */
  /* 初期の空回し */
  for(i=0; i<100; i++) {
    v2[0] = v1[0] + dt * (2.2-v1[2]) * (-v1[1]-v1[2]*20.0);
    v2[1] = v1[1] + dt * (2.2-v1[2]) * (v1[0]+0.2*v1[1]);
    v2[2] = v1[2] + dt * (2.2-v1[2]) * (0.01+v1[2]*(v1[0]-6.7));
    u2[0] = u1[0] + dt * (2.2-u1[2]) * (-u1[1]-u1[2]*20.0);
    u2[1] = u1[1] + dt * (2.2-u1[2]) * (u1[0]+0.2*u1[1]);
    u2[2] = u1[2] + dt * (2.2-u1[2]) * (0.01+u1[2]*(u1[0]-6.7));

    vn[0] = (v2[1]-v1[1])*(u2[2]-v2[2]) - (v2[2]-v1[2])*(u2[1]-v2[1]);
    vn[1] = (v2[2]-v1[2])*(u2[0]-v2[0]) - (v2[0]-v1[0])*(u2[2]-v2[2]);
    vn[2] = (v2[0]-v1[0])*(u2[1]-v2[1]) - (v2[1]-v1[1])*(u2[0]-v2[0]);

    va[0] = (v2[1]-v1[1])*vn[2] - (v2[2]-v1[2])*vn[1];
    va[1] = (v2[2]-v1[2])*vn[0] - (v2[0]-v1[0])*vn[2];
    va[2] = (v2[0]-v1[0])*vn[1] - (v2[1]-v1[1])*vn[0];
    ra = sqrt (va[0]*va[0]+va[1]*va[1]+va[2]*va[2]);

    for(h=0; h<3; h++) {
      u1[h] = v2[h] - va[h]/ra*0.2;
      v1[h] = v2[h];
    }
  }
  /* データを計算して保存 */
  for(i=0 ; i < DATA_SIZE ; i++) {
    v2[0] = v1[0] + dt * (2.2-v1[2]) * (-v1[1]-v1[2]*20.0);
    v2[1] = v1[1] + dt * (2.2-v1[2]) * (v1[0]+0.2*v1[1]);
    v2[2] = v1[2] + dt * (2.2-v1[2]) * (0.01+v1[2]*(v1[0]-6.7));
    u2[0] = u1[0] + dt * (2.2-u1[2]) * (-u1[1]-u1[2]*20.0);
    u2[1] = u1[1] + dt * (2.2-u1[2]) * (u1[0]+0.2*u1[1]);
    u2[2] = u1[2] + dt * (2.2-u1[2]) * (0.01+u1[2]*(u1[0]-6.7));

    vn[0] = (v2[1]-v1[1])*(u2[2]-v2[2]) - (v2[2]-v1[2])*(u2[1]-v2[1]);
    vn[1] = (v2[2]-v1[2])*(u2[0]-v2[0]) - (v2[0]-v1[0])*(u2[2]-v2[2]);
    vn[2] = (v2[0]-v1[0])*(u2[1]-v2[1]) - (v2[1]-v1[1])*(u2[0]-v2[0]);
    rn = sqrt (vn[0]*vn[0]+vn[1]*vn[1]+vn[2]*vn[2]);

    va[0] =  (v2[1]-v1[1])*vn[2] - (v2[2]-v1[2])*vn[1];
    va[1] =  (v2[2]-v1[2])*vn[0] - (v2[0]-v1[0])*vn[2];
    va[2] =  (v2[0]-v1[0])*vn[1] - (v2[1]-v1[1])*vn[0];
    ra = sqrt (va[0]*va[0]+va[1]*va[1]+va[2]*va[2]);

    for(h=0; h<3; h++) {
      u1[h] = v2[h] - va[h]/ra*0.2;
      de_sol[i][h] = v1[h] = v2[h];
      de_n[i][h] = vn[h]/rn/10.0;
      de_a[i][h] = va[h]/ra/25.0;
    }
  }
}

void init_light(void)
{
  GLfloat light_diffuse[]  = {1.0, 0.7, 0.7, 1.0};
  GLfloat light_ambient[]  = {0.5, 0.5, 0.5, 1.0};
  GLfloat light_specular[] = {0.6, 0.6, 0.6, 1.0};

  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
  glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
  glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular);
}

void set_light(void)
{
  GLfloat light_position0[] = {-20.0, 0.0, 10.0, 1.0};
  GLfloat light_position1[] = { 20.0, 0.0,-10.0, 1.0};
  GLfloat light_position2[] = {  0.0, 0.0,  1.0, 1.0};

  glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
  glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
  glLightfv(GL_LIGHT2, GL_POSITION, light_position2);

  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHT2);
}

void set_sight(double offset)
{
  int h;
  double u1[3], ur[3], ue[3], uo[3];
  double rr;

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
#ifdef STEREO
  glTranslated(offset, 0.0, 0.0);
  glRotated(atan2(offset, DISTANCE) * 180.0 / 3.1415926536, 0.0, 1.0, 0.0);
#endif
  if (sws == 1) {		/* 飛行機の斜後方 */
    for(h=0; h<3; h++) {
      u1[h] = de_sol[time-1][h];
      ur[h] = de_sol[time][h] - u1[h] ;
    }
    rr = sqrt(ur[0]*ur[0]+ur[1]*ur[1]+ur[2]*ur[2]);
    for(h=0; h<3; h++)
      ue[h] = u1[h] -ur[h]/rr*(double)(zoom)
	+de_n[time][h]*spos*(double)(zoom);
    for(h=0; h<3; h++)
      uo[h] = u1[h] +de_n[time][h]*(double)(zoom)*1.5;
    gluLookAt(ue[0],ue[1],ue[2], uo[0],uo[1],uo[2], 
	      de_n[time][0],
	      de_n[time][1],
	      de_n[time][2]);
  } else if (sws == 2) {	/* 中心の球 */
    gluLookAt(0.0, 0.0,  de_sol[time][2]+spos,
	      de_sol[time+2][0], de_sol[time+2][1], de_sol[time+2][2],
	      0.0, 0.0, 1.0);
  } else if (sws == 3) {	/* 中心の球と飛行機を結ぶ線の延長上 */
    for(h=0; h<3; h++) u1[h] = de_sol[time+2][h];
    rr = sqrt(u1[0]*u1[0]+u1[1]*u1[1]);
    for(h=0; h<2; h++) ue[h] = u1[h]*16.0/rr;
    gluLookAt(ue[0],ue[1],u1[2]+spos,
	      u1[0],u1[1],u1[2],
	      0.0, 0.0, 1.0);
  } else {			/* 上方固定 */
    gluLookAt(0.0, 0.0, 50.0, 0.0, -2.0, 0.0, 0.0, 1.0, 0.0);
  }
}

void display_lane(void)
{
  int i,j;
  GLdouble c1,c2,c3;
  double v1[3],v2[3],v3[3],v4[3];

  glBegin(GL_QUADS);   
  for(i=0; i<DATA_SIZE-3; i+=3) {
    for(j=0;j<3;j++) {
      v1[j]=de_sol[i][j]-de_a[i][j];
      v2[j]=de_sol[i][j]+de_a[i][j];
      v3[j]=de_sol[i+2][j]+de_a[i][j];
      v4[j]=de_sol[i+2][j]-de_a[i][j];
    }
    c1 = de_sol[i][2] / 2.5 + 0.2;
    c2 = (de_sol[i][0]-de_sol[i][1]) / 40.0 + 0.5;
    c3 = 4.0 * (double)i * (DATA_SIZE - i) / DATA_SIZE / DATA_SIZE ;
    glColor3d (c2*c3, c1, (1.0-c1)*c3);
    glVertex3dv(v1);
    glVertex3dv(v2);
    glVertex3dv(v3);
    glVertex3dv(v4);
  }
  glEnd();
}

void display_tail(void)
{
  int i;
  GLdouble c;

  glBegin(GL_LINE_STRIP);
  for(i=0; i < DISPLAY_DATA_SIZE; i++) {
    c = (double)i/(double)DISPLAY_DATA_SIZE;
    glColor3d (c, c, 0.0);
    glVertex3dv (de_sol[time+i-DISPLAY_DATA_SIZE+2]);
  }
  glEnd();
}

void ext_product(v1,v2,v3,nv)
     double *v1,*v2,*v3,*nv;
{
  int i;
  double u[3],w[3];

  for(i=0; i<3; i++) {
    u[i]=v3[i]-v1[i];
    w[i]=v2[i]-v1[i];
  }
  for(i=0; i<3; i++)
    nv[i]=u[(i+1)%3]*w[(i+2)%3]-u[(i+2)%3]*w[(i+1)%3];
}

void display_plane(void)
{
  int i;
  double u[3],rr;
  double v[7][3],nv[5][3];

  GLfloat mat_diffuse[]   = {1.0, 1.0, 0.7, 1.0};
  GLfloat mat_ambient[]   = {0.3, 0.3, 0.2, 1.0};
  GLfloat mat_specular[]  = {1.0, 1.0, 0.7, 1.0};
  GLfloat mat_shininess[] = {5.0};

  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);

  for(i=0; i<3; i++)
    u[i] = de_sol[time+5][i] - de_sol[time+1][i];
  rr=sqrt(u[0]*u[0]+u[1]*u[1]+u[2]*u[2]);

  for(i=0; i<3; i++) {
    v[0][i] = de_sol[time+1][i]+u[i]/rr+de_n[time+3][i]*0.5;
    v[1][i] = de_sol[time+1][i]+de_a[time+3][i]*7.0+de_n[time+3][i]*0.5;
    v[2][i] = de_sol[time+1][i]-de_a[time+3][i]*7.0+de_n[time+3][i]*0.5;
    v[3][i] = de_sol[time+1][i]+de_n[time+3][i]*0.1;
    v[4][i] = de_sol[time+1][i]+de_n[time+3][i]*0.5;
    v[5][i] = de_sol[time+1][i]+de_n[time+3][i]*2.0;
    v[6][i] = de_sol[time+1][i]+u[i]/rr/2.5+de_n[time+3][i]*0.5;
  }

  for(i=0; i<3; i++) {
    ext_product (v[3],v[2],v[1],nv[0]);
    ext_product (v[2],v[3],v[0],nv[1]);
    ext_product (v[1],v[0],v[3],nv[2]);
    ext_product (v[0],v[1],v[2],nv[3]);
    ext_product (v[5],v[4],v[6],nv[4]);
  }

  glBegin(GL_TRIANGLES);

  glNormal3dv(nv[0]);
  glVertex3dv(v[3]);
  glVertex3dv(v[2]);
  glVertex3dv(v[1]);

  glNormal3dv(nv[1]);
  glVertex3dv(v[2]);
  glVertex3dv(v[3]);
  glVertex3dv(v[0]);

  glNormal3dv(nv[2]);
  glVertex3dv(v[1]);
  glVertex3dv(v[0]);
  glVertex3dv(v[3]);

  glNormal3dv(nv[3]);
  glVertex3dv(v[0]);
  glVertex3dv(v[1]);
  glVertex3dv(v[2]);

  glNormal3dv(nv[4]);
  glVertex3dv(v[6]);
  glVertex3dv(v[4]);
  glVertex3dv(v[5]);

  glEnd();
}

void display_sun(void)
{
  GLfloat mat_diffuse[]   = {1.0, 0.5, 0.2, 1.0};
  GLfloat mat_specular[]  = {0.5, 0.2, 0.1, 1.0};
  GLfloat mat_ambient[]   = {0.5, 0.2, 0.1, 1.0};
  GLfloat mat_shininess[] = {5.0};

  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
  glutSolidSphere(0.5,15,15);
}

void idle(void)
{
  time++;
  if(time >= DATA_SIZE-10)
    if (repeat == 1) quit();
    else time=DISPLAY_DATA_SIZE;

  glutPostRedisplay();
}

void init(void)
{
  glClearColor(0.0, 0.0, 0.1, 0.0);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);

  init_light();

  solv_de();
}


void display(void)
{
#ifdef STEREO
#ifdef CRM
  glDrawBuffer(GL_BACK_RIGHT);
#else
  glViewport(0, 0, 1280, 492);
#endif
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  set_sight(-PARALLAX);
  glNewList(1, GL_COMPILE_AND_EXECUTE);
#else
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  set_sight(0.0);
#endif

  set_light();

  if (altrj == 0) display_tail();
  else display_lane();

  glEnable(GL_LIGHTING);
  display_sun();
  display_plane();
  glDisable(GL_LIGHTING);

#ifdef STEREO
  glEndList();
#ifdef CRM
  glDrawBuffer(GL_BACK_LEFT);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#else
  glViewport(0, 532, 1280, 492);
#endif
  set_sight(PARALLAX);
  glCallList(1);
#endif

  glutSwapBuffers();
}


void reshape(int w, int h)
{
#if !defined(STEREO) || defined(CRM)
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);
#endif
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective (30.0, (GLfloat)w/(GLfloat)h, 1.0, 200.0);
}

void param_vp(int sel)
{
  switch(sel) {
  case 1: sws = 0; break;
  case 2: sws = 1; break;
  case 3: sws = 2; break;
  case 4: sws = 3; break;
  default: break;
  }
  glutPostRedisplay();
  if (sws == 0) glutChangeToMenuEntry(5,"",6);
  else glutChangeToSubMenu(5,"Height",vh);
  if (sws != 1) glutChangeToMenuEntry(6,"",6);
  else glutChangeToSubMenu(6,"Zoom",zm);
}

void param_vh(int sel)
{
  switch(sel) {
  case  1: spos= 5.5; break;
  case  2: spos= 4.5; break;
  case  3: spos= 3.5; break;
  case  4: spos= 2.5; break;
  case  5: spos= 1.5; break;
  case  6: spos= 0.5; break;
  case  7: spos=-0.5; break;
  case  8: spos=-1.5; break;
  case  9: spos=-2.5; break;
  case 10: spos=-3.5; break;
  case 11: spos=-4.5; break;
  case 12: spos=-5.5; break;
  }
  glutPostRedisplay();
}

void param_zm(int sel)
{
  if (sws == 1) {
    switch(sel) {
    case  1: zoom=2; break;
    case  2: zoom=4; break;
    case  3: zoom=8; break;
    case  4: zoom=16; break;
    case  5: zoom=32; break;
    case  6: zoom=64; break;
    }
  }
  glutPostRedisplay();
}

void parameter(int sel)
{
  switch(sel) {
  case 2: altrj=0;
    glutChangeToMenuEntry(2,"Trajectory: Lane",3);
    break;
  case 3: altrj=1;
    glutChangeToMenuEntry(2,"Trajectory: Tail",2);
    break;
  case 20:
    glutIdleFunc(NULL);
    glutChangeToMenuEntry(3,"Restart",21);
    break;
  case 21:
    glutIdleFunc(idle);
    glutChangeToMenuEntry(3,"Pause",20);
    break;
  case 30:
    repeat=1;
    glutChangeToMenuEntry(4,"Repeat: Off -> On",31);
    break;
  case 31:
    repeat=0;
    glutChangeToMenuEntry(4,"Repeat: On -> Off",30);
    break;
  case 99:
    quit();
  }
  glutPostRedisplay();
}

void menu(void)
{

  vh=glutCreateMenu(param_vh);
  glutAddMenuEntry("High",1);
  glutAddMenuEntry("/\\",2);
  glutAddMenuEntry(" .",3);
  glutAddMenuEntry(" .",4);
  glutAddMenuEntry(" .",5);
  glutAddMenuEntry(" .",6);
  glutAddMenuEntry(" .",7);
  glutAddMenuEntry(" .",8);
  glutAddMenuEntry(" .",9);
  glutAddMenuEntry(" .",10);
  glutAddMenuEntry("\\/",11);
  glutAddMenuEntry("Low",12);

  zm=glutCreateMenu(param_zm);
  glutAddMenuEntry("Near",1);
  glutAddMenuEntry("/\\",2);
  glutAddMenuEntry(" .",3);
  glutAddMenuEntry(" .",4);
  glutAddMenuEntry("\\/",5);
  glutAddMenuEntry("Far",6);

  vp=glutCreateMenu(param_vp);
  glutAddMenuEntry("Full view",1);
  glutAddMenuEntry("Follow the Plane",2);
  glutAddMenuEntry("From the Center",3);
  glutAddMenuEntry("From Outside",4);
  glutAddSubMenu("Height",vh);
  glutAddSubMenu("Zoom",zm);

  glutCreateMenu(parameter);
  glutAddSubMenu("View",vp);
  glutAddMenuEntry("Trajectory: Tail",2);
  glutAddMenuEntry("Pause",20);
  glutAddMenuEntry("Repeat: Off -> On",31);
  glutAddMenuEntry("Quit",99);
  glutAttachMenu(GLUT_LEFT_BUTTON);
}

void keyboard(unsigned char key, int x, int y)
{
  switch(key) {
  case 27:			/* [ESC] プログラム終了 */
    quit();
    break;
  case 's':			/* アニメーション一時停止 */
    glutIdleFunc(NULL);
    break;
  case ' ':			/* (停止時に)1コマ進める */
    idle();
    break;
  case 'g':			/* アニメーション再開 */
    glutIdleFunc(idle);
    break;
  case 'V':			/* 視点の変更スイッチ */
    sws--; if(sws == -1) sws=3;
    glutPostRedisplay();
    break;
  case 'v':			/* 視点の変更スイッチ */
    sws++; if(sws == 4) sws=0;
    glutPostRedisplay();
    break;
  case 't':			/* 解曲線全体/部分描画の変更スイッチ */
    altrj = 1-altrj;
    glutPostRedisplay();
    break;
  case 'u':			/* 視点の高さを上げる */
    if (sws > 0) spos += 1.0;
    if (spos > 5.5) spos = 5.5;
    glutPostRedisplay();
    break;
  case 'd':			/* 視点の高さを下げる */
    if (sws > 0) spos -= 1.0;
    if (spos < -5.5) spos = -5.5;
    glutPostRedisplay();
    break;
  case '+':			/* ズームイン */
    if (sws == 1) zoom = zoom/2;
    if (zoom < 2) zoom = 2;
    glutPostRedisplay();
    break;
  case '-':			/* ズームアウト */
    if (sws == 1) zoom = zoom*2;
    if (zoom > 64) zoom = 64;
    glutPostRedisplay();
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

  glutInitWindowSize(480,360);
  glutInitWindowPosition(100,100);

  glutInit(&argc, argv);
#ifdef CRM
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STEREO);
#else
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
#endif

  glutCreateWindow("Flying on Rossler Equation");

  init();
  menu();

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutIdleFunc(idle);
#if defined(STEREO) && !defined(CRM)
  glutFullScreen();
#endif
  glutMainLoop();

  return 0;
}
