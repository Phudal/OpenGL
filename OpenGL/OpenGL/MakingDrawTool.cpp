#include <GL/glut.h>
#include <GL/GL.h>
#include <GL/GLU.h>

GLint TopLeftX, TopLeftY, BottomRightX, BottomRightY;
GLfloat r = 0, g = 0, b = 0;

void MyDisplay() {
	glViewport(0, 0, 300, 300);
	glFlush();
}


void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y) {
	// 마우스 왼쪽버튼을 눌렀을때 실행
	if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN) {
		TopLeftX = X;
		TopLeftY = Y;
	}
}

void MyMouseMove(GLint X, GLint Y) {
	BottomRightX = X;
	BottomRightY = Y;
	glBegin(GL_LINES);
	glColor3f(r, g, b);
	glVertex3f(TopLeftX / 300.0, (300 - TopLeftY) / 300.0, 0.0);
	glVertex3f(BottomRightX / 300.0, (300 - BottomRightY) / 300.0, 0.0);
	glEnd();
	TopLeftX = BottomRightX;
	TopLeftY = BottomRightY;
	glutPostRedisplay();
}



int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("OpenGL Drawing Example");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, 1.0, -1.0);
	glutDisplayFunc(MyDisplay);
	glutMouseFunc(MyMouseClick);
	glutMotionFunc(MyMouseMove);
	glutMainLoop();
	return 0;
}