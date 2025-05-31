/* GLFW3 Implementation */
#include <GLFW/glfw3.h>

#include "progInfo.h"
#include "glShared.h"

static GLFWwindow *window;

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

void impl_render() {
	glFlush();
	glfwSwapBuffers(window);
	return;
}

void impl_init(int, char) {
	if (!glfwInit()) {
		return;
	}
	
	window = glfwCreateWindow(
		RENDER_WIDTH, RENDER_HEIGHT,
		PROGRAM_NAME " v" PROGRAM_VERSION " - GLFW3",
		NULL, NULL
	);
	
	if (window == NULL) {
		glfwTerminate();
		return;
	}
	
	glfwSetWindowSizeLimits(
		window,
		RENDER_WIDTH, RENDER_HEIGHT,
		RENDER_WIDTH, RENDER_HEIGHT
	);
	
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, input);
	
	glSharedInit();
	
	while (!glfwWindowShouldClose(window)) {
		lastTime = glfwGetTime();
		
		glfwPollEvents();
		
		draw();
		
		while (glfwGetTime() < lastTime + (1.0f / MAX_FPS));
	}
	
	glfwTerminate();
	return;
}