var maxFPS;
var fontSize;
var programName = new stringPointer;
var programVersion = new stringPointer;

importList["getMacros"] = function(
	memPos_programName, memPos_programVersion,
	renderWidth, renderHeight,
	macro_maxFPS,
	fontHeight
) {
	programName.memPosition = memPos_programName;
	programVersion.memPosition = memPos_programVersion;
	maxFPS = macro_maxFPS;
	element_canvas.width = renderWidth;
	element_canvas.height = renderHeight;
	element_canvas.style.maxWidth = renderWidth + "px";
	element_canvas.style.maxHeight = renderHeight + "px";
	fontSize = fontHeight;
	return;
}

importList["impl_loopStart"] = function() {
	context.clearRect(
		0, 0,
		element_canvas.width, element_canvas.height
	);
	
	context.fillStyle = "#000";
	context.fillRect(
		0, 0,
		element_canvas.width, element_canvas.height
	);
	return;
}

importList["impl_setColor"] = function(red, green, blue) {
	context.fillStyle = "rgb(" + red + ", " + green + ", " + blue + ")";
	return;
}

/* Drawing */
importList["impl_drawNumber"] = function(
	x, y,
	number
) {
	context.fillText(number, x, y + (fontSize - 1));
	return;
}

importList["impl_drawFillRect"] = function(
	x, y,
	width, height
) {
	context.beginPath();
	context.rect(x, y, width, height);
	context.fill();
	return;
}