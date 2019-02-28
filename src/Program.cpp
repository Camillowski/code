/*
//#include "Game.h"
// #include <list>
// #include <locale>
// #include <deque>
// #include <array>
// #include <forward_list>
// #include <cctype>
// #include <cstring>
// #include <typeinfo>
// #include "Sales_item.h"
// #include <stack>
// #include <algorithm>
// #include <numeric>
// #include <iterator>
// #include <unordered_map>
// #include <cstdlib>

// #include <set>
// #include <map>
// #include <string>
// #include <memory>
// #include <fstream>
// #include <sstream>
// #include "TextQuery.h"
// #include "Sales_data.h"
// #include "MyFcn.h"
// #include "StrVec.h"
*/

#include <iostream>
#include "MyStr.h"
//#include <vector>
// #include <chrono>
// #include <time.h>
// #include <cstdlib>
// #include "MyFcn.h"

using namespace std;


int main() 
{ 
	union union_t{
		 int i; // 4 bytes
		 char c[4]; //1 byte each character
		 struct{
			short hi;	// 2 bytes
			short lo;	// 2 bytes
		 } s;
	};
	
	union_t myUnion;
	myUnion.c[2] = 'z';
	cout<<myUnion.i<<endl;
	cout<<myUnion.s.hi<<endl;
	cout<<myUnion.s.lo<<endl;
	
	enum Monsters {
     Goblin,
     Dragon,
     Lizard
};

Monsters Raghool=Dragon;
Monsters Dorian=Goblin;

cout<<Raghool<<endl;
	return 0; 
} 


//Ex. 14.49
/*
Add a move constructor and move-assignment operator to your StrVec, String, and Message classes.



3. Add to StrVec



//PART 2 Add to MyStr
*/

/*
//PART 1 Add to Message

#include "Ch13_36.h"

void testMoveCtor(){
	Message m1("My Message ctor");
	Folder f1;
	Folder f2;
	m1.save(f1);
	m1.save(f2);
	Message m2(std::move(m1));	
	
	// m2.debug();
	// m1.debug();
	// f1.debug();
	// f2.debug();
	
	if (f1.test().count(&m1)==0 && f1.test().count(&m2)==1)
		cout<<"Message move ctor test PASSED"<<endl;
	else{
		cout<<"Message move ctor test FAILED"<<endl;
		f1.debug();
		m2.debug();
	}
}

void testMoveAssgn(){
	Message m1("My Message that will take new values");
	Message m2("Message being assigned");	
	Folder f1;
	Folder f2;
	m1.save(f1);
	m2.save(f2);
	
	m1=std::move(m2);//Move is to use move assng op. Otherwise copy.
	
	//Test condition
	//	m2 dissapears from folder f2
	//	m1 value dissapears from floder f1
	//  m1 apears in f2.
	if(f2.test().count(&m2)==0 &&
	f2.test().count(&m1)==1 && 
	f1.test().count(&m1)==0){
		cout<<"Message move assignment operator test PASSED"<<endl;
	}
	else{
		cout<<"Message move assignment operator test FAILED"<<endl;
		f1.debug();
		f2.debug();
		m1.debug();
		m2.debug();
	}
}

void testMoveCtorFolder(){
	//Setup
	Message m1("My Message");
	Folder f1;
	m1.save(f1);
	Folder f2(std::move(f1));
	
	//Check test conditions
	if(m1.test().count(&f2)==1 && 
	f1.test().empty()==true && 
	m1.test().count(&f1)==0 && 
	f2.test().count(&m1)==1){
		cout<<"Folder move ctor operator test PASSED"<<endl;
	}
	else{
		cout<<"Folder move ctor operator test FAILED"<<endl;
		cout<<endl;
		f1.debug();
		cout<<endl;
		f2.debug();
		cout<<endl;
		m1.debug();
	}
}

void testMoveAssgnFolder(){
	
	//Setup
	Message m1("My Message");
	Message m2("Kamil Kamil");
	Folder f1;
	m1.save(f1);
	Folder f2;
	m2.save(f2);
	f2=std::move(f1);
	
	//Check 
	if(f2.test().count(&m1)==1 && //If f2 has m1
	f1.test().count(&m1)==0 && //If f1 is empty
	m1.test().count(&f1)==0 && //If m1 has NOT f1
	m1.test().count(&f2)==1){ //If m1 has f2
		cout<<"Folder move assignment PASSED"<<endl;
	}else{
		cout<<"Folder move assignment FAILED"<<endl;
		f1.debug();
		cout<<endl;
		f2.debug();
		cout<<endl;
		m1.debug();
		cout<<&f2<<endl;
	}
}

void TESTS(){
	testMoveCtor();
	testMoveAssgn();
	testMoveCtorFolder();
	testMoveAssgnFolder();
}

int main(){
	
	TESTS();
	
	return 0;
}
*/

//Ex. Experiments with static variables and function pointers
/*
//Create two functions and third that will have fcn ptr as argument.

int add(int a, int b){
	return a+b;
}

int tim(int a, int b){
	return a*b;
}

//Pointer to function
static int result(int x, int y, int(*fcn)(int,int)){
	return fcn(x,y);
}

//Static dont need initialization. Default 0.
static int a;

class statTest {
	static const vector<char> favLtrs;
public:
	void printL(){
		vector<char>::const_iterator begin=favLtrs.begin();
		while(begin!=favLtrs.end())
			cout<<*begin++<<endl;
	}
};

const vector<char> statTest::favLtrs{'a', 'l', 'a'};

int main(){

a=result(5,7,tim);
cout<<a<<endl;

statTest obj;
obj.printL();
}
*/

//Ex. Playing with inheritance
/*
Write an Apple class and a Banana class that are derived from a common Fruit class. Fruit should have two members: a name, and a color.


class Fruit{

public:
	Fruit(string n="", string c=""):name(n),color(c){}
	string getName(){return name;}
	string getColor(){return color;}

private:
	string name;
	string color;
};

class Apple: public Fruit{
public:
	Apple(string c="red", string n="apple"):Fruit(n,c){}
};

class Banana: public Fruit{
public:
	Banana(string c="yellow", string n="banana"):Fruit(n,c){}
};

class GrannySmith: public Apple{
public:
	GrannySmith(string c="green", string n="granny smith apple"):Apple(c,n){}
};

int main()
{
	Apple a("red");
	Banana b;
	GrannySmith c;
	
	cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
	cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
	cout << "My " << c.getName() << " is " << c.getColor() << ".\n";
}
*/

