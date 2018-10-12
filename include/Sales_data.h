#ifndef SALESDATA_H
#define SALESDATA_H


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