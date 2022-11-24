#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#define WINDOW_X (1920)
#define WINDOW_Y (1080)
#define WINDOW_NAME "home"
#define TEXTURE_HEIGHT (512)
#define TEXTURE_WIDTH (512)
#define EPS 0.001
#define DEFAULT_JUMP_COUNT 3

void init_GL(int argc, char *argv[]);
void init();
void set_callback_functions();
double move(double);
void grav(double);
double square(double);

void glut_display();
void menu_display();
void objects_display();
void glut_keyboard(unsigned char key, int x, int y);
void glut_mouse(int button, int state, int x, int y);
void glut_motion(int x, int y);
void glut_idle();
void draw_planex();

void draw_floor();
void draw_plane1();
void draw_plane2();
void draw_plane3();
void draw_plane4();
void draw_plane5();
void set_texture();
void daikei();
void daikei2();
void daikei3();
void daikei6();
void daikei4();
void daikei5();
void daikein1();
void daikein2();
void daikein3();
void draw_line();
void showText(std::string);
int jump = 0;
int g_jump_left = DEFAULT_JUMP_COUNT;
int g_count = 20;
double g_vy = 0;
double g_floor_y = 6.0;
enum class Menu {
    menu,
    objects,
};
Menu g_current_view = Menu::objects;

void cuboid(float, float, float);

// グローバル変数
double g_angle1 = 0.0;
double g_angle2 = 0.0;
double g_distance = 1.0;
bool g_isLeftButtonOn = false;
bool g_isRightButtonOn = false;
double current_x = 0.0;
double current_y = 6.0;
double current_z = 0.0;
int num = 0;
GLuint g_TextureHandles[3] = {0, 0, 0};
GLfloat facecolor4[] = {0.95f, 0.975f, 0.074f, 1.0f};
GLfloat facecolor1[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat facecolor10[] = {1.0f, 0.0f, 0.0f, 1.0f};  // 赤
GLfloat facecolor20[] = {1.0f, 1.0f, 0.0f, 1.0f};  // 黃
GLfloat facecolor30[] = {0.0f, 0.0f, 1.0f, 1.0f};  // 青
GLfloat facecolor40[] = {0.0f, 0.5f, 0.5f, 1.0f};  // 謎
GLfloat facecolor400[] = {1.0f, 1.0f, 1.0f, 1.0f};
double t = 0.0;

double square(double a) { return a * a; }

int main(int argc, char *argv[]) {
    /* OpenGLの初期化 */
    init_GL(argc, argv);

    /* このプログラム特有の初期化 */
    init();

    /* コールバック関数の登録 */
    set_callback_functions();

    /* メインループ */
    glutMainLoop();

    return 0;
}

void init_GL(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_X, WINDOW_Y);
    glutCreateWindow(WINDOW_NAME);
    // glutGameModeString("width=1920 height=1080 bpp~24 hertz>=100");
    // glutEnterGameMode();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);

    glGenTextures(3, g_TextureHandles);

    for (int i = 0; i < 3; i++) {
        glBindTexture(GL_TEXTURE_2D, g_TextureHandles[i]);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        if (i == 1) {
            // changed
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1000, 574, 0, GL_RGB,
                         GL_UNSIGNED_BYTE, NULL);
        } else {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXTURE_WIDTH,
                         TEXTURE_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        }

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    }

    set_texture();
}

void set_callback_functions() {
    glutDisplayFunc(glut_display);
    glutKeyboardFunc(glut_keyboard);
    glutMouseFunc(glut_mouse);
    glutMotionFunc(glut_motion);
    glutPassiveMotionFunc(glut_motion);
    glutIdleFunc(glut_idle);
}

