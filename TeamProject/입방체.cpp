#include <gl\glut.h>

GLfloat theta[3];
int axis = 0; //0 x축, 1 y축, 2 z축
GLfloat vertices[8][3]={{-1.0,-1.0,1.0}, {-1.0,1.0,1.0},
			 	    {1.0,1.0,1.0},   {1.0,-1.0,1.0},
			 	    {-1.0,-1.0,-1.0},{-1.0,1.0,-1.0},
			 	    {1.0,1.0,-1.0},  {1.0,-1.0,-1.0}};
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


void spinCube() 
{
	theta[axis] += 0.5;
	
	if( theta[axis] > 360.0 ) 
		theta[axis] -= 360.0;
	glutPostRedisplay();
}

void mouse(int btn, int state, int x, int y)
{
   if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
           axis = 0;
   if(btn==GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) 
           axis = 1;
   if(btn==GLUT_RIGHT_BUTTON && state == GLUT_DOWN) 
           axis = 2;
}

void colorcube()
{
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cubeIndices);
	/*
	glBegin(GL_TRIANGLES); 
      glVertex3f(-0.5, 0, 0); 
      glVertex3f(0.5, 0, 0);  
      glVertex3f(0, 1, 0);
    glEnd();
	*/
}

void display()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();
   glRotatef(theta[0], 1.0, 0.0, 0.0);
   glRotatef(theta[1], 0.0, 1.0, 0.0);
   glRotatef(theta[2], 0.0, 0.0, 1.0); 
   colorcube();	//큐브 그림
   glutSwapBuffers();
}

void main(int argc, char **argv) 
{    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("colorcube");
	glMatrixMode(GL_PROJECTION);
	glOrtho(-2, 2, -2, 2, -2, 2); 
	glMatrixMode(GL_MODELVIEW);
    //glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutIdleFunc(spinCube);
    glutMouseFunc(mouse);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glColorPointer(3, GL_FLOAT, 0, colors);
    glEnable(GL_DEPTH_TEST); //은면제거?
    glutMainLoop();
}
