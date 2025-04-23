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

const colors = {
	BLACK: 0,
	BLUE: 1,
	GREEN: 2,
	CYAN: 3,
	RED: 4,
	PURPLE: 5,
	BROWN: 6,
	DKGRAY: 7,
	LTGRAY: 8,
	LTBLUE: 9,
	LTGREEN: 10,
	LTCYAN: 11,
	LTRED: 12,
	LTPURPLE: 13,
	YELLOW: 14,
	WHITE: 15
};

colorPalette = [
	[ "0", "0", "0" ],
	[ "0", "0", "A" ],
	[ "0", "A", "0" ],
	[ "0", "A", "A" ],
	[ "A", "0", "0" ],
	[ "A", "0", "A" ],
	[ "A", "5", "0" ],
	[ "A", "A", "A" ],
	[ "5", "5", "5" ],
	[ "5", "5", "F" ],
	[ "5", "F", "5" ],
	[ "5", "F", "F" ],
	[ "F", "5", "5" ],
	[ "F", "5", "F" ],
	[ "F", "F", "5" ],
	[ "F", "F", "F" ]
];

function colorPalette_setColor(
	context,
	color
) {
	context.fillStyle = "#" + colorPalette[color][0] + colorPalette[color][1] + colorPalette[color][2];
	return;
}