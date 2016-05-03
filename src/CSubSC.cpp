
 #include "CSubSC.h"

 CSubSC::CSubSC(const string& name, const map<string,string> attributes) : CParent(name,attributes) {}


 CParent * CSubSC::getParent()const{
 	return m_parent;
 }

void CSubSC::addParent(CParent *parent){
 	m_parent = parent;
 }

void CSubSC::printNode(WINDOW *p,int indent,map<int,CParent*>& elements){
	int curX,curY;
	getyx(p,curY,curX);
	wmove(p,curY,curX+indent);
	//save to element maps
	map<int,CParent*>::iterator it= elements.find(curY);
	if(it == elements.end()){
		elements.insert(make_pair(curY,this));
	}

	wattrset(p,COLOR_PAIR(1));
	waddch(p,'<');
	waddstr(p,m_name.c_str());
	if(m_attribute.empty()){
		waddstr(p,"/>\n");
		wattroff(p,COLOR_PAIR(1));
	}
	else{
		printAttr(p,curY,curX,indent);
		wattrset(p,COLOR_PAIR(1));
		waddstr(p,"/>\n");
		wattroff(p,COLOR_PAIR(1));
	}
 }

string CSubSC::printOutElement()const {
	string element;
	element += "<";
	element += m_name;
	element += printOutAttr();
	element += "/>";
	return element;
 }
 
void CSubSC::printOut(ostream& os) const{
 	os << printOutElement();
 }