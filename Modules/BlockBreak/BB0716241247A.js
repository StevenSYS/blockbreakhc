/*
	Date and time format:	MM/DD/YYYY HH:MM TT
	Last Modified:		07/16/2024 12:47 AM
*/

/* Booleans */
reset = false;
timerStart = false;
exitDown = false;
 
/* Intergers */
fps = 30;
blockWidth = 0;
blockHeight = 0;
dotX = 156;
dotY = 230;
direction = 0;
level = 1;
timer = 500;
score = 0;
highScore = 0;
 
/* Strings */
randomColor = "";

function blockBreakInit() {
	$(".frame").css("cursor", "none");
	$(".frame").css("user-select", "none");
	$("title").replaceWith("<title> Block Break - Unnamed Game</title>");
	if (!$(".crt").length)
		$(".frame").append("<div class=\"crt\"></div>");
	$(".frame").before("<div class=\"edge\" style=\"width: 320px; height: 16px; left: 3px; top: -15px; position: absolute;\"></div>");
	$(".frame").before("<div class=\"edge\" style=\"width: 320px; height: 16px; left: 3px; bottom: -15px; position: absolute;\"></div>");
	$(".frame").before("<div class=\"edge\" style=\"width: 16px; height: 240px; left: -15px; top: 3px; position: absolute;\"></div>");
	$(".frame").before("<div class=\"edge\" style=\"width: 16px; height: 240px; right: -15px; top: 3px; position: absolute;\"></div>");
	$(".frame").before("<div class=\"timer\">" + timer + "</div>");
	$(".frame").before("<div class=\"score\">0</div>");
	$(".frame").before("<div class=\"highScore\">" + highScore + "</div>");
	startBlockBreak();
}

function startBlockBreak() {
	if (localStorage.getItem("bBHighScore") == undefined)
		localStorage.setItem("bBHighScore", 0);
	highScore = localStorage.getItem("bBHighScore");
	$(".highScore").text(highScore);
	if ($(".dot").length) {
		$(".dot").remove();
		$(".block").remove();
		direction = 0;
		dotX = 156;
		dotY = 230;
		clearInterval(bBInterval);
		if (!reset) {
			score += Math.round(timer / 4);
			level++;
			timer += Math.round(level * 50);
		}
		$(".timer").text(timer);
		$(".score").text(score);
	}

	$(".frame").append("<div class=\"dot\"></div>");

	for (i = 0; i <= level + 4; i++) {
		randomColor = (Math.random() * 0xFFFFFF << 0).toString(16).padStart(6, "0");
console.log(jQuery.type(randomColor));
		for (j = 0; j <= level; j++) {
			blockWidth = 320 / (level + 1);
			blockHeight = 240 / (level + 7);
			$(".frame").append("<div class=\"block\" style=\"background-color: #" + randomColor + "; left: " + j * blockWidth + "px; top: " + i * blockHeight + "px; width:" + blockWidth + "px; height: " + blockHeight + "px;\"></div>");
	}}

	bBInterval = setInterval(runLoop, 1000 / fps);

	function runLoop() {
		if (timer > 0 && timerStart) {
			timer--;
			$(".timer").text(timer);
		} else if (timer == 0) {
			if (score > localStorage.getItem("bBHighScore")) {
				localStorage.setItem("bBHighScore", score);
				highScore = score;
			}
			reset = true;
			timerStart = false;
			timer = 500;
			level = 1;
			score = 0;
			startBlockBreak();
		}
		
		$(document).keydown(function(event) {
			if (!timerStart)
				timerStart = true;
			switch (event.keyCode) {
				case 13: // Enter (Exit)
					if (!exitDown)
						window.location.href = "?";
					exitDown = true;
					break;
				case 37: // Left
					direction = 1;
					break;
				case 38: // Up
					direction = 2;
					break
				case 39: // Right
					direction = 3;
					break;
				case 40: // Down
					direction = 4;
					break;
		}})
		
		$(".dot").css("top", dotY);
		$(".dot").css("left", dotX);

		touchingEdge = $(".edge").overlaps($(".dot"));	
		touchingBlock = $(".block").overlaps($(".dot"));
		if (!$(".block").length) {
			reset = false;
			startBlockBreak();
		}
		if (touchingEdge.targets.length || touchingBlock.targets.length) {
			if (touchingBlock.targets.length) {
				playSound("Block Break/BlockHit.wav", "0.25");
				for (i = 0; i < touchingBlock.targets.length; i++)
					touchingBlock.targets[i].remove();
					score += i * 10;
					$(".score").text(score);
			} else {
				playSound("Block Break/EdgeHit.wav", "0.25");
				if (dotY >= 233)
					direction = 2;
				else if (dotY <= 1)
					direction = 4;
				if (dotX >= 313)
					direction = 1;
				else if (dotX <= 1)
					direction = 3;
		}}

		if (dotY > 240)
			dotY = 240;
		if (dotY < 0)
			dotY = 0;
		if (dotX > 320)
			dotX = 320;
		if (dotY < 0)
			dotX = 0;

		if (direction > 0) {
			switch (direction) {
			case 1: // Left
				dotX -= 4;
				break;
			case 2: // Up
				dotY -= 4;
				break;
			case 3: // Right
				dotX += 4;
				break;
			case 4: // Down
				dotY += 4;
				break;
}}}}