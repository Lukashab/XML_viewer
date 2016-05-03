
#ifndef CSCREEN_H
#define CSCREEN_H

#include <iostream>
#include <ncurses.h>
#include <string>
#include "Exception.h"

using namespace std;
/**
 * @brief class to operate with screen
 */
class CScreen {
public:
	/**
	 * @brief Sets help labels on the bottom of the main screen
	 * 
	 * @param labels array of strings representing labels
	 * @param size size of the given array
	 */
	static void setLabels(const string * labels,int size);
	/**
	 * @brief Creates new window with given parameters
	 * 
	 * @param height height of the window
	 * @param width width of the window
	 * @param posY y - window position due to main screen
	 * @param posX x - window position due to main screen
	 * @param header header of the window
	 * @param description description of the window
	 * @return returns created window
	 */
	static WINDOW * win(int height,int width,int posY,int posX,const string& header,const string& description);
	/**
	 * @brief Prints string to given window 
	 * 
	 * @param p Ncurses window
	 * @param text String to be printed
	 * @param indent indent of the string
	 */
	static void printToWin(WINDOW *p,const string& text,int indent);
	/**
	 * @brief Displays exception window
	 * 
	 * @param e Exception to be printed on window
	 */
	static void EWindow(Exception e);
	/**
	 * @brief Loads input of given window
	 * 
	 * @param win Ncurses window
	 * @param text string, which can be modified by user input
	 * @param height height of the given window
	 * @param width width of the given window
	 * @param upBorder first row of the input
	 * @param padding padding of the given window
	 */
	static void loadInput(WINDOW *win,string& text,int height,int width,int upBorder,int padding);
	/**
	 * @brief Starts color mode
	 * @details Tests terminal for color ability and in case of success initialize color mode
	 */
	static void startColors();
	/**
	 * @brief Initialize screen
	 */
	static void initScreen();
	/**
	 * @brief Draws menu window
	 * @details highlights selected item
	 * 
	 * @param menu Ncurses window
	 * @param width width of the menu
	 * @param selected value of selected item
	 * @param items Items contained in the menu
	 * @param size number of menu items
	 */
	static void drawMenu(WINDOW * menu,int width,int selected,string * items,int size);
	/**
	 * @brief Displays home screen
	 */
	static void homeScreen();

};


#endif //CSCREEN_H