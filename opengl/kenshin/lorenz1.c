/*
 *
 *  OpenGL, glut を使った Lorenz方程式の解曲線を描画するデモ・プログラム   
 *                                                  ver.0.11 (1998/12/2)
 */

#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <GL/glut.h>

#define DATA_SIZE 10000
#define CARS 6

static double lane[DATA_SIZE][3];
static double lanecolor[DATA_SIZE][3];
static double cars[CARS][3],carsp[CARS][3];
static int carlap[CARS];

static int zoom=8;                 /* ズームのパラメーター */
static double vht=0.3;             /* 視点の高さ */
static int car_num=0;              /* 視点を設定する車の番号 */
static int vall=1;                 /* 視点の切り替えスイッチ */

static int vp,vh,zm;               /* menu ID's */

void solv_de(u,v) /* Lorenz方程式の差分化方程式の繰り返し計算 */
double u[3],v[3];
{
    static double dt = 0.005;                /* 時間間隔 */

    v[0] = u[0] + dt * (10.0 * (u[1] - u[0]));
    v[1] = u[1] + dt * (28.0 * u[0] - u[1] - u[0] * u[2]);
    v[2] = u[2] + dt * (-2.666666667 * u[2] + u[0] * u[1]);
}

void make_lane(void) /* 解曲線のデータ作成 */
{
    int  i,j;
    double v1[3],v2[3];
    GLdouble c1,c2,c3;

    v1[0] = 2.0; v1[1] = 2.0; v1[2] = 2.0;               /* 初期値 */

    for(i=0; i<300; i++) {                       /* 初期の空回し */
        solv_de(v1,v2);
        for (j=0; j<3; j++) v1[j] = v2[j];
    }
    
    for(i=0; i < DATA_SIZE; i++) {       /* データを計算して保存 */
        solv_de(v1,v2);

        lane[i][0] = v2[0] + v2[1];
        lane[i][1] = (v2[0] - v2[1]) / 10.0;
        lane[i][2] = v2[2];

        for (j=0; j<3; j++) v1[j] = v2[j];

        c1 = (lane[i][0]+lane[i][1]) / 100.0 + 0.5;
        c2 = 4.0 * (double)i * (DATA_SIZE - i) / DATA_SIZE / DATA_SIZE;
        c3 = lane[i][2] / 100.0;
        lanecolor[i][0] = c2*c3;
        lanecolor[i][1] = c2*(1.0-c1);
        lanecolor[i][2] = c2*c1;
    }
}

void move_cars(void)
{
    int i;
    double v1[3],v2[3];

    for(i=0; i<CARS; i++) {
        carsp[i][0] = cars[i][0];
        carsp[i][1] = cars[i][1];
        carsp[i][2] = cars[i][2];
        v1[0] = cars[i][0] / 2.0 + cars[i][1] * 5.0;
        v1[1] = cars[i][0] / 2.0 - cars[i][1] * 5.0;
        v1[2] = cars[i][2];
        solv_de(v1,v2);
        cars[i][0] = v2[0] + v2[1];
        cars[i][1] = (v2[0] - v2[1]) / 10.0;
        cars[i][2] = v2[2];

        if ((cars[i][0] < -16.97 || cars[i][0] > 16.97) 
             && carsp[i][2] < 27.0 && cars[i][2] > 27.0 ) carlap[i]++;
    }
}

void init_cars(void)  /* 解の初期値設定 */
{
    int i;
    double r;

    for(i=0; i<CARS; i++) {
        r = (double) rand() / (RAND_MAX+1) - 0.5;
        cars[i][0] = r * 10.0;
        cars[i][1] = 0.0;
        cars[i][2] = 40.0;

        carlap[i]=0;
    }
    move_cars();
}

void init(void)
{
    time_t tp;
    char time_c[100];

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    srand ((unsigned int) time(&tp));

    make_lane();

    init_cars();
}

void idle(void)
{
    move_cars();

    glutPostRedisplay();
}

void set_sight(void)
{
    int i;
    double u1[3], ur[3], ue[3];
    double rr;

    if (vall == 1) {           /* 視点を上方遠方に固定 */
        glLoadIdentity();
        gluLookAt(0.0,100.0,30.0, 0.0,0.0,30.0, 0.0,0.0,1.0);
    } else {
        for(i=0; i<3; i++) {
            u1[i] = carsp[car_num][i];
            ur[i] = cars[car_num][i] - u1[i];
        }
        rr = sqrt(ur[0]*ur[0]+ur[1]*ur[1]+ur[2]*ur[2]);
        for(i=0; i<3; i++)
            ue[i] = u1[i] - (double)zoom * ur[i] / rr;
        ue[1] += (double)(zoom * vht);
        glLoadIdentity();
        gluLookAt(ue[0],ue[1],ue[2], u1[0],u1[1],u1[2], 0.0,1.0,0.0);
    }
}

