#include <stdlib.h>
#include <gl/glut.h>
#include <stdio.h>
#define d 1.0

GLfloat ang_ref1, ang_ref2; //회전각도
GLfloat angle1, angle2;
int w_width = 600, w_height = 400;   // 윈도우 크기
float now_x = 0;
float rsize = 0.06;   // 공 반지름

/*bar를 직육면체로 설정*/
GLfloat vertices[8][3]={{-0.1,-0.04,0.06}, {-0.1,0.04,0.06},
			 			 {0.1,0.04,0.06},   {0.1,-0.04,0.06},
			 			 {-0.1,-0.04,-0.06},{-0.1,0.04,-0.06},
			 			 {0.1,0.04,-0.06},  {0.1,-0.04,-0.06}};
GLfloat colors[8][3]={{0.0,0.0,0.0},{1.0,0.0,0.0},
				  {1.0,1.0,0.0},{0.0,1.0,0.0},
				  {0.0,0.0,1.0},{1.0,0.0,1.0},
				  {1.0,1.0,1.0},{0.0,1.0,1.0}};
GLubyte cubeIndices[24] = {0,3,2,1,
					   	   2,3,7,6,
    					   0,4,7,3,
						   1,2,6,5,
						   4,5,6,7,
						   0,1,5,4};


void display();
void myinit(void);
void myReshape(int w, int h);
void idle();
void myTimer(int value);
void mykey(int key, int x, int y);
void draw_bar();
void draw_ball();

int main(int argc, char **argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);//추가한거

    glutInitWindowSize(w_width, w_height);
   glutCreateWindow("Ping-Pong");

   //myinit();

   //glutMouseFunc(mouse);
   glutSpecialFunc(mykey);
   glutDisplayFunc(display);
   //glutTimerFunc(20, myTimer, 1);
   glutReshapeFunc(myReshape);
   glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glColorPointer(3, GL_FLOAT, 0, colors);
    glEnable(GL_DEPTH_TEST); //은면제거?
   glutMainLoop();
}

void display()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   //glClearColor(0.0, 0.0, 0.0, 1.0);   /* 배경색 지정 */

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   ////////추가한 부분
   glRotatef(angle1, 0, 1, 0);
   
   draw_bar();
   draw_ball();

   /* 이중 버퍼 사용 */
   glutSwapBuffers();
   glutPostRedisplay();

   glFlush();
}
/*
void myinit(void)
{
   glViewport(0.0, 0.0, w_width, w_height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   //glOrtho(-1, 1, -1, 1, -1, 1);
   //glOrtho(0, 200, 0, 150, -100, 100);
   //gluOrtho2D(0, 200, 0, 150);
   glMatrixMode(GL_MODELVIEW);
}*/

void myReshape(int w, int h)
{
   w_width = w; w_height = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

   glMatrixMode(GL_MODELVIEW);
}

void myTimer(int value)
{
	angle1++;
	glutTimerFunc(20, myTimer, 1);
}

void mouse(int button, int state, int x, int y) 
{
}

void mykey(int key, int x, int y)
{
	if(key == GLUT_KEY_LEFT)
   {
      if(now_x - 0.2 > -1)
         draw_bar(now_x - 0.1);// 상자 왼쪽 이동
   }
   else if(key ==  GLUT_KEY_RIGHT)
   {
      if(now_x + 0.2 < 1)
         draw_bar(now_x + 0.1);// 상자 오른쪽 이동
   }
}

//수정됨
void draw_bar(float now_x)
{
   glTranslatef(0, -0.8, 0);
   glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cubeIndices);
   glLoadIdentity();

}

void draw_ball()
{
   glColor3f(1, 0, 0);

   glutSolidSphere(rsize, 32, 32);

}