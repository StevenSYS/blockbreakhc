/* GLUT Implementation */
#include <stdio.h>
#include <string.h>
#include <GL/glut.h>

#include "entity.h"
#include "random.h"
#include "progInfo.h"
#include "numberSheet.h"

void reset();
void draw();

extern char timerStart;
extern entity_t player;

static char string[11];

static void input(
	unsigned char key,
	int, int
) {
	random_increase();
	switch (key) {
		case '\r': /* Enter */
			reset();
			break;
		default:
			break;
	}
}

static void inputSpecial(
	int key,
	int, int
) {
	random_increase();
	switch (key) {
		case GLUT_KEY_UP:
			player.direction  = ENTITY_DIR_UP;
			timerStart = 1;
			break;
		case GLUT_KEY_DOWN:
			player.direction = ENTITY_DIR_DOWN;
			timerStart = 1;
			break;
		case GLUT_KEY_LEFT:
			player.direction = ENTITY_DIR_LEFT;
			timerStart = 1;
			break;
		case GLUT_KEY_RIGHT:
			player.direction = ENTITY_DIR_RIGHT;
			timerStart = 1;
			break;
		default:
			break;
	}
	return;
}

static void drawLoop(int) {
	glutPostRedisplay();
	glutTimerFunc(MAX_MS, drawLoop, 0);
	return;
}

void impl_clear() {
	glClear(GL_COLOR_BUFFER_BIT);
	return;
}

void impl_render() {
	glFlush();
	return;
}

void impl_setColor(
	unsigned char red,
	unsigned char green,
	unsigned char blue
) {
	glColor3ub(red, green, blue);
	return;
}

void impl_init(
	int argc,
	char *argv[]
) {
	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutCreateWindow(PROGRAM_NAME " v" PROGRAM_VERSION " - GLUT");
	glutReshapeWindow(RENDER_WIDTH, RENDER_HEIGHT);
	
	glOrtho(0, RENDER_WIDTH, RENDER_HEIGHT, 0, -1, 1);
	
	numberSheet_init();
	
	glutKeyboardFunc(input);
	glutSpecialFunc(inputSpecial);
	glutDisplayFunc(draw);
	glutTimerFunc(MAX_MS, drawLoop, 0);
	
	glutMainLoop();
	return;
}

/* Draw */
void impl_drawNumber(
	short x, short y,
	unsigned int number
) {
	sprintf(string, "%u", number);
	for (unsigned char i = 0; i < strlen(string); i++) {
		glRasterPos2s(x + (i * FONT_WIDTH), y + FONT_HEIGHT);
		glBitmap(
			FONT_WIDTH, FONT_HEIGHT,
			0, 0,
			0, 0,
			numberSheetGL[string[i] - 48]
		);
	}
	return;
}

void impl_drawFillRect(
	short x, short y,
	unsigned short width, unsigned short height
) {
	glRects(x, y, x + width, y + height);
	return;
}