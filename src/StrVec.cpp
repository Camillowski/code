#include <iostream>
#include <exception>
#include <algorithm>
#include "StrVec.h"
using namespace std;


/*
FUNCTIONS
*/

//STATIC ALLOCATOR FOR ALL OBJECTS
allocator<string> StrVec::alloc;


//DEFAULT COPY CONSTRUCTOR
StrVec::StrVec(const StrVec &svec):
elem(alloc.allocate(svec.capacity())),cap(elem+svec.capacity()){
	
	//copy previous strings to new object
	first_free=uninitialized_copy(svec.begin(),svec.end(),elem);
	cout<<"Copy ctor done\n";
}

//INITIALIZER LIST CTOR
StrVec::StrVec(initializer_list<string> il):StrVec(){
	initializer_list<string>::iterator beg=il.begin();
	while(beg!=il.end())
		push_back(*beg++);
}
	
//DEFAULT DESTRUCTOR
StrVec::~StrVec(){
	//Destroy all objects and erase memory
	free();
}


//ASSIGNMENT OPERATOR
StrVec& StrVec::operator=(const StrVec &svec){
	//When enough space
	if (capacity()>=svec.capacity()){
		dstrElem(begin(),end());
		first_free=uninitialized_copy(svec.begin(),svec.end(),elem);
		
	//When not enough space
	}else{
		free();
		elem=alloc.allocate(svec.capacity());
		first_free=uninitialized_copy(svec.begin(),svec.end(),elem);
		cap=elem+svec.capacity();
	}
	return *this;
}


//ADD ELEMENT
string* StrVec::push_back(const string &str){
	
	//If capacity is full reallocate
	if(first_free==cap){
		reallocate(capacity()*2);
	}
	
	//Add new element to the end
	alloc.construct(first_free++,str);
	return first_free;

}


//REMOVE LAST ELEMENT FROM VECTOR
std::string* StrVec::pop_back(){

	//Destroy last object and decrement pointer to one past end
	alloc.destroy(--first_free);
	
	//Reallocates vector and shrinks allocated memory
	if( (size()<=capacity()/4) && (capacity()>init_size) ){
		reallocate(capacity()/2);
	}
	
	return first_free;
}


//REMOVE OR ADD OBJECTS TO MAKE IT N
void StrVec::resize(size_t n){
	
	int chngSize=size()-n;
	//If nothing to add/delete
	if (chngSize==0){
		return;
	}
	
	if (chngSize>0){
	//Delete
		for(int i=0;i<chngSize;++i){
			pop_back();
		}
	}else{
		//Add
		for(int i=1;i<=(-chngSize);++i){
			push_back("New "+to_string(i));
		}
	}
	
}


//RESERVE CAPACITY
bool StrVec::reserve(size_t n){
	if(n>capacity()){
		reallocate(n);
		return true;
	}
	return false;
}


//DESTROY OBJECTS AND FREE SPACE
/*
void StrVec::free(){
	//Destroy objects
	dstrElem(begin(),end());
	
	//Deallocate mem
	alloc.deallocate(elem,cap-elem);
}
*/
//LAMBDA VERSION
void StrVec::free(){
	//Destroy objects
	
	for_each(elem,first_free,[](string &ptr)->void{
		alloc.destroy(&ptr);
		});
	//Deallocate mem
	alloc.deallocate(elem,cap-elem);
}

//DESTROY ELEMENTS IN RANGE
void StrVec::dstrElem(string *beg, string *end){
	while(beg!=end){
		alloc.destroy(beg++);
	}
}


//REALLOCATE VECTOR TO NEW BIGGER SPACE
void StrVec::reallocate(const size_t &new_size){
	
	//Allocation and copy	
	string* new_elem = alloc.allocate(new_size);
	string* new_cap = new_elem+new_size;
	//string* new_first_free = uninitialized_copy(elem,first_free,new_elem);
	auto beg= begin();
	auto new_first_free=new_elem;
	while(beg!=end()){
		alloc.construct(new_first_free++,std::move(*beg++));
	}
	
	//Destroy objects and free memory
	free();
	
	//Assogn pointers to new memory
	swap(elem,new_elem);
	swap(first_free,new_first_free);
	swap(cap,new_cap);	
}


//CHECK NUMBER OF ELEMENTS
size_t StrVec::size(){
	return first_free - elem;
}

//CHECK WHOLE CAPACITY
size_t StrVec::capacity() const{
	return cap-elem;
}

//RETURN REFERENCE TO VALUE AT INDEX
std::string& StrVec::at(size_t n){
	if(n>=size())
		throw out_of_range("Index out of range!");
	else{
		return *(elem+n);
	}
}

//TESTS
	
//Check if entering new element works good
string Test::chk_pb(StrVec &svec){
	string* testPtr=svec.push_back("Test String")-1;
	
	if (*testPtr=="Test String" && (testPtr<svec.end()))
		return "PASSED";
	else
		return "FAILED";	
}

//Check in no overflow when add new elements over curent cap.
string Test::is_overflow(StrVec &svec, int size){
	for (int i=0; i<size;++i){
		string s="Element "+to_string(i);
		string*ptr = svec.push_back(s);
		if(ptr==nullptr){
			return "FAILED";
		}
	}
	return "PASSED";
}

//Check pop_back()
string Test::chk_pop_back(StrVec &svec, int n){
	size_t old_cap=svec.capacity();
	for (int i=0;i<(n-3);++i){
		svec.pop_back();
	}
	size_t new_cap=svec.capacity();
	if(new_cap>=old_cap){
		return "FAILED";
	}
	return "PASSED";
}

//VECTOR OPERATIONS

//Print vector
void printVec(StrVec &svec){	

	string *begin=svec.begin();
	while(begin!=svec.end()){
		cout<<*begin++<<endl;
	}
}

//Fill vector with n elements
void fillVec(StrVec &svec, size_t n){
	for (int i=0; i<n;++i){
		string s="Element "+to_string(i);
		svec.push_back(s);
	}
}

//Destroy n elements in vector
void destVec(StrVec &svec, size_t n){
	for (int i=0;i<n;++i){
		svec.pop_back();
	}	
}

//AGREGGATE TEST FUNCTION
void TEST(StrVec &svec){
	
	size_t n=129; //Vector size
	cout<<"Check is_empty(): "<<svec.is_empty()<<endl;
	cout<<"Check size(): "<<svec.size()<<endl;
	cout<<"Check capacity(): "<<svec.capacity()<<endl;
	//cout<<"Check reallocate(): "<<Test::is_overflow(svec,n)<<endl;
	//cout<<"Check push_back(): "<<Test::chk_pb(svec)<<endl;
	//cout<<"Check pop_back(): "<<Test::chk_pop_back(svec,n-10)<<endl;
	cout<<"Checl begin(): "<<svec.begin()<<endl;
	cout<<"Check end(): "<<svec.end()<<endl;
	cout<<endl;
}