//Ex. Playing with timing execution time of functions
/*

int pot(int p, int w){
	if (w==0)
		return 1;
	else
		return p*pot(p,w-1);

		//return (w==0)?1:(p*pot(p,w-1));
}

int pot2(int p, int w){
	int res=0;
	for(int i=0;i<w;++i)
		res*=p;
	return res;
}

void printXtimes(string s, int tms){
	
	if(tms>0){
		cout<<"[ "<<tms<<" ]\t"<<s<<endl;
		printXtimes(s,tms-1);
	}
}

void printXnor(string s, int tms){
	for (int i=tms;i>=1;--i)
		cout<<"[ "<<i<<" ]\t"<<s<<endl;
}

int main(){
	//cout<<pot(5,5)<<endl;
	
	// auto start=high_resolution_clock::now();
	// //1st fcn
	// //printXtimes("Kamil to miszcz!",10);
	// cout<<"Res1: "<<pot(5,5)<<endl;
	
	// auto stop=high_resolution_clock::now();
	// auto dur=duration_cast<microseconds>(stop-start);
	// cout<<"Function time: "<<dur.count()<<endl;
	
	
	// start=high_resolution_clock::now();
	// //2md fcn
	// cout<<"Res2: "<<pot2(5,10)<<endl;
	// //printXnor("Kamil to miszcz!!",10);
	
	// stop=high_resolution_clock::now();	
	// dur=duration_cast<microseconds>(stop-start);
	// cout<<"Function time: "<<dur.count()<<endl;
	
	cout<<"Now some C stuff!"<<endl;
	
	clock_t start, stop;
	double time;
	uint wyk=1000000;
	start=clock();
	for(uint i=0;i<=wyk;++i)
		pot2(5,10);
	stop=clock();
	time=(double)(stop-start)/CLOCKS_PER_SEC*1000;
	cout<<"Function time: "<<time<<endl;
	
	start=clock();
	for(uint i=0;i<=wyk;++i)
		pot(5,10);
	stop=clock();
	time=(double)(stop-start)/CLOCKS_PER_SEC*1000;
	cout<<"Function time: "<<time<<endl;
}\
*/

//Ex.13.44
/*
Write a class named String that is a simpliﬁed version of the library
string class. Your class should have at least a default constructor and a constructor that takes a pointer to a C-style string. Use an allocator to allocate memory that your String class uses.

Files: MyStr.h and MyStr.cpp

int main(){

MyStr s2("Kamil cccc sssssxx dsaftrfs");
MyStr s1(s2);
MyStr s3(" to jest Mistrzunio!!!!!!");

//s2.print();
MyStr s4(s1);
//s4.print();
//cout<<s4.size()<<" "<<s4.capacity()<<endl;
//cout<<s4+" A to jest kolejna linijka!\nJoł!"<<endl;

MyStr s5=s4;

//cout<<s5+" is a New String\n";
cout<<s5.size()<<" "<<s5.capacity()<<endl;
s5="Camillowski to Miszcz nad miszczami i rodzajamiLALALA!";
cout<<s5<<endl;
cout<<s5.size()<<" "<<s5.capacity()<<endl;
//cout<<s4<<endl;
}
*/

//Ex.13.43
/*
Rewrite the free member to use for_each and a lambda (§ 10.3.2,
p. 388) in place of the for loop to destroy the elements. Which implementation do you prefer, and why?

#include <algorithm>
//DESTROY OBJECTS AND FREE SPACE
void StrVec::free(){
	//Destroy objects
	
	for_each(begin(),end(),[](string &str)->void{
		alloc.destroy(&ptr);
	})
	//Deallocate mem
	alloc.deallocate(elem,cap-elem);
}
*/

//Ex.13.42
/*
Test your StrVec class by using it in place of the vector<string>
in your TextQuery and QueryResult classes (§ 12.3, p. 484).

//#include "StrVec.h"
//#include "TextQuery.h"
// #include <fstream>
// #include <sstream>

void runQueries(ifstream &infile){
	TextQuery tq(infile);
	while(true){
		cout<<"Enter word or q to quit: ";
		string word;
		if(!(cin>>word) || word=="q") break;
		print(cout,tq.query(word));
		cin.ignore(numeric_limits<streamsize>::max(),'\n').clear();
	}
}
int main(){
	ifstream fstrm(flText);
	runQueries(fstrm);	
}
*/

//Ex. Create own string vector
/*
Learned:
When pass pointer to function it is a copy of pointer. When changed it wont affect original.
Create own vector that will hold data, dynamicaly allocate memory and have some operations the same as regular vector.

DONE Check StrVec.h and StrVec.cpp
*/

//Ex. Copy-Control Example
/*
#include "Ch13_36.h"

Create two classes. Folder and Message class.
Main idea is to connect those two classes together and create proper working functions for them. First I will start with Message class.

REQUIREMENTS
Message:
-One copy of string message. VALUE
-Apear in many folders
-When change is made, it is visible the same in all folders
-Has set of pointers to folders where it appears.
-Create with message but without putting to folder
OPS:
-Save - to put message to folder
-Remove - to remove message from folder
-Copying - Makes two separate messages(text) but both are in the same folders. 
	1. Copy set of pointers to new message.
	2. Insert ptr to new message to all folders.
-Destroing - 
	1. Remove message from all folders
-Assign - msg1 = msg2
	1. Copy text from msg2 to msg1
	2. Remove msg1 from all it's folders.
	3. Copy msg2 folders to msg1
	4. Add msg1 to folders
-Create two private functions which add and remove from folders.
	1. addToFolder for copy ctor and copy assignment
	2. remFromFolder for destructor and copy assignment


Folder:
-Store set of pointers to all messages it includes.
-addMsg - Adds message to set of messages
-remMsg - Removes message from set
-Copy-control => Create functions that Add and remove from all mesages


int main(){
	
	Message m1("Message 1");
	Message m2("Message 2");
	Folder f1;
	Folder f2;
	
	m1.save(f1);
	m1.save(f2);
	m2.save(f2);
	m1.debug();
	m2.debug();
	return 0;
}
*/

