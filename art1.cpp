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
void daikei();
void daikei2();
void daikei3();

// グローバル変数
double g_angle1 = 0.0;
double g_angle2 = 0.0;
double g_distance = 20.0;
bool g_isLeftButtonOn = false;
bool g_isRightButtonOn = false;
double current_x = 10.0;
double current_y = 1.5;
double current_z = 10.0;
GLfloat facecolor4[] = {0.95f, 0.975f, 0.074f, 1.0f};

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
	glClearColor(0.1485, 0.1328, 0.1211, 0.0);         // 背景の塗りつぶし色を指定
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
		g_angle2 = 0.550000;
		break;

	case 'p':
		g_distance = 15.075;
		g_angle1 = -0.500000;
		g_angle2 = 0.550000;
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

	// 穴あき直方体(上下)

    glPushMatrix();
    
    glTranslatef(0.0, 1.55, 0.0);
    daikei2();
    glPopMatrix();

    glPushMatrix();
    
    glTranslatef(0.0, 1.55, 0.0);
    daikei3();
    glPopMatrix();

    glPushMatrix();
    
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glTranslatef(0.5, 1.55, 0.5);
    daikei();
    glPopMatrix();

    glPushMatrix();
    
	glRotatef(-90.0, 0.0, 1.0, 0.0);
	glTranslatef(-0.5, 1.55, 0.5);
    daikei();
    glPopMatrix();

    glPushMatrix();
    
	glRotatef(180.0, 0.0, 1.0, 0.0);
	glTranslatef(0.0, 1.55, 1.0);
    daikei();
    glPopMatrix();

    glPushMatrix();
    
    glTranslatef(0.0, -1.55, 0.0);
    daikei();
    glPopMatrix();

    glPushMatrix();
    
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glTranslatef(0.5, -1.55, 0.5);
    daikei();
    glPopMatrix();

    glPushMatrix();
    
	glRotatef(-90.0, 0.0, 1.0, 0.0);
	glTranslatef(-0.5, -1.55, 0.5);
    daikei();
    glPopMatrix();

    glPushMatrix();
    
	glRotatef(180.0, 0.0, 1.0, 0.0);
	glTranslatef(0.0, -1.55, 1.0);
    daikei();
    glPopMatrix();

	// 4本の柱
	glPushMatrix();
	
	glTranslatef(1.25, 0.0, 0.75);
	cuboid(0.5, 3.1, 0.5);
	glPopMatrix();

	glPushMatrix();
	
	glTranslatef(-1.25, 0.0, 0.75);
	cuboid(0.5, 3.1, 0.5);
	glPopMatrix();

	glPushMatrix();
	
	glTranslatef(1.25, 0.0, -1.75);
	cuboid(0.5, 3.1, 0.5);
	glPopMatrix();

	glPushMatrix();
	
	glTranslatef(-1.25, 0.0, -1.75);
	cuboid(0.5, 3.1, 0.5);
	glPopMatrix();

	glFlush();
	glDisable(GL_DEPTH_TEST);

	glutSwapBuffers();
}

void cuboid(float width,float height,float depth)
{
 glBegin(GL_QUADS);
 //前
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor4);
 glNormal3f(0.0,0.0,1.0);
 glVertex3f(width/2,height/2,depth/2);
 glVertex3f(-width/2,height/2,depth/2);
 glVertex3f(-width/2,-height/2,depth/2);
 glVertex3f(width/2,-height/2,depth/2);

 //左
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor4);
 glNormal3f(1.0,0.0,0.0);
 glVertex3f(width/2,height/2,depth/2);
 glVertex3f(width/2,height/2,-depth/2);
 glVertex3f(width/2,-height/2,-depth/2);
 glVertex3f(width/2,-height/2,depth/2);

 //右
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor4);
 glNormal3f(-1.0,0.0,0.0);
 glVertex3f(-width/2,height/2,-depth/2);
 glVertex3f(-width/2,height/2,depth/2);
 glVertex3f(-width/2,-height/2,depth/2);
 glVertex3f(-width/2,-height/2,-depth/2);

 //後
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor4);
 glNormal3f(0.0,0.0,-1.0);
 glVertex3f(width/2,height/2,-depth/2);
 glVertex3f(-width/2,height/2,-depth/2);
 glVertex3f(-width/2,-height/2,-depth/2);
 glVertex3f(width/2,-height/2,-depth/2);

 //上
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor4);
 glNormal3f(0.0,1.0,0.0);
 glVertex3f(width/2,height/2,depth/2);
 glVertex3f(-width/2,height/2,depth/2);
 glVertex3f(-width/2,height/2,-depth/2);
 glVertex3f(width/2,height/2,-depth/2);

 //下
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor4);
 glNormal3f(0.0,-1.0,0.0);
 glVertex3f(width/2,-height/2,depth/2);
 glVertex3f(-width/2,-height/2,depth/2);
 glVertex3f(-width/2,-height/2,-depth/2);
 glVertex3f(width/2,-height/2,-depth/2);
 glEnd();

}

