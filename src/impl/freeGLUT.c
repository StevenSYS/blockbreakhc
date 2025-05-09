/*
	This file is part of BlockBreakC.

	BlockBreakC is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	any later version.

	BlockBreakC is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License along with BlockBreakC.
	If not, see <https://www.gnu.org/licenses/>.
*/

/* FreeGLUT Implementation */
#include <GL/freeglut.h>

#include "entity.h"
#include "progInfo.h"

const unsigned char impl_fontHeight = 13;

void reset();

extern char timerStart;
extern entity_t player;

static void input(
	unsigned char key,
	int, int
) {
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
	char *argv[],
	void *draw
) {
	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutCreateWindow(PROGRAM_NAME " v" PROGRAM_VERSION);
	glutReshapeWindow(RENDER_WIDTH, RENDER_HEIGHT);
	
	glOrtho(0, RENDER_WIDTH, RENDER_HEIGHT, 0, -1, 1);
	
	glutKeyboardFunc(input);
	glutSpecialFunc(inputSpecial);
	glutDisplayFunc(draw);
	glutTimerFunc(1000 / 60, drawLoop, 0);
	
	glutMainLoop();
	return;
}

/* Draw */
void impl_drawText(
	short x, short y,
	char *text
) {
	glRasterPos2s(x, y + 11);
	glutBitmapString(GLUT_BITMAP_8_BY_13, text);
	return;
}

void impl_drawFillRect(
	short x, short y,
	unsigned width, unsigned height
) {
	glRects(x, y, x + width, y + height);
	return;
}