void glut_keyboard(unsigned char key, int x, int y) {
    double d = 8 * g_distance * cos(g_angle2);
    switch (key) {
        case 'k':
            printf("%lf, %lf, %lf\n", g_distance, g_angle1, g_angle2);
            break;

        case 'd':
            current_x +=
                g_distance * cos(g_angle2) * sin(g_angle1 - M_PI/2) / d;
            current_z +=
                g_distance * cos(g_angle2) * cos(g_angle1 - M_PI/2) / d;
            break;

        case 'a':
            current_x +=
                g_distance * cos(g_angle2) * sin(g_angle1 + M_PI / 2) / d;
            current_z +=
                g_distance * cos(g_angle2) * cos(g_angle1 + M_PI / 2) / d;
            break;

        case 'w':
            current_x += g_distance * cos(g_angle2) * sin(g_angle1) / d;
            current_z += g_distance * cos(g_angle2) * cos(g_angle1) / d;
            break;

        case 's':
            current_x -= g_distance * cos(g_angle2) * sin(g_angle1) / d;
            current_z -= g_distance * cos(g_angle2) * cos(g_angle1) / d;
            break;

		case 'c':
			if (square(current_x + 11) + square(current_z) < 40) {
				pid_t pid;
				pid = fork();
				if (pid == 0) {
					execlp("./art1", "./art1", NULL);
				}
			} else if (square(current_x - 0) + square(current_z - 11) < 40) {
				pid_t pid1;
				pid1 = fork();
				if (pid1 == 0) {
					execlp("./art2", "./art2", NULL);
				}
			} else if (square(current_x - 11) + square(current_z) < 40) {
				pid_t pid2;
				pid2 = fork();
				if (pid2 == 0) {
					execlp("./art3", "./art3", NULL);
				}
			}
			break;

        case ' ':
            if (jump == 0) jump = 1;
            break;

        case 'q':
        case 'Q':
        case '\033':
            exit(0);
    }
    glutPostRedisplay();
}

void glut_mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_UP) {
            g_isLeftButtonOn = false;
        } else if (state == GLUT_DOWN) {
            g_isLeftButtonOn = true;
        }
    }

    if (button == GLUT_RIGHT_BUTTON) {
        if (state == GLUT_UP) {
            g_isRightButtonOn = false;
        } else if (state == GLUT_DOWN) {
            g_isRightButtonOn = true;
        }
    }
}

void glut_motion(int x, int y) {
    static int px = -1, py = -1;
    if (g_isLeftButtonOn == true) {
        if (px >= 0 && py >= 0) {
            g_angle1 += (double)-(x - px) / 200;
            g_angle2 += (double)(y - py) / 200;
            if (g_angle2 < -M_PI / 4) g_angle2 = -M_PI / 4;
            if (g_angle2 > M_PI / 4) g_angle2 = M_PI / 4;
        }
        px = x;
        py = y;
    } else if (g_isRightButtonOn == true) {
        if (px >= 0 && py >= 0) {
            g_distance += (double)(y - py) / 200;
        }
        px = x;
        py = y;
    } else {
        px = -1;
        py = -1;
    }
    glutPostRedisplay();
}

void objects_display() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.0, 0.1, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(current_x, current_y, current_z,
              g_distance * cos(g_angle2) * sin(g_angle1) + current_x,
              g_distance * sin(g_angle2) + current_y,
              g_distance * cos(g_angle2) * cos(g_angle1) + current_z, 0.0, 1.0,
              0.0);

    GLfloat lightpos[] = {0.0, 8.0, 0.0, 1.0f};
    GLfloat diffuse[] = {1.0, 1.0, 1.0, 1.0};
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    t += 1.0;

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, diffuse);

    glPushMatrix();
    draw_floor();
    glPopMatrix();

    glPushMatrix();
    draw_plane1();
    glPopMatrix();
    glPushMatrix();
    draw_plane2();
    glPopMatrix();
    glPushMatrix();
    draw_plane3();
    glPopMatrix();
    glPushMatrix();
    draw_plane4();
    glPopMatrix();
    glPushMatrix();
    draw_planex();
    glPopMatrix();

    glPushMatrix();
    draw_plane5();
    glPopMatrix();

    // 台座
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor1);
    glTranslatef(0.0, 0.0, 11.0);
    cuboid(2.0, 10.0, 2.0);
    glPopMatrix();

    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor1);
    glTranslatef(-11.0, 0.0, 0.0);
    cuboid(2.0, 10.0, 2.0);
    glPopMatrix();

    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor1);
    glTranslatef(11.0, 0.0, 0.0);
    cuboid(2.0, 10.0, 2.0);
    glPopMatrix();

    // 作品1
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor4);

    glTranslatef(-10.75, 6.5 + move(t), 0.15);
    glScalef(0.3, 0.45, 0.3);
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
    glPopMatrix();

    // 作品2
    glPushMatrix();

    glTranslatef(0.0, 7.0 + move(t), 11.5);
    glScalef(0.3, 0.45, 0.3);
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
    glPopMatrix();

    // 作品3
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor400);

    glTranslatef(10.75, 7.3 + move(t), 0.35);
    glScalef(0.3, 0.45, 0.3);
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

    glPopMatrix();

    glFlush();
    // glDisable(GL_LIGHT0);
    // glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glutSwapBuffers();
}

