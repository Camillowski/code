/*
CHAPTER 9 - OPERATORS OVERLOADING
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <cassert>
#include <iomanip>

using namespace std;

//Ex.CODEWARS: Sum of two lowest positive integers
/*
Create a function that returns the sum of the two lowest positive numbers given an array of minimum 4 integers. No floats or empty arrays will be passed.

For example, when an array is passed like [19, 5, 42, 2, 77], the output should be 7.

[10, 343445353, 3453445, 3453545353453] should return 3453455.

*/

long sumTwoSmallestNumbers(std::vector<int> numbers)
{
    sort(numbers.begin(), numbers.end());
    std::cout<<numbers[0]<<" Size: "<<sizeof(numbers[0])<<std::endl;
   std::cout<<numbers[1]<<std::endl;
    long sum=long(numbers[0])+numbers[1];
   std::cout<<sum<<" Size: "<<sizeof(sum)<<endl;
  
    return sum;
}

int main(){
vector<int> vec{2000000000,2000000000,2000000001,2000000002};

auto res=sumTwoSmallestNumbers(vec);
cout<<"Sum; "<<res;

}


//Ex.(11.4)
/*
1) Let’s implement our Fruit example that we talked about in our introduction to inheritance.
Create a Fruit base class that contains two private members: a name (std::string), and a color (std::string).
Create an Apple class that inherits Fruit.
Apple should have an additional private member: fiber (double).
Create a Banana class that also inherits Fruit. Banana has no additional members.


class Fruit{
	string name;
	string color;
public:
	Fruit(const string& n, const string& c):name(n), color(c){}
	string getName()const {return name;}
	string getColor()const {return color;}
	
};

class Apple: public Fruit{
	double fiber;
public:
	Apple(const string& n, const string& c, double f):Fruit(n,c),fiber(f){}
	double getFiber()const{return fiber;}
	friend ostream& operator<<(ostream& out, const Apple& a);
};

class Banana: public Fruit{
public:
	Banana(const string& n, const string& c):Fruit(n,c){}
	friend ostream& operator<<(ostream& out, const Banana& b);
};


ostream& operator<<(ostream& out, const Apple& a){
	cout<<"Apple("<<a.getName()<<", "<<a.getColor()<<", "<<a.getFiber()<<")";
	
	return out;
}

ostream& operator<<(ostream& out, const Banana& b){
	cout<<"Banana("<<b.getName()<<", "<<b.getColor()<<")";
	return out;
}
int main()
{
	const Apple a("Red delicious", "red", 4.2);
	std::cout << a<<endl;
 
	const Banana b("Cavendish", "yellow");
	std::cout << b<<endl;
 
	return 0;
}
*/