//Ex. Messing with binary search trees TO CONTINUE! FIX!
/*
Make Recursive mode


class Node{
	private:
	//public:
		int data;
		Node* left;
		Node* right;
	
	public:
		Node(const int &d=0):data(d),left(nullptr),right(nullptr){}
		~Node(){
			if(left!=nullptr){
				delete left;
				//cout<<"Value "<<data<<" Left deleted"<<endl;
			}
			if(right!=nullptr){
				delete right;
				//cout<<"Value "<<data<<" Right deleted"<<endl;
			}
			//cout<<"Deleted node with value: "<<data<<endl;
		}
		bool operator<(const Node &rhs){return data<rhs.data;}
		bool operator==(const Node &rhs){return data==rhs.data;}
		
		//Getters and setters. Interface.
		int getData(){return data;}
		Node& setData(int d){ data=d; return *this;}
		
		Node*& getLeft(){ return left;}
		Node& setLeft(Node *l){left=l; return *this;}
		
		Node*& getRight(){ return right;}
		Node& setRight(Node *r){right=r; return *this;}
};


class Tree{
	//private:
	public:
		Node *root;
		int levels;
		string name;
		static int count;
		
	public:
		Tree():root(nullptr), levels(0), name("Tree "+to_string(count++)){};
		Tree(initializer_list<int> il):root(nullptr), levels(0),name("Tree "+to_string(count++)){
			for(auto el:il){
				this->addNode(el);
				//cout<<"Node "<<el<<" initialized.\n";
			}
		}
		
		~Tree(){delete root;}
	
		Tree& addNode(int);
		Tree& addNodeRec(int, Node*&);
		Tree& remNode(Node&);
		
		void printTree();

};

int Tree::count=0;

//STUFF TO AVOID?
Tree& Tree::addNode(int nodeVal){
	Node *temp=new Node(nodeVal);
	Node **curr;
	curr=&root;//curr contains address of root
	//Check if empty
	while(true){
		if(*curr==nullptr){
			*curr=temp; //If empty then set L/R pointer to new node
			cout<<name<<" Node added:\t"<<(*curr)->getData()<<endl;
			break;
		}else if(*temp==**curr){
			//cout<<"Node "<<temp->getData()<<" exists. Procdure aborted.";
			break;
		}		
		else{
			if(temp<(*curr)){ //Travel L/R
				//cout<<"Prev data: "<<(*curr)->getData()<<endl;
				curr=&(*curr)->getLeft(); //Make curr to point to *left
				//cout<<"Go left\n";
			}else{
				//cout<<"Prev data: "<<(*curr)->getData()<<endl;
				curr=&(*curr)->getRight();
				//cout<<"Go right\n";
			}
		}
	}
	return *this;
}



//Recurent version of addNode()
void Tree::addNodeRec(int nodeVal, Node *&curr){

		if(*curr==nullptr){
			*curr=new Node(nodeVal);
			break;
		}else if(nodeVal==(*curr)->getData()){
			break;
		}		
		else{
			if(nodeVal<(*curr)->getData()){
				addNodeRec(nodeVal,curr->getLeft())
			}else{
				addNodeRec(nodeVal,curr->getRight())
			}
		}
	}
}	

Tree& Tree::remNode(Node &node){
	//Leaf node
	
	//One child node
	
	//Two children node
	
	//Print if node does not exist.
	return *this;
}

void Tree::printTree(){
	//Traverse and print
}
	
//Create function to add a node DONE
//Create constructor to take init list and create a tree. DONE
//Prevent from adding node with the same value DONE
//Transform addNode to recurent version.
//Create function to delete node
//Function to print tree sorted.
//Create function to search tree for value.


//Create function that will take a number and print all range from 0 to the number.
void recurent(int start){
	if (start>0){
		recurent(--start);
		cout<<start<<endl;
	}
}

//Create silnia function that takes number and print silnia.
int silnia(int n){
	//ITERATION VERSION
	// int suma=1;
	// for (int i=1;i<=n;++i){
		// suma=suma*i;
	// }
	if(n==1)
		return 1;
	int sum=n*silnia(n-1);
	return sum;
}

int main(){
	
	Tree t1;
	//cout<<"1 node\n";
	t1.addNode(10);
	//cout<<"2 node\n";
	t1.addNode(9);
	//cout<<"3 node\n";
	t1.addNode(8);
	t1.addNode(15);
	t1.addNode(20);
	Tree t2{3,4,5,6,7,8};
	t2.addNode(3);
	Tree t3{33};
	
	//recurent(10);
	cout<<"Silnia: "<<silnia(10);
	
	// cout<<"\nTests of access:\n";
	// cout<<"Root: "<<t1.root->getData()<<endl;
	// cout<<"1st node: "<<t1.root->getLeft()->getData()<<endl;
	// cout<<"2nd node: "<<t1.root->getLeft()->getLeft()->getData()<<endl;
	
}
*/


//Ex.13.30 + 13.31
/*
13.30
Write and test a swap function for your valuelike version of HasPtr.
Give your swap a print statement that notes when it is executed.

13.31
Give your class a < operator and deﬁne a vector of HasPtrs. Give
that vector some elements and then sort the vector. Note when swap is called.



class HasPtr {
	public:
	//Default ctor
	HasPtr(const std::string &s = std::string()):ps(new std::string(s)), i(0) { }
	
	//Copy constructor
	HasPtr(const HasPtr &hp):ps(new string(*hp.ps)),i(hp.i){}
	
	//Destructor
	~HasPtr(){
		delete ps;
	}
	
	//Assignment operator
	HasPtr& operator=(const HasPtr &rhs){
		delete ps;//Dealocate memory held before
		ps=new string(*rhs.ps); //Allocate new mem and initialize it with value from rhs
		i=rhs.i;
		
		return *this;
	}
	
	//<operator FIX!
	bool operator<(HasPtr &rhs){
	return *this->ps<*rhs.ps;
	}
	
	friend void swap(HasPtr&, HasPtr&);
	
	//private:
	std::string *ps;
	int i;
};

void swap(HasPtr &lhs, HasPtr &rhs){
		using std::swap;
		swap(lhs.ps,rhs.ps);
		swap(lhs.i, rhs.i);
}
int main(){
	HasPtr ob1("Kamil");
	HasPtr ob2("Wiki");
	//swap(ob1,ob2);
	cout<<(ob1<ob2);
	
	cout<< *ob1.ps<<" "<<*ob2.ps;
}
*/

