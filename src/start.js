const element_canvas = document.createElement("canvas");
const element_title = document.getElementById("title");
const context = element_canvas.getContext("2d");

element_canvas.style.maxWidth = "0px";
element_canvas.style.maxHeight = "0px";

document.body.appendChild(element_canvas);

var importList = {};