//Ex.(10.7)
/*
Create class that holds array of integers. Write necessary members to use the class.



class IntArray{
private:
	int size;
	int* data;
	//Copy one array to another
	void copy(const int*,const int*, int*);
public:
//CTORS
	//Default ctor
	IntArray(int);
	//Ctor with size and default filling
	IntArray(int,int);
	//Copy constructor
	IntArray(const IntArray&);
	//Copy assignment
	IntArray& operator=(const IntArray&);
	//List ctor
	IntArray(const initializer_list<int>);
	//List copy assignment
	IntArray& operator=(const initializer_list<int>);
	//Dtor
	~IntArray(){clear();}
	
//MEMBERS	
	//Clear array
	void clear();
	//Access element []
	int& operator[](int index){ return data[index];}
	//Print array
	friend ostream& operator<<(ostream&, const IntArray&);
	//Array size()
	int chkSize(){return size;}
	//Chceck if empty
	bool isEmpty(){return size==0?true:false;}
	//Insert element
	int& insert(int index, int value);
	//Remove element
	IntArray& remove(int index);
	//Push_back
	int& push_back(int value){insert(size,value); return data[size-1];}
	//Push_front
	int& push_front(int value){insert(0,value); return data[0];}
	//Pop_back
	int& pop_back(){remove(0);return data[0];}
	//Pop_front
	int& pop_front(){remove(size-1);return data[size-1];}
	//Sort array
	void sort(){std::sort(data,data+size);}
};
//--------------------------------------------------------

//Default Ctor that create empty array.
IntArray::IntArray(int s=0):size(s){
		assert(s>=0);
		if(size>0)
			data=new int[size]();
		else
			data=nullptr;
}

//Ctor with size and default filling
IntArray::IntArray(int s, int f):IntArray(s){
	assert(s>0);//Make sure data is not nullptr
	
	data= new int[size];
	for(int i=0; i<size; ++i)
		data[i]=f;
}

//Copy constructor
IntArray::IntArray(const IntArray& ar):IntArray(ar.size){
	assert(size>0);
	
	copy(ar.data,ar.data+ar.size,data);
}

//Copy assignment
IntArray& IntArray::operator=(const IntArray& ar){
	if(this==&ar)
		return *this; //Selfassignment guard
	
	if(size!=ar.size){
		if(data)//Make sure its not a nullptr
			delete[] data;
		size=ar.size;
		data=new int[size];
	}
		copy(ar.data,ar.data+ar.size,data);
	return *this;
}

//List ctor
IntArray::IntArray(const initializer_list<int> li):IntArray(li.size()){
	
	if(size>0)
		copy(li.begin(),li.end(),data);
}

//List copy assignment
IntArray& IntArray::operator=(const initializer_list<int> li){
	if(size!=li.size()){
		//Resize
		if(data)//Make sure its not a nullptr
			delete[] data;
		size=li.size();
		data=new int[size];
	}
	copy(li.begin(),li.end(),data);
	
	return *this;
}

//Clear array
void IntArray::clear(){
	
	if(data!=nullptr){
		delete[] data;
		data=nullptr;
		size=0;
	}
}

//Print array
ostream& operator<<(ostream& out, const IntArray& ar){
	
	out<<"Array[";
	for(int i=0;i<ar.size;++i)
		out<<ar.data[i]<<",";
	ar.size>0?out<<'\b'<<"]":out<<"]";//Remove last coma by deleting it and replacing with ]. If array size is zero, then ommit backspace.
}

//Insert element
int& IntArray::insert(int index, int value){
	//Check is index is in range
	assert(index>=0 && index<=size);
	
	//Create temporary array
	int* tmp_data= new int[size+1];
	
	//Copy content of array and insert value
	for(int i=0; i<index;++i)
		tmp_data[i]=data[i];
	tmp_data[index]=value;
	for(int i=index;i<size;++i)
		tmp_data[i+1]=data[i];
	
	//Free memory from old data, update size and assign new memory to data.
	++size;
	delete[] data;
	data=tmp_data;
	
	return data[index];
}

//Remove element
IntArray& IntArray::remove(int index){
	//Check for index validity
	
	assert(index>=0 && index<size);
	
	int* tmp_data= new int[size-1];
	
	//Copy content of array with out pointed index.
	for(int i=0; i<index;++i)
		tmp_data[i]=data[i];
	for(int i=index+1;i<size;++i)
		tmp_data[i-1]=data[i];
	
	//Free memory from old data, update size and assign new memory to data.
	--size;
	delete[] data;
	data=tmp_data;
	
	return *this;
}

//Copy. begin= first element, end= one past last. Manual check if dest is enough
void IntArray::copy(const int* begin,const int* end, int* dest){
	for(const int* i=begin;i<end;++i){
		*dest=*i;
		++dest;
	}
}
	
int main(){
	
	IntArray array(10,2);
	IntArray array2(20);
	IntArray array3;
	IntArray array4{1,2,3,4,5,6,7,8,9,10};
	array3=array;

	array.insert(5,9)=7;
	array.remove(6);
	array.push_back(12)=11;
	array.push_front(5)=3;
	array.pop_back()=8;
	array.pop_front()=8;
	array.sort();
	cout<<array<<endl;
	cout<<array2<<endl;
	cout<<array3<<endl;
	cout<<array4<<endl;
	array2={22,33,44,55,66};
	cout<<array2<<endl;
}
*/

