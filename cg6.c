/* g++ cg7.c -lglut -lGL -lGLEW -lGLU -o pat
./pat
*/
#include<GL/glut.h>
#include <GL/gl.h>
#include<stdlib.h>
#include<stdio.h>
#include<iostream>

#define ROUND(x) ((int)(x+0.5))

int x1=10,x2=150,y1=10,y2=10;

void coordinate_system(void)
{
	glBegin(GL_POINTS);
	glColor3f (0.0, 0.0, 0.0);
	 for(int i=-200 ; i<=200 ; i++)
	 {
		 glVertex2s(i,0);
 		 glVertex2s(0,i);
	 }
	 for(int i=-2; i<=2 ; i++)
	 {
		 glVertex2s(195+i,4+i);
		 glVertex2s(195-i,4+i);
	 } 
	 for(int i=0; i<=2 ; i++)
	 {
		 glVertex2s(4+i,195+i);
		 glVertex2s(4-i,195+i);
		 glVertex2s(4,195-i);
	 }

	glEnd();
	glFlush();
}
void putpixel(int x, int y)
{
	glColor3f (1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	glVertex2s(ROUND(x),ROUND(y));
	glEnd();
}
void ddaline(int xa,int ya,int xb,int yb)
 {
	int dx=xb-xa,dy=yb-ya,steps,k;
	float xIncrement,yIncrement,x=xa,y=ya;

	 if(abs(dx)>abs(dy))
 		steps=abs(dx);
	 else 
		steps=abs(dy);
 
	 xIncrement=dx/(float)steps;
	 yIncrement=dy/(float)steps;

	for(k=0;k<steps;k++)
	 {
		putpixel(ROUND(x),ROUND(y)); 
		x+=xIncrement;
		 y+=yIncrement;
	 }
	 glFlush();
 }
void init(void)
 {
	 glClearColor (1.0, 1.0, 1.0, 1.0);
 	glOrtho(-200.0, 200.0, -200.0, 200.0, -1.0, 1.0);
 }

void drawpat(int ax,int ay,int bx,int by)
{
	int m1x,m1y,m2x,m2y,m3x,m3y,m4x,m4y,n,len,len1,len2;
	m1x=(ax+bx)/2;
	m1y=(ay+by)/2;
	m2x=(ax+m1x)/2;
	m2y=(ay+m1y)/2;
	m3x=(m1x+bx)/2;
	m3y=(m2x+by)/2;
	len1=(m3x-m1x);
	len2=(m3y=m1y);
	if(len1>=len2)
		len=len1;
	else
		len=len2;

	m4x=m1x;
	m4y=(1.732*len)/2;
	ddaline(ax,ay,m2x,m2y);
	ddaline(m2x,m2y,m4x,m4y);
	ddaline(m4x,m4y,m3x,m3y);
	ddaline(m3x,m3y,bx,by);
	
}
void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f (1.0, 0.0, 0.0);
	coordinate_system();
	drawpat(x1,y1,x2,y2);
}


int main(int argc, char** argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (500, 500);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("Draw Pattern");
	init ();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
