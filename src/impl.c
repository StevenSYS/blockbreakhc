#include "random.h"
#include "entity.h"
#include "progInfo.h"

void reset();

int main(
	int argc,
	char *argv[]
);

extern char timerStart;
extern entity_t player;

void getMacros(
	char *programName, char *programVersion,
	int renderWidth, int renderHeight,
	int maxFPS,
	int fontHeight
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

void impl_loopEnd() {
	return;
}

void impl_init(
	int argc,
	char *argv[]
) {
	return;
}

void _start() {
	getMacros(
		PROGRAM_NAME, PROGRAM_VERSION,
		RENDER_WIDTH, RENDER_HEIGHT,
		MAX_FPS,
		FONT_HEIGHT
	);
	main(0, 0);
	return;
}