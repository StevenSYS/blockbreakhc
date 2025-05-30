/* Implementation Template */
#include "entity.h"
#include "progInfo.h"

void reset();
void draw();

extern char timerStart;
extern entity_t player;

void impl_clear() {
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
	return;
}

void impl_init(
	int argc,
	char *argv[],
	void (*draw)()
) {
	return;
}

/* Draw */
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