// void showText(std::string str) {
//     unsigned char str2[100] = str;
//     int w = glutBitmapLength(GLUT_BITMAP_8_BY_13, str2);
//     glRasterPos2f(0., 0.);

// }

void glut_display() {
    if (g_current_view == Menu::menu) {
        menu_display();
    } else if (g_current_view == Menu::objects) {
        objects_display();
    } else {
        fprintf(stderr, "unknown type.\n");
        exit(1);
    }
}

void menu_display() {
    // TODO: メニュー画面の表示内容を書く
    printf("menu_display called!\n");
}

void glut_idle() {
    grav(0.01);
    glutPostRedisplay();
}

void draw_floor() {
    GLdouble pointA[] = {12.0, 0.0, 12.0};
    GLdouble pointB[] = {12.0, 0.0, -12.0};
    GLdouble pointC[] = {-12.0, 0.0, -12.0};
    GLdouble pointD[] = {-12.0, 0.0, 12.0};

    glBindTexture(GL_TEXTURE_2D, g_TextureHandles[0]);
    glNormal3d(0.0, 1.0, 0.0);
    // glMaterialfv(GL_FRONT, GL_DIFFUSE, floorcolor);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glTexCoord2d(4.0, 4.0);
    glVertex3dv(pointA);
    glTexCoord2d(4.0, 0.0);
    glVertex3dv(pointB);
    glTexCoord2d(0.0, 0.0);
    glVertex3dv(pointC);
    glTexCoord2d(0.0, 4.0);
    glVertex3dv(pointD);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

GLfloat facecolor2[] = {0.6627f, 0.7176f, 0.2078f, 1.0f};

void draw_plane1() {
    glBegin(GL_QUADS);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor2);
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3d(-12.0, 0.0, 12.0);
    glVertex3d(-12.0, 16.0, 12.0);
    glVertex3d(-12.0, 16.0, -12.0);
    glVertex3d(-12.0, 0.0, -12.0);
    glEnd();
}

void draw_plane2() {
    glBegin(GL_QUADS);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor2);
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3d(12.0, 0.0, 12.0);
    glVertex3d(12.0, 16.0, 12.0);
    glVertex3d(12.0, 16.0, -12.0);
    glVertex3d(12.0, 0.0, -12.0);
    glEnd();
}

void draw_plane3() {
    glBegin(GL_QUADS);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor2);
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3d(12.0, 0.0, 12.0);
    glVertex3d(12.0, 16.0, 12.0);
    glVertex3d(-12.0, 16.0, 12.0);
    glVertex3d(-12.0, 0.0, 12.0);
    glEnd();
}

void draw_plane4() {
    glBegin(GL_QUADS);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor2);
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3d(12.0, 0.0, -12.0);
    glVertex3d(12.0, 16.0, -12.0);
    glVertex3d(-12.0, 16.0, -12.0);
    glVertex3d(-12.0, 0.0, -12.0);
    glEnd();
}

