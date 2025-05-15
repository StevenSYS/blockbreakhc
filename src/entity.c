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

#include "impl.h"
#include "entity.h"

unsigned char entity_collision(
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

void entity_init(
	entity_t *entity,
	unsigned char red, unsigned char green,	unsigned char blue,
	unsigned char direction,
	unsigned short width, unsigned short height,
	short x, short y,
	short speed,
	char visible
) {
	entity->color[0] = red;
	entity->color[1] = green;
	entity->color[2] = blue;
	entity->direction = direction;
	entity->size[0] = width;
	entity->size[1] = height;
	entity->position[0] = x;
	entity->position[1] = y;
	entity->speed = speed;
	entity->visible = visible;
	return;
}

void entity_draw(
	entity_t *entity,
	char useDirection
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
		impl_setColor(entity->color[0], entity->color[1], entity->color[2]);
		impl_drawFillRect(
			entity->position[0],
			entity->position[1],
			entity->size[0],
			entity->size[1]
		);
	}
}