//Ex.(10.3)
/*
2) Update the Teacher/Dept example so the Dept can handle multiple Teachers. The following code should execute {code on site}:


class Teacher
{
private:
    std::string m_name;
 
public:
    Teacher(std::string name)
        : m_name(name)
    {
    }
 
    std::string getName() { return m_name; }
};
 
class Department
{
private:
    vector<Teacher*> m_vec;
 
public:
    Department(){}
	
	//Create function to add teachers
	void add(Teacher* &t){
		m_vec.push_back(t);
	}
	
	//Create function to print dept.
	friend ostream& operator<<(ostream&,const Department&);
};

ostream& operator<<(ostream& out,const Department& dept){
	out<<"Departament: ";
	for(Teacher* el:dept.m_vec)
		out<<el->getName()<<" ";
	out<<endl;
}

int main()
{
    // Create a teacher outside the scope of the Department
    Teacher *t1 = new Teacher("Bob"); // create a teacher
    Teacher *t2 = new Teacher("Frank");
    Teacher *t3 = new Teacher("Beth");
 
    {
        // Create a department and use the constructor parameter to pass
        // the teacher to it.
        Department dept; // create an empty Department
        dept.add(t1);
        dept.add(t2);
        dept.add(t3);
 
        std::cout << dept;
 
    } // dept goes out of scope here and is destroyed
 
    std::cout << t1->getName() << " still exists!\n";
    std::cout << t2->getName() << " still exists!\n";
    std::cout << t3->getName() << " still exists!\n";
 
    delete t1;
    delete t2;
    delete t3;
 
    return 0;
}
*/

