// ���������� ������������ ���� ��� ������ � Windows - ��������� ���
//	������������ ������ OpenGL
#include <windows.h>
//	������������ ���� ��� ���������� �������������� OpenGL - glut
#include "glut.h"

//http://grafika.me/node/130
//http://www.cyberforum.ru/opengl/thread660416.html
//


//	���������� ����������� ���������� - ������ ������� ������ ������:
//	������ w � ����� h
static int w = 0, h = 0;

static float rtrX = 0.0f;
static float rtrY = 0.0f;
static float rtrZ = 0.0f;

static float OX = 0.0f;
static float OY = 0.0f;
static float OZ = -50.0f;

static float AS = 1.0f;


//	������� ���������� ��� ��������� � ������� ���� ����������
void Init(void) {
	glShadeModel(GL_SMOOTH);            // ��������� ������� �������� �����������
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);          // ������� ������ � ������ ����
	glClearDepth(1.0f);              // ��������� ������� ������ �������
	glEnable(GL_DEPTH_TEST);            // ��������� ���� �������
	glDepthFunc(GL_LEQUAL);            // ��� ����� �������
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);      // ��������� � ���������� �����������
}	//	void Init(void)



void DrawGLScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// ������� ������ � ������ �������
	glLoadIdentity();                               // ����� ���������
	glTranslatef(OX, OY, OZ);                 // ����� ����� � ������ ������
	glScalef(AS,AS,AS);

	glRotatef(rtrY, 0.0f, 1.0f, 0.0f);                 // �������� �������� �� ��� Y
	glRotatef(rtrX, 1.0f, 0.0f, 0.0f);				    //�������� �� ��� X
	glRotatef(rtrZ, 0.0f, 0.0f, 1.0f);				    //�������� �� ��� Z

	glColor3f(255, 0, 0); // �����
	glBegin(GL_QUADS);
	// ������ �
	//|
	glVertex3i(-2, 8, -2);
	glVertex3i(2, 8, -2);
	glVertex3i(2, -8, -2);
	glVertex3i(-2, -8, -2);
	//"/"
	glVertex3i(2, -2, -2);
	glVertex3i(2, 2, -2);
	glVertex3i(6, 8, -2);
	glVertex3i(10, 8, -2);
	//"\"
	glVertex3f(3.6, 0, -2);
	glVertex3i(2, -2, -2);
	glVertex3i(6, -8, -2);
	glVertex3i(10, -8, -2);

	// �������� �
	//|
	glVertex3i(-2, 8, 2);
	glVertex3i(2, 8, 2);
	glVertex3i(2, -8, 2);
	glVertex3i(-2, -8, 2);
	//"/"
	glVertex3i(2, -2, 2);
	glVertex3i(2, 2, 2);
	glVertex3i(6, 8, 2);
	glVertex3i(10, 8, 2);
	//"\"
	glVertex3f(3.6, 0, 2);
	glVertex3i(2, -2, 2);
	glVertex3i(6, -8, 2);
	glVertex3i(10, -8, 2);

	//[
	glVertex3i(-2, 8, -2);
	glVertex3i(-2, 8, 2);
	glVertex3i(-2, -8, 2);
	glVertex3i(-2, -8, -2);

	//]
	glVertex3i(2, 8, -2);
	glVertex3i(2, 8, 2);
	glVertex3i(2, -8, 2);
	glVertex3i(2, -8, -2);

	//-^
	glVertex3i(-2, 8, 2);
	glVertex3i(2, 8, 2);
	glVertex3i(2, 8, -2);
	glVertex3i(-2, 8, -2);
	//-V
	glVertex3i(-2, -8, 2);
	glVertex3i(2, -8, 2);
	glVertex3i(2, -8, -2);
	glVertex3i(-2, -8, -2);

	//"/"^
	glVertex3i(2, 2, 2);
	glVertex3i(2, 2, -2);
	glVertex3i(6, 8, -2);
	glVertex3i(6, 8, 2);

	//"/"-
	glVertex3i(6, 8, -2);
	glVertex3i(10, 8, -2);
	glVertex3i(10, 8, 2);
	glVertex3i(6, 8, 2);
	//"/"V

	glVertex3i(2, -2, 2);
	glVertex3i(2, -2, -2);
	glVertex3i(10, 8, -2);
	glVertex3i(10, 8, 2);
	//////

	//"\"^
	glVertex3f(3.6, 0, -2);
	glVertex3i(10, -8, -2);
	glVertex3i(10, -8, 2);
	glVertex3f(3.6, 0, 2);


	//"\"-
	glVertex3i(6, -8, -2);
	glVertex3i(10, -8, -2);
	glVertex3i(10, -8, 2);
	glVertex3i(6, -8, 2);
	//"\"V

	glVertex3i(2, -2, 2);
	glVertex3i(2, -2, -2);
	glVertex3i(6, -8, -2);
	glVertex3i(6, -8, 2);


	glEnd();

	glFlush();
	//	������ ������� ������ � �������� ������
	glutSwapBuffers();
}


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
	gluPerspective(70.0f, w / h, 0.1f, 100);
	//	��������� ������� - ������� �������� ��������������, ����� �����
	//	� ��������� �� ����� �������� ������ � ���
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}	//	void Reshape(int width, int height)

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'q':{rtrZ += 0.5f;glutPostRedisplay();}break;
	case 'e': {rtrZ -= 0.5f;glutPostRedisplay();}break;
	case 'w': {OZ -= 0.5f;glutPostRedisplay();}break;
	case 's': {OZ += 0.5f;glutPostRedisplay();}break;
	case 'a': {OX -= 0.5f;glutPostRedisplay();}break;
	case 'd': {OX += 0.5f;glutPostRedisplay();}break;
	case '-': {AS -= 0.1f; glutPostRedisplay(); }break;
	case '=': {AS += 0.1f; glutPostRedisplay(); }break;
	case '0': {

	     rtrX = 0.0f;
		 rtrY = 0.0f;
		 rtrZ = 0.0f;

		 OX = 0.0f;
		 OY = 0.0f;
		 OZ = -50.0f;

		AS = 1.0f;

		glutPostRedisplay(); }break;
	default: break;
	}
}

void Specialkeyboard(int key, int x, int y) {

	switch (key) {
	case GLUT_KEY_UP:
		rtrX += 0.5f;

		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		rtrX -= 0.5f;
		//rtrY += 0.5f;
		glutPostRedisplay();
		break;
	case  GLUT_KEY_LEFT:
		//rtrZ += 0.5f;
		rtrY += 0.5f;
		glutPostRedisplay();
		break;
	case  GLUT_KEY_RIGHT:
		//rtrZ += 0.5f;
		rtrY -= 0.5f;
		glutPostRedisplay();
		break;

	default:
		break;
	}

}


//	�������� ����� ����� � ���������� - ������� ������� main
void main(int argc, char *argv[]) {
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
	glutDisplayFunc(DrawGLScene);
	//	������ glut �������, ������� ����� ���������� ��� ���������
	//	������� ���� ����������
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(Specialkeyboard);
	//glutMouseFunc();
	//	������� ������� Init() ����� ��� ��� ������� � ������� ����
	Init();
	//	����� � ������� ���� ����������
	glutMainLoop();

	//	���������� �������� ������ ����

}	//	int main(int argc, char *argv[])
