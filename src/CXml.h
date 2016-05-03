
#ifndef CXML_H
#define CXML_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <map>
#include <set>
#include <ncurses.h>
#include "Exception.h"
#include "CParent.h"
#include "CSubSC.h"
#include "CSub.h"
#include "CScreen.h"


using namespace std;
/**
* @brief class representing structure of input XML file
* @details CXml class represents structure of input XML file. It contains methods to parse this file and divide it to individual elements.
*/
class CXml {

 private:
 	CParent * m_parent; ///<pointer to root element 
 	map<int,CParent*> all_elements; ///< map with all (visible) elements with its row numbers used for interaction with the user
 	set<CParent*> SC_elements; ///< map of all (visible) self-closing elements for better control of manipulation with elements
 	bool existParent; ///< bool value to indicate existence of root element
 	string m_path; ///< remembered current part of loaded xml file
 	/**
 	 * @brief Filter structure
 	 * @details Structure used to keep filtering informations during the program cycle
 	 * 
 	 */
 	struct TFilter{
		string t_element;
		vector<pair<string,string> > t_attributes;
	};
  /**
   * @brief Saves modified xml file
   * @details Displays save window and saves modified xml file to given path
   */
  void save();
  /**
  * @brief Printing method
  * @details This function prints full formated XML document to the given ncurses window
 
  * @param p ncurses window 
  */
  void printXml(WINDOW *p);
  /**
   * @brief Filtering method
   * @details Display filter window and operate with filter input
   * 
   * @param p ncurses window with printed xml file
   * @param filter structure to be filled with filtering rules (used to keep filtering)
   * 
   * @return return bool value according to correctness of filter input
   */
  bool filter(WINDOW *p,TFilter& filter);
  /**
   * @brief Parsing filter input
   * @details This method is used as part of filter method to parse filter input
   * 
   * @param text filter input
   * @param element string to be filled with searched element name
   * @param attributes vector to be filled with searched element attributes 
   * @return return bool value according to success of parsing
   */
  bool parseFilter(const string& text,string& element, vector<pair<string,string> >& attributes);
  /**
   * @brief Displays node menu
   * @details Method displays menu with 3 options (edit, inset, delete), and operate with its browsing
   * 
   * @param p ncurses window with printed xml file
   * @param element element for which is menu displayed
   */
  void nodeMenu(WINDOW *p,CParent* element);
  /**
   * @brief Edits elemnt
   * @details Display edit window and edit choosen element
   * 
   * @param element element to be edited
   */
  void Edit(CParent* element);
  /**
   * @brief Insert element
   * @details Displays insert window and insert the element as subelement of choosen element
   * 
   * @param parent parent of inserted element
   * @return returns bool value according to result of insertion
   */
  bool Insert(CParent * parent);
 public:
 	/**
 	* @brief Constructor of Xml class
 	*/
 	CXml();
 	/**
	 * @brief Destructor of XMl class
	 * @details If parent element of XML class is not empty, it will be freed
	 */
 	~CXml();
 	/**
 	 * @brief Gets path to xml file
 	 * @details Displays open window and proccess input string containing path to xml file
 	 * @return path to xml file
 	 */
 	string open();
 	/**
    * @brief Method to parse input XML file
    * @details This method will divide input XML file to individual elements according to standart XML syntax. Valid XML file should have
    * only one parent element that contains all sub-elements and no comments
    * @param inputFile Path to XML file to parse
    * @return Method returns true if input XML file is valid and successfully parsed, false if input XML input file is not valid and so cannot be parsed 
    */
 	bool parse(const char* inputFile);
 	/**
 	* @brief Main program cycle
 	* @details this method represents cycle of the program and interact with the user (scrolling, editing, filetring etc.)
 	*/
 	void program();
 };
/**
 * @brief function to parse element tag and its possible content
 * 
 * @param element input element string
 * @param name string to be filled with element name
 * @param attributes map to be filled with element attributes
 * @param m_content string to be filled with element content
 * @return return 0 if parsing is unsuccesfull, 1 if element is self-closing, 2 if element is paired
 */
int parseElement(string& element,string& name,map<string,string> &attributes,string& m_content);
/**
   * @brief function to parse element tag
   * @details This function is parsing element tag to name of an element and its attributes 
   * 
   * @param element whole element tag
   * @param name string to be filled with element name
   * @param attributes map to be filled with element attributes
   * @return return 0 if parsing is unsuccesfull, 1 if element is unpaired, 2 if element is paired
   */
int parseElementHeader(string& element, string& name,map<string,string>& attributes);
/**
 * @brief function to parse one attribute of an element
 * 
 * @param attribute whole attribute string
 * @param attribute_name string to be filled with attribute name
 * @param attribute_content string to be filled with attribute content
 * @return return length of attribute, if parsing is unsuccesfull, it returns 0
 */
int parseAttribute(string& attribute, string& attribute_name, string& attribute_content);

#endif //CXML_H