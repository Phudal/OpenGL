#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

void MyDisplay()
{

    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_LINE_LOOP);
    glVertex3f(1.0, 0.0, 0.0);
    glVertex3f(-1.0, 0.0, 0.0);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, -1.0, 0.0);
    glEnd();

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
    for (double x = -1.0; x <= 1.0; x += 0.01)
    {
        glVertex3f(x, x * x, 0.0);
    }
    glEnd();
    glFlush();
}

int main()
{
    glutCreateWindow("OpenGL Drawing Example");
    glutDisplayFunc(MyDisplay);
    glutMainLoop();
    return 0;
}