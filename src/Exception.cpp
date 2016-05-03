#include "Exception.h"

string Exception::getMsg()const {
	return msg;
}
WrongFilePathException::WrongFilePathException(string path){
	msg = "Invalid file path: ";
	msg += path;
}
WrongInsertionException::WrongInsertionException(string problem){
	msg = "Insertion problem: " + problem;
}
WrongFilterException::WrongFilterException(){
	msg = "Cannot filter: bad syntax";
}
WrongEditException::WrongEditException(string problem){
	msg = "Cannot edit element: " + problem;
}
WrongXmlException::WrongXmlException(){
	msg = "Xml file is not valid!";
}
WrongDeletionException::WrongDeletionException(){
	msg = "Root element cannot be deleted";
}
