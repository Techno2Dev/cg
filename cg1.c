/* g++ cg1.c -lglut -lGL -lGLEW -lGLU -o cg1
./pat
*/

#include<GL/glut.h>
#include <GL/gl.h>
#include<stdlib.h>
#include<stdio.h>
#include<iostream>

#define ROUND(x) ((int)(x+0.5))

int x1=10,x2=150,y1=10,y2=100;
//int x1,x2,y1,y2;

void coordinate_system(void)
{
	glBegin(GL_POINTS);
	glColor3f (1.0, 1.0, 1.0);
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
	 glClearColor (0.0, 0.0, 0.0, 0.0);
 	glOrtho(-200.0, 200.0, -200.0, 200.0, -1.0, 1.0);
 }

void drawpat(int ax,int ay,int bx,int by,int cx,int cy,int dx,int dy,int n)
{
	int m1x,m1y,m2x,m2y,m3x,m3y,m4x,m4y;
	ddaline(ax,ay,bx,by);
	ddaline(bx,by,cx,cy);
	ddaline(cx,cy,dx,dy);
	ddaline(dx,dy,ax,ay);
	m1x=(ax+bx)/2;
	m1y=(ay+by)/2;
	m2x=(bx+cx)/2;
	m2y=(by+cy)/2;
	m3x=(cx+dx)/2;
	m3y=(cy+dy)/2;
	m4x=(dx+ax)/2;
	m4y=(dy+ay)/2;
	n--;
	if(n!=0)
	{
		drawpat(m1x,m1y,m2x,m2y,m3x,m3y,m4x,m4y,n);
	}
}
void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f (1.0, 0.0, 0.0);
	coordinate_system();//draw Cartesian coordinate system
	drawpat(x1,y1,x1,y2,x2,y2,x2,y1,3);
}
int main(int argc, char** argv)
{
	//printf("Enter the points\n");
	//scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
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
