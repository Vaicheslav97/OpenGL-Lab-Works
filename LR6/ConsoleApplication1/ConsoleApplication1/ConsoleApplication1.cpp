
#include <stdlib.h>
/* подключаем библиотеку GLUT */
#include "glut.h"
/* начальная ширина и высота окна */

	GLint Width = 512, Height = 512;
	/* эта функция управляет всем выводом на экран */



	void Display(void) {
		float CX = Width / 2, CY = Height / 2;

		int HeadWeightHalf = 20;
		int NekHalf = 10;
		int BodyWeightHalf = 30;

		int HeadHeight = 30;
		int BodyHeight = -50;



		glClearColor(255, 255, 255, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3ub(0, 0, 0);
		GLfloat BlueCol[3] = { 0, 0, 1 };
		glLineWidth(3);

		glBegin(GL_LINE_LOOP); // body
		glVertex3f(CX - 20, CY + HeadHeight, 0.0); glVertex3f(CX + 20, CY + HeadHeight, 0.0);
		glVertex3f(CX + HeadWeightHalf - NekHalf, CY, 0.0);
		glVertex3f(CX + BodyWeightHalf, CY + BodyHeight, 0.0); glVertex3f(CX - BodyWeightHalf, CY + BodyHeight, 0.0);
		glVertex3f(CX - HeadWeightHalf + NekHalf, CY, 0.0);
		glEnd();


		glBegin(GL_LINE_LOOP); // Tale
		glVertex3f(CX + BodyWeightHalf, CY + BodyHeight + 10, 0.0);
		glVertex3f(CX + BodyWeightHalf + HeadWeightHalf, CY + 10, 0.0);
		glVertex3f(CX + BodyWeightHalf + HeadWeightHalf + 10, CY - 10, 0.0);

		glEnd();

		int FootHeight = -10;
		int FootWeight = 10;

		int LFootXPos = -15;
		int RFootXPos = 10;
		int RFootWeight = 10;



		glBegin(GL_LINE_LOOP); // LFoot
		glVertex3f(CX + LFootXPos, CY + BodyHeight, 0.0);
		glVertex3f(CX + LFootXPos + FootWeight, CY + BodyHeight, 0.0);
		glVertex3f(CX + LFootXPos + 5, CY + BodyHeight + FootHeight, 0.0);
		glVertex3f(CX + LFootXPos - 5, CY + BodyHeight + FootHeight, 0.0);
		glEnd();

		glBegin(GL_LINE_LOOP); // RFoot
		glVertex3f(CX + RFootXPos, CY + BodyHeight, 0.0);
		glVertex3f(CX + RFootXPos + FootWeight, CY + BodyHeight, 0.0);
		glVertex3f(CX + RFootXPos + RFootWeight + 5, CY + BodyHeight + FootHeight, 0.0);
		glVertex3f(CX + RFootXPos + RFootWeight - 5, CY + BodyHeight + FootHeight, 0.0);
		glEnd();

		int EarsWeight = 10;
		int EarsHeight = 10;

		int LEarPos = 5;
		int REarPos = 5;



		glBegin(GL_LINE_LOOP); // LEar
		glVertex3f(CX - HeadWeightHalf + LEarPos, CY + HeadHeight, 0.0);
		glVertex3f(CX - HeadWeightHalf + LEarPos + EarsWeight, CY + HeadHeight, 0.0);
		glVertex3f(CX - HeadWeightHalf + LEarPos + (EarsWeight / 2), CY + HeadHeight + EarsHeight, 0.0);
		glEnd();

		glBegin(GL_LINE_LOOP); // REar
		glVertex3f(CX + REarPos, CY + HeadHeight, 0.0);
		glVertex3f(CX + REarPos + EarsWeight, CY + HeadHeight, 0.0);
		glVertex3f(CX + REarPos + (EarsWeight / 2), CY + HeadHeight + EarsHeight, 0.0);
		glEnd();

		int MauthrWeightHalf = 3;
		int MauthrHeight = 5;
		glLineWidth(1);

		glBegin(GL_LINE_LOOP); // Mauthr
		glVertex3f(CX - MauthrWeightHalf, CY + 10, 0.0);
		glVertex3f(CX + MauthrWeightHalf, CY + 10, 0.0);
		glVertex3f(CX, CY + MauthrHeight, 0.0);
		glEnd();



		int EyeRad = 3;
		int EyePosY = 20;
		int LEyePos = -8;
		int REyePos = 8;

		glBegin(GL_LINE_LOOP); // LEye
		glVertex3f(CX + LEyePos - EyeRad, CY + EyePosY, 0.0);
		glVertex3f(CX + LEyePos, CY + EyeRad + EyePosY, 0.0);
		glVertex3f(CX + LEyePos + EyeRad, CY + EyePosY, 0.0);
		glVertex3f(CX + LEyePos, CY + EyePosY - EyeRad, 0.0);
		glEnd();


		glBegin(GL_LINE_LOOP); // REye
		glVertex3f(CX + REyePos - EyeRad, CY + EyePosY, 0.0);
		glVertex3f(CX + REyePos, CY + EyeRad + EyePosY, 0.0);
		glVertex3f(CX + REyePos + EyeRad, CY + EyePosY, 0.0);
		glVertex3f(CX + REyePos, CY + EyePosY - EyeRad, 0.0);
		glEnd();


		int UYPos = 8;

		glBegin(GL_LINES);
		glVertex3f(CX - BodyWeightHalf, CY + UYPos + 5, 0.0);
		glVertex3f(CX - 5, CY + UYPos, 0.0);

		glVertex3f(CX + BodyWeightHalf, CY + UYPos + 5, 0.0);
		glVertex3f(CX + 5, CY + UYPos, 0.0);

		glVertex3f(CX - BodyWeightHalf, CY + UYPos - 5, 0.0);
		glVertex3f(CX - 5, CY + UYPos, 0.0);

		glVertex3f(CX + BodyWeightHalf, CY + UYPos - 5, 0.0);
		glVertex3f(CX + 5, CY + UYPos, 0.0);

		glEnd();



		int LOFX = CX + 100;
		int LOFY = CX - 100;
		//	int BMask = ToInt64(value, 2);

		glLineWidth(3);
		glBegin(GL_LINES);
		glVertex3f(LOFX - 30, LOFY + 30, 0.0);
		glVertex3f(LOFX + 45, LOFY, 0.0);
		glEnd();

		glLineWidth(2);
		glEnable(GL_LINE_STIPPLE);
		glLineStipple(1, 65472);
		glBegin(GL_LINES);
		glVertex3f(LOFX, LOFY, 0.0);
		glVertex3f(LOFX + 80, LOFY, 0.0);
		glEnd();

		glFinish();
	}
	/* Функция вызывается при изменении размеров окна */
	void Reshape(GLint w, GLint h)
	{
		Width = w; Height = h;
		/* устанавливаем размеры области отображения */
		glViewport(0, 0, w, h);
		/* ортографическая проекция */
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, w, 0, h, -1.0, 1.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
	/* Функция обрабатывает сообщения от клавиатуры */
	void Keyboard(unsigned char key, int x, int y) {
#define ESCAPE '\033'
		if (key == ESCAPE) exit(0);
	}
	/* головная программа */
	int main(int argc, char *argv[]) {
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_RGB);
		glutInitWindowSize(Width, Height);
		glutCreateWindow("example");

		glutDisplayFunc(Display);
		glutReshapeFunc(Reshape);
		glutKeyboardFunc(Keyboard);
		glutMainLoop();
	}

