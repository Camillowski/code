#ifndef SALESDATA_H
#define SALESDATA_H


//-----TEXTQUERY---------------------------------
/*
Classes that search for word in file. Then return all line numbers where this word apears.
*/

class TextQuery;

//Hold data returned by query fcn in TextQuery class
class QueryResult{
	public:
	using File=std::shared_ptr<std::vector<std::string>>;
	using SetIter=std::set<int>::iterator;
	//Ctors
	QueryResult(){}//Default Ctor
	File get_file();
	SetIter begin();
	SetIter end();
	
	private:
	std::string srch_word;
	std::shared_ptr<std::set<int>> lineNr;//Lines numbers
	std::shared_ptr<std::vector<std::string>> fileVec; //text lines
	
	friend void print(std::ostream&, QueryResult);
	//friend QueryResult TextQuery::query(string);
	friend class TextQuery;
};

QueryResult::File QueryResult::get_file(){
	return fileVec;
}

QueryResult::SetIter QueryResult::begin(){
	return lineNr->begin();
}
	
QueryResult::SetIter QueryResult::end(){
	return lineNr->end();
}

void print(std::ostream &os, QueryResult res){
	if(res.lineNr==nullptr){
		os<<"No word "<<res.srch_word<<std::endl;
		return;
	}
	os<<"Word "<<res.srch_word<<" occurs in "<<res.lineNr->size()<<" lines:"<<std::endl;
	auto begin=res.lineNr->begin();
	//cout<<*begin;
	while(begin!=res.lineNr->end()){
		os<<"(line #"<<*begin+1<<"): "<<res.fileVec->at(*begin)<<std::endl<<std::endl;
		++begin;
	}
}

//Create map with words and lines, search and return lines coresonding to searched word.
class TextQuery{
	public:
	
	//ctor that fills in vector and map
	TextQuery(std::istream& is);
	
	//Functions
	QueryResult query(std::string);//Takes map and vector and Return Queryresult

	
	private:
	//string srch_word;
	std::shared_ptr<std::vector<std::string>> fileVec; //text lines
	std::map<std::string,std::shared_ptr<std::set<int>>> wordMap;//Takes set
	
	friend class QueryResult;
};


TextQuery::TextQuery(std::istream& is){
	//fileVec=make_shared<vector<string>>(); //optional assignment
	fileVec.reset(new std::vector<std::string>);
	
	//Fill in vector
	std::string line;
	while(std::getline(is,line)){
		fileVec->push_back(line);
	}
	
	//Fill in the map
	auto begin=fileVec->begin();
	while(begin!=fileVec->end()){
		std::istringstream sstrm(*begin);
		size_t line_no=begin-fileVec->begin();
		
		std::string word;
		while(sstrm>>word){
			
			if(wordMap[word]==nullptr) //If shared_ptr empty...
				wordMap[word].reset(new std::set<int>); //Allocate new set
			wordMap[word]->insert(line_no);
			}
		++begin;
	}
}

QueryResult TextQuery::query(std::string srch_word){
	QueryResult res;
	res.srch_word=srch_word;
	
	auto found=wordMap.find(srch_word);
	if(found!=wordMap.end()){
		res.lineNr=found->second;
		res.fileVec=fileVec;
	}
	
	return res;
}



//-----STRBLOB-----------------------------------
/*
Class that allocate vector<string> in dynamic mem.
It can add, remove and peek elements.
Checks if element in vector exists before removing or peeking.
*/
class StrBlobPtr;
class StrBlob{
	public:
	
	friend class StrBlobPtr;
	StrBlobPtr begin()const ;
	StrBlobPtr end()const;
	
	StrBlob():data(std::make_shared<std::vector<std::string>>()){} //Empty vector
	StrBlob(std::initializer_list<std::string> il):data(std::make_shared<std::vector<std::string>> (il)){}
	
	StrBlob(const StrBlob &bl):
	data(std::make_shared<std::vector<std::string>>(*bl.data)){}
	
	StrBlob& operator=(const StrBlob &rhs){
		*data=*rhs.data;
		return *this;
	}
	
	void push_back(const std::string&);
	void pop_back();
	std::string front();
	std::string front()const;
	std::string back();
	std::string back() const;
	void print();
	
	private:
	void check(std::size_t, const std::string&)const;
	std::shared_ptr<std::vector<std::string>> data;
};

void StrBlob::check(std::size_t sz, const std::string &msg)const{
	if(sz>=data->size())
		throw std::out_of_range(msg);
}

