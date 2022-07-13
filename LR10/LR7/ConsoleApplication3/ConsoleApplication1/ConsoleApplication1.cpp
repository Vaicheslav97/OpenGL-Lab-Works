

#include <windows.h>
//	������������ ���� ��� ���������� �������������� OpenGL - glut
#include "glut.h"
#include <stdio.h> 

//	���������� ����������� ���������� - ������ ������� ������ ������:
//	������ w � ����� h
static int w = 0, h = 0, rt = 0;
static float Angle = 0.0f;
static float ScaleX = 1.0f;
static float ScaleY = 1.0f;

//	������� ���������� ��� ��������� � ������� ���� ����������
void Init(void) {
	//	��������� OpenGL ����� ������ ������� ������ ����� - ������
	glClearColor(255, 255, 255, 1.0f);
}	

void Update(void) {
	
	//Angle += 0.05f;

	glClear(GL_COLOR_BUFFER_BIT);
	
	glLoadIdentity();//	�������� ��������� ������� �������� ��������������
	//	�������� ������� ����, �������� �������� ������, ������ ����������
	//	� �������� �����
	gluLookAt(0.0f, 0.0f, 100.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	//	�������� ������� �������� �� ������� ������� �������� �������-
	//	�������
	glRotatef((GLfloat)Angle, 0.0f, 0.0f, 1.0f);
	glTranslatef(rt, rt, 0.0);
	//	������ �������������
	glClearColor(255, 255, 255, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3ub(0, 0, 0);
	GLfloat BlueCol[3] = { 0, 0, 1 };

	glScalef(ScaleX, ScaleY, 1);

	//	int BMask = ToInt64(value, 2); 

	glEnable(GL_TEXTURE_2D);

	FILE *F ;
	if ((F = fopen("Desert.bmp", "rb")) == NULL)return;

	int texturW =0, texturH=0;
	unsigned char *Image; GLuint  textura_id;
	fseek(F, 18, SEEK_SET);
	fread(&texturW, 2, 1, F);
	fseek(F, 2, SEEK_CUR);
	fread(&texturH, 2, 1, F);
	fseek(F, 30, SEEK_CUR);
	Image = ((unsigned char *)malloc(sizeof(unsigned char)* 3 * texturW * texturH));
	fread(Image, 3, texturW * texturH, F);
	
fclose(F);
	glGenTextures(1, &textura_id);
	glBindTexture(GL_TEXTURE_2D, textura_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

#define GL_BGR 0x80E0
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, texturW, texturH, GL_BGR, GL_UNSIGNED_BYTE, Image);
	free(Image);
	


	glColor3ub(255, 255, 255);
	glBegin(GL_QUADS);

	 glTexCoord2d(0, 1); glVertex3f(-10, 10, 0);
	glTexCoord2d(1, 1); glVertex3f(10, 10, 0);
	glTexCoord2d(1, 0); glVertex3f(10, -10, 0);
	glTexCoord2d(0, 0); glVertex3f(-10, -10, 0);

	glEnd();

	glColor3ub(0, 0, 255);
	glBegin(GL_QUADS);

	glVertex3f(-3.5, 4 -14, 0);
	glTexCoord2d(1, 0); glVertex3f(3.5, 4 - 14, 0);
	glTexCoord2d(1, 0); glVertex3f(3.5, -4 - 14, 0);
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
		ScaleX = 2; ScaleY = 0.5;
		glutPostRedisplay();
		break;
	case '2': {
		rt += 10;
		glutPostRedisplay();
	}break;
	case '3':
	{Angle += 45.0f;
	//Angle += 30.0f;
	// day = (day + 10) % 360;
	glutPostRedisplay(); }
		break;
	
	default: {} break;
		
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