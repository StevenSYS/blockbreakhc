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

#ifndef __ENTITY__
#define __ENTITY__

enum entity_directions {
	ENTITY_DIR_NONE,
	ENTITY_DIR_UP,
	ENTITY_DIR_DOWN,
	ENTITY_DIR_LEFT,
	ENTITY_DIR_RIGHT
};

struct entity {
	unsigned char color[3];
	unsigned char direction;
	unsigned short size[2];
	short position[2];
	short speed;
	
	char visible;
};

typedef struct entity entity_t;

unsigned char entity_collision(
	entity_t *entity1,
	entity_t *entity2
);

void entity_init(
	entity_t *entity,
	unsigned char red, unsigned char green,	unsigned char blue,
	unsigned char direction,
	unsigned short width, unsigned short height,
	short x, short y,
	short speed,
	char visible
);

void entity_draw(
	entity_t *entity,
	char useDirection
);

#endif