void draw_planex() {
    // changed
    GLdouble pointA[] = {4.0, 10.592, -11.5};
    GLdouble pointB[] = {4.0, 1.408, -11.5};
    GLdouble pointC[] = {-4.0, 1.408, -11.5};
    GLdouble pointD[] = {-4.0, 10.592, -11.5};

    glBindTexture(GL_TEXTURE_2D, g_TextureHandles[1]);
    glNormal3d(0.0, 0.0, 1.0);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    // changed
    glTexCoord2d(1.0, 0.0);
    glVertex3dv(pointA);
    // changed
    glTexCoord2d(1.0, 1.0);
    glVertex3dv(pointB);
    // changed
    glTexCoord2d(0.0, 1.0);
    glVertex3dv(pointC);
    // changed
    glTexCoord2d(0.0, 0.0);
    glVertex3dv(pointD);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void draw_plane5() {
    GLdouble pointA[] = {12.0, 16.0, 12.0};
    GLdouble pointB[] = {12.0, 16.0, -12.0};
    GLdouble pointC[] = {-12.0, 16.0, -12.0};
    GLdouble pointD[] = {-12.0, 16.0, 12.0};

    glBindTexture(GL_TEXTURE_2D, g_TextureHandles[2]);
    glNormal3d(0.0, 1.0, 0.0);
    // glMaterialfv(GL_FRONT, GL_DIFFUSE, floorcolor);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glTexCoord2d(4.0, 4.0);
    glVertex3dv(pointA);
    glTexCoord2d(4.0, 0.0);
    glVertex3dv(pointB);
    glTexCoord2d(0.0, 0.0);
    glVertex3dv(pointC);
    glTexCoord2d(0.0, 4.0);
    glVertex3dv(pointD);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void set_texture() {
    const char *inputFileNames[3] = {"floor(2).jpg", "wall.png", "天井.jpg"};
    for (int i = 0; i < 3; i++) {
        cv::Mat input = cv::imread(inputFileNames[i], 1);
        //printf("%d: cols=%d, rows=%d\n", i, input.cols, input.rows);
        // BGR -> RGBの変換
        cv::cvtColor(input, input, cv::COLOR_BGR2RGB);

        glBindTexture(GL_TEXTURE_2D, g_TextureHandles[i]);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, input.cols, input.rows, GL_RGB,
                        GL_UNSIGNED_BYTE, input.data);
    }
}

void cuboid(float width, float height, float depth) {
    glBegin(GL_QUADS);
    // 前
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(width / 2, height / 2, depth / 2);
    glVertex3f(-width / 2, height / 2, depth / 2);
    glVertex3f(-width / 2, -height / 2, depth / 2);
    glVertex3f(width / 2, -height / 2, depth / 2);

    // 左
    // glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor4);
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(width / 2, height / 2, depth / 2);
    glVertex3f(width / 2, height / 2, -depth / 2);
    glVertex3f(width / 2, -height / 2, -depth / 2);
    glVertex3f(width / 2, -height / 2, depth / 2);

    // 右
    // glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor4);
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(-width / 2, height / 2, -depth / 2);
    glVertex3f(-width / 2, height / 2, depth / 2);
    glVertex3f(-width / 2, -height / 2, depth / 2);
    glVertex3f(-width / 2, -height / 2, -depth / 2);

    // 後
    // glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor4);
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(width / 2, height / 2, -depth / 2);
    glVertex3f(-width / 2, height / 2, -depth / 2);
    glVertex3f(-width / 2, -height / 2, -depth / 2);
    glVertex3f(width / 2, -height / 2, -depth / 2);

    // 上
    // glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor4);
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(width / 2, height / 2, depth / 2);
    glVertex3f(-width / 2, height / 2, depth / 2);
    glVertex3f(-width / 2, height / 2, -depth / 2);
    glVertex3f(width / 2, height / 2, -depth / 2);

    // 下
    // glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor4);
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(width / 2, -height / 2, depth / 2);
    glVertex3f(-width / 2, -height / 2, depth / 2);
    glVertex3f(-width / 2, -height / 2, -depth / 2);
    glVertex3f(width / 2, -height / 2, -depth / 2);
    glEnd();
}

void daikei() {
    glBegin(GL_QUADS);

    // 前
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor4);
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(1.5, 0.5, 1.0);
    glVertex3f(-1.5, 0.5, 1.0);
    glVertex3f(-1.5, 0.0, 1.0);
    glVertex3f(1.5, 0.0, 1.0);

    // 右
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor4);
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(1.5, 0.5, 1.0);
    glVertex3f(1.0, 0.5, 0.5);
    glVertex3f(1.0, 0.0, 0.5);
    glVertex3f(1.5, 0.0, 1.0);

    // 左
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor4);
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(-1.0, 0.5, 0.5);
    glVertex3f(-1.5, 0.5, 1.0);
    glVertex3f(-1.5, 0.0, 1.0);
    glVertex3f(-1.0, 0.0, 0.5);

    // 後
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor4);
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(1.0, 0.5, 0.5);
    glVertex3f(-1.0, 0.5, 0.5);
    glVertex3f(-1.0, 0.0, 0.5);
    glVertex3f(1.0, 0.0, 0.5);

    // 上
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor4);
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(1.5, 0.5, 1.0);
    glVertex3f(-1.5, 0.5, 1.0);
    glVertex3f(-1.0, 0.5, 0.5);
    glVertex3f(1.0, 0.5, 0.5);

    // 下
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor4);
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(1.5, 0.0, 1.0);
    glVertex3f(-1.5, 0.0, 1.0);
    glVertex3f(-1.0, 0.0, 0.5);
    glVertex3f(1.0, 0.0, 0.5);
    glEnd();
}

