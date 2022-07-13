// Подключить заголовочный файл для работы с Windows - требуется для
//	заголовочных файлов OpenGL
#include <windows.h>
//	Заголовочный файл для библиотеки инструментария OpenGL - glut
#include "glut.h"

//http://grafika.me/node/130
//http://www.cyberforum.ru/opengl/thread660416.html
//


//	Глобальные статические переменные - хранят текущий размер экрана:
//	ширина w и длина h
static int w = 0, h = 0;

static float rtrX = 0.0f;
static float rtrY = 0.0f;
static float rtrZ = 0.0f;

static float OX = 0.0f;
static float OY = 0.0f;
static float OZ = -50.0f;

static float AS = 1.0f;


//	Функция вызываемая при вхождении в главный цикл приложения
void Init(void) {
	glShadeModel(GL_SMOOTH);            // Разрешить плавное цветовое сглаживание
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);          // Очистка экрана в черный цвет
	glClearDepth(1.0f);              // Разрешить очистку буфера глубины
	glEnable(GL_DEPTH_TEST);            // Разрешить тест глубины
	glDepthFunc(GL_LEQUAL);            // Тип теста глубины
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);      // Улучшение в вычислении перспективы
}	//	void Init(void)



void DrawGLScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// Очистка экрана и буфера глубины
	glLoadIdentity();                               // Сброс просмотра
	glTranslatef(OX, OY, OZ);                 // Сдвиг влево и вглубь экрана
	glScalef(AS,AS,AS);

	glRotatef(rtrY, 0.0f, 1.0f, 0.0f);                 // Вращение пирамиды по оси Y
	glRotatef(rtrX, 1.0f, 0.0f, 0.0f);				    //Вращение по оси X
	glRotatef(rtrZ, 0.0f, 0.0f, 1.0f);				    //Вращение по оси Z

	glColor3f(255, 0, 0); // Синий
	glBegin(GL_QUADS);
	// Задняя К
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

	// Передняя К
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
	//	Меняем местами задний и передний буферы
	glutSwapBuffers();
}


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
	gluPerspective(70.0f, w / h, 0.1f, 100);
	//	Установим текущей - матрицу видового преобразования, чтобы далее
	//	В программе мы могли работать только с ней
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


//	Основная точка входа в приложение - главная функция main
void main(int argc, char *argv[]) {
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
	glutDisplayFunc(DrawGLScene);
	//	Укажем glut функцию, которая будет вызываться при изменении
	//	размера окна приложения
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(Specialkeyboard);
	//glutMouseFunc();
	//	Вызовем функцию Init() перед тем как входить в главный цикл
	Init();
	//	Войти в главный цикл приложения
	glutMainLoop();

	//	Возвращаем значение равное нулю

}	//	int main(int argc, char *argv[])
