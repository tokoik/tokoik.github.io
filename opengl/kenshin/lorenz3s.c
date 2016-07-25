#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <GL/glut.h>

#define OPEN_LEN 15
#define OPEN_TIM 600

static double open_s[OPEN_LEN][OPEN_LEN][OPEN_LEN][3];
static double open_c[OPEN_LEN][OPEN_LEN][OPEN_LEN][3];
static int    open_t = 10;

#define TORUS     6
#define DATA_SIZE 10000
#define RND_TIM   100

static double lane[DATA_SIZE][3];
static double lanecolor[DATA_SIZE][3];

static double torus[TORUS][3],torusp[TORUS][3];
static int    toruslap[TORUS];

static int rndmd=1;                /* 視点位置のランダムモードのスイッチ */
static int mainr=0;                /* オープニング-メインのフラグ */
static int zoom=8;                 /* ズームのパラメーター */
static double vht=0.2;             /* 視点の高さ */
static int torus_num=0;            /* 視点を設定するトーラスの番号 */
static int vall=1;                 /* 視点の切り替えスイッチ */
static int stop=0;                 /* 一時停止-再開スイッチ */
static int winx,winy;              /* ウィンドウのサイズ */

void quit(void)
{
#ifdef STEREO
    system("/usr/gfx/setmon -n 60HZ");
#endif
    exit(0);
}

void solv_de(u,v) /* Lorenz方程式の差分化方程式の繰り返し計算 */
double u[3],v[3];
{
    static double dt = 0.005;                /* 時間間隔 */

    v[0] = u[0] + dt * (10.0 * (u[1] - u[0]));
    v[1] = u[1] + dt * (28.0 * u[0] - u[1] - u[0] * u[2]);
    v[2] = u[2] + dt * (-2.666666667 * u[2] + u[0] * u[1]);
}

void project1(u,v)
double u[3],v[3];
{
    v[0] = u[0]+u[1];
    v[1] = (u[0]-u[1])/10.0;
    v[2] = u[2];
}

void project2(u,v)
double u[3],v[3];
{
    v[0] = (u[0]+u[1]*10.0)/2.0;
    v[1] = (u[0]-u[1]*10.0)/2.0;
    v[2] = u[2];
}

o_solv_de()
{
    int i,j,k;
    double u[3],v[3];

    for(i=0; i<OPEN_LEN; i++)
        for(j=0; j<OPEN_LEN; j++)
            for(k=0; k<OPEN_LEN; k++) {
                project2(open_s[i][j][k],u);
                solv_de(u,v);
                project1(v,open_s[i][j][k]);
            }
}

void o_display(void)
{
    int i,j,k;
    double ye,ze;

    glClear(GL_COLOR_BUFFER_BIT);

    o_solv_de();

    ye = 50.0 + 50.0 * OPEN_TIM /(double)open_t;
    ze = 80.0 - 50.0 * (double)open_t / OPEN_TIM;

#ifdef STEREO
    glLoadIdentity();
    gluLookAt(0.2,ye,ze, 0.0,0.0,ze, 0.0,0.0,1.0);
    glViewport(0, 0, 1280, 492);
    glNewList(1, GL_COMPILE_AND_EXECUTE);
#else
    glLoadIdentity();
    gluLookAt(0.0,ye,ze, 0.0,0.0,ze, 0.0,0.0,1.0);
#endif

    glBegin(GL_POINTS);
    for(i=0; i<OPEN_LEN; i++)
        for(j=0; j<OPEN_LEN; j++)
            for(k=0; k<OPEN_LEN; k++) {
                glColor3dv(open_c[i][j][k]);
                glVertex3dv(open_s[i][j][k]);
            }
    glEnd();

#ifdef STEREO
    glEndList();
    glLoadIdentity();
    gluLookAt(-0.2,ye,ze, 0.0,0.0,ze, 0.0,0.0,1.0);
    glViewport(0, 532, 1280, 492);
    glCallList(1);
#endif

    glutSwapBuffers();
}


void make_lane(void) /* 解曲線のデータ作成 */
{
    int  i,j;
    double v1[3],v2[3];
    GLdouble c1,c2,c3;

    v1[0] = 2.0; v1[1] = 2.0; v1[2] = 2.0;             /* 初期値 */

    for(i=0; i<300; i++) {                       /* 初期の空回し */
        solv_de(v1,v2);
        for (j=0; j<3; j++) v1[j] = v2[j];
    }
    
    for(i=0; i < DATA_SIZE; i++) {       /* データを計算して保存 */
        solv_de(v1,v2);
        project1(v2,lane[i]);
        for (j=0; j<3; j++) v1[j] = v2[j];

        c1 = (lane[i][0]+lane[i][1]) / 100.0 + 0.5;
        c2 = 4.0 * (double)i * (DATA_SIZE - i) / DATA_SIZE / DATA_SIZE;
        c3 = lane[i][2] / 100.0;
        lanecolor[i][0] = c2*c3;
        lanecolor[i][1] = c2*(1.0-c1);
        lanecolor[i][2] = c2*c1;
    }
}