void daikei2() {
    glBegin(GL_QUADS);

    // 前
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor4);
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(-0.615, 0.5, 1.0);
    glVertex3f(-1.5, 0.5, 1.0);
    glVertex3f(-1.5, 0.0, 1.0);
    glVertex3f(-0.615, 0.0, 1.0);

    // 左
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor4);
    glNormal3f(1.0, 1.0, 0.0);
    glVertex3f(-0.615, 0.5, 1.0);
    glVertex3f(-0.34, 0.5, 0.5);
    glVertex3f(-0.34, 0.0, 0.5);
    glVertex3f(-0.615, 0.0, 1.0);

    // 右
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor4);
    glNormal3f(1.0, 1.0, 0.0);
    glVertex3f(-1.0, 0.5, 0.5);
    glVertex3f(-1.5, 0.5, 1.0);
    glVertex3f(-1.5, 0.0, 1.0);
    glVertex3f(-1.0, 0.0, 0.5);

    // 後
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor4);
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(-0.34, 0.5, 0.5);
    glVertex3f(-1.0, 0.5, 0.5);
    glVertex3f(-1.0, 0.0, 0.5);
    glVertex3f(-0.34, 0.0, 0.5);

    // 上
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor4);
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(-0.615, 0.5, 1.0);
    glVertex3f(-1.5, 0.5, 1.0);
    glVertex3f(-1.0, 0.5, 0.5);
    glVertex3f(-0.34, 0.5, 0.5);

    // 下
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor4);
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(-0.615, 0.0, 1.0);
    glVertex3f(-1.5, 0.0, 1.0);
    glVertex3f(-1.0, 0.0, 0.5);
    glVertex3f(-0.34, 0.0, 0.5);
    glEnd();
}

