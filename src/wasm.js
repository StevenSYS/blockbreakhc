var fps;

const importObject = {
	env: {
		getMacros: getMacros
	},
	impl: {
		clear: implJS_clear,
		setColor: implJS_setColor,
		drawNumber: implJS_drawNumber,
		drawFillRect: implJS_drawFillRect
	}
};

WebAssembly.instantiateStreaming(
	fetch("blockBreak.wasm"),
	importObject
).then(result => {
	document.body.appendChild(canvas);
	function input(event) {
		result.instance.exports.input(event.keyCode);
	}
	document.addEventListener("keydown", input);
	result.instance.exports._start();
	context.font = "16px Fixedsys";
	loop = setInterval(result.instance.exports.draw, 1000 / fps);
});