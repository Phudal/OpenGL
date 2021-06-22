#include <GL/glut.h>

void MyDisplay1() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
	glVertex3f(-0.3f, -0.2f, 0.0);
	glVertex3f(0.1f, -0.2f, 0.0);
	glVertex3f(0.1f, 0.2f, 0.0);
	glVertex3f(-0.3f, 0.2f, 0.0);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0.3f, 0.0, 0.0);
	glVertex3f(0.6f, -0.3f, 0.0);
	glVertex3f(0.9f, 0.0, 0.0);
	glVertex3f(0.6f, 0.3f, 0.0);
	glEnd();
	glFlush();
}

int main() {
	glutCreateWindow("OpenGL Drawing Example");
	glutDisplayFunc(MyDisplay1);
	glutMainLoop();
	return 0;
}