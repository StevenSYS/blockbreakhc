const element_canvas = document.createElement("canvas");
const context = element_canvas.getContext("2d");

element_canvas.width = renderWidth;
element_canvas.height = renderHeight;
element_canvas.style.maxWidth = renderWidth + "px";
element_canvas.style.maxHeight = renderHeight + "px";

document.body.appendChild(element_canvas);
document.addEventListener("keydown", input);
document.addEventListener("touchstart", touchStart);
document.addEventListener("touchend", touchEnd);

var oldRandomColor = 13;
var randomColor = 13;
var level = 1;
var randomColors = [
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

var blockCount = 0;
var timer = 0;

var score = 0;
var highScore = 0;
if (localStorage.getItem(programName + "_highScore") != undefined) {
	highScore = parseInt(localStorage.getItem(programName + "_highScore"));
}

var timerStart = false;

var player = new entity;
var blocks = [];

for (var i = 0; i < maxBlocks; i++) {
	blocks.push([]);
	for (j = 0; j < maxBlocks; j++) {
		blocks[i].push(new entity);
	}
}

/* Touch Input */
var touch_startX;
var touch_startY;

function touchStart(event) {
	for (const touch of event.changedTouches) {
		touch_startY = touch.pageY;
		touch_startX = touch.pageX;
	}
	return;
}

function touchEnd(event) {
	event.preventDefault();
	for (const touch of event.changedTouches) {
		if ((touch.pageY - touch_startY) < -touch_threshold) {
			random_increase();
			player.direction = directions.UP;
			timerStart = true;
		} else if ((touch.pageY - touch_startY) > touch_threshold) {
			random_increase();
			player.direction = directions.DOWN;
			timerStart = true;
		}
		
		if ((touch.pageX - touch_startX) < -touch_threshold) {
			random_increase();
			player.direction = directions.LEFT;
			timerStart = true;
		} else if ((touch.pageX - touch_startX) > touch_threshold) {
			random_increase();
			player.direction = directions.RIGHT;
			timerStart = true;
		}
	}
	return;
}

/* Keyboard Input */
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
		default:
			break;
	}
}

function generateLevel(level) {
	blockCount = 0;
	
	if (level) {
		blockSize = [
			Math.round(element_canvas.width / level),
			Math.round(element_canvas.height / (level * 1.5))
		];
		
		for (i = 0; i < level; i++) {
			oldRandomColor = randomColor;
			
			while (randomColor == oldRandomColor) {
				randomColor = random_get();
			}
			
			for (j = 0; j < level; j++) {
				if ((j * blockSize[0] < element_canvas.width) && (i * blockSize[1] < element_canvas.height)) {
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
		playerWidth, playerHeight,
		playerStartX, playerStartY,
		playerSpeed,
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

function draw() {
	context.clearRect(0, 0, element_canvas.width, element_canvas.height);
	
	context.fillStyle = "#000";
	context.fillRect(0, 0, element_canvas.width, element_canvas.height);
	
	if (!blockCount) {
		score += Math.round(timer / 4);
		if (level < maxBlocks) {
			level++;
		}
		init(level, player);
	}
	
	if (player.position[1] <= screenEdgeUp) {
		player.direction = directions.DOWN;
		player.position[1] = screenEdgeUp;
	} else if (player.position[1] >= screenEdgeDown) {
		player.direction = directions.UP;
		player.position[1] = screenEdgeDown;
	} else if (player.position[0] <= screenEdgeLeft) {
		player.direction = directions.RIGHT;
		player.position[0] = screenEdgeLeft;
	} else if (player.position[0] >= screenEdgeRight) {
		player.direction = directions.LEFT;
		player.position[0] = screenEdgeRight;
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
	context.fillText(timer, 0, (renderHeight - fontHeight * 3) - 1);
	context.fillText(score, 0, (renderHeight - fontHeight) - 1);
	context.fillText(highScore, 0, renderHeight - 1);
	
	if (timerStart) {
		timer--;
	}
	
	if (!timer) {
		if (score > highScore) {
			highScore = score;
			localStorage.setItem(programName + "_highScore", highScore);
		}
		reset();
	}
	return;
}

function main() {
	init(level, player);
	
	context.font = fontHeight + "px Fixedsys";
	
	loop = setInterval(draw, 1000 / maxFPS);
	return;
}

main();