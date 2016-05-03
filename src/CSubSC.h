
#ifndef CSUBSC_H
#define CSUBSC_H
#include "CParent.h"
#include "Exception.h"

/**
 * @brief Class for all sub elements which are self-closing
 */
class CSubSC: public CParent {
public:
	/**
	 * @brief constructor inherited from 
	 * 
	 * @param name name of an element
	 * @param attributes map with all element attributes
	 */
	CSubSC(const string& name, const map<string,string> attributes);
	/**
	 * @brief inherited method to get parent of an element
	 * @return parent element of an element
	 */
	virtual CParent * getParent()const;
	/**
	 * @brief Inherited parent setter
	 * @param  parent Parent element of an element
	 */
	virtual void addParent(CParent* parent);
	/**
	 * @brief Prints element
	 * @details Prints self closing element
	 * 
	 * @param p Ncurses window
	 * @param indent indent of an element
	 * @param elements map of elements, which stores every visible element with its row number (To interact with the user)
	 */
	virtual void printNode(WINDOW *p,int indent,map<int,CParent*>& elements);
	/**
	 * @brief Creating output for the ofstream 
	 * @return Formated string, containing element with all attributes
	 */
	virtual string printOutElement() const;
	/**
	 * @brief Fills ofstream with whole xml file
	 * 
	 * @param os Output stream
	 */
	virtual  void printOut(ostream& os)const;

private:
	CParent * m_parent; ///< pointer to a parent element, which can be of type CParent or CSub
 };


#endif //CSUBSC_H
