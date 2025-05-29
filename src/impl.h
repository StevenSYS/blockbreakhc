#ifndef __IMPL__
#define __IMPL__

void impl_clear();

void impl_render();

void impl_setColor(
	unsigned char red,
	unsigned char green,
	unsigned char blue
);

void impl_init(
	int argc,
	char *argv[],
	void (*draw)()
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

#endif