#ifndef MYSTR_H
#define MYSTR_H

#include <memory>

class MyStr{
public:
	//CTORS
	MyStr(const size_t &sz=16):elem(alloc.allocate(sz)),first_free(elem),cap(elem+sz){}
	
	MyStr(const char*);
	MyStr(const MyStr&);
	~MyStr();
	MyStr& operator=(const MyStr&);
	MyStr& operator=(const char*);
	
	//FUNCTIONS
	MyStr operator+(const MyStr&);
	MyStr operator+(const char*);
	friend std::ostream& operator<<(std::ostream&, const MyStr&);
	
	size_t size()const;
	size_t capacity()const;
	char* begin()const;
	char* end()const;
	void print()const;
	
private:
	//FUNCTIONS
	void reallocate(const MyStr&, const size_t&);
	void free();
	void destStr(char*, char*);
	void app_cstr(MyStr&,const char*);
	

	
	//DATA MEMBERS
	static std::allocator<char> alloc;
	
	size_t init_size=16;	
	char* elem;
	char* first_free;
	char* cap;
	
	
};

	
#endif