void StrBlob::push_back(const std::string &s){
	data->push_back(s);
}

void StrBlob::pop_back(){
	check(0,"Error");
	data->pop_back();
}

std::string StrBlob::front(){
	check(0,"Error");
	return data->front();
}

std::string StrBlob::front()const {
	check(0,"Error");
	return data->front();
}

std::string StrBlob::back(){
	check(0,"Error");
	return data->back();
}

std::string StrBlob::back()const {
	check(0,"Error");
	return data->back();
}

void StrBlob::print(){
	check(0,"Error");
	for(auto el:*data){
		std::cout<<el<<std::endl;
	}
}

//POINTER TO BLOB
class StrBlobPtr{
	public:
	//ctors
	StrBlobPtr():curr(0){}
	StrBlobPtr(const StrBlob &a, size_t sz=0):wptr(a.data), curr(sz){}
	
	//fcns
	std::string deref();
	StrBlobPtr& incr();
	friend bool operator!=(const StrBlobPtr&,const StrBlobPtr&);
	
	
	private:
	std::shared_ptr<std::vector<std::string>> check(size_t,const std::string&);
	std::weak_ptr<std::vector<std::string>> wptr;
	size_t curr;
	
	
};

std::shared_ptr<std::vector<std::string>>
StrBlobPtr::check(size_t sz, const std::string &msg){
	//Check if there is shared pointer and if element exists
	std::shared_ptr<std::vector<std::string>> ret=wptr.lock();
	if(!ret)
		throw std::runtime_error("No pointer");
	if(sz>=ret->size())
		throw std::out_of_range(msg);
	
	return ret;
}

std::string StrBlobPtr::deref(){
	auto ret=check(curr,"No element");
	return (*ret)[curr];
}

StrBlobPtr&  StrBlobPtr::incr(){
	check(curr,"No element");
	++curr;
	return *this;
}

bool operator!=(const StrBlobPtr &lhs,const StrBlobPtr &rhs){
	return (lhs.curr!=rhs.curr); 
}

StrBlobPtr StrBlob::begin()const {
	return StrBlobPtr(*this);
};
StrBlobPtr StrBlob::end()const {
		return StrBlobPtr(*this,data->size());
	}

void printBlob(const StrBlob &blob){ //Put const here!
	
	for (StrBlobPtr ptr=blob.begin(), end=blob.end();ptr!=end;ptr.incr())
	std::cout<<ptr.deref()<<std::endl;
	
}


//-----SCREEN-----------------------------------
class Screen;

class Window_mgr{
	public:
	using ScreenIndex=std::vector<Screen>::size_type;
	inline void clear(ScreenIndex);
	ScreenIndex addScreen(const Screen&);
	
	private:
	std::vector<Screen> screens;
};

Window_mgr::ScreenIndex

Window_mgr::addScreen(const Screen &s){

//Add new screen
screens.push_back(s);
//return number where it is in the screens
return screens.size()-1;
};

class Screen{
public:
	Window_mgr::ScreenIndex var=8;
	typedef std::string::size_type pos;
	friend class Window_mgr;
	//friend void Window_mgr::clear(Window_mgr::ScreenIndex);
	Screen()=default;
	
	//ctor sets screen dimensions and fills it with one char 
	Screen(pos ht, pos wd, char c=' '):height(ht), width(wd), contents(ht*wd,c){}
	
	//get(int,int) returns character on cursor or on (row,col)
	char get()const{ return contents[cursor]; }//Inline implicitly
	char get(pos, pos)const;
	
	//move(int,int) moves cursor to coordinates
	Screen move(pos row, pos col);
	
	//set() Sets character on cursor or on cordinates
	Screen set(char c){
		contents[cursor]=c;
		return *this;
	}
	Screen& set(pos row, pos col, char c);
	
	//Display screen made to be overloaded based on const
	Screen& display(std::ostream &os){do_display(os);return *this;};
	const Screen& display(std::ostream &os)const{do_display(os);return *this;};
		
private:
	pos cursor=0;
	pos height=0, width=0;
	std::string contents;
	mutable size_t getAccess_ctr=0; //Gts modified in const object
	
	void do_display(std::ostream&)const;
};

void Window_mgr::clear(ScreenIndex i){
	Screen &s=screens[i]; //Making reference to particular screen
	s.contents=std::string(s.height*s.width,' ');//Reset contents by puting there string filled with ' '
}

