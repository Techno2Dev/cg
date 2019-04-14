#include <GL/glut.h>
#include <math.h>
/* Handler for window-repaint event. Call back when the window first appears and
   whenever the window needs to be re-painted. */
void Init()
{
    glClearColor(0.0,1.0,1.0,0);     // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT);    // Clear the color buffer (background)
    glColor3f(0.0,0.0,1.0);
 glViewport(0 , 0 , 640 , 480);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0 , 640 , 0 , 480);
}

void DDALine(double X1, double Y1, double X2, double Y2) {

    double dx=X2-X1 , dy=Y2-Y1,steps;
    float xInc,yInc,x=X1,y=Y1;
    steps=(abs(dx)>abs(dy))? abs(dx):abs(dy);
    xInc=dx/(float)steps;
    yInc=dy/(float)steps;

    glBegin(GL_POINTS);
    {
        glVertex2d(x,y);
        for(int k=0;k<steps;k++)
        {
            x+=xInc;
            y+=yInc;
            glVertex2d(x,y);
        }
    }glEnd();
}
void ChessBoard()
{
            Init();
            int i,  k = 0,j;
            float cbvalue;  //color bit value
            //Chess board outline
          /*  for(i=0;i<9;i++)
            {
                DDALine(50,50+k,450,50+k);
                DDALine(50+k,50,50+k,450);
                k+=50;
            }*/
  //Now variable i and j represents row  and column number from bottom to top respectively

            //To Fill the Chess Board  cells with alternate black and white
            cbvalue = 1.0;

            int row=4;
            for(i=0; i<8; i++)
            {
                int col = 4; row +=50;
                for(j=0; j<8; j++)
                {
                    glColor3f(cbvalue, cbvalue,cbvalue);
                    for(int r=0; r<50; r++)
                        DDALine(50 + col,row+r,100 + col,row+r);
                    col = col+50;
                    if (j<7)
                        if (cbvalue == 1.0)
                                cbvalue =0.0;
                        else
                                cbvalue =1.0;
                }
             }
            glFlush();
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
   glutInit(&argc, argv);                 // Initialize GLUT
   glutCreateWindow("OpenGL ChessBoard using DDA Line Algorithm");
        // Create a window with the given title
   glutInitWindowSize(640, 480);   // Set the window's initial width & height
   glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
   glutDisplayFunc(ChessBoard); // Register display callback handler for window re-paint

   glutMainLoop();           // Enter the event-processing loop
   return 0;
}
