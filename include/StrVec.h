#ifndef STRVEC_H
#define STRVEC_H

#include <memory>
#include <string>
/*
STRVEC CLASS
*/


class StrVec{
public:
	friend void TEST(StrVec&);
	
	//CTORS + ASSIGNMENT
	StrVec():elem(alloc.allocate(init_size)),
		first_free(elem),cap(elem+init_size){}
	StrVec(const StrVec&);
	StrVec(std::initializer_list<std::string>);
	~StrVec();
	StrVec& operator=(const StrVec&);
	

	//FAKE ITERATORS
	std::string* begin() const{return elem;}
	std::string* end() const{return first_free;}
	
	
	//FUNCTIONS
	std::string* push_back(const std::string&);
	std::string* pop_back();
	void resize(size_t);
	bool reserve(size_t);
	size_t size();
	size_t capacity() const;
	bool is_empty(){return elem==first_free?true:false;}
	std::string& at(size_t n);
	

private:
	//PVT FUNCTIONS
	void reallocate(const size_t&);
	void free();
	void dstrElem(std::string*, std::string*);
	
	//DATA MEMBERS
	static std::allocator<std::string> alloc;
	size_t init_size=16;
	
	std::string* elem;
	std::string* first_free;
	std::string* cap;
};

//TESTS 
namespace Test{
	//Check if entering new element works good
	std::string chk_pb(StrVec &svec);
	
	//Check in no overflow when add new elements over curent cap.
	std::string is_overflow(StrVec &svec, int size);
	
	//Check pop_back()
	std::string chk_pop_back(StrVec &svec, int n);
};

//VECTOR OPERATIONS

//Print vector
void printVec(StrVec &svec);

//Fill vector with n elements
void fillVec(StrVec &svec, size_t n);

//Destroy n elements in vector
void destVec(StrVec &svec, size_t n);

//AGREGGATE TEST FUNCTION
void TEST(StrVec &svec);


#endif