#include <GL/GLUT.h>
#include <GL/glu.h>
#include <GL/gl.h>

// 금성의 날짜와 시간
static int VDay = 0, VTime = 0;

// 지구의 날짜와 시간
static int Day = 0, Time = 0;

// 화성의 날짜와 시간
static int MDay = 0, MTime = 0;

GLfloat black[] = { 0.0f,0.0f,0.0f,1.0f };
GLfloat yellow[] = { 0.7f,0.3f,0.0f,1.0f };
GLfloat Position[] = { 0,0,0,0.1 };

GLfloat light_specular[] = { 1.0,1.0,1.0,1.0 };
GLfloat light_diffuse[] = { 0.8,0.8,0.8,1.0 };
GLfloat light_ambient[] = { 0.3,0.3,0.3,1.0 };

// 카메라 부분을 계속 해봤는데 자꾸 시점이 고정되어서
// 일부러 함수를 뺐습니다.
void MyCamera() 
{
    glLoadIdentity();
    gluLookAt(0, 2, 5,
        0, 0, 0,
        0, 0, 0);
    glRotatef(45, 0, 1, 0);
}

// 조명 부분
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
    glMatrixMode(GL_MODELVIEW); // 모델의 matrix를 모델뷰로
    

    // 지구
    glLoadIdentity(); // 전역 좌표계 초기화
    glTranslatef(0.0, 0.0, -2.0);
    glPushMatrix(); // 지구을 표현하는 지역 좌표계 추가
    //지구의 공전
    glRotatef((float)Day, 0.0, 1.0, 0.0);
    glTranslatef(0.7, 0.0, 0.0);
    //지구의 자전
    glRotatef((float)Time, 0.0, 1.0, 0.0);
    glColor3f(0.0, 0.0, 1.0); // 파랑
    glutSolidSphere(0.1, 30, 8); // 지구 그리기

    // 달
    glPushMatrix(); // 달을 표현하는 지역 좌표계 추가
    //달의 공전
    glRotatef((float)Day, 0.0, 1.0, 0.0);
    glTranslatef(0.2, 0.0, 0.0);
    glColor3f(0.4, 0.4, 0.4); // 회색
    glutSolidSphere(0.04, 30, 8); // 달 그리기


    glPopMatrix(); // 저장해 둔 달의 지역 좌표계를 제거 함
    glPopMatrix(); // 저장해 둔 지구의 지역 좌표계를 제거

    // 화성
    glLoadIdentity(); // 전역 좌표계 초기화
    glPushMatrix(); // 화성을 표현하는 지역 좌표계 추가
    // 화성의 공전
    glRotatef((float)(MDay), 0.0, 1.0, 0.0); // 화성의 공전 주기는 지구보다 상대적으로 2배 느리게 설정
    glTranslatef(1.4, 0.0, 0.0);
    // 화성의 자전
    glRotatef((float)(MTime), 0.0, 1.0, 0.0); // 화성의 자전  주기는 지구보다 상대적으로 2배 빠르게 설정
    glColor3f(1.0, 0.0, 0.0); // 빨강
    glutSolidSphere(0.1, 30, 16); // 화성 그리기

    glPopMatrix(); // 저장해둔 화성의 지역 좌표계를 제거

    //금성
    glLoadIdentity(); // 전역 좌표계 초기화
    glTranslatef(0.0, 0.0, -1.0);
    glPushMatrix();
    //금성의 공전
    glRotatef((float)VDay, 0.0, 1.0, 0.0);
    glTranslatef(0.5, 0.0, 0.0);
    // 금성의 자전
    glRotatef((float)VTime, 0.0, 1.0, 0.0);
    glColor3f(1.0, 1.0, 0.0); // 노랑
    glutSolidSphere(0.1, 30, 8); // 금성 그리기
    glPopMatrix(); // 저장해둔 금성의 지역 좌표계를 제거

    /***태양***/
    glColor3f(1.0, 0.7, 0.0); // 주황
    glLightfv(GL_LIGHT0, GL_POSITION, Position); // 조명을 생성합니다
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, yellow); // 재질 색생 등을 설정합니다.
    glutSolidSphere(0.2, 30, 16); // 태양 그리기
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black); // 태양 빛이 닿지 않는 부분은 그림자가 져 보입니다.

    glutSwapBuffers();
}

void MyTimer(int value) {
    VDay = (VDay + 15) % 360;   // 금성의 공전 주기는 지구보다 1.5배 빠르게 설정
    VTime = (VTime + 10) % 360; // 금성의 자전 주기는 지구보다 1.5배 느리게 설정

    Day = (Day + 10) % 360; 
    Time = (Time + 15) % 360;

    MDay = (MDay + 5) % 360; // 화성의 공전 주기는 지구보다 2배 느리게 설정
    MTime = (MTime + 30) % 360; // 화성의 자전 주기는 지구보다 2배 빠르게 설정

    glutTimerFunc(100, MyTimer, 1);
    glutPostRedisplay();
}

// 이 함수도 카메라 조작을 위한 콜백 함수였는데, 시점 변환이 원활하게 되지 않습니다
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

    // glOrtho는 view volume을 설정하는 함수
    // 두개씩 x, y, z의 범위를 표현 함
    glOrtho(-3.0, 3.0, -3.0, 3.0, -2.0, 3.0); 
    glutDisplayFunc(MyDisplay);
    glutMouseFunc(MyMouseClick);
    glutTimerFunc(100, MyTimer, 1);
    glutMainLoop();
    return 0;
}