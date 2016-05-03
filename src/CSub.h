
#ifndef CSUB_H
#define CSUB_H
#include "CParent.h"

/**
 * @brief class for all paired sub elements contained in XML file under the parent element
 */
class CSub: public CParent {
public:
	/**
	 * @brief CSub class constructor
	 * 
	 * @param name name of an element
	 * @param attributes attributes of an element
	 */
	CSub(const string& name, const map<string,string> attributes);
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
private:
	
	CParent * m_parent; ///< pointer to a parent element, which can be of type CParent or CSub
	
 };

#endif //CSUB_H
