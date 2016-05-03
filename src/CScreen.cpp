#include "CScreen.h"


void CScreen::startColors(){
	//test for color ability of the terminal 
	if(has_colors()){
		start_color();
		init_pair(1,COLOR_GREEN,COLOR_BLACK);
		init_pair(2,COLOR_CYAN,COLOR_BLACK);
		init_pair(3,COLOR_YELLOW,COLOR_BLACK);
		init_pair(4,COLOR_BLACK,COLOR_WHITE);
		init_pair(5,COLOR_BLACK,COLOR_YELLOW);
		init_pair(6,COLOR_BLACK,COLOR_CYAN);
	}
}
void CScreen::initScreen(){
	initscr();
	noecho();
	keypad(stdscr,TRUE);
	curs_set(0);
}
void CScreen::homeScreen(){

	attron(COLOR_PAIR(6));
	mvaddstr(10,2," XML Viewer ");
	attroff(COLOR_PAIR(6));
	mvaddstr(12,2,"For help, look at the help labels located on the bottom of the screen. ");
	mvaddstr(13,2,"After the xml file is loaded, you can scroll up and down by using arrow keys. ");
	attroff(COLOR_PAIR(4));
	mvaddstr(15,2,"Author: Lukas Haberzettl");
}
WINDOW * CScreen::win(int height,int width,int posY,int posX,const string& header,const string& description){
	WINDOW * win;
	win = newwin(height,width,posY,posX);
	wbkgd(win,COLOR_PAIR(4));
	wattrset(win,A_BOLD);
	mvwaddstr(win,1,1,header.c_str());
	wattroff(win,A_BOLD);
	wattrset(win,A_DIM);
	waddstr(win,description.c_str());
	wattroff(win,A_DIM);
	wrefresh(win);
	return win;
}
void CScreen::printToWin(WINDOW *p,const string& text,int indent){
	int curY,curX;
	for(unsigned int i=0;i<text.length();i++){
		getyx(p,curY,curX);
		if(curX<indent) wmove(p,curY,indent+1);
		waddch(p,text[i]);
	}
}
void CScreen::EWindow(Exception e){
	WINDOW * EWindow;
	int y,x;
	getmaxyx(stdscr,y,x);
	string header= "ERROR\n ";
	string description = e.getMsg();
	
	EWindow = win(5,x,y-7,0,header,description);
	wbkgd(EWindow,COLOR_PAIR(5));
	touchwin(EWindow);
	curs_set(0);
	wrefresh(EWindow);
	getch();
	delwin(EWindow);

}

void CScreen::loadInput(WINDOW *win,string& text,int height,int width,int upBorder,int padding){
	int curY,curX;
	int ch;
	wmove(win,upBorder,padding);
	curs_set(1);
	if(!text.empty()){
		for(unsigned int i=0;i<text.length();i++){
			getyx(win,curY,curX);
			if(curY==height-1 && curX==width-padding) break;
			if(curX==width-padding) wmove(win,curY+1,padding);
			else if(text[i]=='\n') {
				wmove(win,curY+1,padding);
				continue;
			}
			waddch(win,text[i]);
		}
	}
	wrefresh(win);
	while((ch=getch())!='\n'){
		getyx(win,curY,curX);		
		if(ch==KEY_BACKSPACE){
			if(curY==upBorder && curX==padding) continue;
			else if(curY>upBorder && curX==padding) {
				wmove(win,curY-1,width-padding);
				continue;
			}
			wmove(win,curY,curX-padding);
			wdelch(win);
			text.pop_back();
			wrefresh(win);
			continue;
		}
		else if(!isprint(ch)) continue;
		if(curX==width-padding) {
			if(curY==(height-1)){
				continue;
			}
			wmove(win,curY+1,padding);
		}				 
		text += ch;
		waddch(win,ch);
		wrefresh(win);
	}
}
void CScreen::setLabels(const string * labels,int size){
	int y,x;
	getmaxyx(stdscr,y,x);
	
	for(int i=0;i<x;i++){
		mvaddch(y-2,i,'-');
	}
	mvaddch(y-1,0,' ');
	for(int i=0;i<size;i++){
		attron(COLOR_PAIR(4));
		addstr(labels[i].c_str());
		attroff(COLOR_PAIR(4));
		addch(' ');
	}
	refresh();
}
void CScreen::drawMenu(WINDOW * menu,int width,int selected,string * items,int size){
	wclear(menu);
	for(int i=0,j=0;i<size;i++){
		j +=2;
		if(i==selected){
			wattrset(menu,A_REVERSE);
		}
		mvwaddstr(menu,j,(width-items[i].length())/2,items[i].c_str());
		wattroff(menu,A_REVERSE);
	}
}