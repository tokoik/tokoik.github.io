/*
 *   OpenGL, glut を使った カオスのおもちゃのシミュレーション
 *
 *                           toychaos.c   1998/12/16  ver.0.3
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

/* 以下の数値はお好みで設定してください。 */

#define SPEED 0.5          /* ボールの動くスピード */
#define MAGNET 0.7         /* 磁石の強さ */

/* ここまで */

#define WHASPCT 1.8 /* 表示の縦横比(本当は視線の角度によって変えた方が良い) */
#define STAND_ANGLE_P 24
#define MAGNET_ANGLE_P 12
#define BALL_PART 15

#define PI2 (3.14159265358979*2.0)

static double data_stand[STAND_ANGLE_P +1][2];
static double data_magnet[MAGNET_ANGLE_P +1][2];
static double magnet_pos[4][2];
static int    magnet_men[4];
static double xcenter,ycenter,xstandr,ystandr,ystandh;
static double xball,yball,zball, vx,vy /* ,vz */;
static int    gostop=1;
static double viewangle = PI2/8.0;
static double armangle = 60.0;
static double zoom = 1.4;
static double wd,ht;

void init(void)
{
    int i;
    double x,y,th;

    glClearColor(0.9,1.0,0.9,0.0);
    glShadeModel(GL_SMOOTH);

    /* construct stand data */
    for(i=0; i<STAND_ANGLE_P; i++) {
        th = (double)i / (double)STAND_ANGLE_P * PI2;
        data_stand[i][0] = 5.0 * cos(th);
        data_stand[i][1] = 5.0 * sin(th);
    }
    data_stand[STAND_ANGLE_P][0] = 5.0;
    data_stand[STAND_ANGLE_P][1] = 0.0;

    /* construct magnet data */
    for(i=0; i<MAGNET_ANGLE_P; i++) {
        th = (double)i / (double)MAGNET_ANGLE_P * PI2;
        data_magnet[i][0] = 0.7 * cos(th);
        data_magnet[i][1] = 0.7 * sin(th);
    }
    data_magnet[MAGNET_ANGLE_P][0] = 0.7;
    data_magnet[MAGNET_ANGLE_P][1] = 0.0;

    /* initial magnet's positon */
    magnet_pos[0][0] =  4.0;
    magnet_pos[0][1] =  0.0;
    magnet_pos[1][0] =  0.0;
    magnet_pos[1][1] =  4.0;
    magnet_pos[2][0] = -4.0;
    magnet_pos[2][1] =  0.0;
    magnet_pos[3][0] =  0.0;
    magnet_pos[3][1] =  0.0;

    /* initial magnet's face */
    magnet_men[0] = 1;
    magnet_men[1] = 0;
    magnet_men[2] = 1;
    magnet_men[3] = 1;

    /* initial ball positon and speed */
    xball = 0.01; yball = 0.0; zball = 4.4;
    vx = vy /* = vz */ = 0.0;
}

void set_light(void)
{
    GLfloat light_ambient[] = {0.2,0.2,0.2,1.0};
    GLfloat light_position0[] = {-4.0,-8.0,0.0};
    GLfloat light_position1[] = {0.0,2.0,25.0};
    GLfloat light_diffuse[] = {0.8,0.8,0.8,1.0};

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
}

void force(void)
{
    int i;
    double ax,ay,az;
    double xr,yr,zr,rr;
    double prod;

    /* gravity */
    ax=0.0; ay=0.0; az=-1.0;

    /* magnets */
    for(i=0; i<4; i++) {
        xr = xball - magnet_pos[i][0];
        yr = yball - magnet_pos[i][1];
        zr = zball - 1.2 - 2.1;
        rr = sqrt (xr*xr + yr*yr + zr*zr);
        if (magnet_men[i]>0) {
            ax += MAGNET * xr/rr/rr/rr;
            ay += MAGNET * yr/rr/rr/rr;
            az += MAGNET * zr/rr/rr/rr;
        } else {
            ax -= MAGNET * xr/rr/rr/rr;
            ay -= MAGNET * yr/rr/rr/rr;
            az -= MAGNET * zr/rr/rr/rr;
        }
    }

    /* projection */
    rr = sqrt(xball*xball + yball*yball +(zball-22.6)*(zball-22.6));
    prod = (ax*xball + ay*yball + az*(zball-22.6))/rr;
    ax -= prod * xball / rr;
    ay -= prod * yball / rr;
/*  az -= prod * (zball-22.6) / rr;   */

    vx += ax;
    vy += ay;
/*  vz += az;   */
}

