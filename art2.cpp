#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#define WINDOW_X (1200)
#define WINDOW_Y (1200)
#define WINDOW_NAME "art"

void init_GL(int argc, char *argv[]);
void init();
void set_callback_functions();

void glut_display();
void glut_keyboard(unsigned char key, int x, int y);
void glut_mouse(int button, int state, int x, int y);
void glut_motion(int x, int y);

void daikei6();
void daikei4();
void daikei5();

// グローバル変数
double g_angle1 = 0.0;
double g_angle2 = 0.0;
double g_distance = 20.0;
bool g_isLeftButtonOn = false;
bool g_isRightButtonOn = false;
double current_x = 10.0;
double current_y = 1.5;
double current_z = 10.0;

GLfloat facecolor10[] = {1.0f, 0.0f, 0.0f, 1.0f}; //赤
GLfloat facecolor20[] = {1.0f, 1.0f, 0.0f, 1.0f}; //黃
GLfloat facecolor30[] = {0.0f, 0.0f, 1.0f, 1.0f}; //青
GLfloat facecolor40[] = {0.0f, 0.5f, 0.5f, 1.0f}; //謎

int main(int argc, char *argv[]){
	/* OpenGLの初期化 */
	init_GL(argc,argv);

	/* このプログラム特有の初期化 */
	init();

	/* コールバック関数の登録 */
	set_callback_functions();

	/* メインループ */
	glutMainLoop();

	return 0;
}

void init_GL(int argc, char *argv[]){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_X,WINDOW_Y);
	glutCreateWindow(WINDOW_NAME);
}

void init(){
	//glClearColor(0.574, 0.0, 0.465, 0.0); 
	glClearColor(0.2, 0.4, 0.2, 0.0);
}

void set_callback_functions(){
	glutDisplayFunc(glut_display);
	glutKeyboardFunc(glut_keyboard);
	glutMouseFunc(glut_mouse);
	glutMotionFunc(glut_motion);
	glutPassiveMotionFunc(glut_motion);
}

void glut_keyboard(unsigned char key, int x, int y){
	switch(key){
	case 'k':
		printf("%lf, %lf, %lf\n", g_distance, g_angle1, g_angle2);
		break;

	case 'p':
		g_distance = 23.475;
		g_angle1 = -19.725;
		g_angle2 = 6.95;
		break;

	case 'q':
	case 'Q':
	case '\033':
		exit(0);
	}
	glutPostRedisplay();
}

void glut_mouse(int button, int state, int x, int y){
	if(button == GLUT_LEFT_BUTTON){
		if(state == GLUT_UP){
			g_isLeftButtonOn = false;
		}else if(state == GLUT_DOWN){
			g_isLeftButtonOn = true;
		}
	}

	if(button == GLUT_RIGHT_BUTTON){
		if(state == GLUT_UP){
			g_isRightButtonOn = false;
		}else if(state == GLUT_DOWN){
			g_isRightButtonOn = true;
		}
	}
}

void glut_motion(int x, int y){
	static int px = -1, py = -1;
	if(g_isLeftButtonOn == true){
		if(px >= 0 && py >= 0){
			g_angle1 += (double)-(x - px)/40;
			g_angle2 += (double)(y - py)/40;
		}
		px = x;
		py = y;
	}else if(g_isRightButtonOn == true){
		if(px >= 0 && py >= 0){
			g_distance += (double)(y - py)/40;
		}
		px = x;
		py = y;
	}else{
		px = -1;
		py = -1;
	}
	glutPostRedisplay();
}

void glut_display(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, 1.0, 0.1, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if (cos(g_angle2)>0){
	gluLookAt(g_distance * cos(g_angle2) * sin(g_angle1),
		g_distance * sin(g_angle2),
		g_distance * cos(g_angle2) * cos(g_angle1),
		0.0, 0.0, 0.0, 0.0, 1.0, 0.0);}
	else{
	gluLookAt(g_distance * cos(g_angle2) * sin(g_angle1),
                g_distance * sin(g_angle2),
                g_distance * cos(g_angle2) * cos(g_angle1),
                0.0, 0.0, 0.0, 0.0, -1.0, 0.0);}

	GLfloat lightpos[] = {10*cosf((float)g_angle2) * sinf((float)g_angle1),
		10*sinf((float)g_angle2),
		10*cosf((float)g_angle2) * cosf((float)g_angle1),
		1.0f};

    GLfloat diffuse[] = {1.0, 1.0, 1.0, 1.0};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

    glPushMatrix();
    glScalef(0.5, 0.5, 0.5);
    glTranslatef(5.0, -4.0, 0.0);
    daikei6();
    glPopMatrix();

    glPushMatrix();
    glScalef(0.5, 0.5, 0.5);
    glTranslatef(5.0, -4.0, 0.0);
    daikei4();
    glPopMatrix();

    glPushMatrix();
    glScalef(0.5, 0.5, 0.5);
    glTranslatef(5.0, -4.0, 0.0);
    daikei5();
    glPopMatrix();

	glFlush();
	glDisable(GL_DEPTH_TEST);

	glutSwapBuffers();
}

