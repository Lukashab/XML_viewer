

 #include "CXml.h"

#define WIDE 5000

int parseAttribute(string& attribute, string& attribute_name, string& attribute_content){
	unsigned i=0;
	while(attribute[i]!= '='){
 			if(i==attribute.length()) {
 				attribute_name.clear();
 				return false;
 			}
 			attribute_name += attribute[i];
 			i++;
 		}
 		if(attribute[++i]!='\"') return false;
 		while(attribute[++i]!= '\"'){
 			if(i==attribute.length()) {
 				attribute_name.clear();
 				attribute_content.clear();
 				return false;
 			}
 			attribute_content += attribute[i];
 		}
 	return i;
}
  
int parseElementHeader(string& element, string& name,map<string,string>& attributes)
{
  	unsigned int i=0;
  	bool hasAttribute = 0;
  	string tmp;
  	name.clear();
  	string attribute_name;
  	string attribute_content;
 	//checking syntax---------------------
 	char c = element[0];
 	if(isdigit(c) || ispunct(c) || element.empty()) return 0;

 	if(element.length()>=3){
 		for(i=0;i<3;i++){
 			tmp +=toupper(element[i]);
 		}
 		if(tmp == "XML") return 0;
 		i=0;
 	}
 	//parsing-----------------------------
 	while(i!=element.length()){
 		if(element[i]==' '){
 			hasAttribute = 1;
 			break;
 		}
 		if(element[i]!='/') name +=element[i];
 		i++;
 	}
 	//parsing possible attribute
 	if(hasAttribute==1){
 		tmp.clear();
 		int tmp_length;
 		while(1){
 			//parsing one attribute
 			tmp = element.substr(++i);
 			tmp_length = parseAttribute(tmp,attribute_name,attribute_content);
			//saving attribute to map
			attributes.insert(make_pair(attribute_name,attribute_content));
			attribute_name.clear();
			attribute_content.clear();
			if(tmp_length==0) return 0;
			else i += tmp_length;
			if(i==element.length()-1) return 2;
			else if(element[i+1]=='/') return 1;
			else if(element[++i]==' ') continue;
			else return 0;
 		}
 	}
 	if(element[element.length()-1]=='/') return 1;
 	else return 2;
 }

int parseElement(string& element,string& name,map<string,string>&attributes,string& m_content){
	//parse header
	string header;
	string temp_name;
	unsigned int i,result=0;
	//separating header and controling validy of an element
	if(element[0]!='<') return 0;
	for(i=1;i<element.length();i++){
		if(element[i]=='>') break;
		header += element[i];
		if(i==element.length()-1) return 0;
	}
	result = parseElementHeader(header,name,attributes);
	if(result == 1) return result;
	i++;
	for(;i<element.length();i++){
		m_content += element[i];
		if(element[i]=='<') return 0;
	}
	return result;

}

 CXml::CXml(){
 	existParent = 0;
 }

 CXml::~CXml(){
 	if(existParent){
 		delete m_parent;
 	}
 }

bool CXml::parse(const char * inputFile){
	//create filestream
	ifstream xmlFile (inputFile, ifstream::in);
	if(xmlFile.fail()){
		string WrongPath(inputFile);
		throw WrongFilePathException(WrongPath);
	}
	char c;
	int p_result = 0;
	// 1 means loading opening element tag, 2 - closing tag, 3 - element content
	int elem_flag = 1;
	string tmp_line;
	string name;
	map<string,string> tmp_attributes;
	//if first character of XML file isn't "<" it's not valid XML document
	xmlFile.get(c);
	if(c!='<') throw WrongXmlException();
	//parsing xml file--------------------------------------------------------------
	//parent element
	getline(xmlFile,tmp_line,'>');
	if(!parseElementHeader(tmp_line,name,tmp_attributes)) throw WrongXmlException();
	existParent = 1;
	CParent * parentElement = new CParent(name,tmp_attributes);
	tmp_attributes.clear();
	m_parent = parentElement;
	tmp_line.clear();
	//pointer to current element
	CParent * current_elem = m_parent;
	while(xmlFile.get(c)){
		if(c=='<'){
			xmlFile.get(c);
			if(c=='/'){
				elem_flag = 2;
				continue;
			}
			else {
				xmlFile.unget();
				getline(xmlFile,tmp_line,'>');
				//parsing one element
				if((p_result = parseElementHeader(tmp_line,name,tmp_attributes)) == 0) throw WrongXmlException();
				CParent * subElement;
				if(p_result==2)  subElement = new CSub(name,tmp_attributes);
				else {
					subElement = new CSubSC(name,tmp_attributes);
					SC_elements.insert(subElement);
				}
				current_elem->addSub(subElement);
				subElement->addParent(current_elem);
				tmp_attributes.clear();				
				if(p_result == 2){
					current_elem = subElement;
				}
				tmp_line.clear();
				continue;
			}
		}
		else if(c=='>'){
			if(current_elem->sameName(tmp_line)){
				current_elem = current_elem->getParent();
				elem_flag = 1;
				tmp_line.clear();
				continue;
			}
			else throw WrongXmlException();
		}
		//saving text content
		if(elem_flag!=2){
			if(!isspace(c) || elem_flag==3){
				if(isspace(c) && c!=' ') continue;
				elem_flag = 3;
				current_elem->addContent(c);
			}
		}
		//remembering name of closing tag
		else if(elem_flag==2){
			tmp_line += c;
		}
	}

	return true;
}

