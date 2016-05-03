/**
 * @mainpage XML Viewer
 * @author Lukas Haberzettl
 * 
 * XML Viewer is designated for reading and editing input XML files\n\n	
 * Supported xml format rules:\n
 * 1) There cannot be any characters before root element tag (even whitespaces) \n
 * 2) Comments are not supported \n
 * 3) Elements can contains sub elements with same name \n
 * 4) Self-closing elements are supported \n
 * 5) Elements can contains sub elements and content at the same time \n
 * 6) Name of any element cannot start with "xml" \n
 * 7) Xml viewer ignore all white spaces besides spaces 
 * 
 * Xml Viewer will not work properly if xml input files will not fulfill these rules \n
 */
#include "CXml.h"

 using namespace std;


int main(){
	char ch;
	//start NCURSES
	CScreen::initScreen();
	//start colors
	CScreen::startColors();
	
	string path;
	string labels[2] = {" q - quit "," o - open "};
	do{
		clear();
		CXml xmlFile;
		CScreen::homeScreen();
		CScreen::setLabels(labels,2);
		ch = getch();
		switch(ch){
			case 'o':
				path = xmlFile.open();
				const char * pathChar = path.c_str();
				try{
					xmlFile.parse(pathChar);
				}
				catch(Exception e){
					CScreen::EWindow(e);
					continue;
				}
				xmlFile.program();
					
				break;
		}
	}while(ch!='q');

	endwin();
	return 0;
 }