void daikei6(){
 glBegin(GL_QUADS);

 //右
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor10);
 glNormal3f(1.0,0.0,0.0);
 glVertex3f(1.7,1.7,1.7);
 glVertex3f(1.7, 1.7, -10.7);
 glVertex3f(1.7, 0.0,-10.7);
 glVertex3f(1.7, 0.0, 1.7);

 //左
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor20);
 glNormal3f(-1.0,0.0,0.0);
 glVertex3f(0.0, 1.7, -10.7);
 glVertex3f(0.0, 1.7, 0.0);
 glVertex3f(0.0, 0.0, 0.0);
 glVertex3f(0.0, 0.0, -10.7);

 //後
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor40);
 glNormal3f(0.0,0.0,-1.0);
 glVertex3f(1.7, 1.7, -10.7);
 glVertex3f(0.0, 1.7, -10.7);
 glVertex3f(0.0, 0.0, -10.7);
 glVertex3f(1.7, 0.0, -10.7);

 //上
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor30);
 glNormal3f(0.0,1.0,0.0);
 glVertex3f(1.7, 1.7, 1.7);
 glVertex3f(0.0, 1.7, 0.0);
 glVertex3f(0.0, 1.7, -10.7);
 glVertex3f(1.7, 1.7, -10.7);

 //下
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor20);
 glNormal3f(0.0,-1.0,0.0);
 glVertex3f(1.7, 0.0, 1.7);
 glVertex3f(0.0, 0.0, 0.0);
 glVertex3f(0.0, 0.0, -10.7);
 glVertex3f(1.7, 0.0, -10.7);
 glEnd();
}

void daikei4(){
 glBegin(GL_QUADS);

 // 前
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor10);
 glNormal3f(0.0,0.0,1.0);
 glColor3f(1.0, 0.0, 0.0);
 glVertex3f(1.7, 1.7, 1.7);
 glVertex3f(-8.7, 1.7, 1.7);
 glVertex3f(-8.7, 0.0, 1.7);
 glVertex3f(1.7, 0.0, 1.7);

 //後
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor20);
 glNormal3f(0.0,0.0,-1.0);
 glVertex3f(0.0, 1.7, 0.0);
 glVertex3f(-8.7, 1.7, 0.0);
 glVertex3f(-8.7, 0.0, 0.0);
 glVertex3f(0.0, 0.0, 0.0);

 //上
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor30);
 glNormal3f(0.0,1.0,0.0);
 glVertex3f(1.7, 1.7, 1.7);
 glVertex3f(0.0, 1.7, 0.0);
 glVertex3f(-8.7, 1.7, 0.0);
 glVertex3f(-8.7, 1.7, 1.7);

 //下
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor20);
 glNormal3f(0.0,-1.0,0.0);
 glVertex3f(1.7, 0.0, 1.7);
 glVertex3f(0.0, 0.0, 0.0);
 glVertex3f(-8.7, 0.0, 0.0);
 glVertex3f(-8.7, 0.0, 1.7);
 glEnd();
}

void daikei5(){
 glBegin(GL_QUADS);

 //前
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor10);
 glNormal3f(0.0,0.0,1.0);
 glVertex3f(-8.7, 8.6, 1.7);
 glVertex3f(-8.7, 0.0, 1.7);
 glVertex3f(-10.4, 0.0, 1.7);
 glVertex3f(-10.4, 10.4, 1.7);

 //右
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor30);
 glNormal3f(1.0,0.0,0.0);
 glVertex3f(-8.7,8.6,1.7);
 glVertex3f(-8.7, 8.6, 0.0);
 glVertex3f(-8.7, 0.0,0.0);
 glVertex3f(-8.7, 0.0, 1.7);

 //左
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor20);
 glNormal3f(-1.0,0.0,0.0);
 glVertex3f(-10.4,10.4,1.7);
 glVertex3f(-10.4, 10.4, 0.0);
 glVertex3f(-10.4, 0.0,0.0);
 glVertex3f(-10.4, 0.0, 1.7);

 //後
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor40);
 glNormal3f(0.0,0.0,-1.0);
 glVertex3f(-8.7, 8.6, 0.0);
 glVertex3f(-8.7, 0.0, 0.0);
 glVertex3f(-10.4, 0.0, 0.0);
 glVertex3f(-10.4, 10.4, 0.0);

 //上
 glNormal3f(1.0,1.0,0.0);
 glVertex3f(-8.7, 8.6, 1.7);
 glVertex3f(-8.7, 8.6, 0.0);
 glVertex3f(-10.4, 10.4, 0.0);
 glVertex3f(-10.4, 10.4, 1.7);

 //下
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor20);
 glNormal3f(0.0,-1.0,0.0);
 glVertex3f(-8.7, 0.0, 1.7);
 glVertex3f(-10.4, 0.0, 1.7);
 glVertex3f(-10.4, 0.0, 0.0);
 glVertex3f(-8.7, 0.0, 0.0);
 glEnd();
}