//Ex. CHAPTER 9 COMPREHENSIVE QUIZZZZZZ ex.4
/*
4) Extra credit: This one is a little more tricky. A floating point number is a number with a decimal where the number of digits after the decimal can be variable. A fixed point number is a number with a fractional component where the number of digits in the fractional portion is fixed.

In this quiz, we’re going to write a class to implement a fixed point number with two fractional digits (e.g. 12.34, 3.00, or 1278.99). Assume that the range of the class should be -32768.99 to 32767.99, that the fractional component should hold any two digits, that we don’t want precision errors, and that we want to conserve space.

4b) Write a class named FixedPoint2 that implements the recommended solution from the previous question.
If either (or both) of the non-fractional and fractional part of the number are negative, the number should be treated as negative.
Provide the overloaded operators and constructors required for the following program to run:{Code in the book}

4c) Now add a constructor that takes a double. You can round a number (on the left of the decimal) by using the round() function (included in header cmath).

4d) Overload operator==, operator >>, operator- (unary), and operator+ (binary).


class FixedPoint{
private:
	int16_t nr;
	int8_t dec;
public:
	FixedPoint(int16_t n, int8_t d): dec(d), nr(n){
		//transform both numbers to 0 of one of them is.
		if(dec<0 || nr<0){
			if(dec>0) dec=-dec;
			if(nr>0) nr=-nr;
		}
	}
	
	//ctor accepting double
	FixedPoint(double d){
		nr=(static_cast<int>(d));
		dec=round((d-nr)*100);
		//cout<<"Nr: "<<nr<<" Dec: "<<int(dec)<<endl;
	}
	
	//output operator
	friend ostream& operator<<(ostream&,const FixedPoint&);
	//convert to double.
	
	operator double()const{
		return nr+static_cast<double>(dec)/100;
	}
	
	//operator==
	friend bool operator==(const FixedPoint&,const FixedPoint&);
	
	//operator>>
	friend istream& operator>>(istream&, FixedPoint&);
	//operator-U
	FixedPoint operator-(int);
	
	//operator +
	friend FixedPoint operator+(const FixedPoint, const FixedPoint);
};

//operator<<
ostream& operator<<(ostream& out, const FixedPoint& fp){
	//print number converted to double
	out<<static_cast<double>(fp);
	return out;
}

//operator==
bool operator==(const FixedPoint& a,const FixedPoint& b){
	return (a.dec==b.dec && a.nr==b.nr)?true:false;
}

//operator>>
istream& operator>>(istream& in, FixedPoint& f){
	
	double temp;
	in>>temp;
	
	f.nr=(static_cast<int>(temp));
	f.dec=round((temp-f.nr)*100);
	return in;
}

//operator-
FixedPoint FixedPoint::operator-(int){
	return FixedPoint(-nr,-dec);
}

//operator +
FixedPoint operator+(const FixedPoint a, const FixedPoint b){
	double temp= static_cast<double>(a) + static_cast<double>(b);
	return FixedPoint(temp);
}
	

void testAddition()
{
	// h/t to reader Sharjeel Safdar for this function
	std::cout << std::boolalpha;
	std::cout << (FixedPoint(0.75) + FixedPoint(1.23) == FixedPoint(1.98)) << '\n'; // both positive, no decimal overflow
	std::cout << (FixedPoint(0.75) + FixedPoint(1.50) == FixedPoint(2.25)) << '\n'; // both positive, with decimal overflow
	std::cout << (FixedPoint(-0.75) + FixedPoint(-1.23) == FixedPoint(-1.98)) << '\n'; // both negative, no decimal overflow
	std::cout << (FixedPoint(-0.75) + FixedPoint(-1.50) == FixedPoint(-2.25)) << '\n'; // both negative, with decimal overflow
	std::cout << (FixedPoint(0.75) + FixedPoint(-1.23) == FixedPoint(-0.48)) << '\n'; // second negative, no decimal overflow
	std::cout << (FixedPoint(0.75) + FixedPoint(-1.50) == FixedPoint(-0.75)) << '\n'; // second negative, possible decimal overflow
	std::cout << (FixedPoint(-0.75) + FixedPoint(1.23) == FixedPoint(0.48)) << '\n'; // first negative, no decimal overflow
	std::cout << (FixedPoint(-0.75) + FixedPoint(1.50) == FixedPoint(0.75)) << '\n'; // first negative, possible decimal overflow
}
	
	
int main()
{
	FixedPoint a(34, 56);
	std::cout << a << '\n';
 
	FixedPoint b(-2, 8);
	std::cout << b << '\n';
 
	FixedPoint c(2, -8);
	std::cout << c << '\n';
 
	FixedPoint d(-2, -8);
	std::cout << d << '\n';
 
	FixedPoint e(0, -5);
	std::cout << e << '\n';
 
	std::cout << static_cast<double>(e) << '\n';
	
	//4c)
	cout<<endl;
	FixedPoint f(0.01);
	std::cout << f << '\n';
 
	FixedPoint g(-0.01);
	std::cout << g << '\n';
 
	FixedPoint h(5.01); // stored as 5.0099999... so we'll need to round this
	std::cout << h << '\n';
 
	FixedPoint i(-5.01); // stored as -5.0099999... so we'll need to round this
	std::cout << i << '\n';
 
	//4d)
	cout<<endl;
	testAddition();
 
	FixedPoint j(-0.48); 
	std::cout << j << '\n';
 
	std::cout << -j << '\n';
 
	std::cout << "Enter a number: "; // enter 5.678
	std::cin >> j;
	
	std::cout << "You entered: " << j << '\n';
	return 0;
}
*/