void CXml::printXml(WINDOW *p){
	wclear(p);
	all_elements.clear();
	int indent = 2;
	m_parent->printNode(p,indent,all_elements);
}

bool CXml::parseFilter(const string& text,string& element, vector<pair<string,string> >& attributes){
	if(text.empty()) return 0;
	unsigned int i;
	for(i=0;i<text.length();i++){
		if(text[i]!='>'){
			element += text[i];
		}
		else break;
	}
	i++;
	if(i>=text.length()) return true;
	string attribute;
	string value;
	//0=attribute,1=value
	int switcher=0;
	for(;i<text.length();i++){
		if(text[i]=='"'){
			if(!switcher) return false;
			attributes.push_back(make_pair(attribute,value));
			attribute.clear();
			value.clear();
			switcher = 0;
		}
		else if(text[i]=='=') switcher = 1;
		else if(!switcher) attribute += text[i];
		else value += text[i];
	}
	if(!switcher) return false;
	attributes.push_back(make_pair(attribute,value));

	return true;
}

bool CXml::filter(WINDOW *p,CXml::TFilter& filter){
	WINDOW * filterBox;
	int x,y;
	getmaxyx(stdscr,y,x);
	string header = "FILTER BOX";
	string description = " - filter pattern: element>attribute=value\"attribute=value... ( press ENTER to filter (to print default structure of XML file leave the box empty))";
	filterBox = CScreen::win(5,x,y-7,0,header,description);
	//creating filtering box and setting color mode
	string text;
	CScreen::loadInput(filterBox,text,5,x,3,1);
	curs_set(0);
	vector<pair<string,string> > attributes;
	string element;
	if(text.empty()){
		printXml(p);
		return false;
	}
	else if(!parseFilter(text,element,attributes)){
		throw WrongFilterException();
		return false;
	}
	else{
		//filtering-----
		wclear(p);
		all_elements.clear();
		m_parent->printFiltered(p,element,attributes,all_elements,0);
		filter.t_attributes = attributes;
		filter.t_element = element;
	}
	delwin(filterBox);
	return true;
}
bool CXml::Insert(CParent * parent) {
	WINDOW * insertBox;
	int x,y;
	getmaxyx(stdscr,y,x);
	string header = "INSERT BOX";
	string description = " - type an element in normal syntax (for insert press ENTER)";
	insertBox = CScreen::win(20,x,y-22,0,header,description);
	string text;
	CScreen::loadInput(insertBox,text,20,x,3,1);
	curs_set(0);
	if(text.empty()){
		return 0;
	}
	else {
		//parsing input text	
		string name;
		map<string,string> attributes;
		string content;
		int result;
		result = parseElement(text,name,attributes,content);
		CParent * inserted;
		if(result==1){
				inserted = new CSubSC(name,attributes);
				SC_elements.insert(inserted);
			}
		else if(result==2){
				inserted = new CSub(name,attributes);
				if(!content.empty()) inserted->addContent(content);
			}
		else {
			delwin(insertBox);
			return 0;
		}
		parent->addSub(inserted);
		inserted->addParent(parent);
		delwin(insertBox);
		return true;
	}
	
}
void CXml::Edit(CParent * element) {
	WINDOW * editBox;
	int x,y;
	getmaxyx(stdscr,y,x);
	string header = "EDIT BOX";
	string description = " - edit element by using normal syntax without closing tag (for edit press ENTER)";
	editBox = CScreen::win(20,x,y-22,0,header,description);
	//print current content of an element
	string text = element->printOutElement();
	CScreen::loadInput(editBox,text,20,x,3,1);
	curs_set(0);
	
	if(text.empty()){
		string problem = "edit box is empty";
		throw WrongEditException(problem);
	}
	else {
		//parsing input text
		string name;
		map<string,string> attributes;
		string content;
		int result;
		result = parseElement(text,name,attributes,content);
		if(result){
				element->update(name,attributes,content);
			}
		else {
			string problem = "bad syntax of an element";
			throw WrongEditException(problem);
		}
	}
	delwin(editBox);
	
}
void CXml::nodeMenu(WINDOW *p,CParent* element){
	WINDOW * menu;
	int x,y;
	int ch;
	string items[3] = {" Edit "," Insert "," Delete "};
	getmaxyx(stdscr,y,x);
	//number of actual selection and menu items
	int selection = 0;
	string header ="";
	string description = "";
	menu = CScreen::win(10,30,y-12,0,header,description);
	curs_set(0);
	//print menu content 
	CScreen::drawMenu(menu,30,selection,items,3);
	wrefresh(menu);
	while((ch=getch())!='\n'){
		if(ch==KEY_UP){
			if(selection==0) continue;
			else CScreen::drawMenu(menu,30,--selection,items,3);
		}
		else if(ch==KEY_DOWN){
			if(selection==2) continue;
			else CScreen::drawMenu(menu,30,++selection,items,3);
		}
		wrefresh(menu);
	}
	//check if element is self-closing or not
	set<CParent*>::iterator it = SC_elements.find(element);
	switch(selection){
		case 2:
			if(element == m_parent){
				throw WrongDeletionException();
				break;
			}			
			if(it != SC_elements.end()) SC_elements.erase(it);
			element->deleteNode();
			break;
		case 1:
			if(it != SC_elements.end()) {
				string problem = "Self closing element cannot have any childs";
				throw WrongInsertionException(problem);
			}
			else if(!Insert(element)) {
				string problem = "bad syntax";
				throw WrongInsertionException(problem);	
			}
			break;
		case 0:
			Edit(element);
			break;
	}
	delwin(menu);
}
string CXml::open(){
	WINDOW *open;
	int x,y;
	getmaxyx(stdscr,y,x);
	string header = "OPEN";
	string description = " - type path to xml file and press ENTER";
	open = CScreen::win(5,x,y-7,0,header,description);
	wrefresh(open);
	string text = "./examples/example4.xml";
	CScreen::loadInput(open,text,5,x,3,1);
	curs_set(0);
	m_path = text;
	wclear(open);
	delwin(open);
	refresh();
	return text;
}
void CXml::save(){
	WINDOW *open;
	int x,y;
	getmaxyx(stdscr,y,x);
	string header = "SAVE";
	string description = " - type path for modified xml file";
	open = CScreen::win(5,x,y-7,0,header,description);
	wrefresh(open);
	string text = m_path;
	CScreen::loadInput(open,text,5,x,3,1);
	curs_set(0);
	ofstream   XmlOut;
	XmlOut.open(text.c_str());
	m_parent->printOut(XmlOut);
	if(XmlOut.fail()){
		throw WrongFilePathException(text);
		return;
	}
	XmlOut.close();
}

