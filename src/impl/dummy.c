/* Dummy/Template Implementation */
#include "entity.h"
#include "random.h"
#include "progInfo.h"

void reset();
void draw();

static char *main_timerStart;

static entity_t *main_player;

void impl_loopStart() {
	return;
}

void impl_loopEnd() {
	return;
}

void impl_setColor(
	unsigned char red,
	unsigned char green,
	unsigned char blue
) {
	return;
}

void impl_init(
	int argc, char *argv[],
	char *timerStart, entity_t *player
) {
	main_timerStart = timerStart;
	main_player = player;
	return;
}

/* Drawing */
void impl_drawNumber(
	short x, short y,
	unsigned int number
) {
	return;
}

void impl_drawFillRect(
	short x, short y,
	unsigned short width, unsigned short height
) {
	return;
}