/*
	Date and time format:	MM/DD/YYYY HH:MM TT
	Last modified:		11/15/2024 01:14 PM
*/

var Menu_History = [];
var Menu_CSSMap = ["color", "color", "font-family", "font-size", "text-align", "text-height", "background-color", "background-image", "overflow", "scrollbar-color"]
var Menu_CSSMapMenu = ["color", "linkColor", "fontFamily", "fontSize", "textAlign", "textHeight", "backgroundColor", "backgroundImage", "overflow", "scrollBarColor"];

function Menu_Load(JSON, Overlay, Filename) {
	var List = [];
	$("title").text(JSON.title + " - " + Global_Name);
	Music_Play(JSON);
	if ($(".Menu_Container").length) {
		$(".Menu_Container").empty();
		$(".Global_MenuLayer").removeAttr("style");
	} else
		$(".Global_MenuLayer").append("<div class=\"Menu_Container\"></div>");
	Menu_History.push(Filename);
	$.each(JSON, function(key, value) {
		List.push(key + ":" + value);
		if (key.indexOf("Javascript") != -1)
			eval(value);
	});
	for (var i = 0; i < List.length; i++) {
		if (List[i].split(":")[0].indexOf("set") != -1) {
			var Set_Current = List[i].split(":")[0];
			var Set_FullJSON = eval("JSON." + Set_Current);
			if (Set_FullJSON.image != undefined) {
				if (Set_FullJSON.links.imageLink == undefined)
					$(".Menu_Container").append("<img src=\"" + Set_FullJSON.image + "\">");
				else
					$(".Menu_Container").append("<a href=\"" + Set_FullJSON.links.imageLink + "\"><img src=\"" + Set_FullJSON.image + "\"></a>");
			}
			$.each(Set_FullJSON, function(key, value) {
				if (key.indexOf("text") != -1) {
					var textLink = eval("Set_FullJSON.links.textLink" + key.replace("text", ""));
					if (textLink == undefined) {
						var textHeader = eval("Set_FullJSON.header" + key.replace("text", ""));
						if (textHeader == undefined)
							$(".Menu_Container").append("<p>" + value + "</p>");
						else
							$(".Menu_Container").append("<h" + textHeader + ">" + value + "</h" + textHeader + ">");
					} else
						$(".Menu_Container").append("<a href=\"" + textLink + "\">" + value + "</a><p></p>");
				}
				if (key.indexOf("html") != -1)
					$(".Menu_Container").append(value);
				if (key.indexOf("button") != -1) {
					var Button_Link = eval("Set_FullJSON.links.buttonLink" + key.replace("button", ""));
					var Button_Command = "";
					var Button_Disabled = false;
					if (Button_Link == undefined) {
						var Button_Link = eval("Set_FullJSON.links.buttonMenu" + key.replace("button", ""));
						if (Button_Link != undefined) {
							switch (Button_Link.toLowerCase()) {
								case "back":
									if (Overlay && Menu_History.length <= 1)
										Button_Command = "$('.Menu_Container').empty(); $('.Global_MenuLayer').removeAttr('style'); menuOpen[0] = false; menuOpen[1] = true; Menu_History = [];";
									else
										Button_Command = "$.getJSON('Assets/Menus/" + Menu_History[Menu_History.length - 2] + ".json', function(JSONMenu) {  Menu_History.pop(); Menu_History.pop(); Menu_Load(JSONMenu, true, '" + Menu_History[Menu_History.length - 2] + "'); });";
									break;
								default:
									Button_Command = "$.getJSON('Assets/Menus/" + Button_Link + ".json', function(JSONMenu) { Menu_Load(JSONMenu, false, '" + Button_Link + "'); });";
							}
						} else {
							var Button_Link = eval("Set_FullJSON.links.buttonJavaScript" + key.replace("button", ""));
							if (Button_Link != undefined)
								Button_Command = Button_Link;
					}} else {
						switch (Button_Link.toLowerCase()) {
							case "disabled":
								Button_Disabled = true;
								break;
							case "backGame":
								if (Overlay)
									Button_Command = "$('.Menu_Container').empty(); $('.Global_MenuLayer').removeAttr('style'); menuOpen[0] = false; menuOpen[1] = true; Menu_History = [];";
								break;
							default:
								Button_Command = "location.href = '" + Button_Link + "'";
					}}
					$(".Menu_Container").append("<div class=\"Menu_Button" + (Button_Disabled ? " disabled" : "") + "\" onClick=\"" + Button_Command + "\">" + value + "</div><br>");
	}});}}
	$.each(JSON.css, function(key, value) {
		if (Menu_CSSMapMenu.indexOf(key) != -1) {
			switch (key) {
				case "linkColor":
					$(".Global_MenuLayer a").css("color", value);
					break;
				case "backgroundImage":
					$(".Global_MenuLayer").css("background-image", "url(" + value + ")");
					break;
				default:
					$(".Global_MenuLayer").css(Menu_CSSMap[Menu_CSSMapMenu.indexOf(key)], value);
		}
}});} 