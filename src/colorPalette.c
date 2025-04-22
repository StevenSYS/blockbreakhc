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

#include <SDL3/SDL.h>

#include "colorPalette.h"

static const unsigned char palette[16][3] = {
	{ 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0xAA },
	{ 0x00, 0xAA, 0x00 },
	{ 0x00, 0xAA, 0xAA },
	{ 0xAA, 0x00, 0x00 },
	{ 0xAA, 0x00, 0xAA },
	{ 0xAA, 0x55, 0x00 },
	{ 0xAA, 0xAA, 0xAA },
	{ 0x55, 0x55, 0x55 },
	{ 0x55, 0x55, 0xFF },
	{ 0x55, 0xFF, 0x55 },
	{ 0x55, 0xFF, 0xFF },
	{ 0xFF, 0x55, 0x55 },
	{ 0xFF, 0x55, 0xFF },
	{ 0xFF, 0xFF, 0x55 },
	{ 0xFF, 0xFF, 0xFF }
};

void colorPalette_setColor(
	SDL_Renderer *renderer,
	enum colorPalette_colors color
) {
	SDL_SetRenderDrawColor(renderer, palette[color][0], palette[color][1], palette[color][2], SDL_ALPHA_OPAQUE);
	return;
}