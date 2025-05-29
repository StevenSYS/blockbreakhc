const canvas = document.createElement("canvas");
var context = canvas.getContext("2d");
canvas.width = screen_width;
canvas.height = screen_height;
document.body.appendChild(canvas);
document.addEventListener("keydown", input);

oldRandomColor = 13;
randomColor = 13;
level = 1;
randomColors = [
	[ "0", "0", "A" ],
	[ "0", "A", "0" ],
	[ "0", "A", "A" ],
	[ "A", "0", "0" ],
	[ "A", "0", "A" ],
	[ "A", "5", "0" ],
	[ "5", "5", "F" ],
	[ "5", "F", "5" ],
	[ "5", "F", "F" ],
	[ "F", "5", "5" ],
	[ "F", "5", "F" ],
	[ "F", "F", "5" ]
];

blockCount = 0;
timer = 0;

score = 0;
highScore = 0;
if (localStorage.getItem(program_name + "_highScore") != undefined) {
	highScore = parseInt(localStorage.getItem(program_name + "_highScore"));
}

timerStart = false;

player = new entity;
blocks = [];

for (i = 0; i < max_blocks; i++) {
	blocks.push([]);
	for (j = 0; j < max_blocks; j++) {
		blocks[i].push(new entity);
	}
}

function generateLevel(level) {
	blockCount = 0;
	
	if (level) {
		blockSize = [
			Math.round(canvas.width / level),
			Math.round(canvas.height / (level * 1.5))
		];
		
		for (i = 0; i < level; i++) {
			oldRandomColor = randomColor;
			
			while (randomColor == oldRandomColor) {
				randomColor = random_get();
			}
			
			for (j = 0; j < level; j++) {
				if ((j * blockSize[0] < canvas.width) && (i * blockSize[1] < canvas.height)) {
					blockCount++;
					entity_init(
						blocks[j][i],
						randomColors[randomColor][0], randomColors[randomColor][1], randomColors[randomColor][2],
						directions.NONE,
						blockSize[0], blockSize[1],
						j * blockSize[0], i * blockSize[1],
						0,
						true
					);
				}
			}
		
		}
	}
	return;
}

function init(
	level,
	player
) {
	timer += level * 35;
	
	entity_init(
		player,
		"F", "F", "F",
		directions.NONE,
		player_width, player_height,
		player_startX, player_startY,
		player_speed,
		true
	);
	
	generateLevel(level);
	return;
}

function reset() {
	timer = 0;
	level = 1;
	score = 0;
	timerStart = false;
	init(level, player);
	return;
}

function input(event) {
	random_increase();
	switch (event.keyCode) {
		case 38: /* Up */
			player.direction = directions.UP;
			timerStart = true;
			break;
		case 40: /* Down */
			player.direction = directions.DOWN;
			timerStart = true;
			break;
		case 37: /* Left */
			player.direction = directions.LEFT;
			timerStart = true;
			break;
		case 39: /* Right */
			player.direction = directions.RIGHT;
			timerStart = true;
			break;
		case 13: /* Enter */
			reset();
			break;
	}
}

function draw() {
	context.clearRect(0, 0, canvas.width, canvas.height);
	
	context.fillStyle = "#000";
	context.fillRect(0, 0, canvas.width, canvas.height);
	
	if (!blockCount) {
		score += Math.round(timer / 4);
		if (level < max_blocks) {
			level++;
		}
		init(level, player);
	}
	
	if (player.position[1] <= screen_edgeUp) {
		player.direction = directions.DOWN;
		player.position[1] = screen_edgeUp;
	} else if (player.position[1] >= screen_edgeDown) {
		player.direction = directions.UP;
		player.position[1] = screen_edgeDown;
	} else if (player.position[0] <= screen_edgeLeft) {
		player.direction = directions.RIGHT;
		player.position[0] = screen_edgeLeft;
	} else if (player.position[0] >= screen_edgeRight) {
		player.direction = directions.LEFT;
		player.position[0] = screen_edgeRight;
	}	
	
	entity_draw(context, player, true);
	
	for (i = 0; i < level; i++) {
		for (j = 0; j < level; j++) {
			if (blocks[j][i].visible) {
				entity_draw(context, blocks[j][i], false);
				if (entity_collision(player, blocks[j][i])) {
					blocks[j][i].visible = false;
					blockCount--;
					score += 10;
				}
			}
		}
	}
	
	context.fillStyle = "#FFF";
	context.fillText(timer, 0, (screen_height - font_height * 3) - 1);
	context.fillText(score, 0, (screen_height - font_height) - 1);
	context.fillText(highScore, 0, screen_height - 1);
	
	if (timerStart) {
		timer--;
	}
	
	if (!timer) {
		if (score > highScore) {
			highScore = score;
			localStorage.setItem(program_name + "_highScore", highScore);
		}
		reset();
	}
	return;
}

function main() {
	init(level, player);
	
	context.font = font_height + "px Fixedsys";
	
	loop = setInterval(draw, max_ms);
	return;
}

main();