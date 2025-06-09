const element_title = document.getElementById("title");

function pointerToString(
	memoryBuffer,
	memPosition
) {
	var ret = [];
	var currentCharacter;
	var memoryArray = new Uint8Array(memoryBuffer);
	
	for (var i = memPosition; i < memoryArray.length; i++) {
		currentCharacter = String.fromCharCode(memoryArray[i]);
		if (currentCharacter == "\0") {
			break;
		}
		ret.push(currentCharacter);
	}
	return ret.join("");
}

WebAssembly.instantiateStreaming(
	fetch("build/BlockBreakC-WASM.wasm"),
	{ "env": importList }
).then(result => {
	document.body.appendChild(element_canvas);
	function input(event) {
		result.instance.exports.input(event.keyCode);
	}
	document.addEventListener("keydown", input);
	result.instance.exports._start();
	element_title.innerText = pointerToString(
		memory,
		memPos_programName
	) + "-WASM v" + pointerToString(
		memory,
		memPos_programVersion
	);
	element_context.font = fontSize + "px Fixedsys";
	loop = setInterval(result.instance.exports.draw, 1000 / fps);
});