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
#ifdef _WIN32
#include <windows.h>
#else
#include <time.h>
#endif

#include "impl.h"
#include "entity.h"
#include "progInfo.h"

unsigned char oldRandomColor = 0;
unsigned char randomColor = 0;
unsigned char level = 1;
unsigned char colors[12][3] = {
	{ 0x00, 0x00, 0xAA },
	{ 0x00, 0xAA, 0x00 },
	{ 0x00, 0xAA, 0xAA },
	{ 0xAA, 0x00, 0x00 },
	{ 0xAA, 0x00, 0xAA },
	{ 0xAA, 0x55, 0x00 },
	{ 0x55, 0x55, 0xFF },
	{ 0x55, 0xFF, 0x55 },
	{ 0x55, 0xFF, 0xFF },
	{ 0xFF, 0x55, 0x55 },
	{ 0xFF, 0x55, 0xFF },
	{ 0xFF, 0xFF, 0x55 }
};

unsigned short blockCount = 0;
unsigned short timer = 0;

unsigned int score = 0;
unsigned int highScore = 0;

char timerStart = 0;
char timerString[255];
char scoreString[255];
char highScoreString[255];

entity_t player;
entity_t blocks[MAX_BLOCKS][MAX_BLOCKS];

void generateLevel(unsigned char level) {
	#ifdef _WIN32
	srand(GetTickCount());
	#else
	srand(time(NULL));
	#endif
	
	blockCount = 0;
	
	if (level) {
		unsigned short blockSize[2] = {
			(unsigned short)(RENDER_WIDTH / level),
			(unsigned short)(RENDER_HEIGHT / (level * 1.5))
		};
		
		for (unsigned char i = 0; i < level; i++) {
			oldRandomColor = randomColor;
			
			while (randomColor == oldRandomColor) {
				randomColor = rand() % 12;
			}
			
			for (unsigned j = 0; j < level; j++) {
				if ((j * blockSize[0] < RENDER_WIDTH) && (i * blockSize[1] < RENDER_HEIGHT)) {
					blockCount++;
					entity_init(
						&blocks[j][i],
						colors[randomColor][0], colors[randomColor][1], colors[randomColor][2],
						ENTITY_DIR_NONE,
						blockSize[0], blockSize[1],
						j * blockSize[0], i * blockSize[1],
						0,
						1
					);
				}
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
		0xff, 0xff, 0xff,
		ENTITY_DIR_UP,
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
	for (unsigned char i = 0; i < MAX_BLOCKS; i++) {
		for (unsigned char j = 0; j < MAX_BLOCKS; j++) {
			blocks[j][i].visible = 0;
		}
	}
	init(level, &player);
}

void draw() {
	impl_clear();
	
	if (!blockCount) {
		score += timer / 4;
		if (level < MAX_BLOCKS) {
			level++;
		}
		init(level, &player);
	}
	
	if (player.position[1] <= SCREEN_EDGE_UP) {
		player.direction = ENTITY_DIR_DOWN;
		player.position[1] = SCREEN_EDGE_UP;
	} else if (player.position[1] >= SCREEN_EDGE_DOWN) {
		player.direction = ENTITY_DIR_UP;
		player.position[1] = SCREEN_EDGE_DOWN;
	} else if (player.position[0] <= SCREEN_EDGE_LEFT) {
		player.direction = ENTITY_DIR_RIGHT;
		player.position[0] = SCREEN_EDGE_LEFT;
	} else if (player.position[0] >= SCREEN_EDGE_RIGHT) {
		player.direction = ENTITY_DIR_LEFT;
		player.position[0] = SCREEN_EDGE_RIGHT;
	}
	
	entity_draw(&player, 1);
	for (unsigned char i = 0; i < level; i++) {
		for (unsigned char j = 0; j < level; j++) {
			if (blocks[j][i].visible) {
				entity_draw(&blocks[j][i], 0);	
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
	
	sprintf(timerString, "Timer: %u", timer);
	sprintf(scoreString, "Score: %u", score);
	sprintf(highScoreString, "High Score: %u", highScore);
	
	impl_setColor(0xFF, 0xFF, 0xFF);
	impl_drawText(0, RENDER_HEIGHT - (impl_fontHeight * 4), timerString);
	
	impl_drawText(0, RENDER_HEIGHT - (impl_fontHeight * 2), scoreString);
	impl_drawText(0, RENDER_HEIGHT - impl_fontHeight, highScoreString);
	
	impl_render();
}

int main(
	int argc,
	char *argv[]
) {
	init(level, &player);
	
	impl_init(argc, argv, &draw);
	return 0;
}