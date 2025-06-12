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