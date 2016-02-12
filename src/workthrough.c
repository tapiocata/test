#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#include<math.h>
#define PI  3.14159265
#define cameraspeed 0.1
#define mousespeed 2000

/*glutGetModefiersの値格納*/
int key_shift;
/*speed*/
double k = 0;

//int mouseflug = 0;
int keyflug = 0;
double z = -10.0;
double x = 0.0;
double y = 0.0;
double R = 0.0;

/*カメラの視点*/
double ax;
double ay;
double az;

printf("abcde");
printf("aaa");

int dx = 0;
int dy = 0;
double angles = PI / 2;
double angles_y = 0;

GLdouble normal[][3] = { { 0.0, 0.0, -1.0 }, { 1.0, 0.0, 0.0 },
		{ 0.0, 0.0, 1.0 }, { -1.0, 0.0, 0.0 }, { 0.0, -1.0, -1.0 }, { 0.0, 1.0,
				0.0 }, };

GLuint objects;

void scene(void) {
	int i, j;

	static GLfloat red[] = { 0.8, 0.2, 0.2, 1.0 };
	static GLfloat green[] = { 0.2, 0.8, 0.2, 1.0 };
	static GLfloat blue[] = { 0.2, 0.2, 0.8, 1.0 };
	static GLfloat yellow[] = { 0.8, 0.8, 0.2, 1.0 };
	static GLfloat ground[][4] = { { 0.6, 0.6, 0.6, 1.0 },
			{ 0.3, 0.3, 0.3, 1.0 } };
	objects = glGenLists(1);
	glNewList(objects, GL_COMPILE);

	/*赤の箱設置*/
	glPushMatrix();
	glTranslated(0.0, 0.0, -3.0);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
	glutSolidCube(1.0);
	glPopMatrix();

	/*緑の箱設置*/
	glPushMatrix();
	glTranslated(0.0, 0.0, 3.0);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, green);
	glutSolidCube(1.0);
	glPopMatrix();

	/*青の箱設置*/
	glPushMatrix();
	glTranslated(-3.0, 0.0, 0.0);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
	glutSolidCube(1.0);
	glPopMatrix();

	/*黄色の箱設置*/
	glPushMatrix();
	glTranslated(3.0, 0.0, 0.0);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow);
	glutSolidCube(1.0);
	glPopMatrix();
	/*黄色の箱設置*/
	glPushMatrix();
	glTranslated(6.0, 0.0, 0.0);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow);
	glutSolidCube(1.0);
	glPopMatrix();
	/*地面*/
	glBegin(GL_QUADS);
	glNormal3d(0.0, 1.0, 0.0);
	for (j = -100; j < 100; ++j) {
		for (i = -100; i < 100; ++i) {
			glMaterialfv(GL_FRONT, GL_DIFFUSE, ground[(i | j) % 50]);
			glVertex3d((GLdouble) i, -0.5, (GLdouble) j);
			glVertex3d((GLdouble) i, -0.5, (GLdouble) (j + 1));
			glVertex3d((GLdouble) (i + 1), -0.5, (GLdouble) (j + 1));
			glVertex3d((GLdouble) (i + 1), -0.5, (GLdouble) j);
		}
	}
	glEnd();
	glEndList();
}

double twopi(double x) {
	if (x > (2 * PI))
		return twopi(x - 2 * PI);

	else
		return x;

}

