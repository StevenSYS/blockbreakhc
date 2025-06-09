const element_canvas = document.createElement("canvas");
const element_title = document.getElementById("title");
const context = element_canvas.getContext("2d");
const touchDeadZone = 64;

element_canvas.style.maxWidth = "0px";
element_canvas.style.maxHeight = "0px";

document.body.appendChild(element_canvas);

var importList = {};
var maxFPS;
var fontSize;

class stringPointer {
	string = "";
	memPosition = 0;
	
	init(memoryBuffer) {
		var stringArray = [];
		var currentCharacter;
		var memoryArray = new Uint8Array(memoryBuffer);
		
		for (var i = this.memPosition; i < memoryArray.length; i++) {
			currentCharacter = String.fromCharCode(memoryArray[i]);
			if (currentCharacter == "\0") {
				break;
			}
			stringArray.push(currentCharacter);
		}
		this.string = stringArray.join("");
		return;
	}
};

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

/* Start Game */
WebAssembly.instantiateStreaming(
	fetch("build/BlockBreakC-WASM.wasm"),
	{ "env": importList }
).then(result => {
	function input(event) {
		result.instance.exports.input(event.keyCode);
		return;
	}
	document.addEventListener("keydown", input);
	
	var touch_startX;
	var touch_startY;
	
	function touchStart(event) {
		for (const touch of event.changedTouches) {
			touch_startX = touch.pageX;
			touch_startY = touch.pageY;
		}
		return;
	}
	
	function touchEnd(event) {
		event.preventDefault();
		for (const touch of event.changedTouches) {
			if ((touch.pageY - touch_startY) < -touchDeadZone) {
				result.instance.exports.input(38); /* Up */
			} else if ((touch.pageY - touch_startY) > touchDeadZone) {
				result.instance.exports.input(40); /* Down */
			}
			
			if ((touch.pageX - touch_startX) < -touchDeadZone) {
				result.instance.exports.input(37); /* Left */
			} else if ((touch.pageX - touch_startX) > touchDeadZone) {
				result.instance.exports.input(39); /* Right */
			}
		}
		return;
	}
	document.addEventListener("touchstart", touchStart);
	document.addEventListener("touchend", touchEnd);
	
	result.instance.exports._start();
	
	programName.init(result.instance.exports.memory.buffer);
	programVersion.init(result.instance.exports.memory.buffer);
	
	element_title.innerText = programName.string + "-WASM v" + programVersion.string;
	
	context.font = fontSize + "px Fixedsys";
	
	loop = setInterval(result.instance.exports.draw, 1000 / maxFPS);
});