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

void cuboid(float width,float height,float depth);
void daikein1();
void daikein2();
void daikein3();

// グローバル変数
double g_angle1 = 0.0;
double g_angle2 = 0.0;
double g_distance = 20.0;
bool g_isLeftButtonOn = false;
bool g_isRightButtonOn = false;
double current_x = 10.0;
double current_y = 1.5;
double current_z = 10.0;
GLfloat facecolor400[] = {1.0f, 1.00f, 1.0f, 1.0f};

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
	glClearColor(0.4, 0.4, 0.6, 0.0);         // 背景の塗りつぶし色を指定
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

	case 'o':
		g_distance = 20.000000;
		g_angle1 = -0.500000;
		g_angle2 = 0.60000;
		break;

	case 'p':
		g_distance = 20.0;
		g_angle1 = 1.0;
		g_angle2 = 1.275;
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

	// 1面
    glPushMatrix();
    glScalef(1.3, 1.3, 1.3);
    glTranslatef(-1.5, -1.4, 0.0);
    glPushMatrix();
    cuboid(0.5, 2.6, 0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.5, 0.075, 0.0);
    cuboid(0.7, 2.75, 0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1.2, 0.15, 0.0);
    cuboid(0.7, 2.9, 0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1.7, 0.275, 0.0);
    cuboid(0.5, 3.15, 0.5);
    glPopMatrix();

    // 2面
    glPushMatrix();
    glTranslatef(1.7, 0.35, -0.5);
    cuboid(0.5, 3.3, 0.7);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1.7, 0.425, -1.2);
    cuboid(0.5, 3.45, 0.7);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1.7, 0.5, -1.7);
    cuboid(0.5, 3.6, 0.5);
    glPopMatrix();

    // 3面
    glPushMatrix();
    glTranslatef(1.075, 0.6, -1.7);
    cuboid(0.75, 3.8, 0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.575, 0.7, -1.7);
    cuboid(0.5, 4.0, 0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.26, -1.3, -0.235);
    daikein1();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.26, -1.3, -0.235);
    daikein2();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.26, -1.3, -0.235);
    daikein3();
    glPopMatrix();
    glPopMatrix();

	glFlush();
	glDisable(GL_DEPTH_TEST);

	glutSwapBuffers();
}

void cuboid(float width,float height,float depth)
{
 glBegin(GL_QUADS);
 //前
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor400);
 glNormal3f(0.0,0.0,1.0);
 glVertex3f(width/2,height/2,depth/2);
 glVertex3f(-width/2,height/2,depth/2);
 glVertex3f(-width/2,-height/2,depth/2);
 glVertex3f(width/2,-height/2,depth/2);

 //左
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor400);
 glNormal3f(1.0,0.0,0.0);
 glVertex3f(width/2,height/2,depth/2);
 glVertex3f(width/2,height/2,-depth/2);
 glVertex3f(width/2,-height/2,-depth/2);
 glVertex3f(width/2,-height/2,depth/2);

 //右
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor400);
 glNormal3f(-1.0,0.0,0.0);
 glVertex3f(-width/2,height/2,-depth/2);
 glVertex3f(-width/2,height/2,depth/2);
 glVertex3f(-width/2,-height/2,depth/2);
 glVertex3f(-width/2,-height/2,-depth/2);

 //後
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor400);
 glNormal3f(0.0,0.0,-1.0);
 glVertex3f(width/2,height/2,-depth/2);
 glVertex3f(-width/2,height/2,-depth/2);
 glVertex3f(-width/2,-height/2,-depth/2);
 glVertex3f(width/2,-height/2,-depth/2);

 //上
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor400);
 glNormal3f(0.0,1.0,0.0);
 glVertex3f(width/2,height/2,depth/2);
 glVertex3f(-width/2,height/2,depth/2);
 glVertex3f(-width/2,height/2,-depth/2);
 glVertex3f(width/2,height/2,-depth/2);

 //下
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor400);
 glNormal3f(0.0,-1.0,0.0);
 glVertex3f(width/2,-height/2,depth/2);
 glVertex3f(-width/2,-height/2,depth/2);
 glVertex3f(-width/2,-height/2,-depth/2);
 glVertex3f(width/2,-height/2,-depth/2);
 glEnd();

}

