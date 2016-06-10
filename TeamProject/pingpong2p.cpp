#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<glut.h>
#include <math.h>

using namespace std;

int state = 1; //���Ӹ��. 2�̸� 3d���Ӹ��
double paddle1x, paddle1y; //player1�� �е���ǥ
double paddle2x, paddle2y; //player2�� �е���ǥ
double ballx, bally;//���� ��ǥ
double balldirx, balldiry; //���� ����
double theta = 0;//����

GLfloat vertices[8][3] = { { -10, -30, 10 },{ -10, 30, 10 },
{ 10, 30, 10 },{ 10, -30, 10 },
{ -10, -30, -10 },{ -10, 30, -10 },
{ 10, 30, -10 },{ 10, -30, -10 } };
GLfloat colors1[8][3] = { { 1.0, 0.0, 0.0 },{ 1.0, 0.0, 0.0 },
{ 1.0, 0.0, 0.0 },{ 1.0, 0.0, 0.0 },
{ 0.0, 0.0, 1.0 },{ 0.0, 0.0, 1.0 },
{ 0.0, 0.0, 1.0 },{ 0.0, 0.0, 1.0 } };
GLfloat colors2[8][3] = { { 0.0, 1.0, 0.0 },{ 0.0, 1.0, 0.0 },
{ 0.0, 1.0, 0.0 },{ 0.0, 1.0, 0.0 },
{ 1.0, 1.0, 0.0 },{ 1.0, 1.0, 0.0 },
{ 1.0, 1.0, 0.0 },{ 1.0, 1.0, 0.0 } };
GLubyte cubeIndices[24] = { 0, 3, 2, 1,
2, 3, 7, 6,
0, 4, 7, 3,
1, 2, 6, 5,
4, 5, 6, 7,
0, 1, 5, 4 };

int player1score, player2score;//�÷��̾� ���ھ�
char buffer[10];//���ھ� �޴� ����

bool keystates[256];

typedef struct materialStruct {
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat shininess;
}materialStruct;

materialStruct ball = { 1.0, 0.2, 0.2, 1.0,
1.0, 0.2, 0.2, 1.0,
1.0, 0.2, 0.2, 1.0, 50.0 };

void materials(materialStruct *material) {
	glMaterialfv(GL_FRONT, GL_AMBIENT, material->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material->specular);
	glMaterialf(GL_FRONT, GL_SHININESS, material->shininess);
}

void setLighting() {
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat light_pos[] = { -1.0, 0.0, 0.0, 0.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

	glShadeModel(GL_SMOOTH);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

/*���� �ʱ�ȭ*/
void initgame()
{
	ballx = -20;
	bally = 160;
	paddle1x = -270;
	paddle1y = 30;
	paddle2x = 270;
	paddle2y = 0;
	balldirx = 5;
	balldiry = 5;
}

/*Ű����up_press*/
void KeyUpPress(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		keystates['w'] = false;
		break;
	case 's':
		keystates['s'] = false;
		break;
	case 'o':
		keystates['o'] = false;
		break;
	case 'k':
		keystates['k'] = false;
		break;
	case 'c':
		break;
	case 27:
		exit(0);
	}
}
/*Ű����down_press*/
void KeyDownPress(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		keystates['w'] = true;
		break;
	case 's':
		keystates['s'] = true;
		break;
	case 'o':
		keystates['o'] = true;
		break;
	case 'k':
		keystates['k'] = true;
		break;
	case 'c':
		break;
	case 27:
		exit(0);
	}
}

/*string ȭ�鿡 ���*/
void drawString(void * font, char *s, float x, float y) {
	unsigned int i;
	glRasterPos2f(x, y);

	for (i = 0; i < strlen(s); i++)
		glutBitmapCharacter(font, s[i]);
}


/*player1�� �е�׸���*/
void drawpaddle1()
{
	if (state == 2)
		glRotated(theta, 0, 1, 0);
	glTranslatef(-280, paddle1y, 0);

	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glColorPointer(3, GL_FLOAT, 0, colors1);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cubeIndices);
	glFlush();
}

/*player1�� �е�׸���*/
void drawpaddle2()
{
	glLoadIdentity();

	if (state == 2)
		glRotated(theta, 0, 1, 0);
	glTranslatef(280, paddle2y, 0);

	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glColorPointer(3, GL_FLOAT, 0, colors2);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cubeIndices);

	glFlush();


}