void idle(void)
{
    force();
    xball += SPEED * vx;
    yball += SPEED * vy;
    if (xball*xball + yball*yball > 100.0) {
        printf("Too large ampl.: %f %f\n",xball,yball);
        exit(0);
    }
    zball = 22.6 - sqrt((18.2)*(18.2) - xball*xball - yball*yball);

    glutPostRedisplay();
}

void display_arm(void)
{
    GLfloat mat_diffuse[] = {0.3, 0.35, 0.4, 1.0};
    GLfloat mat_ambient[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat mat_specular[] = {0.3, 0.35, 0.4, 1.0};
    GLfloat mat_shininess[] = {5.0};

    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glPushMatrix();
    glRotated(armangle,0.0,0.0,1.0);

    glBegin(GL_QUAD_STRIP);
        glNormal3d(0.0,-1.0,0.0);
        glVertex3d(5.0,-0.15,1.5);
        glVertex3d(5.0,-0.15,1.2);
        glVertex3d(6.0,-0.15,1.5);
        glVertex3d(6.1,-0.15,1.2);
        glVertex3d(9.0,-0.15,5.5);
        glVertex3d(9.3,-0.15,5.5);
        glVertex3d(1.0,-0.15,22.0);
        glVertex3d(1.2,-0.15,22.2);
        glVertex3d(0.0,-0.15,22.5);
        glVertex3d(0.0,-0.15,22.8);
    glEnd();

    glBegin(GL_QUAD_STRIP);
        glNormal3d(0.0,1.0,0.0);
        glVertex3d(5.0,0.15,1.2);
        glVertex3d(5.0,0.15,1.5);
        glVertex3d(6.1,0.15,1.2);
        glVertex3d(6.0,0.15,1.5);
        glVertex3d(9.3,0.15,5.5);
        glVertex3d(9.0,0.15,5.5);
        glVertex3d(1.2,0.15,22.2);
        glVertex3d(1.0,0.15,22.0);
        glVertex3d(0.0,0.15,22.8);
        glVertex3d(0.0,0.15,22.5);
    glEnd();

    glBegin(GL_QUADS);
        glNormal3d(0.0,0.0,1.0);
        glVertex3d(5.0, 0.15,1.5);
        glVertex3d(5.0,-0.15,1.5);
        glVertex3d(6.0,-0.15,1.5);
        glVertex3d(6.0, 0.15,1.5);
        glNormal3d(-0.8,0.0,0.6);
        glVertex3d(6.0, 0.15,1.5);
        glVertex3d(6.0,-0.15,1.5);
        glVertex3d(9.0,-0.15,5.5);
        glVertex3d(9.0, 0.15,5.5);
        glNormal3d(-0.9,0.0,-0.45);
        glVertex3d(9.0, 0.15,5.5);
        glVertex3d(9.0,-0.15,5.5);
        glVertex3d(1.0,-0.15,22.0);
        glVertex3d(1.0, 0.15,22.0);
        glNormal3d(-0.45,0.0,-0.9);
        glVertex3d(1.0, 0.15,22.0);
        glVertex3d(1.0,-0.15,22.0);
        glVertex3d(0.0,-0.15,22.5);
        glVertex3d(0.0, 0.15,22.5);
        glNormal3d(1.0,0.0,0.0);
        glVertex3d(0.0, 0.15,22.5);
        glVertex3d(0.0,-0.15,22.5);
        glVertex3d(0.0,-0.15,22.8);
        glVertex3d(0.0, 0.15,22.8);
        glNormal3d(0.45,0.0,0.9);
        glVertex3d(0.0, 0.15,22.8);
        glVertex3d(0.0,-0.15,22.8);
        glVertex3d(1.2,-0.15,22.2);
        glVertex3d(1.2, 0.15,22.2);
        glNormal3d(0.9,0.0,0.45);
        glVertex3d(1.2, 0.15,22.2);
        glVertex3d(1.2,-0.15,22.2);
        glVertex3d(9.3,-0.15,5.5);
        glVertex3d(9.3, 0.15,5.5);
        glNormal3d(0.8,0.0,-0.6);
        glVertex3d(9.3, 0.15,5.5);
        glVertex3d(9.3,-0.15,5.5);
        glVertex3d(6.0,-0.15,1.2);
        glVertex3d(6.0, 0.15,1.2);
        glNormal3d(-1.0,0.0,0.0);
        glVertex3d(6.1, 0.15,1.2);
        glVertex3d(6.1,-0.15,1.2);
        glVertex3d(5.0,-0.15,1.2);
        glVertex3d(5.0, 0.15,1.2);
    glEnd();

    glPopMatrix();
}

void display_stand(void)
{
    int i;
    GLfloat mat_diffuse[] = {0.3, 0.35, 0.4, 1.0};
    GLfloat mat_ambient[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat mat_specular[] = {0.3, 0.35, 0.4, 1.0};
    GLfloat mat_shininess[] = {5.0};

    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glBegin(GL_QUADS);
    for(i=0; i< STAND_ANGLE_P; i++) {
        glNormal3d (data_stand[i][0]/5.0,data_stand[i][1]/5.0,0.0);
        glVertex3d (data_stand[i][0],data_stand[i][1],1.6);
        glVertex3d (data_stand[i][0],data_stand[i][1],0.0);
        glNormal3d (data_stand[i+1][0]/5.0,data_stand[i+1][1]/5.0,0.0);
        glVertex3d (data_stand[i+1][0],data_stand[i+1][1],0.0);
        glVertex3d (data_stand[i+1][0],data_stand[i+1][1],1.6);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glNormal3d(0.0,0.0,1.0);
    glVertex3d(0.0,0.0,1.6);
    for(i=0; i<= STAND_ANGLE_P; i++) {
        glNormal3d(0.0,0.0,1.0);
        glVertex3d (data_stand[i][0],data_stand[i][1],1.6);
    }
    glEnd();
}

void display_magnet(void)
{
    int i,j;
    GLfloat mat_diffuse[6][4] = { {1.0, 0.0, 0.0, 1.0},  /* red */
                                  {1.0, 1.0, 0.0, 1.0},  /* yellow */
                                  {1.0, 1.0, 1.0, 1.0},  /* white */
                                  {0.0, 0.3, 1.0, 1.0},  /* blue */
                                  {0.1, 0.1, 0.1, 1.0},  /* dark gray */
                                  {0.4, 0.4, 0.4, 1.0}}; /* light gray */
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = {20.0};

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    for(i=0; i<4; i++) {
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse[4+magnet_men[i]]);
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_diffuse[4+magnet_men[i]]);

        glBegin(GL_TRIANGLE_FAN);
        glNormal3d (0.0,0.0,1.0);
        glVertex3d (magnet_pos[i][0],magnet_pos[i][1],2.05);
        for(j=0; j<= MAGNET_ANGLE_P; j++) {
            glNormal3d(0.0,0.0,1.0);
            glVertex3d (magnet_pos[i][0]+0.7*data_magnet[j][0],
                        magnet_pos[i][1]+0.7*data_magnet[j][1],2.05);
        }
        glEnd();

        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse[i]);
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_diffuse[i]);

        glBegin(GL_QUADS);
        for(j=0; j< MAGNET_ANGLE_P; j++) {
            glNormal3d (data_magnet[j][0]/0.7,
                        data_magnet[j][1]/0.7, 0.0);
            glVertex3d (magnet_pos[i][0]+data_magnet[j][0],
                        magnet_pos[i][1]+data_magnet[j][1],2.1);
            glVertex3d (magnet_pos[i][0]+data_magnet[j][0],
                        magnet_pos[i][1]+data_magnet[j][1],1.6);
            glNormal3d (data_magnet[j+1][0]/0.7,
                        data_magnet[j+1][1]/0.7, 0.0);
            glVertex3d (magnet_pos[i][0]+data_magnet[j+1][0],
                        magnet_pos[i][1]+data_magnet[j+1][1],1.6);
            glVertex3d (magnet_pos[i][0]+data_magnet[j+1][0],
                        magnet_pos[i][1]+data_magnet[j+1][1],2.1);
        }
        glEnd();

        glBegin(GL_QUAD_STRIP);
        for(j=0; j<= MAGNET_ANGLE_P; j++) {
            glNormal3d(0.0,0.0,1.0);
            glVertex3d (magnet_pos[i][0]+0.7*data_magnet[j][0],
                        magnet_pos[i][1]+0.7*data_magnet[j][1],2.05);
            glVertex3d (magnet_pos[i][0]+data_magnet[j][0],
                        magnet_pos[i][1]+data_magnet[j][1],2.1);
        }
        glEnd();
    }
}

