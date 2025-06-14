/* SDL3 + GL Implementation */
#include "glShared.h"

#ifdef __APPLE
	#include <SDL.h>
	#include <gl.h>
#else
	#include <SDL3/SDL.h>
	#include <GL/gl.h>
#endif

static char running = 1;

static unsigned int lastTime;

static SDL_Event event;
static SDL_Window *window;
static SDL_GLContext glContext;

static void handleEvent() {
	SDL_PollEvent(&event);
	
	switch (event.type) {
		case SDL_EVENT_KEY_DOWN:
			random_increase();
			switch (event.key.scancode) {
				case SDL_SCANCODE_UP:
					player.direction = ENTITY_DIR_UP;
					timerStart = 1;
					break;
				case SDL_SCANCODE_DOWN:
					player.direction = ENTITY_DIR_DOWN;
					timerStart = 1;
					break;
				case SDL_SCANCODE_LEFT:
					player.direction = ENTITY_DIR_LEFT;
					timerStart = 1;
					break;
				case SDL_SCANCODE_RIGHT:
					player.direction = ENTITY_DIR_RIGHT;
					timerStart = 1;
					break;
				case SDL_SCANCODE_RETURN:
					reset();
					break;
				case SDL_SCANCODE_ESCAPE:
					running = 0;
					break;
				default:
					break;
			}
			break;
		case SDL_EVENT_QUIT:
			running = 0;
			break;
	}
	return;
}

void impl_loopEnd() {
	SDL_GL_SwapWindow(window);
	return;
}

void impl_init(int argc, char *argv[]) {
	window = SDL_CreateWindow(
		PROGRAM_NAME " v" PROGRAM_VERSION " - SDL3 + GL",
		RENDER_WIDTH, RENDER_HEIGHT,
		SDL_WINDOW_OPENGL
	);
	
	if (window == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Couldn't create window: %s\n", SDL_GetError());
		return;
	}
	
	glContext = SDL_GL_CreateContext(window);
	
	if (glContext == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Couldn't create renderer: %s\n", SDL_GetError());
		return;
	}
	
	glSharedInit();
	
	while (running) {
		lastTime = SDL_GetTicks();
		
		handleEvent();
		draw();
		
		while (SDL_GetTicks() < lastTime + (1000.0f / MAX_FPS)) {
			handleEvent();
			SDL_Delay(1);
		}
	}
	
	SDL_GL_DestroyContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return;
}