/*
Class StrVec is a class that stores a strings in contigous memory.
It allocates memory and constructs objects only when needed.

REQUIREMENTS:
- Preallocates more storage at the beginning
- When not enough to construct new objects it reallocates, and doubles cap
- Removing element destroys it
- 
*/
#include <memory>

using namespace std;
using Ptr=allocator<string>::pointer;

class StrVec{
public:
	//CTORS
	StrVec();
	StrVec(const StrVec&);
	StrVec operator=(const StrVec&);
	~StrVec();

	//MEMBER FUNCTIONS
	void push_back(const string&); //Add element to end of vec
	size_t size(); //Return size of constructed space
	size_t capacity();//Ret capacity of vector
	string *begin();//Ptr begin of constructed
	string *end(); //One past constructed
	
	
private:
	static allocator<string> alloc; //Allocates memory for vector
	
	//POINTERS
	Ptr elements; //First elem
	Ptr first_free; //First unconstructed
	Ptr cap; //Past end of unconstructed
	
	//INTERNAL FUNCTIONS
	pair<string*,string*> alloc_n_copy(string*,string*); //Alloc space and copy range of elements
	void free(); // Destroy all elements and deallocate space
	void chk_n_alloc(); //Checks if enough space to add object. If not reallocate
	void reallocate(); //Realocate vector when out of space
};