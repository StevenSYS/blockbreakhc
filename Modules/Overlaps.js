/*
	The original version didn't use this, it instead used jQuery Overlaps - https://github.com/yckart/jquery.overlaps.js
*/

var element1Pos = {};
var element2Pos = {};

function overlaps_getPositions(element) {
	var ret = {
		x1: 0,
		y1: 0,
		x2: 0,
		y2: 0
	};
	
	ret.x1 = parseInt(element.css("left"));
	ret.y1 = parseInt(element.css("top"));
	ret.x2 = ret.x1 + parseInt(element.css("width"));
	ret.y2 = ret.y1 + parseInt(element.css("height"));
	
	return ret;
}

(function($) {
	$.fn.overlaps = function(elements) {
		var ret = {
			targets: []
		};
		$(this).each(function(index) {
			element1Pos = overlaps_getPositions($(this));
			for (const element2 of elements) {
				element2Pos = overlaps_getPositions($(element2));
				
				if (
					(element1Pos.x2 >= element2Pos.x1) &&
					(element1Pos.x1 <= element2Pos.x2) &&
					(element1Pos.y1 <= element2Pos.y2) &&
					(element1Pos.y2 >= element2Pos.y1)
				) {
					ret.targets.push($(this));
				}
			}
		})
		return ret;
	}
})(jQuery);