void set_light(void)
{
    GLfloat light_ambient[] = { 0.2,0.2,0.2,1.0 };
    GLfloat light_position0[] = {  17.0, 50.0, 27.0, 1.0 };
    GLfloat light_position1[] = { -17.0,-50.0, 27.0, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
}

void display(void)
{
    int i;
    GLfloat mat_diffuse1[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_diffuse[6][4]= {{1.0, 0.2, 0.2, 1.0},
                                {0.2, 1.0, 0.2, 1.0},
                                {0.2, 0.2, 1.0, 1.0},
                                {1.0, 1.0, 0.2, 1.0},
                                {1.0, 0.2, 1.0, 1.0},
                                {0.2, 1.0, 1.0, 1.0}};

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    set_sight();

    set_light();

    /* 解軌道を点線で表示 */
    glBegin(GL_LINE_STRIP);
    for(i=0; i < DATA_SIZE; i++) {
        glColor3dv(lanecolor[i]);
        glVertex3dv (lane[i]);
    }
    glEnd();

    glEnable(GL_LIGHTING);

    /* 解軌道上の点をトーラスで表示 */
    for(i=0; i<CARS; i++) {
        glPushMatrix();
        glTranslated(cars[i][0],cars[i][1],cars[i][2]);
        glRotated(90.0, 1.0, 0.0, 0.0);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse[i % 6]);
        if (vall == 0) glutSolidTorus(0.04, 0.2, 4, 3+carlap[i]/5);
                  else glutSolidSphere(0.4, 10,10);
        glPopMatrix();
    }

    /* 方程式の2個の平衡点を球で表示 */
    glPushMatrix();
    glTranslated(16.97, 0.0, 27.0);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);
    glutSolidSphere(0.2*(1+vall*2),20,20);
    glPopMatrix();
    glPushMatrix();
    glTranslated(-16.97, 0.0, 27.0);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);
    glutSolidSphere(0.2*(1+vall*2),20,20);
    glPopMatrix();

    glDisable(GL_LIGHTING);

    glutSwapBuffers();
}


void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, (GLfloat)w/(GLfloat)h, 1.0, 500.0);
}

void quit(void)
{
    int i;
    double x,y,r;

    printf("Laps of the Tori:\n");
    for(i=0; i<CARS; i++) {
        if (cars[i][0] > 0.0) x =   cars[i][0] - 16.97;
                         else x = - cars[i][0] - 16.97;
            y = cars[i][2] - 27.0;
        r = atan2(y,x) / 6.2832;
        if (r < 0.0) r = r+1.0;

        printf("%1d : %3d laps and %3d%%\n", i+1,carlap[i],(int)(r*100));
    }
    exit(0);
}

void keyboard(unsigned char key, int x, int y)
{
    switch(key) {
         case 27:  /* [ESC] プログラムの終了 */
             quit();
             break;
         case 's':  /* アニメーション一時停止 */
             glutIdleFunc(NULL);
             break;
         case 'g':  /* アニメーション開始 */
             glutIdleFunc(idle);
             break;
         case ' ':  /* (停止時に)1コマ進める */
             idle();
             break;
         case '0':  /* 視点を上方遠方にする */
             vall = 1;
             glutPostRedisplay();
             break;
         case '1':  /* 視点を1番の車にする */
             vall = 0;
             car_num = 0;
             glutPostRedisplay();
             break;
         case '2':  /* 視点を2番の車にする */
             vall = 0;
             car_num = 1;
             glutPostRedisplay();
             break;
         case '3':  /* 視点を3番の車にする */
             vall = 0;
             car_num = 2;
             glutPostRedisplay();
             break;
         case '4':  /* 視点を4番の車にする */
             vall = 0;
             car_num = 3;
             glutPostRedisplay();
             break;
         case '5':  /* 視点を5番の車にする */
             vall = 0;
             car_num = 4;
             glutPostRedisplay();
             break;
         case '6':  /* 視点を6番の車にする */
             vall = 0;
             car_num = 5;
             glutPostRedisplay();
             break;
         case 'u':  /* 視点を上にずらす */
             if (vall == 0) {
                 vht += 0.2; if(vht > 1.1) vht = 1.1;
                 glutPostRedisplay();
             }
             break;
         case 'd':  /* 視点を下にずらす */
             if (vall == 0) {
                 vht -= 0.2; if (vht < -1.1) vht = -1.1;
                 glutPostRedisplay();
             }
             break;
         case '+':  /* ズームイン */
             if (vall == 0) {
                 zoom = zoom / 2; if (zoom < 2) zoom = 2;
                 glutPostRedisplay();
             }
             break;
         case '-':  /* ズームアウト */
             if (vall == 0) {
                 zoom = zoom * 2; if (zoom > 128) zoom = 128;
                 glutPostRedisplay();
             }
             break;
    }
}

