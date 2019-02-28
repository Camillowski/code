#include <iostream>
#include <cstring>
#include <ostream>
#include <cstdlib>
#include <algorithm>
#include "MyStr.h"

using namespace std;
/*
FUNCTIONS FOR MY STRING CLASS
*/
allocator<char> MyStr::alloc;



//COPY CSTRING CTOR
MyStr::MyStr(const char* cstr){

	auto cstrSize=strlen(cstr);

	//Set pointers and capapcity
	elem=(cstrSize<=init_size)?alloc.allocate(init_size):
	alloc.allocate(cstrSize);
	first_free=elem;
	cap=elem +((cstrSize<=init_size)?init_size:cstrSize);

	// Copy whole cstring to this object
	app_cstr(*this,cstr);
	cout<<"Copy cstring run\n";

}

//COPY STRING CTOR
MyStr::MyStr(const MyStr &str):elem(alloc.allocate(str.capacity())),first_free(elem+str.size()),cap(elem+str.capacity()){
	// Copy whole cstring
	uninitialized_copy(str.begin(),str.end(),elem);
	cout<<"Copy MyStr run\n";
}

//ASSIGNMENT OPERATORS
MyStr& MyStr::operator=(const MyStr& str){
	if(capacity()<str.size()){
		reallocate(str,str.size());
	}else{
		destStr(elem,first_free);
		first_free=uninitialized_copy(str.begin(),str.end(),elem);
	}
	cout<<"Assignment Mystr run\n";
	return *this;	
}

MyStr& MyStr::operator=(const char* cstr){
	if(capacity()<strlen(cstr)){
		reallocate(*this,strlen(cstr));	
	}
	destStr(elem,first_free);
	app_cstr(*this,cstr);
	cout<<"Assignment cstring run\n";
}


//DESTRUCTOR
MyStr::~MyStr(){
	free();
}

void MyStr::destStr(char* beg, char* end){
	for_each(beg,end,[](char &ch){
		alloc.destroy(&ch);
	});
	first_free=elem;
}

//FREE MEMORY
void MyStr::free(){
	destStr(elem,first_free);
	alloc.deallocate(elem,cap-elem);
}

// APPEND CSTRING TO STRING
void MyStr::app_cstr(MyStr &str,const char* cstr){
	while(*cstr!='\0'){
		alloc.construct(str.first_free++,*cstr++);
	}	
}
	
//REALLOCATE STRING
void MyStr::reallocate(const MyStr &str, const size_t &newSize){
	//New empty mem
	char *tmp_elem=alloc.allocate(newSize);
	char *tmp_first_free=tmp_elem;
	char *tmp_cap=tmp_elem+newSize;
	
	//Copy content and update first_free
	tmp_first_free=uninitialized_copy(str.begin(),str.end(),tmp_elem);
	
	//Free old memory
	free();
	
	//Swap pointers
	elem=tmp_elem;
	first_free=tmp_first_free;
	cap=tmp_cap;
}

//ADD TO STRING. REALLOCATE WHEN NEEDS
MyStr MyStr::operator+(const MyStr &str){
	MyStr result(*this);
	
	if(str.size()>(cap-first_free)){
		size_t newSize=size()+str.size();
		result.reallocate(result,newSize);
	}
	
	result.first_free=uninitialized_copy(str.begin(),str.end(),result.end());
	return result;
}

//ADD CSTRING.
MyStr MyStr::operator+(const char* cstr){
	
	//Create new string with proper size
	size_t newSize= size()+strlen(cstr);
	newSize=newSize<=init_size?init_size:newSize;
	MyStr result(newSize);
	
	//Add first string
	result.first_free=uninitialized_copy(elem,first_free,result.elem);
	
	//Add whole cstring to result
	app_cstr(result,cstr);
	return result;
	
}

//OPERATOR << OVERLOAD FOR COUT
ostream& operator<<(ostream& os, const MyStr &str){
	
	char* beg=str.begin();
	while(beg!=str.end()){
		os<<*beg++;
	}
	return os;
}

//PRINT STRING
void MyStr::print()const {
	
	cout<<"[";
	char* beg=begin();
	while(beg!=end()){
		cout<<*beg++;
	}
	cout<<"]"<<endl;
}



//NUMBER OF CHARACTERS IN STRING
size_t MyStr::size()const{
	return first_free-elem;
}

//ADDRESS OF FIRST ELEMENT
char* MyStr::begin()const{
	return elem;
}

//ADDRESS OF ONE PAST LAST ELEMENT
char* MyStr::end()const{
	return first_free;
}

//WHOLE CAPACITY OF STRING
size_t MyStr::capacity()const{
	return cap-elem;
}