//Ex.13.28 FIX!
/*
Given the following classes, implement a default constructor and the
necessary copy-control members.

TreeNode
- Treat like pointer. When copied
- 
BinStrTree
- Treat like a value

class TreeNode{
	public:
		//Default
		TreeNode(const string &st=string(), const int &i=1):value(st), coun(i), left(nullptr),right(nullptr){}
		
		//Copy
		TreeNode(const TreeNode &tr): value(tr.value), count(tr.count), left(tr.left), right(tr.right) {}
		
		//Assignment FIX
		TreeNode& operator=(const TreeNode &rhs){
			if(count==0){
				delete count;
		}
		
		//Destructor FIX
	
	private:
		string value;
		int *count;
		TreeNode *left;
		TreeNode *Right;
};

//Treat like value
class BinStrTree{
	public:
	//Default
	BinStrTree(const TreeNode &r=TreeNode()):root(new TreeNode(r)){};
	
	//Copy
	BinStrTree(const BinStrTree &bst):root(new TreeNode(*bst.root)){}
	
	//Operator FIX
	BinStrTree& operator=(const BinStrTree &rhs){
		*root=*rhs.root;
		
		return *this;
	}
	//Destructor FIX
	~BinStrTree(){
		delete root;
	}
	
	private:
		TreeNode *root;
};

int main(){

}
*/

//Ex.13.27
/*
Deﬁne your own reference-counted version of HasPtr.

Make HasPtr pointer like.
- When copied/assigned it will share dynamic memoy with new object.
- Implement counter so when object is copied cnt goes up, and when destroyed/assigned it goes down.

Make:
- Default ctor to create dyn counter
- Copy ctor to copy ptr and increase cter
- Assign to delete one string, assign other and add and reduce cntr in both objects
- Destructor to check if there are other objects pointing to given mem before deleting it.


class HasPtr {
	public:
	//Default ctor
	HasPtr(const string &s = string()):ps(new string(s)),use(new size_t(1)), i(0) { }
	
	//Copy constructor
	HasPtr(const HasPtr &hp):ps(new string(*hp.ps)),use(hp.use),i(hp.i){++*use;}
	
	//Assignment operator
	HasPtr& operator=(const HasPtr &rhs){
		
		++*rhs.use;
		if(--use==0){ //What if counter goest to 0? Obj is deleted
			delete use;
			delete ps;
		}
		
		ps=new string(*rhs.ps); //Allocate new mem and initialize it with value from rhs
		use=rhs.use;
		i=rhs.i;
		
		return *this;
	}
	
	//Destructor
	~HasPtr(){
		if(--use==0){
			delete ps;
			delete use;
		}
	}
	
	string *ps;
	size_t *use;
	int i;
};

int main(){
	HasPtr ob1("Kamil"),ob3;
	HasPtr ob2(ob1);
	cout<<"ob1 "<<*ob1.use<<" ob2 "<<*ob2.use<<" ob3 "<<*ob3.use<<endl;
	ob3=ob2;
	cout<<"ob1 "<<*ob1.use<<" ob2 "<<*ob2.use<<" ob3 "<<*ob3.use;
}
*/

//Ex.13.26
/*
 Write your own version of the StrBlob class described in the previ-
ous exercise.

Improvements to class are made:
- Copy ctor to treat StrBlob like a value
- Assignment operator made the same way.



int main(){

StrBlob ob1({"Kamil","Wiktor"}), ob2;
ob2=ob1;
cout<<ob2.front();
StrBlob ob3(ob2);
}
*/

//Ex.13.18 + 13.19
/*
Deﬁne an Employee class that contains an employee name and a
unique employee identiﬁer.
Give the class a default constructor
and a constructor that takes a string representing the employee’s name. Each constructor should generate a unique ID by incrementing a static data member.


class Employee{
	public:
	static int unique;
	
	//Ctors
	Employee():id(unique++){}
	Employee(const string &n):name(n), id(unique++){}
	
	private:
	string name;
	int id;

};

int Employee::unique=0;

int main(){
Employee e1,e2,e3,e4;
cout<<Employee::unique;
}
*/

//Ex.13.16
/*
Write versions of numbered and f corresponding to the previous
three exercises and check whether you correctly predicted the output.

//13.14 - No copy-control ctors
class Numbered{
	public:
	//Default
	Numbered():mysn(rand()){}

	private:
	
	int mysn;
	friend void f(Numbered s);
};

void f (Numbered s) { cout << s.mysn << endl; }


//13.15 - With only copy ctor.
class Numbered{
	public:
	//Default
	Numbered():mysn(rand()){}
	
	//Copy
	Numbered(Numbered &nr):mysn(rand()){}

	private:
	//Data
	int mysn;
	friend void f(Numbered s);
};
void f (Numbered s) { cout << s.mysn << endl; }

//13.16 - With reference in function
class Numbered{
	public:
	//Default
	Numbered():mysn(rand()){}
	
	//Copy
	Numbered(Numbered &nr):mysn(rand()){cout<<"copy ctor\n";}

	
	//Data
	int mysn;
	friend void f(const Numbered &s);
};
void f (const Numbered &s) { cout << s.mysn << endl; }
int main(){
	srand(time(NULL));
	Numbered a, b=a, c=b;
	cout<<a.mysn<<" "<<b.mysn<<" "<<c.mysn<<endl;
	f(a);
	f(b);
	f(c);
}
*/

//Ex.13.12
/*
Add the copy-assignment operator and destructor to X and write a program using X objects in various ways:
- Pass them as nonreference and reference parameters;
- dynamically allocate them;
- put them in containers; and so forth.
Study the output until you are certain you understand when and why each copy-control member is used.
As you read the output, remember that the compiler can omit calls to the copy constructor.


struct X{
	//Regulat ctor
	X(const string st="Default "):s(st){ cout<<"X() "<<s<<endl;}
	
	//Copy ctor
	X(const X &x){
		cout<<"X(const X&) Copy"<<s<<endl;
		s=x.s;}
	
	//Copy asignment operator
	X& operator=(const X &rhs){
		cout<<"X& operator=() "<<endl;
		s=rhs.s;
		return *this;
	}
		
	//Destructor
	~X(){cout<<"~X() "<<s<<endl;}
	
	//Data field
	string s;
	
};

void nonref(X x){
	cout<<"nonref"<<endl;
}
void ref(X &x){
	cout<<"ref"<<endl;
}


int main(){
	X *ptr=new X("Dynamic");//Dynamic mem
	shared_ptr<X> shptr=make_shared<X>("Shared"); //Shared ptr
	vector<X> vec(5,X("Vector")); //Vector
	X ob1("Regular"); //Regular instantiation
	
	cout<<"asign"<<endl;
	X ob2;
	ob2=ob1; //Assign ctor
	X ob3(ob1);
	nonref(ob2); //Non ref passed as argument
	ref(ob2); //Ref passed as argment
	
	cout<<"\n deletion:\n";
	delete ptr;
}
*/