void Screen::do_display(std::ostream& os)const{
	for(size_t row=0;row<height;++row){
		for(size_t col=0;col<width;col++){
			os<<contents[row*width+col];
		}
		os<<std::endl;
	}
}

Screen& Screen::set(pos row, pos col, char c){
	row*=width;
	contents[row+col]=c;
	return *this;
}

inline char Screen::get(pos row, pos col)const{
	getAccess_ctr++;//It will modify member even in const object
	row=(row)*width;
	return contents[row+col];	
}

//Make move function. Set cursor position (row, col_. Make it chainable, 
inline
Screen Screen::move(pos row, pos col){
	row=row*width;
	cursor=row+col;
	return *this; // (*) because I want to return an object
}

//-----PERSON------------------------------------------------------


//Class Person
class Person{
	private:
	std::string m_name;
	std::string m_address;

	public:
	//Constructiors
	Person():m_name(""), m_address(""){} //Default
	Person(std::istream& is){ is>>m_name>>m_address; } //Cin
	Person(std::string s):m_name(s){}	//Enter just name
	Person(std::string n, std::string a):m_name(n),m_address(a){}
	//enter 2 vaulues
	
	//Functions
	std::string getName() const {
		return m_name;
	}

	std::string getAddress() const {
		return m_address;
	}
	
	std::istream& read(std::istream &is){
		is>>m_name>>m_address;
		return is;
	}
		
	std::ostream& print(std::ostream &os){
		os<<m_name<<"\t"<<m_address;	
		return os;
	}
	
};

//----SALES DATA-------------------------------------------------------


//Fwd declaration to use in class if no friend 
class Sales_data;
std::istream& read(std::istream&, Sales_data &); 

class Sales_data{
	private:
	std::string bookNo;
	unsigned int units_sold;
	double revenue;
	
	double avg_price()const;
	public:
	//Constructors
	Sales_data(std::string s, unsigned int n, double p)
	:bookNo(s), units_sold(n),revenue(n*p) {
		//std::cout<<"Full ctor"<<std::endl;
	}
	
	Sales_data(): Sales_data("",0,0.0) {
		//std::cout<<"Default ctor"<<std::endl;
	}
	
	explicit Sales_data(std::istream &is):Sales_data(){ 
		read(is,*this);
		//std::cout<<"istream ctor"<<std::endl;
	}
	
	Sales_data(const std::string& s):Sales_data(s,0,0.0) {
		//std::cout<<"Str ctor"<<std::endl;
	}

	//Function prototypes
	Sales_data& combine(const Sales_data&);
	std::string isbn() const;
	
	
	
	//Friend functions
	friend std::istream& read(std::istream&, Sales_data&);
	friend Sales_data add(const Sales_data&,const Sales_data&);
	friend std::ostream& printOut(std::ostream&, const Sales_data&);
	
	//Operators
	friend std::istream& operator>>(std::istream&,Sales_data&);
	friend Sales_data operator+(const Sales_data&, const Sales_data&);
};

inline
double Sales_data::avg_price()const{
	return units_sold?revenue/units_sold:0;

}

//isbn - Fetch bookNo from object
std::string Sales_data::isbn()const {
	return bookNo;
}

//combine- add one member to another
Sales_data& Sales_data::combine(const Sales_data &rhs){
	units_sold+=rhs.units_sold;
	revenue+=rhs.revenue;
	return *this;
}

//Add two transactions
Sales_data add(const Sales_data &it1,const Sales_data &it2){
	
	Sales_data sum=it1;
	sum.combine(it2); //Add units
		
	return sum;
}

//Read transaction
std::istream& read(std::istream &is, Sales_data &item){
	double price=0;
	is>>item.bookNo>>item.units_sold>>price;
	item.revenue=item.units_sold*price;
	
	return is;
}

//Print output
std::ostream& printOut(std::ostream& os, const Sales_data &item){
	os<<item.bookNo<<"\t"
	<<item.units_sold<<"\t"
	<<item.revenue<<"\t"
	<<item.avg_price();
	return os;
}

//Operators

std::istream& operator>>(std::istream& is, Sales_data &obj){
	double price=0;
	is>>obj.bookNo>>obj.units_sold>>price;
	obj.revenue=obj.units_sold*price;
	
	return is;
}

Sales_data operator+(const Sales_data &obj1, const Sales_data &obj2){
	Sales_data temp;
	temp.bookNo=obj1.bookNo;
	temp.units_sold=obj1.units_sold + obj2.units_sold;
	temp.revenue=obj1.revenue + obj2.revenue;
	
	return temp;
}
#endif