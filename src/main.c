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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "entity.h"
#include "colorPalette.h"
#include "progInfo.h"

unsigned char randomColors[12] = {
	COLOR_BLUE,
	COLOR_GREEN,
	COLOR_CYAN,
	COLOR_RED,
	COLOR_PURPLE,
	COLOR_BROWN,
	COLOR_LTBLUE,
	COLOR_LTGREEN,
	COLOR_LTCYAN,
	COLOR_LTRED,
	COLOR_LTPURPLE,
	COLOR_YELLOW
};

char timerStart = 0;
char running = 1;

unsigned short blockCount = 0;

unsigned char oldRandomColor = COLOR_BLACK;
unsigned char randomColor = COLOR_BLACK;
unsigned char level = 1;

unsigned short timer = 0;

unsigned int score = 0;
unsigned int highScore = 0;

int frameTime = 0;

entity_t player;
entity_t blocks[BLOCK_MAX_SIZE][BLOCK_MAX_SIZE];

void generateLevel(unsigned char level) {
	blockCount = 0;
	
	if (level) {
		unsigned short blockSize[2] = {
			(unsigned short)(RENDER_WIDTH / level),
			(unsigned short)(RENDER_HEIGHT / (level * 1.5))
		};
		
		for (unsigned char i = 0; i < level; i++) {
			oldRandomColor = randomColor;
			
			while (randomColor == oldRandomColor) {
				randomColor = randomColors[rand() % 12];
			}
			
			for (unsigned j = 0; j < level; j++) {
				blockCount++;
				entity_init(
					&blocks[j][i],
					randomColor,
					ENTITY_DIR_NONE,
					(float)blockSize[0],
					(float)blockSize[1],
					(float)j * blockSize[0],
					(float)i * blockSize[1],
					0,
					1
				);
			}
		
		}
	}
	return;
}

void init(
	unsigned char level,
	entity_t *player
) {
	timer += level * 35;
	
	entity_init(
		player,
		COLOR_WHITE,
		ENTITY_DIR_NONE,
		PLAYER_WIDTH,
		PLAYER_HEIGHT,
		PLAYER_START_X,
		PLAYER_START_Y,
		PLAYER_SPEED,
		1
	);
	
	generateLevel(level);
}

void reset() {
	timer = 0;
	level = 1;
	score = 0;
	timerStart = 0;
	for (unsigned char i = 0; i < BLOCK_MAX_SIZE; i++) {
		for (unsigned char j = 0; j < BLOCK_MAX_SIZE; j++) {
			blocks[j][i].visible = 0;
		}
	}
	init(level, &player);
}

int main() {
	init(level, &player);
	
	srand(time(NULL));
	
	SDL_Event event;
	
	SDL_Window *window = SDL_CreateWindow(
		PROGRAM_NAME " v" PROGRAM_VERSION,
		RENDER_WIDTH, RENDER_HEIGHT,
		0
	);
	
	SDL_Renderer *renderer = SDL_CreateRenderer(
		window,
		"opengl"
	);
	
	while (running) {
		colorPalette_setColor(renderer, COLOR_BLACK);
		
		SDL_PollEvent(&event);
		SDL_RenderClear(renderer);
		
		switch (event.type) {
			case SDL_EVENT_KEY_DOWN:
				switch (event.key.scancode) {
					case SDL_SCANCODE_UP:
						player.direction = ENTITY_DIR_UP;
						timerStart = 1;
						continue;
					case SDL_SCANCODE_DOWN:
						player.direction = ENTITY_DIR_DOWN;
						timerStart = 1;
						continue;
					case SDL_SCANCODE_LEFT:
						player.direction = ENTITY_DIR_LEFT;
						timerStart = 1;
						continue;
					case SDL_SCANCODE_RIGHT:
						player.direction = ENTITY_DIR_RIGHT;
						timerStart = 1;
						continue;
					case SDL_SCANCODE_RETURN:
						reset();
						continue;
					case SDL_SCANCODE_ESCAPE:
						running = 0;
						continue;
					default:
						continue;
				}
				continue;
			case SDL_EVENT_QUIT:
				running = 0;
				break;
		}
		
		if (!blockCount) {
			score += timer / 4;
			if (level < BLOCK_MAX_SIZE) {
				level++;
			}
			init(level, &player);
		}
		
		entity_draw(renderer, &player, 1);
		for (unsigned char i = 0; i < level; i++) {
			for (unsigned char j = 0; j < level; j++) {
				if (blocks[j][i].visible) {
					entity_draw(renderer, &blocks[j][i], 0);	
					if (entity_collision(&player, &blocks[j][i])) {
						blocks[j][i].visible = 0;
						blockCount--;
						score += 10;
					}
				}
			}
		}
		
		if (timerStart) {
			timer--;
		}
		
		if (!timer) {
			if (score > highScore) {
				highScore = score;
			}
			reset();
		}
		
		colorPalette_setColor(renderer, COLOR_WHITE);
		SDL_RenderDebugText(renderer, 0.0f, 0.0f, PROGRAM_NAME " v" PROGRAM_VERSION);
		
		SDL_RenderDebugTextFormat(renderer, 0.0f, (float)RENDER_HEIGHT - (FONT_HEIGHT * 4), "Timer: %i", timer);
		SDL_RenderDebugTextFormat(renderer, 0.0f, (float)RENDER_HEIGHT - (FONT_HEIGHT * 2), "Score: %i", score);
		SDL_RenderDebugTextFormat(renderer, 0.0f, (float)RENDER_HEIGHT - FONT_HEIGHT, "High Score: %i", highScore);
		
		SDL_Delay(MAX_MS);
		
		SDL_RenderPresent(renderer);
	}
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return 0;
}