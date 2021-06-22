#include <GL/glut.h>
#include <time.h>
#include <math.h>
#include <GL/gl.h>
#pragma warning(disable:4996)

static float p_sec = 0;

void draw_arm(float angle, float length)
{
    glPushMatrix();
    glRotatef(-angle, 0.0f, 0.0f, 1.0f);
    glScalef(10 * length, 1.0f, 1.0f);
    if (length == 1.0f)
        glColor3f(0.0, 0.0, 1.0);
    else if (length == 1.2f)
        glColor3f(0.0, 1.0, 0.0);
    else if (length == 1.4f)       
        glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.1, 0.0, 0.0);
    glVertex3f(0.0, 0.02, 0.0);
    glVertex3f(0.0, -0.02, 0.0);
    glEnd();
    glPopMatrix();
}

void pendulum() 
{
    glPushMatrix();

    glRotatef(cos(p_sec) * 50, 0.0f, 0.0, -1.0f);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.02, 0.0, 0.0);
    glVertex3f(-0.02, -1.0, 0.0);
    glVertex3f(-0.05, -1.2, 0.0);
    glVertex3f(0.0, -1.5, 0.0);
    glVertex3f(0.05, -1.2, 0.0);
    glVertex3f(0.02, -1.0, 0.0);
    glVertex3f(0.02, 0.0, 0.0);
    glEnd();

    glPopMatrix();

}

void tick_mark()
{
    glColor3f(0.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.1, 0.0, 0.0);
    glVertex3f(0.0, 0.02, 0.0);
    glVertex3f(0.0, -0.02, 0.0);
    glEnd();
}

void draw_plate()
{
    for (int i = 0; i < 60; i++)
    {
        glPushMatrix();

        glRotatef(i * 6.0f, 0.0f, 0.0f, -1.0f);
        glTranslatef(1.55f, 0.0f, 0.0f);

        if (i % 5 == 0)
            glScalef(2.0f, 1.0f, 1.0f);

        tick_mark();

        glPopMatrix();
    }
}

void Myreshape(int w, int h)
{
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (w <= h)
        gluOrtho2D(-2.0, 2.0, -2.0 * (GLfloat)h / (GLfloat)w, 2.0 * (GLfloat)h / (GLfloat)w);
    else
        gluOrtho2D(-2.0 * (GLfloat)w / (GLfloat)h, 2.0 * (GLfloat)w / (GLfloat)h, -2.0, 2.0);
}

void Mydisplay()
{
    struct tm* nowtime;
    time_t t;
    float hour, minute, second;

    time(&t);

    nowtime = localtime(&t);

    hour = (nowtime->tm_hour % 12) * 30.0 + 90;
    minute = nowtime->tm_min * 6.0 + 90;
    second = nowtime->tm_sec * 6.0 + 90;

    p_sec = second;

    glClear(GL_COLOR_BUFFER_BIT);

    pendulum();
    draw_plate();
    draw_arm(hour, 1.0f);
    draw_arm(minute, 1.2f);
    draw_arm(second, 1.4f);

    glFlush();
}

void Idle()
{
    Mydisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Analog Clock");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glutDisplayFunc(Mydisplay);
    glutReshapeFunc(Myreshape);
    glutIdleFunc(Idle);
    glutMainLoop();
    return 0;
}