void CXml::program(){

	MEVENT mouse;
	//initialize pad
	WINDOW *p;
	int x,y;
	getmaxyx(stdscr,y,x);
	string labels[5] = {" b - back "," s - save "," f - filter "," mouse press - delete/insert/edit ", " mouse click - hide/unhide "};
	p = newpad(WIDE,x);
	int ch;
	printXml(p);
	//help labels
	CScreen::setLabels(labels,5);
	//enable keypad and mouse
	keypad(p,TRUE);
	mousemask(BUTTON1_CLICKED | BUTTON1_PRESSED,NULL);
	//running the main cycle------------------
	int first_row=0;
	bool filtered=false;
	CXml::TFilter cur_filter;
	prefresh(p,first_row,0,0,0,y-3,x-1);
	do{
		ch = wgetch(p);
		try{
			switch(ch){
				case KEY_DOWN:
					if(first_row+y-2==WIDE-1) break;
					else first_row++;
					break;
				case KEY_UP:
					if(first_row==0) break;
					else  first_row--;
					break;
				case 'f':
					filtered = filter(p,cur_filter);
					first_row=0;
					break;
				case 's':
					save();
					break;
				case KEY_RESIZE:
					getmaxyx(stdscr,y,x);
					delwin(p);
					p = newpad(WIDE,x);
					printXml(p);
					keypad(p,TRUE);
					CScreen::setLabels(labels,5);
					first_row = 0;
					prefresh(p,first_row,0,0,0,y-3,x-1);
					break;
				case KEY_MOUSE:
					getmouse(&mouse);
					//checking if element header is clicked
					map<int,CParent*>::iterator it = all_elements.find(mouse.y+first_row);
					if(it != all_elements.end()){
						//program react only if left mouse button is clicked
						if(mouse.bstate == BUTTON1_CLICKED) 
							it->second->changeVisibility();
						else if(mouse.bstate == BUTTON1_PRESSED)
								nodeMenu(p,it->second);
							//refresh 
							if(!filtered) printXml(p);
							else{ 
								wclear(p);
								all_elements.clear();
								m_parent->printFiltered(p,cur_filter.t_element,cur_filter.t_attributes,all_elements,0);
							}
					}
					break;
			}
			prefresh(p,first_row,0,0,0,y-3,x-1);
		}
		catch(Exception e){
			if(!filtered) printXml(p);
			else {
				wclear(p);
				all_elements.clear();
				m_parent->printFiltered(p,cur_filter.t_element,cur_filter.t_attributes,all_elements,0);
			}
			prefresh(p,first_row,0,0,0,y-3,x-1);
			CScreen::EWindow(e);
			prefresh(p,first_row,0,0,0,y-3,x-1);
			continue;
		}
	}while(ch!='b');
	delwin(p);

}