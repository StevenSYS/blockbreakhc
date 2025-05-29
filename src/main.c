#include "random.h"
#include "impl.h"
#include "entity.h"
#include "progInfo.h"

unsigned char oldRandomColor = 13;
unsigned char randomColor = 13;
unsigned char level = 1;
const unsigned char colors[12][3] = {
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

entity_t player;
entity_t blocks[MAX_BLOCKS][MAX_BLOCKS];

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
				randomColor = random_get();
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
	
	impl_setColor(0xFF, 0xFF, 0xFF);
	impl_drawNumber(0, RENDER_HEIGHT - (FONT_HEIGHT * 4), timer);
	
	impl_drawNumber(0, RENDER_HEIGHT - (FONT_HEIGHT * 2), score);
	impl_drawNumber(0, RENDER_HEIGHT - FONT_HEIGHT, highScore);
	
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