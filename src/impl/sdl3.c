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

/* SDL3 Implementation */
#include <stdio.h>
#include <SDL3/SDL.h>

#include "entity.h"
#include "progInfo.h"

static char running = 1;

static SDL_Event event;
static SDL_Window *window;
static SDL_Renderer *renderer;

const unsigned char impl_fontHeight = 8;

void reset();

extern char timerStart;
extern entity_t player;

static void input() {
	SDL_PollEvent(&event);
	
	switch (event.type) {
		case SDL_EVENT_KEY_DOWN:
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
	char *argv[],
	void (*draw)()
) {
	window = SDL_CreateWindow(
		PROGRAM_NAME " v" PROGRAM_VERSION,
		RENDER_WIDTH, RENDER_HEIGHT,
		0
	);
	
	renderer = SDL_CreateRenderer(
		window,
		"opengl"
	);
	
	while(running) {
		input();
		draw();
	}
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return;
}

/* Draw */
void impl_drawText(
	short x, short y,
	char *text
) {
	SDL_RenderDebugText(renderer, (float)x, (float)y, text);
	return;
}

void impl_drawFillRect(
	short x, short y,
	unsigned width, unsigned height
) {
	SDL_FRect rect = { x, y, width, height };
	SDL_RenderFillRect(renderer, &rect);
	return;
}