void move_torus(void)
{
    int i;
    double v1[3],v2[3];

    for(i=0; i<TORUS; i++) {
        torusp[i][0] = torus[i][0];
        torusp[i][1] = torus[i][1];
        torusp[i][2] = torus[i][2];

        project2(torus[i],v1);
        solv_de(v1,v2);
        project1(v2,torus[i]);

        if ((torus[i][0] < -16.97 || torus[i][0] > 16.97) 
             && torusp[i][2] < 27.0 && torus[i][2] > 27.0 ) toruslap[i]++;
    }
}

void init_torus(void)  /* トーラスの初期位置 */
{
    int i;
    double r;

    for(i=0; i<TORUS; i++) {
        r = (double) rand() / (RAND_MAX+1) - 0.5;
        torus[i][0] = r * 15.0;
        torus[i][1] = 0.0;
        r = (double) rand() / (RAND_MAX+1) - 0.5;
        torus[i][2] = 30.0 + r * 10.0;

        toruslap[i]=0;
    }
    move_torus();
}

void init_opening(void)
{
    int  i,j,k;

    for(i=0; i< OPEN_LEN; i++)
        for(j=0; j< OPEN_LEN; j++)
            for(k=0; k< OPEN_LEN; k++) {
                open_s[i][j][k][0]= (double)(i*2-OPEN_LEN)+0.5;
                open_s[i][j][k][1]= (double)(j*2-OPEN_LEN)+0.5;
                open_s[i][j][k][2]= (double)(k*2-OPEN_LEN)+0.5;
                open_c[i][j][k][0]= (double)(i*2+OPEN_LEN)/(OPEN_LEN*3);
                open_c[i][j][k][1]= (double)(j*2+OPEN_LEN)/(OPEN_LEN*3);
                open_c[i][j][k][2]= (double)(k*2+OPEN_LEN)/(OPEN_LEN*3);
            }
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);

    init_opening();

    srand ((unsigned int) time(NULL));
    make_lane();
    init_torus();
}

void idle(void)
{
    if (mainr > 0) move_torus();

    glutPostRedisplay();
}

void set_sight(double offset)
{
    int i;
    double u1[3], ur[3], ue[3];
    double rr;

    if (vall == 1) {                        /* 視点を正面遠方に固定 */
        glLoadIdentity();
        gluLookAt(offset,100.0,30.0, 0.0,0.0,30.0, 0.0,0.0,1.0);
    } else {                            /* 視点をトーラス後方に設定 */
        for(i=0; i<3; i++) {
            u1[i] = torusp[torus_num][i];
            ur[i] = torus[torus_num][i] - u1[i];
        }
        rr = sqrt(ur[0]*ur[0]+ur[2]*ur[2]);

        ue[0] = u1[0] - (double)zoom * ur[0] / rr * cos(vht)
                      + offset * ur[2] / rr;
        ue[2] = u1[2] - (double)zoom * ur[2] / rr * cos(vht)
                      - offset * ur[0] / rr;
        ue[1] = u1[1] + (double)zoom * sin(vht);

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

void m_display(void)
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

#ifdef STEREO
    set_sight(0.2);
    glViewport(0, 0, 1280, 492);
    glNewList(1, GL_COMPILE_AND_EXECUTE);
#else
    set_sight(0.0);
#endif

    set_light();

    /* 解曲線を表示 */
    glBegin(GL_LINE_STRIP);
    for(i=0; i < DATA_SIZE; i++) {
        glColor3dv(lanecolor[i]);
        glVertex3dv (lane[i]);
    }
    glEnd();

    glEnable(GL_LIGHTING);

    /* 解曲線上の点をトーラスで表示 */
    for(i=0; i<TORUS; i++) {
        glPushMatrix();
        glTranslated(torus[i][0],torus[i][1],torus[i][2]);
        glRotated(90.0, 1.0, 0.0, 0.0);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse[i % 6]);
        if (vall == 0) glutSolidTorus(0.04, 0.2, 4, 3+toruslap[i]/5);
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

#ifdef STEREO
    glEndList();

    set_sight(-0.2);
    glViewport(0, 532, 1280, 492);

    glCallList(1);
#endif

    glutSwapBuffers();
}

void rnd_view(void)
{
    double r;

    r = (double) rand() / (RAND_MAX+1);
    if (r < 0.1) vall = 1;
    else {
        vall = 0;
        r = (double) rand() / (RAND_MAX+1);
        torus_num = r * TORUS;
        r = (double) rand() / (RAND_MAX+1);
        vht = 0.2 + (r-0.5)*1.2;
        r = (double) rand() / (RAND_MAX+1);
        zoom = pow(2.0, r*6.0+1.0);
    }
}

void display(void)
{
    if (mainr > 0) {
        m_display(); open_t++;
        if (open_t == OPEN_TIM+RND_TIM) {
            open_t=OPEN_TIM;
            if (rndmd == 1) rnd_view();
        }
    } else if(open_t < OPEN_TIM) {
        o_display(); open_t++;
    } else {
        mainr = 1;
        m_display();
        glShadeModel(GL_SMOOTH);
        glEnable(GL_DEPTH_TEST);
    }
}

void reshape(int w, int h)
{
    winx = w; winy = h;
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, (GLfloat)w/(GLfloat)h, 1.0, 3000.0);
    glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y)
{
    if (mainr == 0) return;

    switch(button) {
        case GLUT_LEFT_BUTTON:
            if(state == GLUT_UP && y > winy*0.2 && y < winy*0.8
                                && x > winx*0.2 && x < winx*0.8) {
                if (stop == 1) {
                    stop = 0;
                    glutIdleFunc(idle);
                } else {
                    stop = 1;
                    glutIdleFunc(NULL);
                }
            }
            if(state == GLUT_UP && vall == 0 && rndmd == 0) {
                if (y < winy*0.2) {
                    vht += 0.1; if(vht > 0.75) vht = 0.8;
                    glutPostRedisplay();
                } else if (y > winy*0.8) {
                    vht -= 0.1; if (vht < -0.75) vht = -0.8;
                    glutPostRedisplay();
                } else if (x < winx*0.2) {
                    zoom = zoom / 2; if (zoom < 2) zoom = 2;
                    glutPostRedisplay();
                } else if (x > winx*0.8) {
                    zoom = zoom * 2; if (zoom > 128) zoom = 128;
                    glutPostRedisplay();
                }
            }
            break;
        case GLUT_RIGHT_BUTTON:
            if(state == GLUT_UP) {
                if (rndmd == 1) {
                    printf("random eye position mode off\n");
                    rndmd = 0; vall = 1;
                } else if (vall == 1) {
                    vall = 0;
                    torus_num = 0;
                    printf("following the torus No.%d\n",torus_num+1);
                } else {
                    torus_num++ ;
                    if (torus_num == TORUS) {
                        rndmd = 1;
                        printf("random eye position mode on\n");
                    } else printf("following the torus No.%d\n",torus_num+1);
                }
                glutPostRedisplay();
            }
            break;
    }
}