/*���� ������ ���*/
void moveball()
{
	ballx = ballx + balldirx;

	//check if the ball hit the wall (�¿�)
	if (ballx + 5 > 320 || ballx - 5 < -320)
	{
		if (ballx + 5 > 320)
			player1score = player1score + 1;
		if (ballx - 5 < -320)
			player2score = player2score + 1;
		balldirx = -balldirx;
	}

	//check if the ball hit the wall(����)
	bally = bally + balldiry;
	if (bally + 5 > 240 || bally - 5 < -240)
		balldiry = -balldiry;

	//check if the ball hit the paddle
	if (balldirx >= 1)
	{
		if (ballx + 5 > paddle2x - 10 && ballx - 5 < paddle2x + 10
			&& bally - 5 < paddle2y + 30 && bally + 5 > paddle2y - 30)
		{
			balldirx = -balldirx;
		}
	}
	else
	{
		if (ballx + 5 > paddle1x - 10 && ballx - 5 < paddle1x + 10
			&& bally - 5 < paddle1y + 30 && bally + 5 > paddle1y - 30)
		{
			balldirx = -balldirx;
		}
	}
}

/*���׸���*/
void drawball()
{
	materialStruct *matp;

	glLoadIdentity();
	if (state == 2)
		glRotated(theta, 0, 1, 0);
	glTranslatef(ballx, bally, 0);

	matp = &ball;
	materials(matp);
	glColor3d(1.0, 0.0, 0.0);
	glutSolidSphere(10, 32, 32);

	glFlush();
}

void myTimer(int v)
{
	theta += 0.2;
	if (theta >= 360.0) theta -= 360.0;

	glutPostRedisplay();
	glutTimerFunc(10, myTimer, v);
}


void display()
{
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0, 0, 1, 0, 0, 0, 0, 1, 0);

	/*10���̻� ������ ���� ���� ��*/
	if (player1score >= 10 || player2score >= 10)
	{
		return;
	}
	else
	{
		/*���� ���*/
		glColor3f(1, 1, 1);
		drawString(GLUT_BITMAP_HELVETICA_18, "Player1:", -310, -220);
		itoa(player1score, buffer, 10);
		drawString(GLUT_BITMAP_HELVETICA_18, buffer, -310, -200);

		drawString(GLUT_BITMAP_HELVETICA_18, "Player2:", 240, -220);
		itoa(player2score, buffer, 10);
		drawString(GLUT_BITMAP_HELVETICA_18, buffer, 240, -200);

		/*"s","w"Ű�� �÷��̾�1 �е��� ���� ������*/
		if (keystates['s'] == true)//Ű���� ������
			if (paddle1y - 30 > -240)
				paddle1y = paddle1y - 5;
		if (keystates['w'] == true)
			if (paddle1y + 30 < 240)
				paddle1y = paddle1y + 5;
		drawpaddle1();

		/*"k","o"Ű�� �÷��̾�2 �е��� ���� ������*/
		if (keystates['k'] == true)
			if (paddle2y - 30 > -240)
				paddle2y = paddle2y - 5;
		if (keystates['o'] == true)
			if (paddle2y + 30 < 240)
				paddle2y = paddle2y + 5;

		setLighting();
		moveball();
		drawball();

		glDisable(GL_LIGHTING);
		drawpaddle2();

		glutSwapBuffers();
	}

}

void demo_menu(int id)
{
	switch (id)
	{
	case 1: state = 1; break;
	case 2: state = 2; break;
	}
	glutPostRedisplay();
}

void reshape(int x, int y)
{
	glViewport(0, 0, x, y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-320, 320, -240, 240, -320, 320);
	glMatrixMode(GL_MODELVIEW);
}

void main(int argc, char **argv)
{
	initgame();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Pong");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(KeyDownPress);
	glutKeyboardUpFunc(KeyUpPress);
	/*�˾��޴��� ���� �ڵ�*/
	glutCreateMenu(demo_menu);
	glutAddMenuEntry("2d���Ӹ��", 1);
	glutAddMenuEntry("3d���Ӹ��", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	/*�Թ�ü�� ���� �ڵ�*/
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	glutTimerFunc(100, myTimer, 1);

	//glutFullScreen();   
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}