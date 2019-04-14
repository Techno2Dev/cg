//g++ exp2.c -lglut -lGL -lGLEW -lGLU -o exp2 



#include<GL/glut.h> 
#include <GL/gl.h> 
#include<stdlib.h> 
#include<stdio.h> 
#include<iostream> 

#define ROUND(x) ((int)(x+0.5)) 

int x1=1,x2=100,y1=1,y2=1; 
int xc, yc; 
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
	 glClearColor (1.0, 1.0, 1.0, 0.0); 
 	glOrtho(-200.0, 200.0, -200.0, 200.0, -1.0, 1.0); 
 } 
void plot_point(int x, int y) 
{ 
  glBegin(GL_POINTS); 
  glVertex2i(xc+x, yc+y); 
  glVertex2i(xc+x, yc-y); 
  glVertex2i(xc+y, yc+x); 
  glVertex2i(xc+y, yc-x); 
  glVertex2i(xc-x, yc-y); 
  glVertex2i(xc-y, yc-x); 
  glVertex2i(xc-x, yc+y); 
  glVertex2i(xc-y, yc+x);  
glEnd(); 
} 
// Function to draw a circle using bresenham's 
// circle drawing algorithm 
void midpt_circle(int r) 
{ 
  int x=0,y=r; 
  float pk=(5.0/4.0)-r; 

  /* Plot the points */ 
  /* Plot the first point */ 
  plot_point(x,y); 
  int k; 
  /* Find all vertices till x=y */ 
  while(x < y) 
  { 
    x = x + 1; 
    if(pk < 0) 
      pk = pk + 2*x+1; 
    else 
    { 
      y = y - 1; 
      pk = pk + 2*(x - y) + 1; 
    } 
    plot_point(x,y); 
  } 
  glFlush(); 
} 


void drawpat(int ax,int ay,int bx,int by) 
{ 
	int m1x,cx,cy,r; 
	float lol,hot; 
	m1x=(ax+bx)/2;//mid pt of line in x term only 
	lol=(bx-ax);//length of line 
	hot=0.866*lol;//height of triangle 
	cx=m1x;cy=hot;//c point of triangle 
	//draw a triangle	 
	ddaline(ax,ay,bx,by); 
	ddaline(bx,by,cx,cy); 
	ddaline(cx,cy,ax,ay); 
	//radius of  inscribed circle 
	r=0.2886*lol; 
xc=m1x; 
	yc=int(r); 
	midpt_circle(r); 
midpt_circle(2*r); 
} 

void display(void) 
{ 
	glClear (GL_COLOR_BUFFER_BIT); 
	glColor3f (1.0, 0.0, 0.0); 
	coordinate_system();//draw Cartesian coordinate system 
	drawpat(x1,y1,x2,y2); 
} 
int main(int argc, char** argv) 
{ 
	glutInit(&argc, argv); 
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); 
	glutInitWindowSize (500, 500); 
	glutInitWindowPosition (100, 100); 
	glutCreateWindow ("Draw In & circumscribed circle with triangle Pattern "); 
	init (); 
	glutDisplayFunc(display); 
	glutMainLoop(); 
	return 0; 
}




