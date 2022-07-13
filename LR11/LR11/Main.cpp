#define _CRT_SECURE_NO_WARNINGS

// ���������� ������������ ���� ��� ������ � Windows - ��������� ���
//	������������ ������ OpenGL
#include <windows.h>
//	������������ ���� ��� ���������� �������������� OpenGL - glut
#include "glut.h"
#include <stdio.h> 
#include <malloc.h> 


//http://grafika.me/node/130
//http://www.cyberforum.ru/opengl/thread660416.html
//
#define GL_BGR 0x80E0

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

GLuint  textura_id;

struct textura_struct
{
	int W;
	int H;
	unsigned char *Image;
}get_textura;

int LoadTexture(char *FileName)
{
	FILE *F;
	/* ��������� ���� */
	if ((F = fopen(FileName, "rb")) == NULL)
		return 0;
	/*������������ � bmp-����� �� ������ �������, � ��������� ������ � ������ */
	fseek(F, 18, SEEK_SET);
	fread(&(get_textura.W), 2, 1, F);
	fseek(F, 2, SEEK_CUR);
	fread(&(get_textura.H), 2, 1, F);

	printf("%d x %d\n", get_textura.W, get_textura.H);

	/* �������� ������ ��� �����������. ���� ������ �� ����������, ��������� ���� � ������� � ������� */
	if ((get_textura.Image = (unsigned char *)malloc(sizeof(unsigned char)* 3 * get_textura.W * get_textura.H)) == NULL)
	{
		fclose(F);
		return 0;
	}
	/* ��������� ����������� � ������ �� 3 ����, �� ���� RGB ��� ������� ������� */
	fseek(F, 30, SEEK_CUR);
	fread(get_textura.Image, 3, get_textura.W * get_textura.H, F);

	glGenTextures(1, &textura_id);
	glBindTexture(GL_TEXTURE_2D, textura_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, get_textura.W, get_textura.H, GL_BGR, GL_UNSIGNED_BYTE, get_textura.Image);


	free(get_textura.Image);
	fclose(F);

	return 1;
}



//	������� ���������� ��� ��������� � ������� ���� ����������
void Init(void) {
	glShadeModel(GL_SMOOTH);            // ��������� ������� �������� �����������
	glClearColor(0,0, 0, 0.0f);          // ������� ������ � ������ ����
	glClearDepth(1.0f);              // ��������� ������� ������ �������
	glEnable(GL_DEPTH_TEST);            // ��������� ���� �������
	glDepthFunc(GL_LEQUAL);            // ��� ����� �������
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // ��������� � ���������� �����������
	GLfloat LightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
	GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
	GLfloat LightPosition[] = { 0.0f, 0.0f, 2.0f, 1.0f };
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);

	glEnable(GL_LIGHT1); // ���������� ��������� ����� ����� ����
	glEnable(GL_LIGHTING);

}	//	void Init(void)



void DrawGLScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// ������� ������ � ������ �������
	glLoadIdentity();                               // ����� ���������
	glTranslatef(OX, OY, OZ);                 // ����� ����� � ������ ������
	glScalef(AS, AS, AS);

	glRotatef(rtrY, 0.0f, 1.0f, 0.0f);                 // �������� �������� �� ��� Y
	glRotatef(rtrX, 1.0f, 0.0f, 0.0f);				    //�������� �� ��� X
	glRotatef(rtrZ, 0.0f, 0.0f, 1.0f);				    //�������� �� ��� Z

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textura_id);


	///GL_AMBIENT, GL_DIFFUSE, GL_SPECULAR,GL_SHININESS
	GLfloat AMB[4] = { 0.14f, 0.22f, 0.16f, 0.95f };
	GLfloat DIF[4] = { 0.54f, 0.89f, 0.63f, 0.95f };
	GLfloat SPE[4] = { 0.32f, 0.32f, 0.32f, 0.95f };

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, AMB);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, DIF);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, SPE);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 12.8f);


	glColor3f(255, 0, 0); // �����
	glBegin(GL_QUADS);
	// ������ �
	//|
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3i(-2, 8, -2);
	glTexCoord2f(1.0f, 1.0f); glVertex3i(2, 8, -2);
	glTexCoord2f(1.0f, 0.0f); glVertex3i(2, -8, -2);
	glTexCoord2f(0.0f, 0.0f); glVertex3i(-2, -8, -2);
	//"/"
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f);  glVertex3i(2, -2, -2);
	glTexCoord2f(1.0f, 1.0f);  glVertex3i(2, 2, -2);
	glTexCoord2f(1.0f, 0.0f); glVertex3i(6, 8, -2);
	glTexCoord2f(0.0f, 0.0f); glVertex3i(10, 8, -2);
	//"\"
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(3.6, 0, -2);
	glTexCoord2f(1.0f, 1.0f);  glVertex3i(2, -2, -2);
	glTexCoord2f(1.0f, 0.0f); glVertex3i(6, -8, -2);
	glTexCoord2f(0.0f, 0.0f); glVertex3i(10, -8, -2);

	// �������� �
	//|
	 glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3i(-2, 8, 2);
	glTexCoord2f(1.0f, 1.0f); glVertex3i(2, 8, 2);
	glTexCoord2f(1.0f, 0.0f); glVertex3i(2, -8, 2);
	glTexCoord2f(0.0f, 0.0f); glVertex3i(-2, -8, 2);
	//"/"
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);  glVertex3i(2, -2, 2);
	glTexCoord2f(1.0f, 1.0f); glVertex3i(2, 2, 2);
	glTexCoord2f(1.0f, 0.0f); glVertex3i(6, 8, 2);
	glTexCoord2f(0.0f, 0.0f); glVertex3i(10, 8, 2);
	//"\"
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);  glVertex3f(3.6, 0, 2);
	glTexCoord2f(1.0f, 1.0f); glVertex3i(2, -2, 2);
	glTexCoord2f(1.0f, 0.0f); glVertex3i(6, -8, 2);
	glTexCoord2f(0.0f, 0.0f); glVertex3i(10, -8, 2);

	//[
	glNormal3f(-1.0f, 0.0f, 0.0f);     // 
	glTexCoord2f(0.0f, 1.0f);  glVertex3i(-2, 8, -2);
	glTexCoord2f(1.0f, 1.0f); glVertex3i(-2, 8, 2);
	glTexCoord2f(1.0f, 0.0f); glVertex3i(-2, -8, 2);
	glTexCoord2f(0.0f, 0.0f); glVertex3i(-2, -8, -2);

	//]
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3i(2, 8, -2);
	glTexCoord2f(1.0f, 1.0f); glVertex3i(2, 8, 2);
	glTexCoord2f(1.0f, 0.0f); glVertex3i(2, -8, 2);
	glTexCoord2f(0.0f, 0.0f); glVertex3i(2, -8, -2);

	//-^
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3i(-2, 8, 2);
	glTexCoord2f(1.0f, 1.0f); glVertex3i(2, 8, 2);
	glTexCoord2f(1.0f, 0.0f); glVertex3i(2, 8, -2);
	glTexCoord2f(0.0f, 0.0f); glVertex3i(-2, 8, -2);
	//-V
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);  glVertex3i(-2, -8, 2);
	glTexCoord2f(1.0f, 1.0f); glVertex3i(2, -8, 2);
	glTexCoord2f(1.0f, 0.0f); glVertex3i(2, -8, -2);
	glTexCoord2f(0.0f, 0.0f); glVertex3i(-2, -8, -2);

	//"/"^
	glNormal3f(-1.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);  glVertex3i(2, 2, 2);
	glTexCoord2f(1.0f, 1.0f); glVertex3i(2, 2, -2);
	glTexCoord2f(1.0f, 0.0f); glVertex3i(6, 8, -2);
	glTexCoord2f(0.0f, 0.0f); glVertex3i(6, 8, 2);

	//"/"-
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);  glVertex3i(6, 8, -2);
	glTexCoord2f(1.0f, 1.0f); glVertex3i(10, 8, -2);
	glTexCoord2f(1.0f, 0.0f); glVertex3i(10, 8, 2);
	glTexCoord2f(0.0f, 0.0f); glVertex3i(6, 8, 2);
	//"/"V
	glNormal3f(1.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3i(2, -2, 2);
	glTexCoord2f(1.0f, 1.0f); glVertex3i(2, -2, -2);
	glTexCoord2f(1.0f, 0.0f); glVertex3i(10, 8, -2);
	glTexCoord2f(0.0f, 0.0f); glVertex3i(10, 8, 2);
	//////

	//"\"^
	glNormal3f(1.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(3.6, 0, -2);
	glTexCoord2f(1.0f, 1.0f); glVertex3i(10, -8, -2);
	glTexCoord2f(1.0f, 0.0f); glVertex3i(10, -8, 2);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(3.6, 0, 2);


	//"\"-
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3i(6, -8, -2);
	glTexCoord2f(1.0f, 1.0f); glVertex3i(10, -8, -2);
	glTexCoord2f(1.0f, 0.0f); glVertex3i(10, -8, 2);
	glTexCoord2f(0.0f, 0.0f); glVertex3i(6, -8, 2);
	//"\"V
	glNormal3f(-1.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3i(2, -2, 2);
	glTexCoord2f(1.0f, 1.0f); glVertex3i(2, -2, -2);
	glTexCoord2f(1.0f, 0.0f); glVertex3i(6, -8, -2);
	glTexCoord2f(0.0f, 0.0f); glVertex3i(6, -8, 2);


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
	case 'q':{rtrZ += 0.5f; glutPostRedisplay(); }break;
	case 'e': {rtrZ -= 0.5f; glutPostRedisplay(); }break;
	case 'w': {OZ -= 0.5f; glutPostRedisplay(); }break;
	case 's': {OZ += 0.5f; glutPostRedisplay(); }break;
	case 'a': {OX -= 0.5f; glutPostRedisplay(); }break;
	case 'd': {OX += 0.5f; glutPostRedisplay(); }break;
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
	if (LoadTexture((char *)"Desert.bmp") != 1){ printf("�� ������� ��������� �����������\n"); }
	Init();
	//	����� � ������� ���� ����������
	glutMainLoop();

	//	���������� �������� ������ ����

}	//	int main(int argc, char *argv[])
