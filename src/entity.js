const directions = {
	NONE: 0,
	UP: 1,
	DOWN: 2,
	LEFT: 3,
	RIGHT: 4
};

class entity {
	color = [];
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
	red, green, blue,
	direction,
	width, height,
	x, y,
	speed,
	visible
) {
	entity.color[0] = red;
	entity.color[1] = green;
	entity.color[2] = blue;
	entity.direction = direction;
	entity.size[0] = width;
	entity.size[1] = height;
	entity.position[0] = x;
	entity.position[1] = y;
	entity.speed = speed;
	entity.visible = visible;
	return;
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
		context.fillStyle = "#" + entity.color[0] + entity.color[1] + entity.color[2];
		context.rect(entity.position[0], entity.position[1], entity.size[0], entity.size[1]);
		context.fill();
	}
	return;
}