#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<GL/glut.h>
using namespace std;
 
double paddle1x, paddle1y;
double paddle2x, paddle2y;
double ballx, bally, balldirx, balldiry;

GLfloat vertices[8][3]={{-10,-30,10}, {-10,30,10},
			 			 {10,30,10},   {10,-30,10},
			 			 {-10,-30,-10},{-10,30,-10},
			 			 {10,30,-10},  {10,-30,-10}};
GLfloat colors[8][3]={{1.0,0.0,0.0},{1.0,0.0,0.0},
				  {1.0,0.0,0.0},{1.0,0.0,0.0},
				  {0.0,0.0,1.0},{0.0,0.0,1.0},
				  {0.0,0.0,1.0},{0.0,0.0,1.0}};
GLubyte cubeIndices[24] = {0,3,2,1,
					   	   2,3,7,6,
    					   0,4,7,3,
						   1,2,6,5,
						   4,5,6,7,
						   0,1,5,4};

int size_up = 3; 
int flag = 0;

 
int player1score, player2score;
char buffer[10];
 
bool keystates[256];
 
void initgame()
{
   ballx = 300-320;
   bally = 400-240;
   paddle1x = 50-320;
   paddle1y = 240-240;
   paddle2x = 590-320;
   paddle2y = 240-240;

   balldirx = 5;
   balldiry = 5;
}

void KeyUpPress(unsigned char key, int x, int y ){
   switch(key){
   case 'w':
      keystates['w'] = false;
      break;
   case 's':
      keystates['s'] = false;
      break;
   case '8':
      keystates['8'] = false;
      break;
   case '2':
      keystates['2'] = false;
      break;
   case 'c':
      break;
   case 27:
      exit(0);

   } 
}
 
void KeyDownPress(unsigned char key, int x, int y ){
    switch(key){
   case 'w':
      keystates['w'] = true;
   break;
 
   case 's':
      keystates['s'] = true;
      break;
 
   case '8':
      keystates['8'] = true;
      break;
   
   case '2':
      keystates['2'] = true;
      break;
   case 'c':
      break;
   case 27:
      exit(0);
 
   }
      
}
 
void drawString (void * font, char *s, float x, float y){
     unsigned int i;
     glRasterPos2f(x, y);
 
     for (i = 0; i < strlen (s); i++)
          glutBitmapCharacter (font, s[i]);
}



void drawpaddle1()
{
	glTranslatef(-280, paddle1y, 0);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cubeIndices);
	//glLoadIdentity();

	/*
   glBegin(GL_POLYGON);
      glColor3f(1, 1, 1);
      glVertex3f (paddle1x - 10, paddle1y - 30,0);
        glVertex3f (paddle1x - 10, paddle1y + 30,0);
        glVertex3f (paddle1x + 10, paddle1y + 30,0);
        glVertex3f (paddle1x + 10, paddle1y - 30,0);
   glEnd();*/
}
 
void drawpaddle2()
{
	glTranslatef(280, paddle2y, 0);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cubeIndices);
	//glLoadIdentity();
	/*
   glBegin(GL_POLYGON);
      glColor3f(1, 1, 1);
      glVertex3f (paddle2x - 10, paddle2y - 30,0);
        glVertex3f (paddle2x - 10, paddle2y + 30,0);
        glVertex3f (paddle2x + 10, paddle2y + 30,0);
        glVertex3f (paddle2x + 10, paddle2y - 30,0);
   glEnd();*/
}
 
void moveball()
{
   ballx = ballx + balldirx;
 
   //check if the ball hit the wall (좌우)
   if(ballx + 5 > 320 || ballx - 5 < -320)   //if(ballx + 5 > 640 || ballx - 5 < 0)
   {
      if(ballx + 5 > 320)
         player1score = player1score + 1;
      if(ballx - 5 < -320)
         player2score = player2score + 1;
      balldirx = -balldirx;
   }   
 
   //check if the ball hit the wall(상하)
   bally = bally + balldiry;
   if(bally + 5 > 240 || bally - 5 < -240)
      balldiry = -balldiry;
 
   //check if the ball hit the paddle
   if(balldirx >= 1)
   {
      if(ballx + 5 > paddle2x - 10 && ballx - 5 < paddle2x + 10 && bally - 5 < paddle2y + 30 && bally + 5 > paddle2y - 30)
      {
         balldirx = -balldirx;
      }
   }
   else
   {
      if(ballx + 5 > paddle1x - 10 && ballx - 5 < paddle1x + 10 && bally - 5 < paddle1y + 30 && bally + 5 > paddle1y - 30)
      {
         balldirx = -balldirx;
      }
   }
}
 
