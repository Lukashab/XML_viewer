
#include "CSub.h"

CSub::CSub(const string& name,const map<string,string> attributes): CParent(name,attributes) {}

CParent * CSub::getParent()const{
 	return m_parent;
 }
/**
 * @brief add pointer to parent element
 */
 void CSub::addParent(CParent *parent){
 	m_parent = parent;
 }