//Ex.13.11
/*
Add a destructor to your HasPtr class from the previous exercises.


class HasPtr {
	public:
	HasPtr(const std::string &s = std::string()):ps(new std::string(s)), i(0) { }
	//Copy constructor
	HasPtr(const HasPtr &hp):ps(new string(*hp.ps)),i(hp.i){}
	
	//Destructor
	~HasPtr(){
		delete ps;
	}
	
	//Assignment operator
	HasPtr& operator=(const HasPtr &rhs){
		delete ps;//Dealocate memory held before
		ps=new string(*rhs.ps); //Allocate new mem and initialize it with value from rhs
		i=rhs.i;
		
		return *this;
	}
	
	private:
	std::string *ps;
	int i;
};
*/

//Ex.13.5 + 13.8 + 13.22
/*
 Given the following sketch of a class, write a copy constructor that
copies all the members. Your constructor should dynamically allocate a new string (§ 12.1.2, p. 458) and copy the object to which ps points, rather than copying ps itself.

Write the assignment operator for the HasPtr class from exercise 13.5
in § 13.1.1 (p. 499). As with the copy constructor, your assignment operator should copy the object to which ps points.



class HasPtr {
	public:
	//Default ctor
	HasPtr(const string &s = string()):ps(new string(s)), i(0) { }
	
	//Copy constructor
	HasPtr(const HasPtr &hp):ps(new string(*hp.ps)),i(hp.i){}
	
	//Assignment operator
	HasPtr& operator=(const HasPtr &rhs){
		string *temp=new string(*rhs.ps); //Allocate new mem and initialize it with value from rhs
		
		delete ps;//Dealocate memory held before
		ps=temp;
		i=rhs.i;
		
		return *this;
	}
	
	//Destructor
	~HasPtr(){
		delete ps;
	}
	
	private:
	std::string *ps;
	int i;
};
*/

//Ex.12.33
/*
In Chapter 15 we’ll extend our query system and will need some addi-
tional members in the QueryResult class.

1. Add members named begin and end that return iterators into the set of line numbers returned by a given query.
(iters to set) 

2. Add member named get_file that returns a shared_ptr to the ﬁle in the QueryResult object. (to vector with lines)


int main(){
//Check class for more details
}
*/

//Ex.12.32
/*
Rewrite the TextQuery and QueryResult classes to use a StrBlob
instead of a vector<string> to hold the input ﬁle.
*/

/*
class TextQuery;
class QueryResult{
	public:
	//ctors
	QueryResult(){}//Default Ctor
		
	private:
	string srch_word;
	shared_ptr<set<int>> lineNr;//Lines numbers
	StrBlob fileVec; //text lines
	
	friend void print(ostream&, QueryResult);
	friend class TextQuery;
};

void print(ostream &os, QueryResult res){
	//If no word found
	if(res.lineNr==nullptr){
		os<<"No word "<<res.srch_word<<endl;
		return;
	}
	
	os<<"Word \""<<res.srch_word<<"\" occurs in "<<res.lineNr->size()<<" lines:"<<endl;
	
	//Print lines from file
	StrBlobPtr begBlob=res.fileVec.begin();
	
	//StrBlobPtr endBlob=res.fileVec.end();
	auto begin=res.lineNr->begin();
	int cnt=0;
	while(begBlob!=res.fileVec.end()){
		if(*begin==cnt){
			cout<<"(line #"<<*begin+1<<"): "<<begBlob.deref()<<endl<<endl;
			++begin;
		}
		++cnt;
		begBlob.incr();
	}
}

class TextQuery{
	//What it does?
		//Create map with words and lines, search and prints lines coresonding to searched wors
	
	public:
		
	//ctor that fills in vector and map
	TextQuery(istream& is);
	
	//Functions
	QueryResult query(string);//Takes map and vector and Return Queryresult

	
	private:
	//string srch_word;
	StrBlob fileVec; //text lines
	map<string,shared_ptr<set<int>>> wordMap;//Takes set
	
	friend class QueryResult;
};


TextQuery::TextQuery(istream& is){
	//fileVec=make_shared<vector<string>>(); //optional assignment
	//fileVec.reset(new StrBlob);
	
	//Fill in vector
	string line;
	while(getline(is,line)){
		fileVec.push_back(line);
	}
	
	//Fill in the map
	auto begin=fileVec.begin();
	size_t line_no=0;
	while(begin!=fileVec.end()){
		istringstream sstrm(begin.deref());
		//size_t line_no=begin-fileVec->begin();
		
		string word;
		while(sstrm>>word){
			
			if(wordMap[word]==nullptr) //If shared_ptr empty...
				wordMap[word].reset(new set<int>); //Allocate new set
			wordMap[word]->insert(line_no);
		}
		begin.incr();
		++line_no;
	}
}

QueryResult TextQuery::query(string srch_word){
	QueryResult res;
	res.srch_word=srch_word;
	
	auto found=wordMap.find(srch_word);
	if(found!=wordMap.end()){
		res.lineNr=found->second;
		res.fileVec=fileVec;
	}
	
	return res;
}

void runQueries(ifstream &infile){
	TextQuery tq(infile);
	while(true){
		cout<<"Enter word or q to quit: ";
		string word;
		if(!(cin>>word) || word=="q") break;
		print(cout,tq.query(word));
		cin.ignore(numeric_limits<streamsize>::max(),'\n').clear();
	}
}
int main(){
	ifstream fstrm(flText);
	runQueries(fstrm);
}
*/

