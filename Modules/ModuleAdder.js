/*
	Date and time format:	MM/DD/YYYY HH:MM TT
	Last modified:		11/11/2024 04:34 PM
*/

var ModuleAdder_AddedModules = [];

function Module_Add(ModuleName, Directory) {
	if (Directory == undefined)
		Directory = "Modules/";
	if (ModuleAdder_AddedModules.indexOf(Directory + ModuleName) == -1) {
		$("body").append("<script src=\"" + Directory + ModuleName + "\"></script>");
		ModuleAdder_AddedModules.push(Directory + ModuleName);
}}