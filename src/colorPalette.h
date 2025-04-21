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

#ifndef __COLORPALETTE__
#define __COLORPALETTE__

enum colorPalette_colors {
	COLOR_BLACK,
	COLOR_BLUE,
	COLOR_GREEN,
	COLOR_CYAN,
	COLOR_RED,
	COLOR_PURPLE,
	COLOR_BROWN,
	COLOR_DKGRAY,
	COLOR_LTGRAY,
	COLOR_LTBLUE,
	COLOR_LTGREEN,
	COLOR_LTCYAN,
	COLOR_LTRED,
	COLOR_LTPURPLE,
	COLOR_YELLOW,
	COLOR_WHITE
};

void colorPalette_setColor(
	SDL_Renderer *renderer,
	enum colorPalette_colors color
);

#endif