//Ex.12.30
/*
Deﬁne your own versions of the TextQuery and QueryResult
classes and execute the runQueries function from § 12.3.1 (p. 486).


class TextQuery;
class QueryResult{
	//What it does?
		//Hold data returned by query fcn in TextQuery class
	public:
	//ctors
	QueryResult(){}//Default Ctor
	//QueryResult(TextQuery &tq):lineNo(tq.wordMaplineNo), fileVec(tq.fileVec){}
	
	private:
	string srch_word;
	shared_ptr<set<int>> lineNr;//Lines numbers
	shared_ptr<vector<string>> fileVec; //text lines
	
	friend void print(ostream&, QueryResult);
	//friend QueryResult TextQuery::query(string);
	friend class TextQuery;
};

void print(ostream &os, QueryResult res){
	if(res.lineNr==nullptr){
		os<<"No word "<<res.srch_word<<endl;
		return;
	}
	os<<"Word "<<res.srch_word<<" occurs in "<<res.lineNr->size()<<" lines:"<<endl;
	auto begin=res.lineNr->begin();
	//cout<<*begin;
	while(begin!=res.lineNr->end()){
		cout<<"(line #"<<*begin+1<<"): "<<res.fileVec->at(*begin)<<endl<<endl;
		++begin;
	}
}

class TextQuery{
	//What it does?
		//Create map with words and lines, search and prints lines coresonding to searched wors
	
	public:
		
	//ctor that fills in vector and map
	TextQuery(istream& is);
	
	//Functions
	QueryResult query(string);//Takes map and vector and Return Queryresult

	
	private:
	//string srch_word;
	shared_ptr<vector<string>> fileVec; //text lines
	map<string,shared_ptr<set<int>>> wordMap;//Takes set
	
	friend class QueryResult;
};


TextQuery::TextQuery(istream& is){
	//fileVec=make_shared<vector<string>>(); //optional assignment
	fileVec.reset(new vector<string>);
	
	//Fill in vector
	string line;
	while(getline(is,line)){
		fileVec->push_back(line);
	}
	
	//Fill in the map
	auto begin=fileVec->begin();
	while(begin!=fileVec->end()){
		istringstream sstrm(*begin);
		size_t line_no=begin-fileVec->begin();
		
		string word;
		while(sstrm>>word){
			
			if(wordMap[word]==nullptr) //If shared_ptr empty...
				wordMap[word].reset(new set<int>); //Allocate new set
			wordMap[word]->insert(line_no);
			}
		++begin;
	}
}

QueryResult TextQuery::query(string srch_word){
	QueryResult res;
	res.srch_word=srch_word;
	
	auto found=wordMap.find(srch_word);
	if(found!=wordMap.end()){
		res.lineNr=found->second;
		res.fileVec=fileVec;
	}
	
	return res;
}

void runQueries(ifstream &infile){
	TextQuery tq(infile);
	while(true){
		cout<<"Enter word or q to quit: ";
		string word;
		if(!(cin>>word) || word=="q") break;
		print(cout,tq.query(word));
		cin.ignore(numeric_limits<streamsize>::max(),'\n').clear();
	}
}
int main(){
ifstream fstrm(flText);
runQueries(fstrm);
}
*/

//Ex.12.29
/*
We could have written the loop to manage the interaction with the
user as a do while (§ 5.4.4, p. 189) loop. Rewrite the loop to use a do while. Explain which version you prefer and why.


void runQueries(ifstream &infile)
{
	TextQuery tq(infile);
	do {
		cout << "enter word to look for, or q to quit: ";
		string s;
		if (!(cin >> s) || s == "q") break;
		print(cout, tq.query(s)) << endl;
	}while(true);
}
//Do while looks better!
*/

//Ex.12.28
/*
Write a program to implement text queries without deﬁning classes to
manage the data.
Your program should take a ﬁle and interact with a user to query for words in that ﬁle. 
Use vector, map, and set containers to hold the data for the ﬁle and to generate the results for the queries

//SOLUTION #1
map<int,string> query(const string &search, const vector<string> &input, int &found){
	//process element(line) in vector
		//Look if it contain word
	
	size_t size=input.size();
	map<int,string> out;
	
	for (int i=0; i<size;i++){
		istringstream sstream(input[i]);
		
		//Do the magic with map and set
		string word;
		while(sstream>>word){
			if(search==word){
				found++;
				out[i]=input[i];
			}
		}
	}
	return out;
}

int main(){

	//Fill vector with file
	ifstream infile(flText);
	vector<string> input;
	string line;
	while(getline(infile,line))
		input.push_back(line);

	//Keep asking user for word until nothing or q
	do{
		cout<<"Please enter word to search or q to exit: ";
		string word;
		if(!(cin>>word) || (word=="q")){
			cout<<"End of program";
			break;
		}
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
		cin.clear();
		
		int found=0;
		//run query
		map<int,string> output=query(word,input,found);
		
		//Print result
		cout<<"\n\""<<word<<"\" occured "<<found<<" times."<<endl;
		for(auto el:output)
			cout<<" (line# "<<el.first<<"): "<<el.second<<endl<<endl;
		cout<<endl;
	}while(true);

}
*/

/*
//SOLUTION #2
//Map all words to sets containing line nr.
//Search by word->return set of line nrs-> print lines designated by set

using Map=map<string,set<int>>;

string enterWord(){
	cout<<"Please enter word to search or q to exit: ";
	string word;
	cin>>word;
	
	cin.ignore(numeric_limits<streamsize>::max(),'\n');
	cin.clear();
	
return word;	
}

vector<string> fillVec(const string &file){
	//Fill in the vector
	ifstream fstrm(file);//Check for exception
	vector<string> lineVec;
	string line;
	while(getline(fstrm,line))
		lineVec.push_back(line);
	
	return lineVec;
}
	
Map createMap(const string &file, vector<string> &lineVec){
	Map fileMap;
	
	for(int i=0; i<lineVec.size();++i){
		istringstream sstrm(lineVec[i]);
		string lineWord;
		while(sstrm>>lineWord){
			fileMap[lineWord].insert(i);
		}
	}
	
	return fileMap;
}

void print(Map &fileMap,const vector<string> &lineVec,const string &word){
	//ptr to pair with key and set
	auto lineSet=fileMap.find(word);
	
	//If word not found end print
	if(lineSet==fileMap.end()){
		cout<<"Word not found\n";
		return;
	}
	
	//Cout first line. How many lines will be there
	cout<<word<<" occured in "<<fileMap[word].size()<<" lines."<<endl;
	
	//cout<<*(lineSet->second.begin())<<*fileMap[word].begin();
	
	//Print each line
	for(auto iter=fileMap[word].begin(); iter!=fileMap[word].end();++iter){
		cout<<" (line #"<<*iter+1<<") "<<lineVec[*iter]<<endl;
	}
	cout<<endl;
}

int main(){
	
	string file=flText;
	
	string word;
	vector<string> lineVec=fillVec(file);
	cout<<lineVec[7];
	//Create map
	Map fileMap=createMap(file,lineVec);
	
	do{
		word=enterWord();
		if(word=="q" || word.empty()){
			cout<<"Input failure\n";
			return 0;
		}
		
		//Print output
		print(fileMap,lineVec,word);
		
	}while(true);
	return 0;
}
*/