//Ex. CHAPTER 9 COMPREHENSIVE QUIZZZZZZ ex.3
/*
3) Write your own integer array class named IntArray from scratch (do not use std::array or std::vector).
Users should pass in the size of the array when it is created, and the array should be dynamically allocated.
Use assert statements to guard against bad data.
Create any constructors or overloaded operators needed to make the following program operate correctly: {Code on website}


class IntArray{
private:
	int size;
	int *array;
public:
	//ctor to pass size
	IntArray(int s=1):size(s),array(new int[s]){}
	~IntArray();
	
	//Copy assignment
	IntArray& operator=(const IntArray& ar);
	
	//Subscript operator
	int& operator[](int);
	
	//<< operator
	friend ostream& operator<<(ostream&,const IntArray&);
};


//Subscript operator
int& IntArray::operator[](int index){
	return array[index];
}


IntArray& IntArray::operator=(const IntArray& ar){
	//Check for self assignment
	if(this == &ar)
		return *this;
	
	//Delete curent mem.
	delete[] array;
	
	//Pass size
	size=ar.size;
	
	//Allocate new mem with proper size
	array=new int[size];
	
	//Copy data members(use subscript operator)
	for(int i=0;i<size;++i){
		array[i]=ar.array[i];
	}
	return *this;
}

// Destructor
IntArray::~IntArray(){
	delete[] array;

}

//Output operator
ostream& operator<<(ostream& out, const IntArray& ar){
	for(int i=0;i<ar.size;++i)
		out<<ar.array[i]<<" ";

	return out;
}

IntArray fillArray()
{
	IntArray a(5);
	a[0] = 5;
	a[1] = 8;
	a[2] = 2;
	a[3] = 3;
	a[4] = 6;
 
	return a;
}
 
int main()
{
	IntArray a = fillArray();
	std::cout << a << '\n';
 
	IntArray b(1);
	a = a;
	b = a;
 
	std::cout << b << '\n';
 
	return 0;
}
*/

//Ex. CHAPTER 9 COMPREHENSIVE QUIZZZZZZ ex.2
/*
2) Write a class named Average that will keep track of the average of all integers passed to it.
Use two members: The first one should be type int32_t, and used to keep track of the sum of all the numbers you’ve seen so far. The second should be of type int8_t, and used to keep track of how many numbers you’ve seen so far.
You can divide them to find your average.


//data: avgSum and count
// - >returns averag
//average
//Add number

#include <numeric>

class Average{
private:
	int8_t count;
	int32_t avgSum;
public:
	Average(initializer_list<int> li):count(li.size()),avgSum(accumulate(li.begin(),li.end(),0)){}
	//Copy assignment
	//No need. Default is enough.
	
	//operator +=
	Average& operator+=(int);
	
	//<<operator
	friend ostream& operator<<(ostream&,const Average&);
	
	void debug(){cout<<"Count: "<<int(count)<<"\navgSum: "<<avgSum<<endl;}
};

Average& Average::operator+=(int nr){
	avgSum+=nr;
	++count;
	return *this;
}

ostream& operator<<(ostream& out,const Average& obj){
	out<<obj.avgSum/double(obj.count);
	return out;
	}


int main(){
	Average obj{1,2,3,4,5,6,7,8,9,3,4,5,6,7,8,9,33,2,4,66,1};
	obj+= 15;
	(obj+= 15)+=20;
	obj.debug();
	cout<<"Average: "<<obj<<endl;

	Average obj2=obj;
	cout<<obj2;
}
*/

//Ex. CodeWars kata
/*

*/

// double pierw(int a){
	// const double e=0.001;
	// double x=0, p=6.0;
	
	// do{
		// x=p;
		// p=(x+a/x)/2;
		// //cout<<p<<endl;
	// }while(abs(p-x)>=e);
	// return p;
// }

// bool is_square(int n)
// {
  // double res=pierw(n);
  // if(res-int(res)<=0.0000001)
    // return true;
  // else
    // return false;
// }

// int main(){
// cout<<is_square(4)<<endl;
// }

//Ex.(9.9)
/*
1) Write a class that holds a string. Overload operator() to return the substring that starts at the index of the first parameter. The length of the substring should be defined by the second parameter.

Hint: You can use array indices to access individual chars within the std::string
Hint: You can use operator+= to append something to a string


class myString{
private:
	string str;
public:
	myString(const string& s):str(s){}
	
	string operator()(int,int) const;
};

string myString::operator()(int begin,int len) const{
	
	if(!str.empty() && //Make sure string is not empty
	(begin+len)<=str.size() && //Make sure substring is in range
	begin>=0 && len>0){ //Make sure Begin and len have valid values
		
	//Return substring using string method
		//return str.substr(begin,len);
		
	//Return string by appending next chars to string
		string temp;
		
		for(int i=begin; i<len+begin; ++i)
			temp+=str[i];
		return temp;
	}else
		//Return Erron message
		return "ERROR";
}

int main(){
	myString str("Kamil");
	cout<<str(0,4);
}
*/

