/* GLFW3 Implementation */
#include <stdio.h>
#include <string.h>
#include <GLFW/glfw3.h>

#include "entity.h"
#include "random.h"
#include "progInfo.h"

void reset();
void draw();

extern char timerStart;
extern entity_t player;

static GLFWwindow *window;

static char string[11];

static const unsigned char numberSheet[10][FONT_HEIGHT] = {
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
static GLubyte numberSheetGL[10][29] = { 0 };

static double lastTime;

static void input(
	GLFWwindow *window,
	int key,
	int,
	int action,
	int
) {
	if (action == GLFW_PRESS) {
		random_increase();
		switch (key) {
			case GLFW_KEY_UP:
				timerStart = 1;
				player.direction = ENTITY_DIR_UP;
				break;
			case GLFW_KEY_DOWN:
				timerStart = 1;
				player.direction = ENTITY_DIR_DOWN;
				break;
			case GLFW_KEY_LEFT:
				timerStart = 1;
				player.direction = ENTITY_DIR_LEFT;
				break;
			case GLFW_KEY_RIGHT:
				timerStart = 1;
				player.direction = ENTITY_DIR_RIGHT;
				break;
			case GLFW_KEY_ENTER:
				reset();
				break;
			case GLFW_KEY_ESCAPE:
				glfwSetWindowShouldClose(window, GL_TRUE);
				break;
			default:
				break;
		}
	}
	return;
}

void impl_clear() {
	glClear(GL_COLOR_BUFFER_BIT);
	return;
}

void impl_render() {
	glFlush();
	glfwSwapBuffers(window);
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
	if (!glfwInit()) {
		return;
	}
	
	window = glfwCreateWindow(
		RENDER_WIDTH, RENDER_HEIGHT,
		PROGRAM_NAME " v" PROGRAM_VERSION " - GLFW3",
		NULL, NULL
	);
	
	glfwSetWindowSizeLimits(
		window,
		RENDER_WIDTH, RENDER_HEIGHT,
		RENDER_WIDTH, RENDER_HEIGHT
	);
	
	if (!window) {
		glfwTerminate();
		return;
	}
	
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, input);
	
	glOrtho(0, RENDER_WIDTH, RENDER_HEIGHT, 0, -1, 1);
	
	for (unsigned char j = 0; j < 10; j++) {
		for (unsigned char i = 0; i <= FONT_HEIGHT * 4; i += 4) {
			numberSheetGL[j][i] = numberSheet[j][i / 4];
		}
	}
	
	while (!glfwWindowShouldClose(window)) {
		lastTime = glfwGetTime();
		
		glfwPollEvents();
		
		draw();
		
		while (glfwGetTime() < lastTime + (1.0f / MAX_FPS));
	}
	
	glfwTerminate();
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