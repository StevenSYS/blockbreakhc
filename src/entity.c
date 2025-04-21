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

#include "entity.h"
#include "colorPalette.h"
#include "progInfo.h"

unsigned char entity_collision(
	entity_t *entity1,
	entity_t *entity2
) {
	if (
		((entity1->rect.x + entity1->rect.w) >= entity2->rect.x) &&
		(entity1->rect.x <= (entity2->rect.x + entity2->rect.w)) &&
		(entity1->rect.y <= (entity2->rect.y + entity2->rect.h)) &&
		((entity1->rect.y + entity1->rect.h) >= entity2->rect.y)
	) {
		return 1;
	}
	return 0;
}

void entity_init(
	entity_t *entity,
	unsigned char color,
	unsigned char direction,
	float width, float height,
	float x, float y,
	short speed,
	bool visible
) {
	entity->color = color;
	entity->direction = direction;
	entity->rect.w = width;
	entity->rect.h = height;
	entity->rect.x = x;
	entity->rect.y = y;
	entity->speed = speed;
	entity->visible = visible;
	return;
}

void entity_draw(
	SDL_Renderer *renderer,
	entity_t *entity,
	char useDirection
) {
	if (useDirection) {
		switch (entity->direction) {
			case ENTITY_DIR_UP:
				entity->rect.y -= entity->speed;
				if (entity->rect.y <= SCREEN_EDGE_UP) {
					entity->direction = ENTITY_DIR_DOWN;
					entity->rect.y = (float)SCREEN_EDGE_UP;
				}
				break;
			case ENTITY_DIR_DOWN:
				entity->rect.y += entity->speed;
				if (entity->rect.y >= SCREEN_EDGE_DOWN) {
					entity->direction = ENTITY_DIR_UP;
					entity->rect.y = (float)SCREEN_EDGE_DOWN;
				}
				break;
			case ENTITY_DIR_LEFT:
				entity->rect.x -= entity->speed;
				if (entity->rect.x <= SCREEN_EDGE_LEFT) {
					entity->direction = ENTITY_DIR_RIGHT;
					entity->rect.x = (float)SCREEN_EDGE_LEFT;
				}
				break;
			case ENTITY_DIR_RIGHT:
				entity->rect.x += entity->speed;
				if (entity->rect.x >= SCREEN_EDGE_RIGHT) {
					entity->direction = ENTITY_DIR_LEFT;
					entity->rect.x = (float)SCREEN_EDGE_RIGHT;
				}
				break;
			default:
				break;
		}
	}
	
	if (entity->visible) {
		colorPalette_setColor(renderer, entity->color);
		SDL_RenderFillRect(renderer, &entity->rect);
	}
}