//Ex.12.27
/*
The TextQuery and QueryResult classes use only capabilities that
we have already covered. Without looking ahead, write your own versions of these classes.

Program to search in a loaded file for apearances of the word.
When found:
	-print #of occureces
	-Print line #
	-print whole line.
Do not repeat lines when word apears more than once
lines go ascending from low to high

Read line at time and precess line by words.


Output:
Occurences: 23
	(line #) Text text text
	(line #) Another text


class QueryResult{
	//What it does?
		//Hold data returned by query fcn in TextQuery class
	
	//ctors
	QueryResult(){}//Default Ctor
	QueryResult(TextQuery &tq):lineNs(tq.lineNs), fileVec(tq.fileVec){}
	
	void print(TextQuery); //Prints query result
	
	private:
	shared_ptr<set<int>> lineNs;//Lines numbers
	shared_ptr<vector<string>> fileVec; //text lines
};

class TextQuery{
	//What it does?
		//Create map with words and lines, search and prints lines coresonding to searched wors
	
	public:

	
	//ctor that fills in vector
	TextQuery(istream& is):{}
	
	//Functions
	QueryResult query(wordMap,fileVec);//Takes map and vector and Return Queryresult

	
	private:
	string file;
	shared_ptr<set<int>> lineNs;//Lines numbers
	shared_ptr<vector<string>> fileVec; //text lines
	map<string,set<int> wordMap;//Takes set
	
	friend class QueryResult;
};
*/

//Ex.12.26
/*
 Rewrite the program on page 481 using an allocator.
 
	string *const p = new string[n];
	string s;
	string *q = p;
	while (cin >> s && q != p + n)
	*q++ = s;
	const size_t size = q - p;
	delete[] p;


int main(){
	//create alloc
	//create ptr to begin
	//create ptr to end
	//loop cin>>construct till fail or end
	//ptr diff to delete objects
	//dealocate mem
	
	allocator<string> alloc;
	size_t size=100;
	
	auto const begin=alloc.allocate(size);
	auto end=begin;
	
	alloc.construct(end);
	while(cin>>*end && (end-begin)<size){
		alloc.construct(++end);
	}
	
	//Printing and destroy
	for(;end>=begin;--end){
		cout<<*end<<" ";
		alloc.destroy(end);
	}
	
	//Deallocate
	alloc.deallocate(begin,size);
}
*/

//Ex.12.24
/*
Write a program that reads a string from the standard input into a
dynamically allocated character array.
Describe how your program handles varying size inputs. Test your program by giving it a string of data that is longer than the array size you’ve allocated.


int main(){
	size_t size=100;
	char *buff=new char[size]; // Use a buffer
	
	cin.getline(buff,size);
	char *str= new char[strlen(buff)+1];
	strcpy(str,buff);
	
	cout<<str;
	delete [] buff;
	delete [] str;
}
*/

//Ex.12.23
/*
Write a program to concatenate two string literals, putting the result
in a dynamically allocated array of char. Write a program to concatenate two library strings that have the same value as the literals used in the ﬁrst program.


char* concatLit(const char* str1, const char* str2){
	//check size of t strings
	size_t size=strlen(str1) + strlen(str2);
	
	//create dynamic array. Check if size of strings is enough or need to add space for '\0'?
	char *result= new char[size+1];//+1 is for '\0'
	
	//Fill array with two strings.
	strcpy(result,str1);
	strcat(result, str2);
	cout<<result<<endl;
	
	return result;
}

string concatStr(const string &str1, const string &str2)
{
	string result= str1 + str2;
	cout<<result;
	return result;
}
int main(){
	concatLit("Kamil", "Wiktor");
	concatStr("Kamil", "Wiktor");
}
*/

//Ex.12.22
/*
What changes would need to be made to StrBlobPtr to create a class
that can be used with a const StrBlob? Deﬁne a class named ConstStrBlobPtr
that can point to a const StrBlob.


class StrBlobPtr{
	public:
	//ctors
	StrBlobPtr():curr(0){}
	StrBlobPtr(const StrBlob &a, size_t sz=0):wptr(a.data), curr(sz){}
	
	//fcns
	string deref();
	StrBlobPtr& incr();
	friend bool operator!=(StrBlobPtr&, StrBlobPtr&);
	
	
	private:
	shared_ptr<vector<string>> check(size_t,const string&);
	weak_ptr<vector<string>> wptr;
	size_t curr;
	
	
};

shared_ptr<vector<string>>
StrBlobPtr::check(size_t sz, const string &msg){
	//Check if there is shared pointer and if element exists
	shared_ptr<vector<string>> ret=wptr.lock();
	if(!ret)
		throw runtime_error("No pointer");
	if(sz>=ret->size())
		throw out_of_range(msg);
	
	return ret;
}

string StrBlobPtr::deref(){
	auto ret=check(curr,"No element");
	return (*ret)[curr];
}

StrBlobPtr&  StrBlobPtr::incr(){
	check(curr,"No element");
	++curr;
	return *this;
}

bool operator!=(StrBlobPtr &lhs, StrBlobPtr &rhs){
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
	cout<<ptr.deref()<<endl;
	
}

int main(){

	const StrBlob b1({"Lorem","Ipsum"});
	StrBlobPtr ptr1(b1);
	printBlob(b1);
}
*/

