/* Shared OpenGL Functions */
#include <stdio.h>
#include <string.h>

#include "entity.h"
#include "random.h"

void draw();
void reset();

extern char timerStart;
extern entity_t player;

static char string[11];

static const GLubyte numberSheet[10][FONT_HEIGHT] = {
	{ 0x00, 0x78, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x78 }, /* 0 */
	{ 0x00, 0xFC, 0x30, 0x30, 0x30, 0xF0, 0x70, 0x30 }, /* 1 */
	{ 0x00, 0xFC, 0xC0, 0xC0, 0x78, 0x0C, 0xCC, 0x78 }, /* 2 */
	{ 0x00, 0x78, 0xCC, 0x0C, 0x38, 0x0C, 0xCC, 0x78 }, /* 3 */
	{ 0x00, 0x18, 0x18, 0xFC, 0xD8, 0x78, 0x38, 0x18 }, /* 4 */
	{ 0x00, 0xF8, 0x0C, 0x0C, 0xF8, 0xC0, 0xC0, 0xFC }, /* 5 */
	{ 0x00, 0x78, 0xCC, 0xCC, 0xF8, 0xC0, 0xCC, 0x78 }, /* 6 */
	{ 0x00, 0x30, 0x30, 0x18, 0x18, 0x0C, 0x0C, 0xFC }, /* 7 */
	{ 0x00, 0x78, 0xCC, 0xCC, 0x78, 0xCC, 0xCC, 0x78 }, /* 8 */
	{ 0x00, 0x78, 0xCC, 0x0C, 0x7C, 0xCC, 0xCC, 0x78 }  /* 9 */
};
static GLubyte numberSheetGL[10][(FONT_HEIGHT * 4) + 1] = { 0 };

static void glSharedInit() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glOrtho(0, RENDER_WIDTH, RENDER_HEIGHT, 0, -1, 1);
	
	for (unsigned char j = 0; j < 10; j++) {
		for (unsigned char i = 0; i <= FONT_HEIGHT * 4; i += 4) {
			numberSheetGL[j][i] = numberSheet[j][i / 4];
		}
	}
	return;
}

void impl_clear() {
	glClear(GL_COLOR_BUFFER_BIT);
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

/* Drawing */
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