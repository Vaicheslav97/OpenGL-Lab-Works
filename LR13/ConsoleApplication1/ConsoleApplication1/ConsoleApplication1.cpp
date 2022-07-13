
#include <stdlib.h>
/* подключаем библиотеку GLUT */
#include "glut.h"
/* начальная ширина и высота окна */

	GLint Width = 512, Height = 512;
	/* эта функция управляет всем выводом на экран */


	void DDRline(float x1, float y1, float x2, float y2){

		if (x1 == x2){

			if (y1 > y2){ float ty = y1; y1 = y2; y2 = ty; }
			glBegin(GL_POINTS);
			glVertex2i((int)x1, (int)y1);
			while (y1 < y2) { y1 += 1; glVertex2i((int)x1, (int)y1); }
			glEnd();


			return;
		}

		if (x1 > x2){
			float tx = x1; x1 = x2; x2 = tx;
			float ty = y1; y1 = y2; y2 = ty;
		}


		float Px = x2 - x1;
		float Py = y2 - y1;

		glBegin(GL_POINTS);
		glVertex2i((int)x1, (int)y1);

		while (x1 < x2) {
			x1 = x1 + 1.0;
			y1 = y1 + Py / Px;
			glVertex2i((int)x1, (int)y1);
		}
		glEnd();
	}


	void DDRlineCent(float x1, float y1, float x2, float y2){
		float CX = (Width / 2);
		float CY = (Width / 2);
		DDRline(CX + x1, CY + y1, CX + x2, CY + y2);
	}


	void Round(float x1, float y1, float R){

		int x = 0;
		int y = R;
		int delta = 1 - 2 * R;
		int error = 0;

		glBegin(GL_POINTS);
		while (y >= 0){
			glVertex2i((int)x1 + x, (int)y1 + y);
			glVertex2i((int)x1 + x, (int)y1 - y);
			glVertex2i((int)x1 - x, (int)y1 + y);
			glVertex2i((int)x1 - x, (int)y1 - y);
			error = 2 * (delta + y) - 1;
			if (delta < 0 && error <= 0){
				x++;
				delta += 2 * x + 1;
				continue;
			}
			if (delta > 0 && error > 0){
				y--;
				delta -= 2 * y + 1;
				continue;
			}
			x++;
			delta += 2 * (x - y);
			y--;
		}
		glEnd();
	}

	void RoundC(float x1, float y1, float R) {
		float CX = (Width / 2);
		float CY = (Width / 2);
		Round(x1 + CX, y1 + CY, R);
	}



	int Color[3] = { 255, 0, 0 };
	int BolderColor[3] = { 0, 0, 0 };

	bool compaireColors(int mas1[], int mas2[]){
		for (int i = 0; i < 3; i++)
			if (mas1[i] != mas2[i]) { return false; }

		return true;
	}

	void getpixel(int x, int y, int* colors){
		unsigned char pixel[4];
		glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);

		colors[0] = pixel[0];
		colors[1] = pixel[1];
		colors[2] = pixel[2];
	}

	int LineFill(int x, int y, int dir, int PrevXl, int PrevXr){
		int xl = x;
		int xr = x;
		int c[3];

		do getpixel(--xl, y, c);   while ((!compaireColors(c, BolderColor)) && (!compaireColors(c, Color)));
		do getpixel(++xr, y, c); while ((!compaireColors(c, BolderColor)) && (!compaireColors(c, Color)));
		xl++; xr--;

		/*Вставить команду рисования линии*/
		DDRline(xl, y, xr , y);



		for (int x = xl; x <= xr; x++){
			getpixel(x, y + dir, c);
			if ((!compaireColors(c, BolderColor)) && (!compaireColors(c, Color)))   x = LineFill(x, y + dir, dir, xl, xr);
		}


		for (int x = xl; x<PrevXl; x++){
			getpixel(x, y - dir, c);
			if ((!compaireColors(c, BolderColor)) && (!compaireColors(c, Color)))   x = LineFill(x, y - dir, -dir, xl, xr);
		}
		
		for (int x = PrevXr; x<xr; x++){
			getpixel(x, y - dir, c);
			if ((!compaireColors(c, BolderColor)) && (!compaireColors(c, Color)))  x = LineFill(x, y - dir, -dir, xl, xr);
		}
		
		return xr;
	}





	



	void Display(void) {
		


		glClearColor(255, 255, 255, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3ub(0, 0, 0);
		GLfloat BlueCol[3] = { 0, 0, 1 };
		//glLineWidth(3);
		
		DDRlineCent(-100, 0, - 50, 50);
		DDRlineCent(-50, 50, 0, 0);

		DDRlineCent(0, 0, 50, 50);
		DDRlineCent(50, 50, 100, 0);

		DDRlineCent(100, 0, 100, -20);
		DDRlineCent(-100, -20, 100, -20);
		DDRlineCent(-100, 0, -100, -20);

		glColor3ub(255, 0, 0);
		LineFill(Width / 2, Height / 2-1, -1, Width / 2, Height / 2);

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