void display_ball(void)
{
    GLfloat mat_diffuse[] = {0.9, 0.9, 0.9, 1.0};
    GLfloat mat_ambient[] = {0.1, 0.1, 0.1, 1.0};
    GLfloat mat_specular[] = {0.7, 0.5, 0.3, 1.0};
    GLfloat mat_shininess[] = {5.0};

    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glPushMatrix();
    glTranslated(xball,yball,zball);
    glutSolidSphere(1.2,BALL_PART,BALL_PART);
    glPopMatrix();

    glBegin(GL_LINES);
    glNormal3d(0.0,0.0,1.0);
    glVertex3d(0.0,0.0,22.5);
    glVertex3d(xball,yball,zball);
    glEnd();

    glBegin(GL_TRIANGLES);
    glNormal3d(0.0,0.0,1.0);
    if (xball*xball + yball*yball < 25.0) {
        glVertex3d(xball,    yball-0.1,1.61);
        glVertex3d(xball+0.1,yball+0.1,1.61);
        glVertex3d(xball-0.1,yball+0.1,1.61);
    } else {
        glVertex3d(xball,    yball-0.1,0.01);
        glVertex3d(xball+0.1,yball+0.1,0.01);
        glVertex3d(xball-0.1,yball+0.1,0.01);
    }
    glEnd();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);

    display_arm();
    display_stand();
    display_magnet();
    display_ball();

    glDisable(GL_LIGHTING);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);

    glutSwapBuffers();
}

