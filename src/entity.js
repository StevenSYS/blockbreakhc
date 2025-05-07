/*
	This file is part of BlockBreakJS.

	BlockBreakJS is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	any later version.

	BlockBreakJS is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License along with BlockBreakJS.
	If not, see <https://www.gnu.org/licenses/>.
*/

const directions = {
	NONE: 0,
	UP: 1,
	DOWN: 2,
	LEFT: 3,
	RIGHT: 4
};

class entity {
	color;
	direction;
	size = [];
	position = [];
	speed;
	
	visible;
};

function entity_collision(
	entity1,
	entity2
) {
	if (
		((entity1.position[0] + entity1.size[0]) >= entity2.position[0]) &&
		(entity1.position[0] <= (entity2.position[0] + entity2.size[0])) &&
		(entity1.position[1] <= (entity2.position[1] + entity2.size[1])) &&
		((entity1.position[1] + entity1.size[1]) >= entity2.position[1])
	) {
		return true;
	}
	return false;
}

function entity_init(
	entity,
	color,
	direction,
	width, height,
	x, y,
	speed,
	visible
) {
	entity.color = color;
	entity.direction = direction;
	entity.size[0] = width;
	entity.size[1] = height;
	entity.position[0] = x;
	entity.position[1] = y;
	entity.speed = speed;
	entity.visible = visible;
}

function entity_draw(
	context,
	entity,
	useDirection
) {
	if (useDirection) {
		switch (entity.direction) {
			case directions.UP:
				entity.position[1] -= entity.speed;
				break;
			case directions.DOWN:
				entity.position[1] += entity.speed;
				break;
			case directions.LEFT:
				entity.position[0] -= entity.speed;
				break;
			case directions.RIGHT:
				entity.position[0] += entity.speed;
				break;
		}
	}
	
	if (entity.visible) {
		context.beginPath();
		colorPalette_setColor(context, entity.color);
		context.rect(entity.position[0], entity.position[1], entity.size[0], entity.size[1]);
		context.fill();
	}
	return;
}