void keyboard(unsigned char key, int x, int y)
{
    if (mainr > 0) {
        switch(key) {
            case 27:  /* [ESC] プログラムの終了 */
            case 'q':
                quit();
                break;
            case 's':  /* アニメーション一時停止 */
                stop = 1;
                glutIdleFunc(NULL);
                break;
            case 'g':  /* アニメーション開始 */
                stop = 0;
                glutIdleFunc(idle);
                break;
            case ' ':  /* (停止時に)1コマ進める */
                idle();
                break;
            case '0':  /* 視点を上方遠方にする */
                rndmd = 0;
                vall = 1;
                glutPostRedisplay();
                break;
            case '1':  /* 視点を1番の車にする */
                rndmd = 0;
                vall = 0;
                torus_num = 0;
                glutPostRedisplay();
                break;
            case '2':  /* 視点を2番の車にする */
                rndmd = 0;
                vall = 0;
                torus_num = 1;
                glutPostRedisplay();
                break;
            case '3':  /* 視点を3番の車にする */
                rndmd = 0;
                vall = 0;
                torus_num = 2;
                glutPostRedisplay();
                break;
            case '4':  /* 視点を4番の車にする */
                rndmd = 0;
                vall = 0;
                torus_num = 3;
                glutPostRedisplay();
                break;
            case '5':  /* 視点を5番の車にする */
                rndmd = 0;
                vall = 0;
                torus_num = 4;
                glutPostRedisplay();
                break;
            case '6':  /* 視点を6番の車にする */
                rndmd = 0;
                vall = 0;
                torus_num = 5;
                glutPostRedisplay();
                break;
            case 'u':  /* 視点を上にずらす */
                if (vall == 0 && rndmd == 0) {
                    vht += 0.1; if(vht > 0.75) vht = 0.8;
                    glutPostRedisplay();
                }
                break;
            case 'd':  /* 視点を下にずらす */
                if (vall == 0 && rndmd == 0) {
                    vht -= 0.1; if (vht < -0.75) vht = -0.8;
                    glutPostRedisplay();
                }
                break;
            case '+':  /* ズームイン */
                if (vall == 0 && rndmd == 0) {
                    zoom = zoom / 2; if (zoom < 2) zoom = 2;
                    glutPostRedisplay();
                }
                break;
            case '-':  /* ズームアウト */
                if (vall == 0 && rndmd == 0) {
                    zoom = zoom * 2; if (zoom > 128) zoom = 128;
                    glutPostRedisplay();
                }
                break;
            case 'r':  /* 視点のランダムモード切替 */
                rndmd = 1;
                break;
        }
    }
}

void main(int argc, char *argv[])
{
#ifdef STEREO
    system("/usr/gfx/setmon -n STR_RECT");
#endif
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(480,360);
    glutInitWindowPosition(50,50);
    glutCreateWindow("Lorenz Attractor");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutIdleFunc(idle);
#ifdef STEREO
    glutFullScreen();
#endif
    glutMainLoop();
}
