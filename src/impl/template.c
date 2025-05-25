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

/* Implementation Template */
#include "entity.h"
#include "progInfo.h"

void reset();

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
	void *draw
) {
	return;
}

/* Draw */
void impl_drawText(
	short x, short y,
	char *text
) {
	return;
}

void impl_drawFillRect(
	short x, short y,
	unsigned short width, unsigned short height
) {
	return;
}