const element_canvas = document.createElement("canvas");
const element_context = element_canvas.getContext("2d");

var importList = {};
var fps;
var fontSize;

var memPos_programName;
var memPos_programVersion;

importList["getMacros"] = function(
	programName, programVersion,
	renderWidth, renderHeight,
	maxFPS,
	fontHeight
) {
	memPos_programName = programName;
	memPos_programVersion = programVersion;
	fps = maxFPS;
	element_canvas.width = renderWidth;
	element_canvas.height = renderHeight;
	fontSize = fontHeight;
	return;
}

importList["impl_loopStart"] = function() {
	element_context.clearRect(
		0, 0,
		element_canvas.width, element_canvas.height
	);
	
	element_context.fillStyle = "#000";
	element_context.fillRect(
		0, 0,
		element_canvas.width, element_canvas.height
	);
	return;
}

importList["impl_setColor"] = function(red, green, blue) {
	element_context.fillStyle = "rgb(" + red + ", " + green + ", " + blue + ")";
	return;
}

/* Drawing */
importList["impl_drawNumber"] = function(
	x, y,
	number
) {
	element_context.fillText(number, x, y + (fontSize - 1));
	return;
}

importList["impl_drawFillRect"] = function(
	x, y,
	width, height
) {
	element_context.beginPath();
	element_context.rect(x, y, width, height);
	element_context.fill();
	return;
}