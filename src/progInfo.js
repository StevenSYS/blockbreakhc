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

program_name = "BlockBreakJS";
program_version = "1.0";

screen_width = 640;
screen_height = 472;

font_size = 8;

player_speed = Math.round(screen_width / 80);
player_width = Math.round(screen_width / 40);
player_height = Math.round(screen_width / 40);
player_startX = Math.round((screen_width / 2) - (player_width / 2));
player_startY = screen_height - (player_height * 3);

screen_edgeUp = 0;
screen_edgeDown = screen_height - player_height;
screen_edgeLeft = 0;
screen_edgeRight = screen_width - player_width;

max_blocks = 255;
max_fps = 30;
max_ms = 1000 / max_fps;