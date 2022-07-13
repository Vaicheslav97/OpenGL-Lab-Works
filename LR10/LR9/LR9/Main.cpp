#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include "gl.h"
#include "glu.h"
#include "glut.h"
#include <stdio.h> 
//	���������� ���� ����������: opengl32.dll, glu32.dll � glut32.dll
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glut32.lib")

#define GL_BGR 0x80E0

int angle = 0; // ���� ��������


				   // ���������� �����
void init() {
	glClearColor(0.0, 0.0, 0.0, 1.0); // ���� ������� ������� - ������
	glEnable(GL_DEPTH_TEST); // �������� ���������� �� �������

	glShadeModel(GL_SMOOTH); // ����� ������������: ��������������� ��������

							 // ������ �������� �����
	//float lightAmb[4] = { 1.0,1.0, 1.0, 1 }; // ������� ���� �����
	float lightDif[4] = {1.0, 1.0, 1.0, 1 }; // ���������� ���� �������
	float lightPos[4] = { 100.0, 0.0, 0.0 , 1 };  // ��������� � ������������
	float light3_spot_direction[4] = {-1, 0, 0,0};
	//glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDif);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF,100);
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, light3_spot_direction);
	glEnable(GL_LIGHT0); // �������� �������� �����
	glEnable(GL_LIGHTING); // �������� ���������
}

// ���������
void display() {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT); // ������� ������� �������

	glPushMatrix(); // �������� ��������� ��������������
	glRotatef(angle, 0, 1, 0); // ������� ��������

	FILE *F;
	if ((F = fopen("Desert.bmp", "rb")) == NULL)return;

	int texturW = 0, texturH = 0;
	unsigned char *Image; GLuint  textura_id;
	fseek(F, 18, SEEK_SET);
	fread(&texturW, 2, 1, F);
	fseek(F, 2, SEEK_CUR);
	fread(&texturH, 2, 1, F);
	fseek(F, 30, SEEK_CUR);
	Image = ((unsigned char *)malloc(sizeof(unsigned char) * 3 * texturW * texturH));
	fread(Image, 3, texturW * texturH, F);

	fclose(F);
	glGenTextures(1, &textura_id);
	glBindTexture(GL_TEXTURE_2D, textura_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, texturW, texturH, GL_BGR, GL_UNSIGNED_BYTE, Image);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textura_id);
	glEnable(GL_TEXTURE_GEN_S);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);


	glutSolidTeapot(1);       //  ��� ������
	glPopMatrix();          // ��������� ��������� ��������������

	glutSwapBuffers();    // ������� �� �����
}

// �������������� ��� ��������� �������� ����
void reshape(int w, int h) {
	// ������� ��������� � ������������ � ������ ������������
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	// ��������� ��������� ������� � ����� MODELVIEW, PROJECTION
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// ��������� �����������: ���� ������ 60 ��������, ������,
	// ������� ������������ 20 ������ 
	gluPerspective(60, GLfloat(1.33), 1, 20);
	// ��������� ������� ������
	// (0,0,5) ������; (0,0,0) ����� �����, ������ ����� ��� Y
	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
}

void key(unsigned char key, int  x, int y) {
	

}

void mytime(int value) {
	angle = (angle>358) ? 0 : angle + 2; // ������ ����

	glutTimerFunc(40, mytime, 0); // ��������� �����
}


int main(int argc, char** argv) {
	glutInit(&argc, argv); // ������������� glut
						   // ����� ������������ ������� �����������, �������� ������������ RGB,
						   // ���������� �� ������� aka Z-�����
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	// ������ ���� ����� ����� 800 �� 600
	glutInitWindowSize(800, 600);
	// ������� ����, �� ������ �������� ������������� ���������� ����
	int glWin = glutCreateWindow("My program");
	init(); // ���������� � ���������
	glutDisplayFunc(display); // ���������
	glutReshapeFunc(reshape); // �������� ��� ��������� ����
	glutKeyboardFunc(key);   // ��������� ������� ������
							 // ��������� ������ � �������������� 40ms �.�. 25 ��� � �������
	glutTimerFunc(40, mytime, 0);
	glutMainLoop(); // ������� ���� glut

	return 0;
}