//Ex.12.19 + 12.20 + 12.22
/*
12.19)
Deﬁne your own version of StrBlobPtr and update your StrBlob
class with the appropriate friend declaration and begin and end members.

12.20)
Write a program that reads an input ﬁle a line at a time into a StrBlob
and uses a StrBlobPtr to print each element in that StrBlob.
-----------------------------

What Is StrBlobPtr for?
Access vector by pointer. Dereference etc.
To prevent user from accesing non existent element in vector made by StrBlob.

What I need?

-ctors
	+default
	+pointer assigned
-member fcns
	+check if accesible
	+dereference ptr
	+increment- traverse trough vector
-data members
	+elem index
	+weakptr to vector

	
class StrBlobPtr{
	public:
	//ctors
	StrBlobPtr():curr(0){}
	StrBlobPtr(StrBlob &a, size_t sz=0):wptr(a.data), curr(sz){}
	
	//fcns
	string deref();
	StrBlobPtr& incr();
	friend bool operator!=(StrBlobPtr&, StrBlobPtr&);
	
	
	private:
	shared_ptr<vector<string>> check(size_t,const string&);
	weak_ptr<vector<string>> wptr;
	size_t curr;
	
	
};

shared_ptr<vector<string>>
StrBlobPtr::check(size_t sz, const string &msg){
	//Check if there is shared pointer and if element exists
	shared_ptr<vector<string>> ret=wptr.lock();
	if(!ret)
		throw runtime_error("No pointer");
	if(sz>=ret->size())
		throw out_of_range(msg);
	
	return ret;
}

string StrBlobPtr::deref(){
	auto ret=check(curr,"No element");
	return (*ret)[curr];
}

StrBlobPtr&  StrBlobPtr::incr(){
	check(curr,"No element");
	++curr;
	return *this;
}

bool operator!=(StrBlobPtr &lhs, StrBlobPtr &rhs){
	return (lhs.curr!=rhs.curr); 
}

StrBlobPtr StrBlob::begin(){
	return StrBlobPtr(*this);
};
StrBlobPtr StrBlob::end(){
		return StrBlobPtr(*this,data->size());
	}

//-----Fcns------------------------------------

void readBlob(StrBlob &blob, string file){
	ifstream strm(file);
	
	string line;
	while(getline(strm,line)){
		blob.push_back(line);
	}
}

void printBlob(StrBlob &blob){ //Put const here!
		
	for (StrBlobPtr ptr=blob.begin(), end=blob.end();ptr!=end;ptr.incr())
		cout<<ptr.deref()<<endl;
		
}

int main(){
	//Write a program that reads an input ﬁle a line at a time into a StrBlob and uses a StrBlobPtr to print each element in that StrBlob.
	
	//Read each line in file, put to strblob, print with strblobptr
	
	StrBlob blob1;
	
	readBlob(blob1,flLorem);
	printBlob(blob1);
}
*/

//Ex.12.16
/*
Compilers don’t always give easy-to-understand error messages if we
attempt to copy or assign a unique_ptr. Write a program that contains these errors to see how your compiler diagnoses them.


int main(){
	shared_ptr<int> iptr(new int());
	unique_ptr<int> uptr(new int());
	unique_ptr<int> uptr2();

	//uptr=uptr2;// Use of deleted function
	}
*/

//Ex.12.15
/*
Rewrite the ﬁrst exercise to use a lambda (§ 10.3.2, p. 388) in place of
the end_connection function.


void f(destination &d)
{
	connection c = connect(&d);//Create object
	shared_ptr<connection>(&c,[](connection *con){
		disconnect(*con);
	}); 
}

int main(){

}
*/

//Ex. 12.4
/*
Write your own version of a function that uses a shared_ptr to man-
age a connection.

using:
-shared_ptr<T>(address of built in ptr, own deleter)
-deleter-function that takes one argument and does sth.


//Data structures of connection params
struct destination; // represents what we are connecting to
struct connection; // information needed to use the connection

//Function prototypes
connection connect(destination*); // open the connection
void disconnect(connection); // close the given connection

void deleter(connection *con){
	disconnect(*con);
}
//funtion using connection struct
void f(destination &d)
{

connection c = connect(&d);//Create object
shared_ptr<connection>(&c,deleter()); //Create pointer. It will close connection on exit or on error throw.

}
*/

//Ex.12.13 TESTS
/*
What happen if...

void fcn(shared_ptr<int> sh){
	//Deletes mem on exit
}

int main(){
	auto sp=make_shared<int>();
	auto p=sp.get();
	cout<<"hi";
	fcn(shared_ptr<int>(p));
	//Core dump
}
*/

//Ex.12.7
/*
Redo the previous exercise, this time using shared_ptr.

Use:
-shared_ptr
-make_shared


shared_ptr<vector<int>> vecAlloc(){
	return make_shared<vector<int>>();
}

shared_ptr<vector<int>> vecFill(shared_ptr<vector<int>> vec){
	
	int read;
	cout<<"Write numbers: ";
	while(cin>>read)
		vec->push_back(read);
	cout<<"\nThanks!"<<endl;
	return vec;
}

void print(shared_ptr<vector<int>> vec){
	
	for (auto el:*vec)
		cout<<el<<" ";
}

int main(){

	print(vecFill(vecAlloc()));

}
*/

//Ex.12.6
/*
Write a function that returns a dynamically allocated vector of ints.
Pass that vector to another function that reads the standard input to give values to the elements. Pass the vector to another function to print the values that were read. Remember to delete the vector at the appropriate time.


vector<int>* vecAlloc(){
	return new vector<int>;
}

vector<int>* vecFill(vector<int>* vec){
	
	int read;
	cout<<"Write numbers: ";
	while(cin>>read)
		vec->push_back(read);
	cout<<"\nThanks!"<<endl;
	return vec;
}

void print(vector<int>* vec){
	
	for (auto el:*vec)
		cout<<el<<" ";
	delete vec;
}

int main(){

	print(vecFill(vecAlloc()));

}
*/

//Ex. 12.2
/*
Write your own version of the StrBlob class including the const ver-
sions of front and back.

What does this class?
I want many objects to share the same vector. When one obj is destroyed, data prevails.

What is needs?

-Ctors V
	+Empty(creates null ptr)
	+Initializer list
-Fcns
	+push_back
	+pop_back
	+front
	+back
-Data members
	+prt to vector of strings
-Private Fcns
	+Check if elem exist and front and pop can access it.


class StrBlob{
	public:
	
	StrBlob():data(make_shared<vector<string>>()){} //Empty vector
	StrBlob(initializer_list<string> il):data(make_shared<vector<string>> (il)){}
	
	void check(size_t, const string);
	void push_back(const string&);
	void pop_back();
	string front();
	string front()const;
	string back();
	string back() const;
	void print();
	
	private:
	shared_ptr<vector<string>> data;
};

void check(size_t sz, const string &msg){
	if(sz>=data->size())
		throw out_of_range(msg);
}

void StrBlob::push_back(const string &s){
	data->push_back(s);
}

void StrBlob::pop_back(){
	check(0,"Error");
	data->pop_back();
}

string StrBlob::front(){
	check(0,"Error");
	return data->front();
}

string StrBlob::front()const {
	check(0,"Error");
	return data->front();
}

string StrBlob::back(){
	check(0,"Error");
	return data->back();
}

string StrBlob::back()const {
	check(0,"Error");
	return data->back();
}

void StrBlob::print(){
	check(0,"Error");
	for(auto el:*data){
		cout<<el<<endl;
	}
}

int main(){
	StrBlob b1;
	StrBlob b2({"Kamil","Wiki"});
	b1=b2;
	b2.push_back("Lodowisko");
	b1.print();//Prints all 3 elements of vector.
}
*/