void daikei3() {
    glBegin(GL_QUADS);

    // 前
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor4);
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(1.5, 0.5, 1.0);
    glVertex3f(0.0, 0.5, 1.0);
    glVertex3f(0.0, 0.0, 1.0);
    glVertex3f(1.5, 0.0, 1.0);

    // 左
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor4);
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(1.5, 0.5, 1.0);
    glVertex3f(1.0, 0.5, 0.5);
    glVertex3f(1.0, 0.0, 0.5);
    glVertex3f(1.5, 0.0, 1.0);

    // 右
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor4);
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(0.3, 0.5, 0.5);
    glVertex3f(0.0, 0.5, 1.0);
    glVertex3f(0.0, 0.0, 1.0);
    glVertex3f(0.3, 0.0, 0.5);

    // 後
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor4);
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(1.0, 0.5, 0.5);
    glVertex3f(0.3, 0.5, 0.5);
    glVertex3f(0.3, 0.0, 0.5);
    glVertex3f(1.0, 0.0, 0.5);

    // 上
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor4);
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(1.5, 0.5, 1.0);
    glVertex3f(0.0, 0.5, 1.0);
    glVertex3f(0.3, 0.5, 0.5);
    glVertex3f(1.0, 0.5, 0.5);

    // 下
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor4);
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(1.5, 0.0, 1.0);
    glVertex3f(0.0, 0.0, 1.0);
    glVertex3f(0.3, 0.0, 0.5);
    glVertex3f(1.0, 0.0, 0.5);
    glEnd();
}

void daikei6() {
    glBegin(GL_QUADS);

    // 右
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor10);
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(1.7, 1.7, 1.7);
    glVertex3f(1.7, 1.7, -10.7);
    glVertex3f(1.7, 0.0, -10.7);
    glVertex3f(1.7, 0.0, 1.7);

    // 左
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor20);
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(0.0, 1.7, -10.7);
    glVertex3f(0.0, 1.7, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, -10.7);

    // 後
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor40);
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(1.7, 1.7, -10.7);
    glVertex3f(0.0, 1.7, -10.7);
    glVertex3f(0.0, 0.0, -10.7);
    glVertex3f(1.7, 0.0, -10.7);

    // 上
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor30);
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(1.7, 1.7, 1.7);
    glVertex3f(0.0, 1.7, 0.0);
    glVertex3f(0.0, 1.7, -10.7);
    glVertex3f(1.7, 1.7, -10.7);

    // 下
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor20);
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(1.7, 0.0, 1.7);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, -10.7);
    glVertex3f(1.7, 0.0, -10.7);
    glEnd();
}

void daikei4() {
    glBegin(GL_QUADS);

    // 前
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor10);
    glNormal3f(0.0, 0.0, 1.0);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(1.7, 1.7, 1.7);
    glVertex3f(-8.7, 1.7, 1.7);
    glVertex3f(-8.7, 0.0, 1.7);
    glVertex3f(1.7, 0.0, 1.7);

    // 後
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor20);
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(0.0, 1.7, 0.0);
    glVertex3f(-8.7, 1.7, 0.0);
    glVertex3f(-8.7, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);

    // 上
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor30);
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(1.7, 1.7, 1.7);
    glVertex3f(0.0, 1.7, 0.0);
    glVertex3f(-8.7, 1.7, 0.0);
    glVertex3f(-8.7, 1.7, 1.7);

    // 下
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor20);
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(1.7, 0.0, 1.7);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(-8.7, 0.0, 0.0);
    glVertex3f(-8.7, 0.0, 1.7);
    glEnd();
}

void daikei5() {
    glBegin(GL_QUADS);

    // 前
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor10);
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(-8.7, 8.6, 1.7);
    glVertex3f(-8.7, 0.0, 1.7);
    glVertex3f(-10.4, 0.0, 1.7);
    glVertex3f(-10.4, 10.4, 1.7);

    // 右
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor30);
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(-8.7, 8.6, 1.7);
    glVertex3f(-8.7, 8.6, 0.0);
    glVertex3f(-8.7, 0.0, 0.0);
    glVertex3f(-8.7, 0.0, 1.7);

    // 左
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor20);
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(-10.4, 10.4, 1.7);
    glVertex3f(-10.4, 10.4, 0.0);
    glVertex3f(-10.4, 0.0, 0.0);
    glVertex3f(-10.4, 0.0, 1.7);

    // 後
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor40);
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(-8.7, 8.6, 0.0);
    glVertex3f(-8.7, 0.0, 0.0);
    glVertex3f(-10.4, 0.0, 0.0);
    glVertex3f(-10.4, 10.4, 0.0);

    // 上
    glNormal3f(1.0, 1.0, 0.0);
    glVertex3f(-8.7, 8.6, 1.7);
    glVertex3f(-8.7, 8.6, 0.0);
    glVertex3f(-10.4, 10.4, 0.0);
    glVertex3f(-10.4, 10.4, 1.7);

    // 下
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor20);
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(-8.7, 0.0, 1.7);
    glVertex3f(-10.4, 0.0, 1.7);
    glVertex3f(-10.4, 0.0, 0.0);
    glVertex3f(-8.7, 0.0, 0.0);
    glEnd();
}

