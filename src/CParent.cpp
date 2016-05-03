
#include "CParent.h"


CParent::CParent(const string& name,const map<string,string> attributes): m_name(name), m_attribute(attributes),hidden(0){}

CParent::~CParent(){
	for(unsigned int i=0;i<m_childs.size();i++){
		delete m_childs[i];
	}
}

void CParent::addContent(const char content){
	m_content += content;
}
void CParent::addContent(const string& content){
	m_content += content;
}
string& CParent::getName(){
	return m_name;
}
bool CParent::sameName(const string& name) const{
	return (name == m_name);
}

CParent * CParent::getParent()const{
	return NULL;
}

void CParent::addSub(CParent *sub){
	m_childs.push_back(sub);
}

void CParent::addParent(CParent* parent){
	return;
}
void CParent::changeVisibility(){
	hidden = !hidden;
}
void CParent::update(const string& name,map<string,string> attributes,const string& content){
	m_name = name;
	m_content = content;
	m_attribute = attributes;
}
void CParent::printAttr(WINDOW *p, int curY,int curX,int indent)const{
	unsigned int x,y;
	getmaxyx(p,y,x);
	//number of additional chars in attribute
	y = 4;
	for(map<string,string>::const_iterator it = m_attribute.begin();it!=m_attribute.end();++it){
			wattrset(p,COLOR_PAIR(2));
			getyx(p,curY,curX);
			if(x<(curX+it->first.length()+y+it->second.length())) wmove(p,curY+1,indent);
			else if(curX<indent)wmove(p,curY,indent);
			waddch(p,' ');
			CScreen::printToWin(p,it->first,indent);
			wattroff(p,COLOR_PAIR(2));
			waddch(p,'=');
			wattrset(p,COLOR_PAIR(3));
	 		waddch(p,'"');
	 		CScreen::printToWin(p,it->second,indent);
	 		waddch(p,'"');
	 		wattroff(p,COLOR_PAIR(3));	
		}
}
void CParent::printContent(WINDOW *p,int indent)const {
	int x,y;
	waddch(p,'\n');
	for(unsigned int i=0;i<m_content.length();i++){
		getyx(p,y,x);
		if(m_content[i]=='\n') {
			wmove(p,y+1,indent+3);
			continue;
		}
		else if(x<(indent+3)) wmove(p,y,indent+3);
		waddch(p,m_content[i]);
	}
}

void CParent::print(WINDOW *p,int indent) const{
	int curX,curY;
	getyx(p,curY,curX);
	wmove(p,curY,curX+indent-1);
	wattroff(p,COLOR_PAIR(1));
	if(!hidden) waddstr(p,"- ");
	else waddstr(p,"+ ");

	wattrset(p,COLOR_PAIR(1));
	waddch(p,'<');
	CScreen::printToWin(p,m_name,indent);

	if(m_attribute.empty()){
		waddch(p,'>');
		wattroff(p,COLOR_PAIR(1));
	}
	else{
		printAttr(p,curY,curX,indent);
		wattrset(p,COLOR_PAIR(1));
		waddch(p,'>');
		wattroff(p,COLOR_PAIR(1));
	}
	if(!m_content.empty() && !hidden){
		printContent(p,indent);
	}

	waddch(p,'\n');
}

void CParent::printEnd(WINDOW *p,int indent) const{
	wattrset(p,COLOR_PAIR(1));
	int x,y;
	getyx(p,y,x);
	wmove(p,y,x+indent);
	waddstr(p," </");
	CScreen::printToWin(p,m_name,indent);

	waddstr(p,">\n");
}
void CParent::printNode(WINDOW *p,int indent,map<int,CParent*>& elements) {

	int curX,curY;
	getyx(p,curY,curX);
	//save element to map
	map<int,CParent*>::iterator it= elements.find(curY);
	if(it == elements.end()){
		elements.insert(make_pair(curY,this));
	}
	print(p,indent);
	if(!hidden){	
		int temp_indent = indent + 2;
		for(unsigned int i=0;i<m_childs.size();i++){
			m_childs[i]->printNode(p,temp_indent,elements);
		}
	}

	printEnd(p,indent);
}
void CParent::printFiltered(WINDOW *p,string element,vector<pair<string,string> > attributes,map<int,CParent*>& elements,int indent){


	int curX, curY;
	int valid=1;
	getyx(p,curY,curX);
	//save element to map
	if(m_name == element){
		for(unsigned int i=0;i<attributes.size();i++){
			map<string,string>::iterator it2 = m_attribute.find(attributes[i].first);
			if(it2==m_attribute.end() || it2->second != attributes[i].second) {
				valid=0;
				break;
			}
		}
	}
	else valid = 0;
	if(valid){
		//hidden = 0;
		map<int,CParent*>::iterator it= elements.find(curY);
		if(it == elements.end()){
			elements.insert(make_pair(curY,this));
		}
		int temp_indent = indent + 2;
		printNode(p,temp_indent,elements);
	}
	else{
		for(unsigned int i=0;i<m_childs.size();i++){
				m_childs[i]->printFiltered(p,element,attributes,elements,indent);
		}
	}
}
string CParent::printOutAttr()const{
	string attributes;
	for(map<string,string>::const_iterator it = m_attribute.begin();it!=m_attribute.end();++it){
		attributes += " ";
		attributes += it->first;
		attributes += "=\"";
		attributes += it->second;
		attributes += "\"";
	}
	return attributes;
}
string CParent::printOutElement()const{
	string element;
	element += "<";
	element += m_name;
	element += printOutAttr();
	element += ">";
	if(!m_content.empty()){
		element += m_content;
	}
	return element;
}
string CParent::printOutEnd()const {
	string end;
	end +="</" + m_name + ">";
	return end;
} 
void CParent::printOut(ostream& os)const{
	os << printOutElement();
	for(unsigned int i=0;i<m_childs.size();i++){
			m_childs[i]->printOut(os);
		}
	
	os << printOutEnd();
}
void CParent::deleteNode(){
	for(unsigned int i=0;i<m_childs.size();i++){
		m_childs[i]->deleteNode();
	}
	CParent* parent = getParent();
	if(parent!=NULL){
		for(vector<CParent*>::iterator it=parent->m_childs.begin();it!=parent->m_childs.end();it++){
				if(*it==this){
					parent->m_childs.erase(it);
					break;
				}
		}
	}
	delete this;
}