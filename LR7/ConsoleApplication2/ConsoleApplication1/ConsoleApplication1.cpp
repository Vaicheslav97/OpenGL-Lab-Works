
#include <windows.h>
//	������������ ���� ��� ���������� �������������� OpenGL - glut
#include "glut.h"

//	���������� ����������� ���������� - ������ ������� ������ ������:
//	������ w � ����� h
static int w = 0, h = 0, rt = 0;
static float Angle = 0.0f;

//	������� ���������� ��� ��������� � ������� ���� ����������
void Init(void) {
	//	��������� OpenGL ����� ������ ������� ������ ����� - ������
	glClearColor(255, 255, 255, 1.0f);
}	

void Update(void) {
	
	Angle += 0.05f;

	glClear(GL_COLOR_BUFFER_BIT);
	
	glLoadIdentity();//	�������� ��������� ������� �������� ��������������
	//	�������� ������� ����, �������� �������� ������, ������ ����������
	//	� �������� �����
	gluLookAt(0.0f, 0.0f, 100.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	//	�������� ������� �������� �� ������� ������� �������� �������-
	//	�������
	glRotatef((GLfloat)Angle, 0.0f, 0.0f, 1.0f);
	glTranslatef(rt, 0.0, 0.0);
	//	������ �������������
	glClearColor(255, 255, 255, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3ub(0, 0, 0);
	GLfloat BlueCol[3] = { 0, 0, 1 };



	//	int BMask = ToInt64(value, 2);

	glColor3ub(0, 0, 255);
	glBegin(GL_QUADS);

	glVertex3f(-10, 10, 0);
	glVertex3f(10, 10, 0);
	glVertex3f(10, -10, 0);
	glVertex3f(-10, -10, 0);

	glEnd();


	glBegin(GL_QUADS);

	glVertex3f(-3.5, 4 -14, 0);
	glVertex3f(3.5, 4 - 14, 0);
	glVertex3f(3.5, -4 - 14, 0);
	glVertex3f(-3.5, -4 - 14, 0);

	glEnd();

				//	�������� ��� ������ �� ��������� � �������� �������������� OpenGL
				//	��� �������� ���������� ���������� ����������
	glFlush();
	//	������ ������� ������ � �������� ������
	glutSwapBuffers();
}	//	void Update(void)

	//	������ ���������� ��� ��������� �������� ���� - ����� ����� ����-
	//	���� �������� ���������� w � h
void Reshape(int width, int height) {
	//	�������� ������� ���� � ���������� ����������
	w = width;
	h = height;
	//	����� ����� OpenGL � ����� ������� ����� ������������� �������-
	//	�� - � ������ ������: �� ����
	glViewport(0, 0, w, h);
	//	��������� ������� ������� - ������� ������������ ��������������
	glMatrixMode(GL_PROJECTION);
	//	������� ������� ������������ �������������� ���������
	glLoadIdentity();
	//	�������� ������� �������������� �������������� ������ �� �����-
	//	���� ���� ������, ��������� ������ � ������ ������� � �������/
	//	������ ���������� ���������� � ���������� ������� � ������� ��-
	//	�������� ����������
	gluPerspective(65.0f, w / h, 1.0f, 1000.0f);
	//	��������� ������� - ������� �������� ��������������, ����� �����
	//	� ��������� �� ����� �������� ������ � ���
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}	//	void Reshape(int width, int height)

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case '1':
		Angle += 45.0f;
		//Angle += 30.0f;
		// day = (day + 10) % 360;
		glutPostRedisplay();
		break;
	case '2':
		rt += 10;
		glutPostRedisplay();
	default:
		break;
	}
}
//	�������� ����� ����� � ���������� - ������� ������� main
int main(int argc, char *argv[]) {
	//	���������������� ��� glut
	glutInit(&argc, argv);
	//	���������� ��������� ������� ����
	glutInitWindowSize(800, 600);
	//	���������� ��������� ���� - ������� ������������ � ���������
	//	����� RGBA
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	//	������� ���� � ���������� OpenGL
	glutCreateWindow("OpenGL");

	//	������ glut �������, ������� ����� �������� ������ ����
	glutDisplayFunc(Update);
	//	������ glut �������, ������� ����� ���������� ��� ���������
	//	������� ���� ����������
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(keyboard);

	//	������� ������� Init() ����� ��� ��� ������� � ������� ����
	Init();
	//	����� � ������� ���� ����������
	glutMainLoop();

	//	���������� �������� ������ ����
	return 0;
}