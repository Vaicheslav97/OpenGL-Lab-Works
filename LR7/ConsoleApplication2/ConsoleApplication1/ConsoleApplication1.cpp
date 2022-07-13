
#include <windows.h>
//	Заголовочный файл для библиотеки инструментария OpenGL - glut
#include "glut.h"

//	Глобальные статические переменные - хранят текущий размер экрана:
//	ширина w и длина h
static int w = 0, h = 0, rt = 0;
static float Angle = 0.0f;

//	Функция вызываемая при вхождении в главный цикл приложения
void Init(void) {
	//	Указывает OpenGL каким цветом очищать буффер цвета - чёрным
	glClearColor(255, 255, 255, 1.0f);
}	

void Update(void) {
	
	Angle += 0.05f;

	glClear(GL_COLOR_BUFFER_BIT);
	
	glLoadIdentity();//	Загрузим единичную матрицу видового преобразования
	//	Применим матрицу вида, заданную позицией камеры, точкой наблюдения
	//	и вектором вверх
	gluLookAt(0.0f, 0.0f, 100.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	//	Применим матрицу поворота на текущую матрицу видового преобра-
	//	зования
	glRotatef((GLfloat)Angle, 0.0f, 0.0f, 1.0f);
	glTranslatef(rt, 0.0, 0.0);
	//	Рисуем прямоугольник
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

				//	Сбросить все данные на обработку в конвейер преобразования OpenGL
				//	без ожидания завершения предидущих инструкций
	glFlush();
	//	Меняем местами задний и передний буферы
	glutSwapBuffers();
}	//	void Update(void)

	//	Функця вызываемая при изменении размеров окна - нужно чтобы поме-
	//	нять значения переменных w и h
void Reshape(int width, int height) {
	//	Сохраним размеры окна в глобальных переменных
	w = width;
	h = height;
	//	Дадим знать OpenGL в какую область будет производиться отрисов-
	//	ка - в данном случае: всё окно
	glViewport(0, 0, w, h);
	//	Установим текущую матрицу - матрицу проективного преобразования
	glMatrixMode(GL_PROJECTION);
	//	Сделаем матрицу проективного преобразования единичной
	glLoadIdentity();
	//	Применим матрицу перспективного преобразования исходя из задан-
	//	ного угла обзора, отношения ширины к высоте боковых и врехних/
	//	нижних отсекающих плоскостей и расстояния ближней и дальней от-
	//	секающих плоскостей
	gluPerspective(65.0f, w / h, 1.0f, 1000.0f);
	//	Установим текущей - матрицу видового преобразования, чтобы далее
	//	В программе мы могли работать только с ней
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
//	Основная точка входа в приложение - главная функция main
int main(int argc, char *argv[]) {
	//	Инициализировать сам glut
	glutInit(&argc, argv);
	//	Установить начальные размеры окна
	glutInitWindowSize(800, 600);
	//	Установить параметры окна - двойная буфферизация и поддержка
	//	цвета RGBA
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	//	Создать окно с заголовком OpenGL
	glutCreateWindow("OpenGL");

	//	Укажем glut функцию, которая будет рисовать каждый кадр
	glutDisplayFunc(Update);
	//	Укажем glut функцию, которая будет вызываться при изменении
	//	размера окна приложения
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(keyboard);

	//	Вызовем функцию Init() перед тем как входить в главный цикл
	Init();
	//	Войти в главный цикл приложения
	glutMainLoop();

	//	Возвращаем значение равное нулю
	return 0;
}