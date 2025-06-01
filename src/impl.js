const canvas = document.createElement("canvas");
const context = canvas.getContext("2d");

function getMacros(
	render_width, render_height,
	max_fps
) {
	canvas.width = render_width;
	canvas.height = render_height;
	fps = max_fps;
	return;
}

function implJS_loopStart() {
	context.clearRect(0, 0, canvas.width, canvas.height);
	
	context.fillStyle = "#000";
	context.fillRect(0, 0, canvas.width, canvas.height);
	return;
}

function implJS_setColor(red, green, blue) {
	context.fillStyle = "rgb(" + red + ", " + green + ", " + blue + ")";
	return;
}

function implJS_drawNumber(
	x, y,
	number
) {
	context.fillText(number, x, y + 15);
	return;
}

function implJS_drawFillRect(
	x, y,
	width, height
) {
	context.beginPath();
	context.rect(x, y, width, height);
	context.fill();
	return;
}