//Ex.(9.8)
/*
1) A map is a class that stores elements as a key-value pair. The key must be unique, and is used to access the associated pair. In this quiz, we’re going to write an application that lets us assign grades to students by name, using a simple map class. The student’s name will be the key, and the grade (as a char) will be the value.

1a) First, write a struct named StudentGrade that contains the student’s name (as a std::string) and grade (as a char).

1b) Add a class named GradeMap that contains a std::vector of StudentGrade named m_map. Add a default constructor that does nothing.


1c) Write an overloaded operator[] for this class. This function should take a std::string parameter, and return a reference to a char.

In the body of the function, first iterate through the vector to see if the student’s name already exists (you can use a for-each loop for this).

If the student exists, return a reference to the grade and you’re done. Otherwise, use the std::vector::push_back() function to add a StudentGrade for this new student.

When you do this, std::vector will add a copy of your StudentGrade to itself (resizing if needed).

Finally, we need to return a reference to the grade for the student we just added to the std::vector.

We can access the student we just added using the std::vector::back() function.

2) Extra credit #1: The GradeMap class and sample program we wrote is inefficient for many reasons. Describe one way that the GradeMap class could be improved.

	* Use tree data structure!
	* Sort and then binary search vector
	* Insert new element on the correct spot


struct StudentGrade{
	string name;
	char grade;
};

class GradeMap{
private:
	vector<StudentGrade> m_map;
	
public:
	GradeMap(){}
	char& operator[](string);
};

	char& GradeMap::operator[](const string &key){
		
		//First need to know which position is the element.
		//Search for element
		vector<StudentGrade>::iterator pos=m_map.begin();
		while(pos!=m_map.end()){
			if(pos->name==key)
				return pos->grade;
			else
				++pos;
		}
		
		//If not found then add key to vector with value 0 and return ref to grade.
		StudentGrade tempStudent{key,' '};
		m_map.push_back(StudentGrade(tempStudent));
		return m_map.back().grade;
	}
	
int main(){
	GradeMap map;

	//cout<<map["Kamil"]<<endl;
	map["Kamil"]='A';
	cout<<map["Kamil"]<<endl;

	GradeMap grades;
	grades["Joe"] = 'A';
	grades["Frank"] = 'B';
	std::cout << "Joe has a grade of " << grades["Joe"] << '\n';
	std::cout << "Frank has a grade of " << grades["Frank"] << '\n';
 
	return 0;
}
*/

//Ex. (9.6)
/*
1) For the Cents example above, rewrite operators < and <= in terms of other overloaded operators.

2) Add an overloaded operator<< and operator< to the Car class at the top of the lesson so that the following program compiles(Program in lesson)


class Cents
{
private:
    int m_cents;
 
public:
    Cents(int cents) { m_cents = cents; }
 
    friend bool operator> (const Cents &c1, const Cents &c2);
    friend bool operator<= (const Cents &c1, const Cents &c2);
 
    friend bool operator< (const Cents &c1, const Cents &c2);
    friend bool operator>= (const Cents &c1, const Cents &c2);
};
 
bool operator> (const Cents &c1, const Cents &c2)
{
    return c1.m_cents > c2.m_cents;
}
 
bool operator>= (const Cents &c1, const Cents &c2)
{
    return c1.m_cents >= c2.m_cents;
}

bool operator<(const Cents &c1, const Cents &c2){
	return !(c1>=c2);
}

bool operator<=(const Cents &c1, const Cents &c2){
		return !(c1>c2);
}

//Class Car
class Car
{
private:
    std::string m_make;
    std::string m_model;
 
public:
    Car(std::string make, std::string model)
        : m_make(make), m_model(model)
    {
    }
 
    friend bool operator== (const Car &c1, const Car &c2);
    friend bool operator!= (const Car &c1, const Car &c2);
    friend bool operator< (const Car &c1, const Car &c2);
	friend ostream& operator<<(ostream& out, const Car &c);
	
};

bool operator== (const Car &c1, const Car &c2){
	return(c1.m_make==c2.m_make && c1.m_model==c2.m_model);
}

bool operator!= (const Car &c1, const Car &c2){
	return (c1.m_make!=c2.m_make || c1.m_model!=c2.m_model);
	
}

bool operator< (const Car &c1, const Car &c2){
	if (c1.m_make<c2.m_make){
		return true;
	}
	else if(c1.m_make==c2.m_make && c1.m_model<c2.m_model)
		return true;
	else
		return false;
		
}

ostream& operator<<(ostream& out, const Car &c){
	out<<c.m_make<<" "<<c.m_model;
	return out;
}

int main(){

	vector<Car> v;
	v.push_back(Car("Toyota", "Corolla"));
	v.push_back(Car("Honda", "Accord"));
	v.push_back(Car("Toyota", "Camry"));
	v.push_back(Car("Honda", "Civic"));
 
	sort(v.begin(), v.end()); // requires an overloaded operator<
 
	for (auto &car : v)
		std::cout << car << '\n'; // requires an overloaded operator<<
}
*/

