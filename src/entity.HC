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

#include "progInfo.HH"

/* Enum - entity_directions */
#define ENTITY_DIR_NONE 0
#define ENTITY_DIR_UP 1
#define ENTITY_DIR_DOWN 2
#define ENTITY_DIR_LEFT 3
#define ENTITY_DIR_RIGHT 4
/* Enum - End */

class entity_t {
	U8 color;
	U8 direction;
	U16 size[2];
	I16 position[2];
	I16 speed;
	
	Bool visible;
};

U8 entity_collision(
	entity_t *entity1,
	entity_t *entity2
) {
	if (
		((entity1->position[0] + entity1->size[0]) >= entity2->position[0]) &&
		(entity1->position[0] <= (entity2->position[0] + entity2->size[0])) &&
		(entity1->position[1] <= (entity2->position[1] + entity2->size[1])) &&
		((entity1->position[1] + entity1->size[1]) >= entity2->position[1])
	) {
		return 1;
	}
	return 0;
}

U0 entity_init(
	entity_t *entity,
	U8 color,
	U8 direction,
	U16 width, U16 height,
	I16 x, I16 y,
	I16 speed,
	Bool visible
) {
	entity->color = color;
	entity->direction = direction;
	entity->size[0] = width;
	entity->size[1] = height;
	entity->position[0] = x;
	entity->position[1] = y;
	entity->speed = speed;
	entity->visible = visible;
	return;
}

U0 entity_draw(
	CDC *dc,
	entity_t *entity,
	Bool useDirection
) {
	if (useDirection) {
		switch (entity->direction) {
			case ENTITY_DIR_UP:
				entity->position[1] -= entity->speed;
				break;
			case ENTITY_DIR_DOWN:
				entity->position[1] += entity->speed;
				break;
			case ENTITY_DIR_LEFT:
				entity->position[0] -= entity->speed;
				break;
			case ENTITY_DIR_RIGHT:
				entity->position[0] += entity->speed;
				break;
		}
	}
	
	if (entity->visible) {
		dc->color = entity->color;
		GrRect(
			dc,
			entity->position[0],
			entity->position[1],
			entity->size[0],
			entity->size[1]
		);
	}
}