void daikein2(){
 glBegin(GL_QUADS);

 // 前
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor400);
 glNormal3f(0.0,0.0,1.0);
 glVertex3f(0.22, 0.0, -0.445);
 glVertex3f(0.22, 3.0, -0.445);
 glVertex3f(0.72, 3.0, -0.445);
 glVertex3f(0.72, 0.0, -0.445);

 //右
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor400);
 glNormal3f(1.0,0.0,0.0);
 glVertex3f(0.72,0.0,-0.445);
 glVertex3f(0.72,3.0, -0.445);
 glVertex3f(0.9198, 3.6,-0.8537);
 glVertex3f(0.9198, 0.0, -0.8537);

 //左
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor400);
 glNormal3f(-1.0,0.0,0.0);
 glVertex3f(0.22,0.0,-0.445);
 glVertex3f(0.22,3.0, -0.445);
 glVertex3f(0.4198, 3.6,-0.8537);
 glVertex3f(0.4198, 0.0, -0.8537);

 //後
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor400);
 glNormal3f(0.0,0.0,-1.0);
 glVertex3f(0.9198, 0.0, -0.8537);
 glVertex3f(0.9198, 3.6,-0.8537);
 glVertex3f(0.4198, 3.6,-0.8537);
 glVertex3f(0.4198, 0.0, -0.8537);

 //上
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor400);
 glNormal3f(0.0,0.65,0.76);
 glVertex3f(0.72,3.0, -0.445);
 glVertex3f(0.9198, 3.6,-0.8537);
 glVertex3f(0.4198, 3.6,-0.8537);
 glVertex3f(0.22, 3.0, -0.445);

 //下
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor400);
 glNormal3f(0.0,-1.0,0.0);
 glVertex3f(0.72,0.0, -0.445);
 glVertex3f(0.9198, 0.0,-0.8537);
 glVertex3f(0.4198, 0.0,-0.8537);
 glVertex3f(0.22, 0.0, -0.445);
 glEnd();
}

void daikein1(){
 glBegin(GL_QUADS);

 // 前
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor400);
 glNormal3f(0.0,0.0,1.0);
 glVertex3f(0.0, 0.0, 0.0);
 glVertex3f(0.0, 2.42, 0.0);
 glVertex3f(0.5, 2.42, 0.0);
 glVertex3f(0.5, 0.0, 0.0);

 //右
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor400);
 glNormal3f(1.0,0.0,0.0);
 glVertex3f(0.5,0.0,0.0);
 glVertex3f(0.5,2.42, 0.0);
 glVertex3f(0.72, 3.1,-0.445);
 glVertex3f(0.72, 0.0, -0.445);

 //左
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor400);
 glNormal3f(-1.0,0.0,0.0);
 glVertex3f(0.0,0.0,0.0);
 glVertex3f(0.0,2.42, 0.0);
 glVertex3f(0.22, 3.1,-0.445);
 glVertex3f(0.22, 0.0, -0.445);

 //後
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor400);
 glNormal3f(0.0,0.0,-1.0);
 glVertex3f(0.22, 0.0, -0.445);
 glVertex3f(0.22, 3.1, -0.445);
 glVertex3f(0.72, 3.1, -0.445);
 glVertex3f(0.72, 0.0, -0.445);

 //上
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor400);
 glNormal3f(0.0,0.65,0.76);
 glVertex3f(0.0,2.42, 0.0);
 glVertex3f(0.5, 2.42, 0.0);
 glVertex3f(0.72, 3.1, -0.445);
 glVertex3f(0.22, 3.1, -0.445);

 //下
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor400);
 glNormal3f(0.0,-1.0,0.0);
 glVertex3f(0.0,0.0, 0.0);
 glVertex3f(0.5, 0.0, 0.0);
 glVertex3f(0.72, 0.0, -0.445);
 glVertex3f(0.22, 0.0, -0.445);
 glEnd();
}

void daikein3(){
 glBegin(GL_QUADS);

 // 前
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor400);
 glNormal3f(0.0,0.0,1.0);
 glVertex3f(0.9198, 0.0, -0.8537);
 glVertex3f(0.9198, 3.5,-0.8537);
 glVertex3f(0.4198, 3.5,-0.8537);
 glVertex3f(0.4198, 0.0, -0.8537);

 //右
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor400);
 glNormal3f(1.0,0.0,0.0);
 glVertex3f(1.1,0.0,-1.225);
 glVertex3f(1.1,4.1, -1.225);
 glVertex3f(0.9198, 3.5,-0.8537);
 glVertex3f(0.9198, 0.0, -0.8537);

 //左
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor400);
 glNormal3f(-1.0,0.0,0.0);
 glVertex3f(0.6,0.0,-1.225);
 glVertex3f(0.6,4.1, -1.225);
 glVertex3f(0.4198, 3.5,-0.8537);
 glVertex3f(0.4198, 0.0, -0.8537);


 //後
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor400);
 glNormal3f(0.0,0.0,-1.0);
 glVertex3f(1.1, 0.0, -1.225);
 glVertex3f(1.1, 4.1,-1.225);
 glVertex3f(0.6, 4.1,-1.225);
 glVertex3f(0.6, 0.0, -1.225);

 //上
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor400);
 glNormal3f(0.0,0.65,0.76);
 glVertex3f(0.9198,3.5, -0.8537);
 glVertex3f(1.1, 4.1,-1.225);
 glVertex3f(0.6, 4.1,-1.225);
 glVertex3f(0.4198, 3.5, -0.8537);

 //下
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor400);
 glNormal3f(0.0,-1.0,0.0);
 glVertex3f(0.9198,0.0, -0.8537);
 glVertex3f(1.1, 0.0,-1.225);
 glVertex3f(0.6, 0.0,-1.225);
 glVertex3f(0.4198, 0.0, -0.8537);
 glEnd();
}