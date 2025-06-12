/* raylib Implementation */
#include <raylib.h>

#include "entity.h"
#include "random.h"
#include "progInfo.h"

void reset();
void draw();

extern char timerStart;
extern entity_t player;

static Color currentColor;

static void input() {
	if (GetKeyPressed()) {
		random_increase();
		if (IsKeyPressed(KEY_UP)) {
			player.direction = ENTITY_DIR_UP;
			timerStart = 1;
		}
		if (IsKeyPressed(KEY_DOWN)) {
			player.direction = ENTITY_DIR_DOWN;
			timerStart = 1;
		}
		if (IsKeyPressed(KEY_LEFT)) {
			player.direction = ENTITY_DIR_LEFT;
			timerStart = 1;
		}
		if (IsKeyPressed(KEY_RIGHT)) {
			player.direction = ENTITY_DIR_RIGHT;
			timerStart = 1;
		}
		if (IsKeyPressed(KEY_ENTER)) {
			reset();
		}
	}
	return;
}

void impl_loopStart() {
	BeginDrawing();
	ClearBackground(BLACK);
	return;
}

void impl_loopEnd() {
	EndDrawing();
	return;
}

void impl_setColor(
	unsigned char red,
	unsigned char green,
	unsigned char blue
) {
	currentColor = (Color){ red, green, blue, 0xFF };
	return;
}

void impl_init(
	int argc,
	char *argv[]
) {
	InitWindow(RENDER_WIDTH, RENDER_HEIGHT, PROGRAM_NAME " v" PROGRAM_VERSION " - raylib");
	
	SetTargetFPS(MAX_FPS);
	
	while (!WindowShouldClose()) {
		input();
		draw();
	}
	
	CloseWindow();
	return;
}

/* Drawing */
void impl_drawNumber(
	short x, short y,
	unsigned int number
) {
	DrawText(
		TextFormat("%u", number),
		x, y,
		FONT_HEIGHT,
		currentColor
	);
	return;
}

void impl_drawFillRect(
	short x, short y,
	unsigned short width, unsigned short height
) {
	DrawRectangle(
		x, y,
		width, height,
		currentColor
	);
	return;
}