//g++ mouse.c -lm -lglut -lGL -lGLU -o cube
/*void glutMouseFunc(void (*func)(int button, int state, int x, int y));
Where,

func –> Function that handles the mouse event i.e. when mouse click is detected, func is called
func must have three parameters, as we see in above syntax
void mouseClick(int button, int state, int x, int y)

The first parameter is button, its value is one of the following
    GLUT_LEFT_BUTTON – when left mouse button click is detected
    GLUT_RIGHT_BUTTON  - when right mouse button click is detected
    GLUT_MIDDLE_BUTTON – when middle mouse button click is detected

The second parameter is state, its value is one of the following

    GLUT_DOWN – When mouse button is pressed
    GLUT_UP – When mouse button is released

When callback is generated with GLUT_DOWN GLUT environment assumes that GLUT_UP comes afterward even if mouse is not inside the window.
Other two parameters x and y are coordinates of the point where mouse pointer is moved.
Detecting Mouse Motion
GLUT provides two types of function as according to types of motion detection either Active Motion or Passive Motion. Active Motion refers to the Motion of mouse when there is Click and Passive motion refers to motion of a mouse without a click. The syntax of two functions are
glutMotionFunc(void (*func)(int x, int y)); //for Active motion
glutMousePassiveMotionFunc(void (*func)(int x, int y)) // for Passive motion
Where,
func –> Function that responsible for handling respective motion
x, y –> coordinates of the mouse relative to upper left corner of window*/
#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
int n;
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

void init()
{
 glClearColor(0.0,0.0,0.0,0.0);
 glMatrixMode(GL_PROJECTION);
 gluOrtho2D(0,500,0,500);
}


int round1(double number)
{
 return (number>=0) ? (int)(number+0.5):(int)(number-0.5);
}
void setPixel(GLint x,GLint y)
{
 glColor3f(0.0f,0.0f,0.0f);
 glBegin(GL_POINTS);
 glVertex2f(x,y);
 glEnd();
}
void DDALine(int x0,int y0,int x1,int y1)
{
 int dy=y1-y0;
 int dx=x1-x0;
 int steps,i;
 float xinc,yinc,x=x0,y=y0;
 if(abs(dx)>abs(dy))
 {
  steps=abs(dx);
 }
 else
 {
  steps=abs(dy);
 }
 xinc=(float)dx/(float)steps;
 yinc=(float)dy/(float)steps;
 setPixel(round1(x),round1(y));
 for(i=0;i<steps;i++)
 {
  x+=xinc;
  y+=yinc;
  setPixel(round1(x),round1(y));
 }
 glutSwapBuffers();
}
int k=1;
int X[10],Y[10];
void mouseClick(int button, int state, int x, int y)
{
 switch(button)
 {
    case GLUT_LEFT_BUTTON:
     if (state == GLUT_DOWN)
     {   
      X[k]=x;
      Y[k]=500-y; 
      if(k%2==0)
      {
       DDALine(X[k-1],Y[k-1],X[k],Y[k]);
      }
      else if(k>1 && k%2!=0)
      {
       DDALine(X[k-1],Y[k-1],X[k],Y[k]);
      }
           glutSwapBuffers();
      k++; 
     }
     break;
   default:
     break;
   }
    fflush(stdout);                         // Force output to stdout
  
}
void Display()
{
 glClearColor(1.0f,1.0f,1.0f,0);
 glClear(GL_COLOR_BUFFER_BIT);
 coordinate_system();//draw Cartesian coordinate system
 glFlush();
}
int main(int argc,char** argv)
{
 glutInit(&argc,argv);
 glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
 glutInitWindowPosition(50,50);
 glutInitWindowSize(500,500);
 glutCreateWindow("Draw polygon using Mouse");
 init();
 glutDisplayFunc(Display);
 glutMouseFunc(mouseClick);//Calling to mouse function
 glutMainLoop();//main function is in loop 
 return 0;
}
