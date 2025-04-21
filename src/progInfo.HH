/*
	This file is part of BlockBreakHC.

	BlockBreakHC is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	any later version.

	BlockBreakHC is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License along with BlockBreakHC.
	If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef __PROGINFO__
#define __PROGINFO__

#define PROGRAM_NAME "BlockBreakHC"
#define PROGRAM_VERSION "1.0"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 472

#define SCREEN_EDGE_UP 0
#define SCREEN_EDGE_DOWN (SCREEN_HEIGHT - PLAYER_HEIGHT)
#define SCREEN_EDGE_LEFT 0
#define SCREEN_EDGE_RIGHT (SCREEN_WIDTH - PLAYER_WIDTH)

#define PLAYER_SPEED 8

#define PLAYER_WIDTH 16
#define PLAYER_HEIGHT 16

#define PLAYER_START_X (SCREEN_WIDTH / 2) - (PLAYER_WIDTH / 2)
#define PLAYER_START_Y (SCREEN_HEIGHT - PLAYER_HEIGHT) - 24

#define BLOCK_MAX_SIZE 255

#endif