void draw_line() {
    glBegin(GL_LINE_LOOP);

    glColor3d(0.0, 1.0, 0.0);
    glVertex3d(12.0, 12.0, 0.0);
    glVertex3d(12.0, 12.0, 16.0);

    glEnd();
}

double move(double t) {
    double r = 0.5;
    double w = 1.0 / 24.0;
    double y;
    // printf("%lf\n", t);
    y = r * sin(w * t);
    return y;
}

void grav(double t) {
    static double prev_y = 6.0;
    double vy = (current_y - prev_y) - 0.5;
    if (jump == 1) {
        current_y = (10.0 + 4.0 * current_y) / 5.0;
        if (abs(current_y - 10.0) < 10 * EPS) jump = 2;
    } else if (jump == 2) {
        current_y = (current_y + vy);
        if (current_y < 6.0) jump = 3;
    } else if (jump == 3) {
        current_y = 6.0;
        jump = 0;
    }
    prev_y = current_y;
}

// void calc(double t) {
//     // 位置の更新
//     if (abs(g_vy) < EPS && abs(current_y - g_floor_y) < EPS) {
//         // do nothing
//         g_jump_left = DEFAULT_JUMP_COUNT;
//     } else {
//         current_y += g_vy;
//     }
//     if (current_y < g_floor_y) {
//         current_y = g_floor_y;
//     }

//     // 速度の更新
//     g_vy -= 0.1;
//     if (abs(current_y - g_floor_y) < EPS) {
//         g_vy = 0;
//     }
// }

// void grav(double t){
// 	static double prev_y = 6.0;
// 	double vy = (current_y-prev_y) - 0.5;
// 	if(jump == 1) {
// 		current_y = (10.0 + 4.0*current_y) / 5.0;
//         g_count--;
// 		// if(abs(current_y-10.0) < 10*EPS)
//         if (g_count <= 0){
//             jump = 2;
//             g_count = 20;
//         }
// 	} else if(jump == 2) {
// 		current_y = (current_y + vy);
// 		// if(current_y < 6.0)
//         if (g_count <= 0) {
//             jump = 3;
//             g_count = 20;
//         } else {
//             g_count--;
//         }
// 	} else if(jump == 3) {
// 		// current_y = 6.0;
// 		jump = 0;
//         g_jump_left = DEFAULT_JUMP_COUNT;
// 	}
// 	prev_y = current_y;
// }