void param_vp(int sel)
{
    switch(sel) {
        case 9: vall = 1; break;
        case 1: vall = 0; car_num = 0; break;
        case 2: vall = 0; car_num = 1; break;
        case 3: vall = 0; car_num = 2; break;
        case 4: vall = 0; car_num = 3; break;
        case 5: vall = 0; car_num = 4; break;
        case 6: vall = 0; car_num = 5; break;
    }
    glutPostRedisplay();
    if (vall == 1) {
        glutChangeToMenuEntry(8,"",9);
        glutChangeToMenuEntry(9,"",9);
    } else {
        glutChangeToSubMenu(8,"Height",vh);
        glutChangeToSubMenu(9,"Zoom",zm);
    }
}

void param_vh(int sel)
{
    switch(sel) {
        case  1: vht =  1.1; break;
        case  2: vht =  0.9; break;
        case  3: vht =  0.7; break;
        case  4: vht =  0.5; break;
        case  5: vht =  0.3; break;
        case  6: vht =  0.1; break;
        case  7: vht = -0.1; break;
        case  8: vht = -0.3; break;
        case  9: vht = -0.5; break;
        case 10: vht = -0.7; break;
        case 11: vht = -0.9; break;
        case 12: vht = -1.1; break;
    }
    glutPostRedisplay();
}

void param_zm(int sel)
{
    switch(sel) {
        case  1: zoom =   2; break;
        case  2: zoom =   4; break;
        case  3: zoom =   8; break;
        case  4: zoom =  16; break;
        case  5: zoom =  32; break;
        case  6: zoom =  64; break;
        case  7: zoom = 128; break;
    }
    glutPostRedisplay();
}

void param_al(int sel)
{
    switch(sel) {
        case  1:  /* Pause */
            glutIdleFunc(NULL);
            glutChangeToMenuEntry(2,"Restart",2);
            glutChangeToMenuEntry(3,"Forward",3);
            break;
        case  2:  /* Restart */
            glutIdleFunc(idle);
            glutChangeToMenuEntry(2,"Pause",1);
            glutChangeToMenuEntry(3,"",4);
            break;
        case  3:  /* Forward */
            idle();
            break;
        case  4:  /* Nothing */
            break;
        case  9:  /* Quit */
            quit();
            break;
    }
    glutPostRedisplay();
}

void menu(void)
{
    vh = glutCreateMenu(param_vh);
    glutAddMenuEntry("High",1);
    glutAddMenuEntry("/\\",2);
    glutAddMenuEntry(" .",3);
    glutAddMenuEntry(" .",4);
    glutAddMenuEntry(" -",5);
    glutAddMenuEntry(" .",6);
    glutAddMenuEntry(" .",7);
    glutAddMenuEntry(" .",8);
    glutAddMenuEntry(" .",9);
    glutAddMenuEntry(" .",10);
    glutAddMenuEntry("\\/",11);
    glutAddMenuEntry("Low",12);

    zm = glutCreateMenu(param_zm);
    glutAddMenuEntry("Near",1);
    glutAddMenuEntry("/\\",2);
    glutAddMenuEntry(" -",3);
    glutAddMenuEntry(" .",4);
    glutAddMenuEntry(" .",5);
    glutAddMenuEntry("\\/",6);
    glutAddMenuEntry("Far",7);

    vp = glutCreateMenu(param_vp);
    glutAddMenuEntry("All",9);
    glutAddMenuEntry("Follow Red",1);
    glutAddMenuEntry("Follow Green",2);
    glutAddMenuEntry("Follow Blue",3);
    glutAddMenuEntry("Follow Yellow",4);
    glutAddMenuEntry("Follow Magenta",5);
    glutAddMenuEntry("Follow Cyan",6);
    glutAddMenuEntry("",7);
    glutAddMenuEntry("",7);

    glutCreateMenu(param_al);
    glutAddSubMenu("View Position",vp);
    glutAddMenuEntry("Restart",2);
    glutAddMenuEntry("Forward",3);
    glutAddMenuEntry("Quit",9);

    glutAttachMenu(GLUT_LEFT_BUTTON);
}

void main(argc, argv)
int argc;
char *argv[];
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(480,360);
    glutInitWindowPosition(50,50);
    glutCreateWindow("Race on the Lorenz Equation");

    init();
    menu();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(NULL);
    glutMainLoop();
}