void drawball()
{
   if((player1score>3 || player2score>3)  & flag ==0)//수정한거
      {size_up +=7;//수정한거
   flag =1;}//수정한거

   glTranslatef(ballx,bally,0);         
   glutSolidSphere(5,32,32);
   glFlush();
   //glBegin(GL_POLYGON);
     // glColor3f(1, 1, 1);
      /*glVertex2f (ballx - 5, bally - 5);
        glVertex2f (ballx - 5, bally + 5);
        glVertex2f (ballx + 5, bally + 5);
        glVertex2f (ballx + 5, bally - 5);*/

      /*glVertex3f (ballx - size_up, bally - size_up,0);
        glVertex3f (ballx - size_up, bally + size_up,0);
        glVertex3f (ballx + size_up, bally + size_up,0);
        glVertex3f (ballx + size_up, bally - size_up,0);*/

  // glEnd();
}
 
char *scoreformat(char *score, int size)
{
   char *formattedscore = new char[size];
   int scorelength;
   int k = 0;
 
   scorelength = strlen(score);
 
   for(int i = 0; i <= size - 1; i++)
   {
      if(i <= (size - 1) - scorelength)
      {
         formattedscore[i] = '0';
      }
      else
      {
         formattedscore[i] = score[k++];
      }
   }
   return formattedscore;
}
 

void display()
{
   glMatrixMode(GL_MODELVIEW);   
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    
   glLoadIdentity();   
   gluLookAt(0,0,1, 0,0,0, 0,1,0);

   if(player1score>10 || player2score>10)
   {      
      if(player1score > player2score)
      {
         glutSwapBuffers();
         glClear(GL_COLOR_BUFFER_BIT);
         drawString(GLUT_BITMAP_HELVETICA_18, "player1 win!!!!!!!!!!!", 300, 240);
      }
      else
      {
         glutSwapBuffers();
         glClear(GL_COLOR_BUFFER_BIT);
         drawString(GLUT_BITMAP_HELVETICA_18, "player2 win!!!!!!!!!!!", 300, 240);
      }
   }

   else{
   //////////////////////////////////
   glClear(GL_COLOR_BUFFER_BIT);


   drawString(GLUT_BITMAP_HELVETICA_18, "Player1:", -310, -220);
   itoa(player1score, buffer, 10);
   drawString(GLUT_BITMAP_HELVETICA_18, buffer, -310, -200);
 
   drawString(GLUT_BITMAP_HELVETICA_18, "Player2:", 240, -220);
   itoa(player2score, buffer, 10);
   drawString(GLUT_BITMAP_HELVETICA_18, buffer, 240, -200);
 
   if(keystates['s'] == true)
      if(paddle1y - 30 > -240)
         paddle1y = paddle1y - 5;
   if(keystates['w'] == true)
      if(paddle1y + 30 < 240)
         paddle1y = paddle1y + 5;
   drawpaddle1();

 
   if(keystates['8'] == true)
      if(paddle2y - 30 > -240)
         paddle2y = paddle2y - 5;
   if(keystates['2'] == true)
      if(paddle2y + 30 < 240)
         paddle2y = paddle2y + 5;
   drawpaddle2();
   
   moveball();

   drawball();
 
   glutSwapBuffers();
}

}
 
void reshape(int x, int y)
{
   glViewport(0, 0, x, y);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   //glOrtho(0, 640, 0, 480, -10, 10);
   glOrtho(-320, 320, -240, 240, -200, 200);
   glMatrixMode(GL_MODELVIEW);
}
 
void main(int argc, char **argv)
{
   initgame();
   glutInit(&argc,argv);
   glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
   glutInitWindowPosition(100,100);
   glutInitWindowSize(640,480);
   glutCreateWindow("Pong");
   glutReshapeFunc(reshape);
   glutDisplayFunc(display);
   //glutIgnoreKeyRepeat(1);
   glutKeyboardFunc(KeyDownPress);
   //glutKeyboardUpFunc(KeyUpPress);
   glutIdleFunc(display);

   /*입방체를 위한 코드*/
   glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glColorPointer(3, GL_FLOAT, 0, colors);

   glutFullScreen();   
   glEnable(GL_DEPTH_TEST);
   glutMainLoop();


}