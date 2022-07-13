#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include "gl.h"
#include "glu.h"
#include "glut.h"
#include <stdio.h> 
//	Подключает сами библиотеки: opengl32.dll, glu32.dll и glut32.dll
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glut32.lib")

#define GL_BGR 0x80E0

int angle = 0; // угол вращения


				   // подготовка сцены
void init() {
	glClearColor(0.0, 0.0, 0.0, 1.0); // цвет очистки буферов - черный
	glEnable(GL_DEPTH_TEST); // включаем сортировку по глубине

	glShadeModel(GL_SMOOTH); // режим закрашивания: интерполируемые значения

							 // ставим источник света
	//float lightAmb[4] = { 1.0,1.0, 1.0, 1 }; // фоновый цвет синий
	float lightDif[4] = {1.0, 1.0, 1.0, 1 }; // отраженный цвет красный
	float lightPos[4] = { 100.0, 0.0, 0.0 , 1 };  // положение в пространстве
	float light3_spot_direction[4] = {-1, 0, 0,0};
	//glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDif);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF,100);
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, light3_spot_direction);
	glEnable(GL_LIGHT0); // включаем источник света
	glEnable(GL_LIGHTING); // включаем освещение
}

// рисование
void display() {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT); // очистка рабочих буферов

	glPushMatrix(); // начинаем матричные преобразования
	glRotatef(angle, 0, 1, 0); // матрица вращения

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


	glutSolidTeapot(1);       //  наш чайник
	glPopMatrix();          // завершаем матричные преобразования

	glutSwapBuffers();    // выводим на экран
}

// перекалибровка при изменении размеров окна
void reshape(int w, int h) {
	// область видимости в соответствии с новыми координатами
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	// загружаем единичные матрицы в стеки MODELVIEW, PROJECTION
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// установка перспективы: угол обзора 60 градусов, аспект,
	// глубина пространства 20 единиц 
	gluPerspective(60, GLfloat(1.33), 1, 20);
	// установка вектора обзора
	// (0,0,5) камера; (0,0,0) центр сцены, верхом будет ось Y
	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
}

void key(unsigned char key, int  x, int y) {
	

}

void mytime(int value) {
	angle = (angle>358) ? 0 : angle + 2; // расчет угла

	glutTimerFunc(40, mytime, 0); // следующий вызов
}


int main(int argc, char** argv) {
	glutInit(&argc, argv); // инициализация glut
						   // будем использовать двойную буферизацию, цветовое пространство RGB,
						   // сортировку по глубине aka Z-буфер
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	// размер окна пусть будет 800 на 600
	glutInitWindowSize(800, 600);
	// создаем окно, на выходе получаем идентификатор созданного окна
	int glWin = glutCreateWindow("My program");
	init(); // подготовка к рисованию
	glutDisplayFunc(display); // рисование
	glutReshapeFunc(reshape); // действия при изменении окна
	glutKeyboardFunc(key);   // обработка нажатий клавиш
							 // запускаем таймер м периодичностью 40ms т.е. 25 раз в секунду
	glutTimerFunc(40, mytime, 0);
	glutMainLoop(); // главный цикл glut

	return 0;
}
