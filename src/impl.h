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
void impl_drawText(
	short x, short y,
	char *text
);

void impl_drawFillRect(
	short x, short y,
	unsigned short width, unsigned short height
);

#endif