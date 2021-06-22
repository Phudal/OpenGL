#include <GL/GLUT.h>
#include <GL/glu.h>
#include <GL/gl.h>

// �ݼ��� ��¥�� �ð�
static int VDay = 0, VTime = 0;

// ������ ��¥�� �ð�
static int Day = 0, Time = 0;

// ȭ���� ��¥�� �ð�
static int MDay = 0, MTime = 0;

GLfloat black[] = { 0.0f,0.0f,0.0f,1.0f };
GLfloat yellow[] = { 0.7f,0.3f,0.0f,1.0f };
GLfloat Position[] = { 0,0,0,0.1 };

GLfloat light_specular[] = { 1.0,1.0,1.0,1.0 };
GLfloat light_diffuse[] = { 0.8,0.8,0.8,1.0 };
GLfloat light_ambient[] = { 0.3,0.3,0.3,1.0 };

// ī�޶� �κ��� ��� �غôµ� �ڲ� ������ �����Ǿ
// �Ϻη� �Լ��� �����ϴ�.
void MyCamera() 
{
    glLoadIdentity();
    gluLookAt(0, 2, 5,
        0, 0, 0,
        0, 0, 0);
    glRotatef(45, 0, 1, 0);
}

// ���� �κ�
void InitLight() 
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
}

void MyDisplay() 
{
    glClear(GL_COLOR_BUFFER_BIT
        | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW); // ���� matrix�� �𵨺��
    

    // ����
    glLoadIdentity(); // ���� ��ǥ�� �ʱ�ȭ
    glTranslatef(0.0, 0.0, -2.0);
    glPushMatrix(); // ������ ǥ���ϴ� ���� ��ǥ�� �߰�
    //������ ����
    glRotatef((float)Day, 0.0, 1.0, 0.0);
    glTranslatef(0.7, 0.0, 0.0);
    //������ ����
    glRotatef((float)Time, 0.0, 1.0, 0.0);
    glColor3f(0.0, 0.0, 1.0); // �Ķ�
    glutSolidSphere(0.1, 30, 8); // ���� �׸���

    // ��
    glPushMatrix(); // ���� ǥ���ϴ� ���� ��ǥ�� �߰�
    //���� ����
    glRotatef((float)Day, 0.0, 1.0, 0.0);
    glTranslatef(0.2, 0.0, 0.0);
    glColor3f(0.4, 0.4, 0.4); // ȸ��
    glutSolidSphere(0.04, 30, 8); // �� �׸���


    glPopMatrix(); // ������ �� ���� ���� ��ǥ�踦 ���� ��
    glPopMatrix(); // ������ �� ������ ���� ��ǥ�踦 ����

    // ȭ��
    glLoadIdentity(); // ���� ��ǥ�� �ʱ�ȭ
    glPushMatrix(); // ȭ���� ǥ���ϴ� ���� ��ǥ�� �߰�
    // ȭ���� ����
    glRotatef((float)(MDay), 0.0, 1.0, 0.0); // ȭ���� ���� �ֱ�� �������� ��������� 2�� ������ ����
    glTranslatef(1.4, 0.0, 0.0);
    // ȭ���� ����
    glRotatef((float)(MTime), 0.0, 1.0, 0.0); // ȭ���� ����  �ֱ�� �������� ��������� 2�� ������ ����
    glColor3f(1.0, 0.0, 0.0); // ����
    glutSolidSphere(0.1, 30, 16); // ȭ�� �׸���

    glPopMatrix(); // �����ص� ȭ���� ���� ��ǥ�踦 ����

    //�ݼ�
    glLoadIdentity(); // ���� ��ǥ�� �ʱ�ȭ
    glTranslatef(0.0, 0.0, -1.0);
    glPushMatrix();
    //�ݼ��� ����
    glRotatef((float)VDay, 0.0, 1.0, 0.0);
    glTranslatef(0.5, 0.0, 0.0);
    // �ݼ��� ����
    glRotatef((float)VTime, 0.0, 1.0, 0.0);
    glColor3f(1.0, 1.0, 0.0); // ���
    glutSolidSphere(0.1, 30, 8); // �ݼ� �׸���
    glPopMatrix(); // �����ص� �ݼ��� ���� ��ǥ�踦 ����

    /***�¾�***/
    glColor3f(1.0, 0.7, 0.0); // ��Ȳ
    glLightfv(GL_LIGHT0, GL_POSITION, Position); // ������ �����մϴ�
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, yellow); // ���� ���� ���� �����մϴ�.
    glutSolidSphere(0.2, 30, 16); // �¾� �׸���
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black); // �¾� ���� ���� �ʴ� �κ��� �׸��ڰ� �� ���Դϴ�.

    glutSwapBuffers();
}

void MyTimer(int value) {
    VDay = (VDay + 15) % 360;   // �ݼ��� ���� �ֱ�� �������� 1.5�� ������ ����
    VTime = (VTime + 10) % 360; // �ݼ��� ���� �ֱ�� �������� 1.5�� ������ ����

    Day = (Day + 10) % 360; 
    Time = (Time + 15) % 360;

    MDay = (MDay + 5) % 360; // ȭ���� ���� �ֱ�� �������� 2�� ������ ����
    MTime = (MTime + 30) % 360; // ȭ���� ���� �ֱ�� �������� 2�� ������ ����

    glutTimerFunc(100, MyTimer, 1);
    glutPostRedisplay();
}

// �� �Լ��� ī�޶� ������ ���� �ݹ� �Լ����µ�, ���� ��ȯ�� ��Ȱ�ϰ� ���� �ʽ��ϴ�
void MyMouseClick(GLint Button, GLint State, GLint x, GLint y) 
{   
    if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN)
        gluLookAt(0, 0, 1.0, 0, 0, 0, 0, 0, 0);

    else if (Button == GLUT_RIGHT_BUTTON && State == GLUT_DOWN)
        gluLookAt(0, 1.0, 0, 0, 0, 0, 0, 0, 0);    
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Solar system");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    InitLight();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // glOrtho�� view volume�� �����ϴ� �Լ�
    // �ΰ��� x, y, z�� ������ ǥ�� ��
    glOrtho(-3.0, 3.0, -3.0, 3.0, -2.0, 3.0); 
    glutDisplayFunc(MyDisplay);
    glutMouseFunc(MyMouseClick);
    glutTimerFunc(100, MyTimer, 1);
    glutMainLoop();
    return 0;
}