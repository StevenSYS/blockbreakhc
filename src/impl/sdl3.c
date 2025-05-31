/* SDL3 Implementation */
#include <SDL3/SDL.h>

#include "entity.h"
#include "random.h"
#include "progInfo.h"

static char running = 1;

static SDL_Event event;
static SDL_Window *window;
static SDL_Renderer *renderer;

void reset();
void draw();

extern char timerStart;
extern entity_t player;

static void input() {
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

void impl_setColor(
	unsigned char red,
	unsigned char green,
	unsigned char blue
) {
	SDL_SetRenderDrawColor(renderer, red, green, blue, SDL_ALPHA_OPAQUE);
	return;
}

void impl_clear() {
	impl_setColor(0x00, 0x00, 0x00);
	SDL_RenderClear(renderer);
	return;
}

void impl_render() {
	SDL_Delay(MAX_MS);
	
	SDL_RenderPresent(renderer);
	return;
}

void impl_init(
	int argc,
	char *argv[]
) {
	window = SDL_CreateWindow(
		PROGRAM_NAME " v" PROGRAM_VERSION " - SDL3",
		RENDER_WIDTH, RENDER_HEIGHT,
		0
	);
	
	if (window == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Couldn't create window: %s\n", SDL_GetError());
		return;
	}
	
	renderer = SDL_CreateRenderer(
		window,
		"opengl"
	);
	
	if (renderer == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Couldn't create renderer: %s\n", SDL_GetError());
		return;
	}
	
	while (running) {
		input();
		draw();
	}
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return;
}

/* Draw */
void impl_drawNumber(
	short x, short y,
	unsigned int number
) {
	SDL_RenderDebugTextFormat(renderer, (float)x, (float)y, "%u", number);
	return;
}

void impl_drawFillRect(
	short x, short y,
	unsigned short width, unsigned short height
) {
	SDL_FRect rect = { x, y, width, height };
	SDL_RenderFillRect(renderer, &rect);
	return;
}