/* ms2mg() で使う定数の計算 */
void scalewin(void)
{
    xcenter=wd/2.0;
    ycenter=ht/2.0;

    if (ht > wd * WHASPCT) {
        xstandr=wd/2.0/zoom;
        ystandr=wd/2.0/zoom*sin(viewangle);
        ystandh=wd/2.0/zoom*cos(viewangle)*7.9/5.0;
    } else {
        xstandr=ht/2.0/zoom/WHASPCT;
        ystandr=ht/2.0/zoom/WHASPCT*sin(viewangle);
        ystandh=ht/2.0/zoom/WHASPCT*cos(viewangle)*7.9/5.0;
    }
}

void set_proj_matrix(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(wd * WHASPCT <= ht)
        glOrtho(-5.0*zoom, 5.0*zoom,
                -5.0*zoom*(GLfloat)ht/(GLfloat)wd,
                 5.0*zoom*(GLfloat)ht/(GLfloat)wd, -10.0, 200.0);
    else
        glOrtho(-5.0*zoom*WHASPCT*(GLfloat)wd/(GLfloat)ht,
                 5.0*zoom*WHASPCT*(GLfloat)wd/(GLfloat)ht,
                -5.0*zoom*WHASPCT, 5.0*zoom*WHASPCT, -10.0, 200.0);
}

void set_model_matrix(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0,-50.0*cos(viewangle),10.0+50.0*sin(viewangle),
              0.0,0.0,10.0,    0.0,0.0,1.0);
    set_light();
}

void reshape(int w, int h)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    wd = (double)w, ht = (double)h;
    scalewin();
    set_proj_matrix();
    set_model_matrix();
}

void viewupdown(int i)
{
    if (i==0) {
        viewangle += PI2 / 72.0;
        if (viewangle > PI2/4.0) viewangle = PI2/4.0;
    } else {
         viewangle -= PI2 / 72.0;
         if (viewangle < PI2/12.0) viewangle = PI2/12.0;
    }
    scalewin();
    set_model_matrix();
}