void daikein2() {
    glBegin(GL_QUADS);

    // 前
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor400);
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(0.22, 0.0, -0.445);
    glVertex3f(0.22, 3.0, -0.445);
    glVertex3f(0.72, 3.0, -0.445);
    glVertex3f(0.72, 0.0, -0.445);

    // 右
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor400);
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(0.72, 0.0, -0.445);
    glVertex3f(0.72, 3.0, -0.445);
    glVertex3f(0.9198, 3.6, -0.8537);
    glVertex3f(0.9198, 0.0, -0.8537);

    // 左
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor400);
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(0.22, 0.0, -0.445);
    glVertex3f(0.22, 3.0, -0.445);
    glVertex3f(0.4198, 3.6, -0.8537);
    glVertex3f(0.4198, 0.0, -0.8537);

    // 後
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor400);
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(0.9198, 0.0, -0.8537);
    glVertex3f(0.9198, 3.6, -0.8537);
    glVertex3f(0.4198, 3.6, -0.8537);
    glVertex3f(0.4198, 0.0, -0.8537);

    // 上
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor400);
    glNormal3f(0.0, 0.65, 0.76);
    glVertex3f(0.72, 3.0, -0.445);
    glVertex3f(0.9198, 3.6, -0.8537);
    glVertex3f(0.4198, 3.6, -0.8537);
    glVertex3f(0.22, 3.0, -0.445);

    // 下
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor400);
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(0.72, 0.0, -0.445);
    glVertex3f(0.9198, 0.0, -0.8537);
    glVertex3f(0.4198, 0.0, -0.8537);
    glVertex3f(0.22, 0.0, -0.445);
    glEnd();
}

void daikein1() {
    glBegin(GL_QUADS);

    // 前
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor400);
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 2.42, 0.0);
    glVertex3f(0.5, 2.42, 0.0);
    glVertex3f(0.5, 0.0, 0.0);

    // 右
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor400);
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(0.5, 0.0, 0.0);
    glVertex3f(0.5, 2.42, 0.0);
    glVertex3f(0.72, 3.1, -0.445);
    glVertex3f(0.72, 0.0, -0.445);

    // 左
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor400);
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 2.42, 0.0);
    glVertex3f(0.22, 3.1, -0.445);
    glVertex3f(0.22, 0.0, -0.445);

    // 後
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor400);
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(0.22, 0.0, -0.445);
    glVertex3f(0.22, 3.1, -0.445);
    glVertex3f(0.72, 3.1, -0.445);
    glVertex3f(0.72, 0.0, -0.445);

    // 上
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor400);
    glNormal3f(0.0, 0.65, 0.76);
    glVertex3f(0.0, 2.42, 0.0);
    glVertex3f(0.5, 2.42, 0.0);
    glVertex3f(0.72, 3.1, -0.445);
    glVertex3f(0.22, 3.1, -0.445);

    // 下
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor400);
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.5, 0.0, 0.0);
    glVertex3f(0.72, 0.0, -0.445);
    glVertex3f(0.22, 0.0, -0.445);
    glEnd();
}

void daikein3() {
    glBegin(GL_QUADS);

    // 前
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor400);
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(0.9198, 0.0, -0.8537);
    glVertex3f(0.9198, 3.5, -0.8537);
    glVertex3f(0.4198, 3.5, -0.8537);
    glVertex3f(0.4198, 0.0, -0.8537);

    // 右
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor400);
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(1.1, 0.0, -1.225);
    glVertex3f(1.1, 4.1, -1.225);
    glVertex3f(0.9198, 3.5, -0.8537);
    glVertex3f(0.9198, 0.0, -0.8537);

    // 左
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor400);
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(0.6, 0.0, -1.225);
    glVertex3f(0.6, 4.1, -1.225);
    glVertex3f(0.4198, 3.5, -0.8537);
    glVertex3f(0.4198, 0.0, -0.8537);

    // 後
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor400);
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(1.1, 0.0, -1.225);
    glVertex3f(1.1, 4.1, -1.225);
    glVertex3f(0.6, 4.1, -1.225);
    glVertex3f(0.6, 0.0, -1.225);

    // 上
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor400);
    glNormal3f(0.0, 0.65, 0.76);
    glVertex3f(0.9198, 3.5, -0.8537);
    glVertex3f(1.1, 4.1, -1.225);
    glVertex3f(0.6, 4.1, -1.225);
    glVertex3f(0.4198, 3.5, -0.8537);

    // 下
    glMaterialfv(GL_FRONT, GL_DIFFUSE, facecolor400);
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(0.9198, 0.0, -0.8537);
    glVertex3f(1.1, 0.0, -1.225);
    glVertex3f(0.6, 0.0, -1.225);
    glVertex3f(0.4198, 0.0, -0.8537);
    glEnd();
}