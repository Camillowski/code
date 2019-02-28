/*
StrVec member functions
*/
#include "StrVec.h"


//Static allocator member
allocator<string> StrVec::alloc;


//Default ctor
StrVec::StrVec(){
	
}

//Copy ctor
StrVec::StrVec(const StrVec&){
	
}

//Assignment operator
StrVec StrVec::operator=(const StrVec&){
	
}

//Destructor
StrVec::~StrVec(){
	
}

//MEMBER FUNCTIONS

/*
-Add element at end of constructed memory.
Args: Input string
Return: No
*/
void StrVec::push_back(const string&){

}

/*
-Calculates size of constructed memory
Args: No
Return: Size of connstructed memory
*/
size_t StrVec::size(){
	return first_free-elements;	
	}

/*
Calculates capacity of vector
Args: No
Return: How many strings can vector have.
*/
size_t StrVec::capacity(){
	return cap-elements;
}

/*
Pointers to first and one past elements
Args: No
Return: Pointer to elements
*/
string* StrVec::begin(){
	return elements;
}
string* StrVec::end(){
	return first_free;
	}


//INTERNAL FUNCTIONS

/*
Alloc space and copy range of elements
Args:
Return:
*/
pair<string*,string*> StrVec::alloc_n_copy(string*,string*){

}

/*
Destroy all elements and deallocate space
Args: No
Return: No
*/	
void StrVec::free(){
	
}

/*
Checks if enough space to add object. If not reallocate
Args: No
Return: No
*/
void StrVec::chk_n_alloc(){
	if (size()==capacity()) reallocate();
}

/*
 Realocate vector when out of space
 Args: No
 Return: No
*/
void StrVec::reallocate(){
	
}