double pi(double x) {
	if (x > PI)
		return pi(x - PI);
	else
		return x;
}
void display(void) {

	static GLfloat light0pos[] = { 0.0, 3.0, 5.0, 1.0 };

	static double ex = 0.0, ez = 0.0;
	static double r = 0.0;

	glRotated(r, 0.0, 1.0, 0.0);
	glTranslated(ex, 0.0, ez);

	/*画面クリア*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/*モデルビュー変換行列の初期化*/
	glLoadIdentity();

	/*shift押している開いだ加速*/
	if (key_shift & GLUT_ACTIVE_SHIFT)
		k = (double) 4;
	/*前進*/
	x += cos(angles) * cos(angles_y) * cameraspeed * k;
	z += sin(angles) * cos(angles_y) * cameraspeed * k;
	y += sin(angles_y) * cameraspeed * k;

/*加速*/
	if (keyflug & 1){
		k+=0.01;
		/*x += cos(angles) * cos(angles_y) * cameraspeed * k;
		z += sin(angles) * cos(angles_y) * cameraspeed * k;
		y += sin(angles_y) * cameraspeed * k;*/
	}
	/*減速*/
	if (keyflug & 2) {
		if(k >= 0)
		k-=0.01;
		/*x -= cos(angles) * cos(angles_y) * cameraspeed * k;
		z -= sin(angles) * cos(angles_y) * cameraspeed * k;
		y -= sin(angles_y) * cameraspeed * k;*/
	}
	if (keyflug & 4) {
		x += cos(angles + PI / 2) * cos(angles_y) * cameraspeed * k;
		z += sin(angles + PI / 2) * cos(angles_y) * cameraspeed * k;
		//y += sin(angles_y + PI);

	}
	if (keyflug & 8) {
		x += cos(angles - PI / 2) * cos(angles_y) * cameraspeed * k;
		z += sin(angles - PI / 2) * cos(angles_y) * cameraspeed * k;
		//y += sin(angles_y + PI);
	}
	if (keyflug & 16) {
		angles = PI / 2;
		angles_y = 0;
		x = 0;
		y = 0;
		z = -10.0;
	}

/*	else if(mouseflug == 2)
	 z--;
	 else if(mouseflug == 3)
	 x = 20.0*cos(R);
	 z = 20.0*sin(R);
	 R += 1.0/100.0;*/
	/*中心との差による角度代入*/
	angles += ((double) dx / mousespeed) * PI * 2;
	angles_y += ((double) dy / mousespeed) * PI * 2;

	az = 10 * sin(angles) * cos(angles_y) + z;
	ax = 10 * cos(angles) * cos(angles_y) + x;
	ay = 10 * sin(angles_y) + y;
	/*視点移動距離初期化*/
	dx = 0;
	dy = 0;
	gluLookAt(x, y, z, ax, ay, az, 0.0, 1.0, 0.0);
	/*視点の移動*/
	// glRotated(25.0,0.0,0.0,0.0);
	/*光源の位置設定*/
	glLightfv(GL_LIGHT0, GL_POSITION, light0pos);

	glCallList(objects);

	glFlush();
}

void resize(int w, int h) {

	/*ウィンドウ全体をビューポートにする*/
	glViewport(0, 0, w, h);
	/*透視変換行列の設定*/
	glMatrixMode(GL_PROJECTION);
	/*変換行列の初期化*/
	glLoadIdentity();
	gluPerspective(30.0, (double) w / (double) h, 1.0, 100.0);

	/*モデルビュー変換行列の指定*/
	glMatrixMode(GL_MODELVIEW);

}

void motion(int x, int y) {
	static int wrap = 0;

	if (!wrap) {
		int ww = glutGet(GLUT_WINDOW_WIDTH);
		int wh = glutGet(GLUT_WINDOW_HEIGHT);

		dx += (x - ww / 2);
		dy += (y - wh / 2);

		wrap = 1;
		glutWarpPointer(ww / 2, wh / 2);

	} else {
		wrap = 0;

	}
}

void keyboard(unsigned char key, int x, int y) {

	switch (key) {
	case 'w':
		keyflug = 1 | keyflug;
		break;
	case 's':
		keyflug = 2 | keyflug;
		break;
	case 'd':
		keyflug = 4 | keyflug;
		break;
	case 'a':
		keyflug = 8 | keyflug;
		break;
	case 'e':
		keyflug = 16 | keyflug;
		break;
	case 'f':
		keyflug = 32 | keyflug;
		break;
	}
	if (key == '\033' || key == 'q') {
		exit(0);
	}
	key_shift = glutGetModifiers();

}

void keyboardup(unsigned char key, int x, int y) {
	switch (key) {
	case 'w':
		keyflug = 1 ^ keyflug;
		break;
	case 's':
		keyflug = 2 ^ keyflug;
		break;
	case 'd':
		keyflug = 4 ^ keyflug;
		break;
	case 'a':
		keyflug = 8 ^ keyflug;
		break;
	case 'e':
		keyflug = 16 ^ keyflug;
		break;
	case 'f':
		keyflug = 32 ^ keyflug;
	}
	if (key == '\033' || key == 'q') {
		exit(0);
	}
	key_shift = glutGetModifiers();
}

/*void mouse(int button, int state, int x, int y)
 {
 switch(button){
 case GLUT_LEFT_BUTTON:
 if(state == GLUT_DOWN)
 mouseflug = 1;
 else
 mouseflug = 0;
 break;
 case GLUT_RIGHT_BUTTON:
 if(state == GLUT_DOWN)
 mouseflug = 2;
 else mouseflug = 0;
 break;
 case GLUT_MIDDLE_BUTTON:
 if(state == GLUT_DOWN)
 mouseflug = 3;
 else mouseflug = 0;
 default: break;
 }
 }
*/
void timer(int value) {
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, timer, 0);
}

void init(void) {
	/*初期設定*/
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	// glCullFace(GL_FRONT);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glutTimerFunc(100, timer, 0);
}

int main(int argc, char *argv[]) {
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1000, 1000);
	glutInit(&argc, argv);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
	glutReshapeFunc(resize);
	//glutMouseFunc(mouse);
	scene();
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardup);
	glutMotionFunc(motion);
	glutPassiveMotionFunc(motion);
	glutSetCursor(GLUT_CURSOR_FULL_CROSSHAIR);
	init();
	glutMainLoop();
	return 0;
}
