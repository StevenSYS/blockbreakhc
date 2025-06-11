/*
	Date and time format: 	MM/DD/YYYY HH:MM TT
	Last modified: 		11/15/2024 01:38 PM
*/

/* Music */
function Music_Play(JSON) {
	console.log(JSON.music);
	if (JSON.music == undefined) {
		if ($(".SoundMusic_Music").length) 
			$(".SoundMusic_Music").remove();
	} else {
		if (JSON.music.continue == undefined || JSON.music.continue != true) {
			if ($(".SoundMusic_Music source").attr("src") != JSON.music.file) {
				if ($(".SoundMusic_music").length)
					$(".SoundMusic_Music").remove();
				$("body").append("<audio autoplay " + (JSON.music.loop ? "loop" : "") + " class=\"SoundMusic_Music\"><source src=\"" + JSON.music.file + "\"></source></video>");
		}}
		if (JSON.music.volume != undefined)
			$(".music").prop("volume", JSON.music.volume / 100);
}}

/* Sound */
function Sound_Play(File, Volume) {
	const Sound = new Audio("Assets/Sounds/" + File);
	Sound.volume = Volume / 100;
	Sound.play();
}