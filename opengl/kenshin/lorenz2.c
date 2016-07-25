/*
 *   OpenGL, glut を使った Lorenz方程式の解曲線を描画するプログラム   
 */

#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#define LENGTH 20
#define DATA_SIZE LENGTH * LENGTH * LENGTH

static double sol[DATA_SIZE][3];
static double col[DATA_SIZE][3];
static int time=5;

void solv_de(void) /* Lorenz方程式の差分化方程式の繰り返し計算 */
{
       static double dt=0.005;          /* 時間間隔 */
       double  u[3],v[3];
       int  i;

       /* データを計算して保存 */
       for(i=0 ; i < DATA_SIZE ; i++) {
            u[0] = (sol[i][0]+sol[i][1]*10.0)/2.0;
            u[1] = (sol[i][0]-sol[i][1]*10.0)/2.0;
            u[2] = sol[i][2];

            v[0] = u[0] + dt * (10.0 * (u[1] - u[0]));
            v[1] = u[1] + dt * (28.0 * u[0] - u[1] - u[0] * u[2]);
            v[2] = u[2] + dt * (-8.0/3.0 * u[2] + u[0] * u[1]);

            sol[i][0] = v[0]+v[1];
            sol[i][1] = (v[0]-v[1])/10.0;
            sol[i][2] = v[2];
       }
}

void init(void)
{
    int  i,ix,iy,iz;

    for(ix=0; ix< LENGTH; ix++) {
        for(iy=0; iy< LENGTH; iy++) {
            for(iz=0; iz< LENGTH; iz++) {
                i = ix*400+iy*20+iz;
                sol[i][0]= (double)(ix*2-LENGTH)+0.5;
                sol[i][1]= (double)(iy*2-LENGTH)+0.5;
                sol[i][2]= (double)(iz*2-LENGTH)+0.5;
                col[i][0]= (double)(ix*2+LENGTH)/(double)(LENGTH*3);
                col[i][1]= (double)(iy*2+LENGTH)/(double)(LENGTH*3);
                col[i][2]= (double)(iz*2+LENGTH)/(double)(LENGTH*3);
            }
        }
    }

    glClearColor(0.0, 0.1, 0.3, 0.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
}

void idle(void)
{
    glutPostRedisplay();
}

void set_sight(void)
{
    double ye,ze;

    ye = 80.0+25000.0/(double)time;
    ze = 75.0-(double)time/10.0;
    glLoadIdentity();
    gluLookAt(0.0,ye,ze, 0.0,0.0,ze, 0.0,0.0,1.0);
}

void set_light(void)
{
    GLfloat light_ambient[] = { 0.2,0.2,0.2,1.0 };
    GLfloat light_position0[] = {  17.0, 50.0, 27.0, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

    glEnable(GL_LIGHT0);
}

void display(void)
{
    int i;
    GLdouble c;
    GLfloat mat_diffuse2[] = { 0.0, 0.0, 1.0, 1.0 };
    GLfloat mat_diffuse3[] = { 0.0, 1.0, 0.0, 1.0 };

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    time++; if(time>500) exit(0);
    solv_de();
    set_sight();
    set_light();

    glBegin(GL_POINTS);
    for(i=0; i<DATA_SIZE; i++) {
        glColor3dv(col[i]);
        glVertex3dv(sol[i]);
    }
    glEnd();

    glEnable(GL_LIGHTING);

    /* 方程式の平衡点を球で表示 */
    glPushMatrix();
    glTranslated(16.97056, 0.0, 27.0);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2);
    glutSolidSphere(0.5,20,20);
    glPopMatrix();
    glPushMatrix();
    glTranslated(-16.97056, 0.0, 27.0);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse3);
    glutSolidSphere(0.5,20,20);
    glPopMatrix();

    glDisable(GL_LIGHTING);

    glutSwapBuffers();
}


void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective( 40.0, (GLfloat)w/(GLfloat)h, 1.0, 2000.0);
}

void keyboard(unsigned char key, int x, int y)
{
    switch(key) {
         case 27:  /* [ESC] プログラムの終了 */
             exit(0);
             break;
         case 's':  /* アニメーション一時停止 */
             glutIdleFunc(NULL);
             break;
         case 'g':  /* アニメーション開始 */
             glutIdleFunc(idle);
             break;
         case ' ':  /* (停止時に)1コマ進める */
             glutPostRedisplay();
             break;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(50,50);
    glutCreateWindow(argv[0]);

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);
    glutMainLoop();

    return 0;
}
