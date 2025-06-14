#ifndef __IMPL__
#define __IMPL__

void impl_loopStart();

void impl_loopEnd();

void impl_setColor(
	unsigned char red,
	unsigned char green,
	unsigned char blue
);

void impl_init(
	int argc, char *argv[],
	char *timerStart, entity_t *player
);

/* Draw */
void impl_drawNumber(
	short x, short y,
	unsigned int number
);

void impl_drawFillRect(
	short x, short y,
	unsigned short width, unsigned short height
);

/* High Score Saving */
unsigned int impl_getHighScore();

void impl_setHighScore(unsigned int highScore);

#endif