#include "random.h"
#include "entity.h"
#include "progInfo.h"

#define WASM_IMPORT(module, name) __attribute__((__import_module__((module)), __import_name__((name))))

void reset();

int main(
	int argc,
	char *argv[]
);

extern char timerStart;
extern entity_t player;

WASM_IMPORT("env", "getMacros") void getMacros(
	unsigned int render_width, unsigned int render_height,
	unsigned short max_fps
);

WASM_IMPORT("impl", "clear") void implJS_clear();

WASM_IMPORT("impl", "setColor") void implJS_setColor(
	unsigned char red,
	unsigned char green,
	unsigned char blue
);

WASM_IMPORT("impl", "drawNumber") void implJS_drawNumber(
	int x, int y,
	unsigned int number
);

WASM_IMPORT("impl", "drawFillRect") void implJS_drawFillRect(
	int x, int y,
	int width, int height
);

void input(unsigned char key) {
	random_increase();
	switch (key) {
		case 38: /* Up */
			player.direction = ENTITY_DIR_UP;
			timerStart = 1;
			break;
		case 40: /* Down */
			player.direction = ENTITY_DIR_DOWN;
			timerStart = 1;
			break;
		case 37: /* Left */
			player.direction = ENTITY_DIR_LEFT;
			timerStart = 1;
			break;
		case 39: /* Right */
			player.direction = ENTITY_DIR_RIGHT;
			timerStart = 1;
			break;
		case 13: /* Enter */
			reset();
			break;
	}
	return;
}

void impl_clear() {
	implJS_clear();
	return;
}

void impl_render() {
	return;
}

void impl_setColor(
	unsigned char red,
	unsigned char green,
	unsigned char blue
) {
	implJS_setColor(red, green, blue);
	return;
}

void impl_init(
	int argc,
	char *argv[]
) {
	return;
}

/* Draw */
void impl_drawNumber(
	short x, short y,
	unsigned int number
) {
	implJS_drawNumber(x, y, number);
	return;
}

void impl_drawFillRect(
	short x, short y,
	unsigned short width, unsigned short height
) {
	implJS_drawFillRect(x, y, width, height);
	return;
}

void _start() {
	getMacros(
		RENDER_WIDTH, RENDER_HEIGHT,
		MAX_FPS
	);
	main(0, 0);
	return;
}