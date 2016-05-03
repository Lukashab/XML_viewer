
#ifndef CPARENT_H
#define CPARENT_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <ncurses.h>
#include "CScreen.h"
#include <map>

using namespace std;
/**
 * @brief Class of root element
 * @details This class represents root element.Other element classes are derivated from this class
 */
class CParent {
public:

	/**
	 * @brief Constructor of CParent class
	 * @details Creates element and defines a name and attributes of its instance
	 * 
	 * @param name element name
	 * @param attributes element attributes
	 */
	CParent(const string& name,const map<string,string> attributes);

	/**
 	* @brief CParent destructor
 	*/
 	virtual ~CParent();
 	/**
 	 * @brief Method to add Content to element
 	 * @details This method adds one char to element content
 	 * 
 	 * @param content char to be added to element content
 	 */
	void addContent(const char content);
	/**
	 * @brief Overloaded addContent function
	 * @details Overloaded function, that adds string to element content
	 * 
	 * @param content string to be added to element content
	 */
	void addContent(const string& content);
	/**
	 * @brief Name testing method
	 * @details Tests if the element has same name as input string
	 * 
	 * @param name string to be compared with element name
	 * @return Result of comparison
	 */
	bool sameName(const string& name) const;
	/**
	 * @brief Child insert 
	 * @details Adds subelement (child) to an element
	 * 
	 * @param sub New subelement
	 */
	void addSub(CParent* sub);
	/**
	 * @brief Name getter
	 * @return Element name
	 */
	string& getName();
	/**
	 * @brief Visibility switcher
	 * @details Change visibility of the element. This method is used to hide or unhide element nodes
	 */
	void changeVisibility();
	/**
	 * @brief Update of element
	 * @details Method to update parameters of the element
	 * 
	 * @param name Element name
	 * @param attributes Element attributes
	 * @param content Element content
	 */
	void update(const string& name,map<string,string> attributes,const string& content);
	/**
	 * @brief Parent getter
	 * @return Parent element
	 */
	virtual CParent * getParent()const;
	/**
	 * @brief Parent setter
	 * @param parent Parent element of an element
	 */
	virtual void addParent(CParent* parent);
	/**
	 * @brief Prints element to the ncurses window
	 * @details This method prints element in specific format to ncurses window with given indent
	 * 
	 * @param p Ncurses window
	 * @param indent Indent  of an element
	 */
	virtual void print(WINDOW *p,int indent) const;
	/**
	 * @brief Node deletion
	 * @details Delete element with all its subelements
	 */
	void deleteNode();
	/**
	 * @brief Creating output for the ofstream 
	 * @return Formated string, containing element with attributes and possible content
	 */
	virtual string printOutElement()const; 
	/**
	 * @brief Fills ofstream with whole xml file
	 * 
	 * @param os Output stream
	 */
	virtual void printOut(ostream& os) const;
	/**
	 * @brief Prints all subelements
	 * @details This method will print all subelements of an element. In case of this class, it will print whole xml document
	 * 
	 * @param p Ncurses window
	 * @param indent indent of an element
	 * @param elements map of elements, which stores every visible element with its row number (To interact with the user)
	 */
	virtual void printNode(WINDOW *p,int indent,map<int,CParent*>& elements);
	/**
	 * @brief Prints filtered elements
	 * @details Prints only that nodes with given name and attributes
	 * 
	 * @param p Ncurses window
	 * @param element name of the searched element
	 * @param attributes attributes of the searched element
	 * @param elements map of elements, which stores every visible element with its row number (To interact with the user)
	 * @param indent indent of an element
	 */
	virtual void printFiltered(WINDOW *p,string element,vector<pair<string,string> > attributes,map<int,CParent*>& elements,int indent);
protected:
	/**
	 * @brief Prints all attributes of element to given ncurses window
	 * @details This method is used as part of the print method
	 * 
	 * @param p Ncurses window
	 * @param curY Current y position in given window
	 * @param curX Current x position in given window
	 * @param indent Indent of an element
	 */
	void printAttr(WINDOW *p, int curY,int curX,int indent)const;
		/**
	 * @brief Prints content to ncurses window
	 * @details This method is used as part of the print method
	 * 
	 * @param p Ncurses window
	 * @param indent indent of an element
	 */
	void printContent(WINDOW *p,int indent)const;
	/**
	 * @brief Prints closing tag of an element to ncurses window 
	 * @details This method is used as part of the print method
	 * 
	 * @param p Ncurses window
	 * @param indent Indent of an element
	 */
	void printEnd(WINDOW *p,int indent) const;
	/**
	 * @brief Creating output for ofstream
	 * @details This method is used as part of printOutElement method
	 * @return formated string, containing closing tag of an element
	 */
	string printOutEnd()const;
	/**
	 * @brief Creating output for the ofstream
	 * @details This method is used as part of printOutElemen method
	 * @return formated string, containing all element attributes
	 */
	string printOutAttr()const ;
	string m_name; ///< name of an element
	map<string,string> m_attribute; ///< map of all element attributes
	string m_content; ///< element content
	vector<CParent*> m_childs; ///<vector of all subelement
	bool hidden; ///< parameter representing visibility of an element

 };


#endif //CPARENT_H