//Ex. (9.5)
/*
1) Implement overloaded operator+ for the Point class.


class Point{
private:
	double m_x,m_y,m_z;
public:
	Point(double x=0.0, double y=0.0, double z=0.0):m_x(x), m_y(y), m_z(z){}
	
	Point& operator+();
};

Point operator+(){
	return *this;
}

int main(){

}
*/

//Ex. (9.2)(9.3)
/*
1a)Write a class named Fraction that has a integer numerator and denominator member. Write a print() function that prints out the fraction.

1b) Add overloaded multiplication operators to handle multiplication between a Fraction and integer, and between two Fractions. Use the friend function method.

1c) Extra credit: the fraction 2/4 is the same as 1/2, but 2/4 is not reduced to the lowest terms. We can reduce any given fraction to lowest terms by finding the greatest common divisor (GCD) between the numerator and denominator, and then dividing both the numerator and denominator by the GCD.

9.3 Take the Fraction class we wrote in the previous quiz (listed below) and add an overloaded operator<< and operator>> to it.


class Fraction{
	int numerator;
	int denominator;
	
	int NWD(int a, int b) {
		return (b == 0) ? (a > 0 ? a : -a) : NWD(b, a % b);
	}

public:
	Fraction(int, int);
	
	void print(){
		cout<<numerator<<"/"<<denominator<<endl;
	}
	//multi fractions
	friend Fraction operator*(const Fraction& f1, const Fraction& f2);
	//multi integer 
	friend Fraction operator*(const Fraction& f, const int i);
	//mlti int second way
	friend Fraction operator*(const int i, const Fraction& f);
	//Output op
	friend ostream& operator<<(ostream& out, const Fraction &f);
	//INput
	friend istream& operator>>(istream& in, Fraction &f);
};

Fraction::Fraction(int n=0, int d=0){
	int nwd=NWD(n,d);
	//cout<<"NWD: "<<nwd<<endl;
	numerator=n/nwd;
	denominator=d/nwd;
}

Fraction operator*(const Fraction& f1, const Fraction& f2){
	return Fraction(f1.numerator*f2.numerator,
	f1.denominator*f2.denominator);
}

Fraction operator*(const Fraction& f, const int i){
	return Fraction(f.numerator*i,f.denominator);
}
Fraction operator*(const int i, const Fraction& f){
	return f*i;
}

ostream& operator<<(ostream& out, const Fraction &f){
	out<<f.numerator<<"/"<<f.denominator;
	return out;
}

istream& operator>>(istream& in, Fraction &f){
	in>>f.numerator;
	in.ignore(1);
	in>>f.denominator;
	
	int nwd=f.NWD(f.numerator, f.denominator);
	f.numerator/=nwd;
	f.denominator/=nwd;
}

int main(){
	
	Fraction f1(8,4);
	f1.print();
	Fraction f2(2,5);
	f2.print();
	cout<<"New Ops"<<endl;
	cin>>f1;
	cout<<f1<<endl;
	cout<<(f1*f2)<<endl;
	cout<<(f1*3)<<endl;
	cout<<(7*f2)<<endl;
	
}
*/