void daikei(){
 glBegin(GL_QUADS);

 // 前
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor4);
 glNormal3f(0.0,0.0,1.0);
 glVertex3f(1.5, 0.5, 1.0);
 glVertex3f(-1.5, 0.5, 1.0);
 glVertex3f(-1.5, 0.0, 1.0);
 glVertex3f(1.5, 0.0, 1.0);

 //右
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor4);
 glNormal3f(1.0,0.0,0.0);
 glVertex3f(1.5,0.5,1.0);
 glVertex3f(1.0, 0.5, 0.5);
 glVertex3f(1.0, 0.0,0.5);
 glVertex3f(1.5, 0.0, 1.0);

 //左
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor4);
 glNormal3f(-1.0,0.0,0.0);
 glVertex3f(-1.0, 0.5, 0.5);
 glVertex3f(-1.5, 0.5, 1.0);
 glVertex3f(-1.5, 0.0, 1.0);
 glVertex3f(-1.0, 0.0, 0.5);

 //後
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor4);
 glNormal3f(0.0,0.0,-1.0);
 glVertex3f(1.0, 0.5, 0.5);
 glVertex3f(-1.0, 0.5, 0.5);
 glVertex3f(-1.0, 0.0, 0.5);
 glVertex3f(1.0, 0.0, 0.5);

 //上
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor4);
 glNormal3f(0.0,1.0,0.0);
 glVertex3f(1.5, 0.5, 1.0);
 glVertex3f(-1.5, 0.5, 1.0);
 glVertex3f(-1.0, 0.5, 0.5);
 glVertex3f(1.0, 0.5, 0.5);

 //下
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor4);
 glNormal3f(0.0,-1.0,0.0);
 glVertex3f(1.5, 0.0, 1.0);
 glVertex3f(-1.5, 0.0,1.0);
 glVertex3f(-1.0, 0.0, 0.5);
 glVertex3f(1.0, 0.0, 0.5);
 glEnd();
}

void daikei2(){
 glBegin(GL_QUADS);

 // 前
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor4);
 glNormal3f(0.0,0.0,1.0);
 glVertex3f(-0.615, 0.5, 1.0);
 glVertex3f(-1.5, 0.5, 1.0);
 glVertex3f(-1.5, 0.0, 1.0);
 glVertex3f(-0.615, 0.0, 1.0);

 //左
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor4);
 glNormal3f(1.0,1.0,0.0);
 glVertex3f(-0.615,0.5,1.0);
 glVertex3f(-0.34, 0.5, 0.5);
 glVertex3f(-0.34, 0.0,0.5);
 glVertex3f(-0.615, 0.0, 1.0);

 //右
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor4);
 glNormal3f(1.0,1.0,0.0);
 glVertex3f(-1.0, 0.5, 0.5);
 glVertex3f(-1.5, 0.5, 1.0);
 glVertex3f(-1.5, 0.0, 1.0);
 glVertex3f(-1.0, 0.0, 0.5);

 //後
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor4);
 glNormal3f(0.0,0.0,-1.0);
 glVertex3f(-0.34, 0.5, 0.5);
 glVertex3f(-1.0, 0.5, 0.5);
 glVertex3f(-1.0, 0.0, 0.5);
 glVertex3f(-0.34, 0.0, 0.5);

 //上
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor4);
 glNormal3f(0.0,1.0,0.0);
 glVertex3f(-0.615, 0.5, 1.0);
 glVertex3f(-1.5, 0.5, 1.0);
 glVertex3f(-1.0, 0.5, 0.5);
 glVertex3f(-0.34, 0.5, 0.5);

 //下
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor4);
 glNormal3f(0.0,-1.0,0.0);
 glVertex3f(-0.615, 0.0, 1.0);
 glVertex3f(-1.5, 0.0,1.0);
 glVertex3f(-1.0, 0.0, 0.5);
 glVertex3f(-0.34, 0.0, 0.5);
 glEnd();
}

void daikei3(){
 glBegin(GL_QUADS);

 // 前
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor4);
 glNormal3f(0.0,0.0,1.0);
 glVertex3f(1.5, 0.5, 1.0);
 glVertex3f(0.0, 0.5, 1.0);
 glVertex3f(0.0, 0.0, 1.0);
 glVertex3f(1.5, 0.0, 1.0);

 //左
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor4);
 glNormal3f(1.0,0.0,0.0);
 glVertex3f(1.5,0.5,1.0);
 glVertex3f(1.0, 0.5, 0.5);
 glVertex3f(1.0, 0.0,0.5);
 glVertex3f(1.5, 0.0, 1.0);

 //右
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor4);
 glNormal3f(-1.0,0.0,0.0);
 glVertex3f(0.3, 0.5, 0.5);
 glVertex3f(0.0, 0.5, 1.0);
 glVertex3f(0.0, 0.0, 1.0);
 glVertex3f(0.3, 0.0, 0.5);

 //後
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor4);
 glNormal3f(0.0,0.0,-1.0);
 glVertex3f(1.0, 0.5, 0.5);
 glVertex3f(0.3, 0.5, 0.5);
 glVertex3f(0.3, 0.0, 0.5);
 glVertex3f(1.0, 0.0, 0.5);

 //上
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor4);
 glNormal3f(0.0,1.0,0.0);
 glVertex3f(1.5, 0.5, 1.0);
 glVertex3f(0.0, 0.5, 1.0);
 glVertex3f(0.3, 0.5, 0.5);
 glVertex3f(1.0, 0.5, 0.5);

 //下
 glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor4);
 glNormal3f(0.0,-1.0,0.0);
 glVertex3f(1.5, 0.0, 1.0);
 glVertex3f(0.0, 0.0,1.0);
 glVertex3f(0.3, 0.0, 0.5);
 glVertex3f(1.0, 0.0, 0.5);
 glEnd();
}