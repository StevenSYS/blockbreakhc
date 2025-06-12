importList["impl_getHighScore"] = function() {
	ret = localStorage.getItem("BlockBreakC-WASM_highScore");
	if (ret == undefined) {
		localStorage.setItem("BlockBreakC-WASM_highScore", 0);
		ret = 0;
	}
	return ret;
}

importList["impl_setHighScore"] = function(highScore) {
	localStorage.setItem("BlockBreakC-WASM_highScore", highScore);
	return;
}