void zoominout(int i)
{
    if (i==0) {
         zoom -= 0.2;
         if (zoom < 1.0 ) zoom = 1.0;
    } else {
         zoom += 0.2;
         if (zoom > 2.0 ) zoom = 2.0;
    }
    scalewin();
    set_proj_matrix();
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
    switch(key) {
        case 'g':
            gostop = 0;
            glutIdleFunc(idle);
            break;
        case 's':
            gostop = 1;
            glutIdleFunc(NULL);
            break;
        case ' ':
            idle();
            break;
        case 'u':
        case 'k':
            viewupdown(0);
            glutPostRedisplay();
            break;
        case 'd':
        case 'j':
            viewupdown(1);
            glutPostRedisplay();
            break;
        case '+':
            zoominout(0);
            glutPostRedisplay();
            break;
        case '-':
            zoominout(1);
            glutPostRedisplay();
            break;
        case 'l':
            armangle += 20.0;
            if (armangle > 360.0) armangle -= 360.0;
            glutPostRedisplay();
            break;
        case 'h':
            armangle -= 20.0;
            if (armangle < 0.0) armangle += 360.0;
            glutPostRedisplay();
            break;
        case 27:
            exit(0);
            break;
    }
}

int find_object(double xm, double ym, double xb, double yb)
{
    double r,rmin;
    int i,imin;

    imin= -1;
    rmin=3.0;
    for(i=0; i<4; i++) {
        r = (xm-magnet_pos[i][0])*(xm-magnet_pos[i][0])
          + (ym-magnet_pos[i][1])*(ym-magnet_pos[i][1]);
        if(r<rmin) {imin=i; rmin=r;}
    }

    r = (xb-xball)*(xb-xball) + (yb-yball)*(yb-yball);
    if(r<rmin) imin=9;

    return imin;
}

/* マウスの位置から磁石の座標を計算 */
int ms2mg(int x, int y, double *xg, double *yg)
{
      *xg = (x-xcenter) / xstandr * 5.0;
      *yg = (ycenter+ystandh-y) / ystandr * 5.0;

      if ((*xg)*(*xg)+(*yg)*(*yg)>20.0) return (-1); else return (0);
}

/* (仮想の)磁石の座標からボールの座標を計算 */
int mg2bl(double x, double y, double *xg, double *yg)
{
      double aa,bb,cc,dd,ss;

      aa = 1.0+tan(viewangle)*tan(viewangle);
      bb = y+20.5*tan(viewangle);
      cc = x*x + y*y + 89.01;
      /* solution of ax^2-2bx+c=0 */
      if ((dd=bb*bb-aa*cc) <= 0.0) return -1;
      ss = (bb - sqrt(dd))/aa;

      *xg = x;
      *yg = y - ss;

      if ((*xg)*(*xg)+(*yg)*(*yg)>40.0) return (-1); else return (0);
}

void mouse(int button, int state, int x, int y)
{
    double x0, y0, x1, y1;
    static int object;

    switch(button) {
        case GLUT_LEFT_BUTTON:
            if(state == GLUT_DOWN) {
                ms2mg(x,y,&x0,&y0);
                mg2bl(x0,y0,&x1,&y1);
                object = find_object(x0,y0,x1,y1);
            } else if(state == GLUT_UP) {
                if (object >= 0 && object <= 3) {
                    if (ms2mg(x,y,&x0,&y0)==0) {
                        magnet_pos[object][0]=x0;
                        magnet_pos[object][1]=y0;
                    }
                } else if (object == 9) {
                    ms2mg(x,y,&x0,&y0);
                    if (mg2bl(x0,y0,&x1,&y1)==0) {
                        xball = x1;
                        yball = y1;
                        zball = 22.6 - sqrt((18.2)*(18.2) - x1*x1 - y1*y1);
                        vx = vy /* = vz */ = 0.0;
                    }
                }
                glutPostRedisplay();
            }
            break;
        case GLUT_RIGHT_BUTTON:
            if(state == GLUT_DOWN) {
                ms2mg(x,y,&x0,&y0);
                object = find_object(x0,y0,9.0,9.0);
                if (object >= 0 && object <= 3)
                    magnet_men[object] = 1 - magnet_men[object];
                glutPostRedisplay();
            }
            break;
        case GLUT_MIDDLE_BUTTON:
            if(state == GLUT_DOWN) {
                gostop = 1 - gostop;
                if (gostop == 0) glutIdleFunc(idle);
                            else glutIdleFunc(NULL);
            }
            break;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(250,450);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Toy of Chaos");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutIdleFunc(NULL);
    glutMainLoop();

    return 0;
}
