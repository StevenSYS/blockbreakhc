/*
	Date and time format:	MM/DD/YYYY HH:MM TT
	Last modified:		11/11/2024 03:44 PM
*/

function Element_GenString(Type, Content, Classes, Style) {
	return "<" + Type + " class=\"" + Classes + "\" style=\"" + Style + "\">" + Content + "</" + Type + ">";
}

function Element_Add(Element, Type, Content, Classes, Style) {
	Element.append("<" + Type + " class=\"" + Classes + "\" style=\"" + Style + "\">" + Content + "</" + Type + ">");
}