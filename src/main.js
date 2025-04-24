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

const canvas = document.createElement("canvas");
var context = canvas.getContext("2d");
canvas.width = screen_width;
canvas.height = screen_height;
document.body.appendChild(canvas);
document.addEventListener("keydown", input);

oldRandomColor = colors.BLACK;
randomColor = colors.BLACK;
level = 1;
randomColors = [
	colors.BLUE,
	colors.GREEN,
	colors.CYAN,
	colors.RED,
	colors.PURPLE,
	colors.BROWN,
	colors.LTBLUE,
	colors.LTGREEN,
	colors.LTCYAN,
	colors.LTRED,
	colors.LTPURPLE,
	colors.YELLOW
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
				randomColor = randomColors[Math.floor(Math.random() * 12)];
			}
			
			for (j = 0; j < level; j++) {
				if ((j * blockSize[0] < canvas.width) && (i * blockSize[1] < canvas.height)) {
					blockCount++;
					entity_init(
						blocks[j][i],
						randomColor,
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
		colors.WHITE,
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
	switch (event.keyCode) {
		case 38: /* Up */
			player.direction = directions.UP;
			timerStart = true;
			break
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
		case 27: /* Escape */
			running = false;
			break;
	}
}

function draw() {
	context.clearRect(0, 0, canvas.width, canvas.height);
	
	colorPalette_setColor(context, colors.BLACK);
	context.fillRect(0, 0, canvas.width, canvas.height);
	
	if (!blockCount) {
		score += Math.round(timer / 4);
		if (level < max_blocks) {
			level++;
		}
		init(level, player);
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
	
	colorPalette_setColor(context, colors.WHITE);
	context.fillText(program_name + " v" + program_version, 0, font_size - 1);
	
	context.fillText("Timer: " + timer, 0, (screen_height - font_size * 3) - 1);
	context.fillText("Score: " + score, 0, (screen_height - font_size) - 1);
	context.fillText("High Score: " + highScore, 0, screen_height - 1);
	
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
	
	context.font = font_size + "px ComIO";
	
	loop = setInterval(draw, max_ms);
	return
}