//#include "Game.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
//#include <list>
//#include <locale>
//#include <deque>
//#include <array>
//#include <forward_list>
//#include <cctype>
#include <string>
//#include <typeinfo>
#include "Sales_data.h"
//#include "Sales_item.h"
//#include <stack>
#include <algorithm>
//#include <numeric>
#include "MyFcn.h"
//#include <functional>
#include <iterator>
#include <map>
#include <unordered_map>
#include <set>
#include <memory>
//using placeholders::_1, placeholders::_2;
using namespace std;



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
	
	StrBlob():data(make_shared<vector<string>>()){} //Null ptr
	StrBlob(initializer_list<string> il):data(make_shared<vector<string>> (il)){}
	
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

void StrBlob::push_back(const string &s){
	data->push_back(s);
}

void StrBlob::pop_back(){
	data->pop_back();
}

string StrBlob::front(){
	return data->front();
}

string StrBlob::front()const {
	return data->front();
}

string StrBlob::back(){
	return data->back();
}

string StrBlob::back()const {
	return data->back();
}

void StrBlob::print(){
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

//Ex.11.38
/*
Rewrite the word-counting (§ 11.1, p. 421) and word-transformation
(§ 11.3.6, p. 440) programs to use an unordered_map.


int main(){
	unordered_map<string,size_t> map;
	string file="/home/cam/Documents/Programowanie/data/loremipsum.txt";
	ifstream fstrm(file);
	
	string word;
	while(fstrm>>word){
		++map[word];
	}
	
	for (auto el:map)
		cout<<el.first<<" "<<el.second<<endl;
	
}
*/

//Ex.11.33
/*
Implement your own version of the word-transformation program.

File with rules
File with text


//Create map of rules
using Map=map<string,string>;
Map make_map(const string &file){
	ifstream fstrm(file);
	map<string, string> map;
	
	if(!fstrm.is_open()){
		cout<<"No file";
	}else{
	string rule, transform;
		while(fstrm>>rule&&getline(fstrm,transform)){
			if(transform.size()>1)//Check if text is valid
				//map.insert(make_pair(rule,transform.substr(1)));
				map.insert({rule,transform.substr(1)});
			else
				throw runtime_error("No rule for "+rule);
		}
	}
	return map; 
}
 
//Transform word if it matches rules
string trans(string word, const Map &tr_map){
	//find word in map
	auto it_map =tr_map.find(word);
	//if found return trans
	if(it_map!=tr_map.end())
		return it_map->second;
	//if not return word
	else
		return word;
}

void do_the_job(string file,Map map){
	ifstream fstrm(file);
	if(!fstrm.is_open()){
		cout<<"No file";
		return;
	}
	
	//Get line from file
	string line;
	while(getline(fstrm,line)){
		//Check each word
		istringstream sstrm(line);
		string word;
		//Print transformed	
		while(sstrm>>word)
			cout<<trans(word,map)<<" ";
		cout<<endl;
	}
}
//Print on the spot

int main(){
	string rules="/home/cam/Documents/Programowanie/data/ex11-33-rules.txt";
	string text="/home/cam/Documents/Programowanie/data/ex11-33-text.txt";
	Map map(make_map(rules));

	do_the_job(text,map);
}
*/

//Ex.11.32
/*
Using the multimap from the previous exercise, write a program to
print the list of authors and their works alphabetically.


int main(){
	//Def multimap
	multimap<string,string> authors;
	//Fill it
	authors.insert({{"Wiki","Book3"},{"Kamil","BBook2"},{"Kamil","ABook1"}});

	//Search for author?
	multimap<string,string>::iterator iter=authors.find("Kami");
	//if no author do nothing.
	if(iter!=authors.end())
		//Erase title
		authors.erase(iter);
	
	multiset<pair<string,string>> ordered;
	
	//Create set, that will sort elements by itself. Map sorts only by key
	for(auto el:authors){
		ordered.insert(make_pair(el.first,el.second));
	}
	
	//Print books in alphabetical order
	for(auto el:ordered)
		cout<<el.first<<" "<<el.second<<endl;
}
*/

//Ex.11.31
/*
Write a program that deﬁnes a multimap of authors and their works.
Use find to ﬁnd an element in the multimap and erase that element. Be sure your program works correctly if the element you look for is not in the map.


int main(){
	//Def multimap
	multimap<string,string> authors;
	//Fill it
	authors.insert({{"Kamil","Book2"},{"Kamil","Book1"},{"Wiki","Book3"}});

	//Search for author?
	multimap<string,string>::iterator iter=authors.find("Kamil");
	//if no author do nothing.
	if(iter!=authors.end())
		//Erase title
		authors.erase(iter);

	for(auto el:authors){
		cout<<el.first<<" "<<el.second<<endl;
	}
}
*/

//Ex.11.23
/*
Rewrite the map that stored vectors of children’s names with a key
that is the family last name for the exercises in § 11.2.1 (p. 424) to use a multimap.


//Define a map
using Map=multimap<string, vector<string>>;

void print(Map fams){
	for(pair<string,vector<string>> const &el:fams){
		cout<<el.first<<" ";
		for(string const& vel:el.second){
			cout<<vel<<" ";
		}
		cout<<endl;
	}
}

void add(Map &fam){
	
	string name;
	do{
		name.clear();
		cout<<"Family name: ";
		cin>>name;
		if (!name.empty()){
			cout<<"Children names: ";
			string children;
			while(cin>>children){
				auto ret=fam.emplace(make_pair(name,vector<string>()));
				ret->second.push_back(children);
			}
			cin.clear();
			cout<<endl;
		}
	}while(!name.empty());
}

int main(){
	Map family;
	
	add(family);
	cout<<endl;
	print(family);
}
*/

//Ex.11.20
/*
Rewrite the word-counting program from § 11.1 (p. 421) to use
insert instead of subscripting. Which program do you think is easier to write and read? Explain your reasoning.


int main(){
	vector<string> vec=fl2vec(flLorem);
	map<string,size_t> word_count;
	
	auto iter= vec.begin();
	while(iter!=vec.end()){
		auto ret= word_count.insert({*iter,1});
			if(!ret.second)
				++ret.first->second;
		++iter;
	}
}
*/

//Ex.11.19
/*
Deﬁne a variable that you initialize by calling begin() on the
multiset named bookstore from § 11.2.2 (p. 425). Write the variable’s type without using auto or decltype.

bool compareIsbn(const Sales_data &lhs, const Sales_data &rhs){
	return lhs.isbn()<rhs.isbn();
}

int main(){

multiset<Sales_data, bool(*)(const Sales_data&, const Sales_data&)>
bookstore(compareIsbn);

//Sales_data variable=*bookstore.begin(); //Empty Cant dereference 
multiset<Sales_data, bool(*)(const Sales_data&, const Sales_data&)>::iterator var2=bookstore.begin();
}
*/

//Ex.11.16
/*
Using a map iterator write an expression that assigns a value to an
element.

int main(){
	map<string, int> m{{"Kamil",0}};
	map<string,int>::iterator iter=m.begin();
	iter->second=33;
}
*/

//Ex.11.14
/*
Extend the map of children to their family name that you wrote for the
exercises in § 11.2.1 (p. 424) by having the vector store a pair that holds a child’s name and birthday.


using Map=map<string, vector<pair<string,int>>>;

void print(Map fams){
	for(pair<string,vector<pair<string,int>>> const &el:fams){
		cout<<"Family name: "<<el.first<<"\nChildren names and age:\n";
		for(pair<string,int> const& vel:el.second){
			cout<<vel.first<<" "<<vel.second<<endl;
		}
		cout<<endl;
	}
}

void add(Map &fam){
	
	string name;
	do{
		name.clear();
		cout<<"Family name: ";
		cin>>name;
		if (!name.empty()){
			cout<<"Children names and age: ";
			string children;
			int age;
			while(cin>>children>>age)
				fam[name].emplace_back(children,age);
			cin.clear();
			cout<<endl;
		}
	}while(!name.empty());
}

int main(){
	Map family;
	
	add(family);
	cout<<endl;
	print(family);
	
}
*/

//Ex.11.13
/*
There are at least three ways to create the pairs in the program for
the previous exercise. Write three versions of that program, creating the pairs in each way. Explain which form you think is easiest to write and understand, and why.


int main(){

	vector<pair<string,int>> pvec;
		
	//Method #1
	// pair<string, int> input;
	// while(cin>>input.first>>input.second)
	// pvec.push_back(input);
	
	//Method #2
	// string s;
	// int i;
	// while(cin>>s>>i)
		// pvec.push_back(make_pair(s,i));
	
	//Method #3
	// string s;
	// int i;
	// while(cin>>s>>i){
		// pair<string,int> p(s,i);
		// pvec.push_back(p);
	// }
	//Method #4
	string s;
	int i;
	while(cin>>s>>i)
		pvec.emplace_back(s,i);

	for(auto el:pvec)
		cout<<el.first<<" "<<el.second<<"\n";
}
*/

//Ex.11.12
/*
Write a program to read a sequence of strings and ints, storing each
into a pair. Store the pairs in a vector.


int main(){

	vector<pair<string,int>> pvec;
	pair<string, int> input;

	while(cin>>input.first>>input.second)
	pvec.push_back(input);

	for(auto el:pvec)
		cout<<el.first<<" "<<el.second<<"\n";
	}
*/

//Ex.11.11
/*
Redeﬁne bookstore without using decltype.

bool compareIsbn(const Sales_data &lhs, const Sales_data &rhs){
	return lhs.isbn()<rhs.isbn();
}

int main(){
//bool(*fcnPtr)(const Sales_item&,const Sales_item&)=compareIsbn;
multiset<Sales_data,bool(*)(const Sales_data&,const Sales_data&)> bookstore(compareIsbn);
}
*/

//Ex.11.10
/*
Could we deﬁne a map from vector<int>::iterator to int? What about from list<int>::iterator to int? In each case, if not, why not?


int main(){
//Yeah
map<vector<int>::iterator, int> map1;
map<list<int>::iterator, int> map2;
}
*/

//Ex.11.9
/*
Deﬁne a map that associates words with a list of line numbers on
which the word might occur.


int main(){
map<string,list<size_t>> word_list{{"Owoc",{1,5,8,9}},{"Warzywo",{3,5,7,9}}};
}
*/

//Ex.11.8
/*
Write a program that stores the excluded words in a vector instead of
in a set. What are the advantages to using a set?


int main(){
map<string, size_t> cnt;
set<string> excluded{"the","The","a","A","An","an"};
vector<string> exclvec{"the","The","a","A","An","an"};

string word;
while(cin>>word)
	//if(excluded.find(word)==excluded.end()) //set version
	if(find(exclvec.begin(),exclvec.end(),word)==exclvec.end())
		++cnt[word];

	cout<<"\n";
for(auto const &el:cnt)
	cout<<el.second<<" "<<el.first<<endl;

}
*/

//Ex.11.7 !!!
/*
Deﬁne a map for which the key is the family’s last name and the value
is a vector of the children’s names.

Write code to add new families and to add new children to an existing family.


//Define a map
using Map=map<string, vector<string>>;

void print(Map fams){
	for(pair<string,vector<string>> const &el:fams){
		cout<<el.first<<" ";
		for(string const& vel:el.second){
			cout<<vel<<" ";
		}
		cout<<endl;
	}
}
*/
//SOLUTION #2
/*
Map add(){
	Map fam;
	for (string ln;cout<<"Last name: ", cin>>ln && ln!="@q";)
		for(string cn; cout<<"|-Children's names: ", cin>>cn && cn!="@q";)
			fam[ln].push_back(cn);
	return fam;
}

int main(){
	print(add());
	return 0;
}
*/
/*
//SOLUTION #1
void add(Map &fam){
	
	string name;
	do{
		name.clear();
		cout<<"Family name: ";
		cin>>name;
		if (!name.empty()){
			cout<<"Children names: ";
			string children;
			while(cin>>children)
				fam[name].push_back(children);
			cin.clear();
			cout<<endl;
		}
	}while(!name.empty());
}

int main(){
	map<string, vector<string>> family;
	
	//family[name]={"Kamil","Wiktor","Agnieszka"};
	

	add(family);
	cout<<endl;
	print(family);
	
}
*/

//Ex.11.4
/*
Extend your program to ignore case and punctuation. For example, “example.” “example,” and “Example” should all increment the same counter.


string trim(string s){
	// //Remove punctuation
	int place=0;
	 while((place=s.find_first_of(",.-():; \n",place))!=string::npos){
		//cout<<place<<" ";
		s.erase(place,1);
	}
	//make to lowercase
	//cout<<s<<" "<<s.length()<<endl;
	for(int i=0;i<s.length();++i)
		s[i]=tolower(s[i]);
	//cout<<s<<endl;
	return s;
}

int main(){
	vector<string> vektor=fl2vec(flText);
	map<string, size_t> ile_slow;
	
	vector<string>::iterator begin=vektor.begin();

	while(begin!=vektor.end()){
		string temp=*begin++;
		temp=trim(temp);
		++ile_slow[temp];
		//++ile_slow[*begin++];
	}
	
	for(const auto el:ile_slow){
		cout<<el.second<<" "<<el.first<<endl;
	}		
}
*/

//Ex.11.3
/*
 Write your own version of the word-counting program.


int main(){
	vector<string> vektor=fl2vec(flLorem);
	map<string, size_t> ile_slow;
	auto begin=vektor.begin();

	while(begin!=vektor.end()){
		++ile_slow[*begin++];
	}
	
	for(const auto el:ile_slow){
		cout<<el.first<<"\t# "<<el.second<<(el.second>1?" slowa":" slowo")<<endl;
	}		
}
*/

//Ex.10.42
/*
Reimplement the program that eliminated duplicate words that we wrote in § 10.2.3 (p. 383) to use a list instead of a vector.

Eliminate duplicates
1. Sort - To have same elems next to.
2. Unique - To move duplicates to end. Return iter to first dupcatw
3. Erase - Erase duplicates from end of container. Unique uses that!


int main(){
	vector<string> svec=fl2vec(flLorem);
	list<string> slst;
	copy(svec.begin(), svec.end(),back_inserter(slst));
	
	slst.sort();
	slst.unique();
	printCont(slst);
}
*/

//Ex.10.37
/*
Given a vector that has ten elements, copy the elements from posi-
tions 3 through 7 in reverse order to a list.

int main(){
	vector<int> vektorek{1,2,3,4,5,6,7,8,9};
	list<int> lista;
	auto iter=vektorek.begin()+2;
	
	copy(iter,vektorek.begin()+7,front_inserter(lista));
	
	for(auto el:lista){
		cout<<el;
	}
	
}
*/

//Ex.10.36
/*
 Use find to ﬁnd the last element in a list of ints with value 0.


int main(){
	vector<int> ivec{1,2,0,3,4,5,6,0,7,8,9};
	auto found=find(ivec.crbegin(),ivec.crend(),0);
	
	for(auto iter=ivec.end()-1;iter>=found.base()-1;--iter)
		cout<<*iter;
}
*/

//Ex.10.35
/*
Now print the elements in reverse order using ordinary iterators.


int main(){
	vector<int> ivec{1,2,3,4,5};
	for(auto end_iter=ivec.end()-1;end_iter>=ivec.begin();--end_iter){
		cout<<*end_iter;
	}
}
*/

//Ex.10.34
/*
Use reverse_iterators to print a vector in reverse order.


int main(){
	vector<int> ivec{1,2,3,4,5};
	
	reverse_iterator<vector<int>::const_iterator> iter=ivec.crbegin();
	for(;iter!=ivec.crend();++iter){
		cout<<*iter;
	}
}
*/


//Ex.10.33
/*
Write a program that takes the names of an input ﬁle and two output
ﬁles.
The input ﬁle should hold integers.
Using an istream_iterator read the input ﬁle.
Using ostream_iterators, write the odd numbers into the ﬁrst output ﬁle. Each value should be followed by a space. Write the even numbers into the second ﬁle. Each of these values should be placed on a separate line.


int main(){
	//Names of 3 files in, 2xout
	string fileIn="/home/cam/Documents/Programowanie/data/intIn.dat";
	string fileOdd="./odd.txt";
	string fileEven="./even.txt";
	
	//use istream to read file
	ifstream strmIn(fileIn);
	cout<<strmIn.is_open();
	ofstream odd(fileOdd,ios::app);
	ofstream even(fileEven,ios::app);
	
	istream_iterator<int> iter(strmIn),eof;
	ostream_iterator<int> oter(odd," ");
	ostream_iterator<int> eter(even," ");
	
	for(;iter!=eof;++iter){
		if ((*iter)%2==0){
			eter=*iter;
		}else{
			oter=*iter;
		}
	}
}
*/

//Ex. Experimemts with templates
/*
template<class T>
T add(T a, T b){
	return a+b;
}
int main(){
	cout<<add(5,6);
	
	double z=add<double>(13.2,11.5);
	cout<<z;
}
*/

//Ex.10.32
/*
Rewrite the bookstore problem from § 1.6 (p. 24) using a vector to hold the transactions and various algorithms to do the processing. Use sort with your compareIsbn function from § 10.3.1 (p. 387) to arrange the transactions in order, and then use find and accumulate to do the sum.

- use vector
- use sort with compareISBN to order
- find and acumulate to sum

	// Sales_item total;
	// if (cin>>total){ //Start cond. If data is there.
		
		////Main loop. Reads transaction, and adds if the same.
		// Sales_item trans;
		// while(cin>>trans){
			// if(total.isbn()==trans.isbn())
				// total+=trans;
			// else{
				// cout<<total<<endl;
				// total=trans;
			// }
		// }
		// cout<<total<<endl; //Print last transaction
	// } else{
		// cerr<<"No data?!";
		// return -1;
	// }
	// return 0;

	
bool compareISBN(Sales_data &obj1, Sales_data &obj2){
	return obj1.isbn() < obj2.isbn();
}

int main(){
	string file="/home/cam/Documents/Programowanie/data/data.dat";
	//data to vec
	ifstream fstrm(file);
	istream_iterator<Sales_data> itr(fstrm),eof;
	vector<Sales_data> dataVec;
	
	//Fill vector with sales data from file.
	while(itr!=eof){
		dataVec.push_back(*(itr++));
	}
	
	//ALTERNATIVE FILLING
	// while(read(fstrm,temp)){
		// dataVec.push_back(temp);
	// }
	// cout<<endl;
	
	//Prepare data. Sort. Elements close to eachother
	sort(dataVec.begin(), dataVec.end(), compareISBN);
	
	//Accumulate
	auto begin=dataVec.begin();
	while(begin!=dataVec.end()){
		//Checks for onet pas the same element
		auto end=find_if(begin,dataVec.end(),[begin](Sales_data ob){
			return ob.isbn()!=begin->isbn();
			});
		//Add elements
		Sales_data output=accumulate(begin,end,Sales_data(begin->isbn()));
		printOut(cout,output)<<endl;
		//Set iterators for new iteration
		begin=end;
	}
	cout<<endl;
	//Print to check
	for (auto el:dataVec){
		printOut(cout,el)<<endl;
	}
}
*/

//Ex.10.31
/*
Update the program from the previous exercise so that it prints only the unique elements. Your program should use unqiue_copy (§ 10.4.1, p. 403).


int main(){
	istream_iterator<int> iter(cin), eof;
	ostream_iterator<int> oiter(cout," ");
	
	vector<int> ivec(iter,eof),ivec2;
	sort(ivec.begin(),ivec.end());
	for(auto el:ivec) cout<<el<<" ";
	cout<<endl;
	
	//Takes just uniques
	unique_copy(ivec.begin(),ivec.end(),back_inserter(ivec2));
	for(auto el:ivec2) cout<<el<<" ";
	
	cout<<endl;
	// Out with odds
	remove_copy_if(ivec2.begin(),ivec2.end(),oiter,
		[](int a){
		return a%2;
	});
}
*/

//Ex. 10.30
/*
Use stream iterators, sort, and copy to read a sequence of integers from the standard input, sort them, and then write them back to the standard output.


int main(){
	istream_iterator<int> iter(cin), eof;
	ostream_iterator<int> oiter(cout," ");
	
	vector<int> ivec(iter,eof);
	sort(ivec.begin(),ivec.end());
	copy(ivec.begin(),ivec.end(),oiter);
}
*/

//Ex.10.29
/*
 Write a program using stream iterators to read a text ﬁle into a vector of strings.


int main(){

	//open txt file
	ifstream fstr(flLorem);

	istream_iterator<string> siter(fstr),eof;
	vector<string> svec;

	//read it into string
	while(siter!=eof){
		svec.push_back(*siter++);
	}
	//Print
	for (string el:svec)
		cout<<el<<" ";
}
*/

//Ex. Playing with osteam iters
/*
int main(){
	
	ostream_iterator<char> out(cout);
	
	string str="Kamil";
	
	for(char el:str)
		out=el;
	
}
*/

//Ex. Playing with iterators, string and containers
/*
Take file, and print words even upper, odd lower. Split file to lines after comma or dot.
Output is one string

string changeCase(string &s, char c){
	
	for(char &el:s){
		if(c=='u')
			el=toupper(el);
		if(c=='l')
			el=tolower(el);
	}
	
	return s;
}

int main(){
	//Fill vector with file string
	ifstream fstr(flLorem);
	istream_iterator<string> input(fstr), end;
	vector<string> svec(input,end);
	
	//Variables
	string output;
	vector<string>::iterator iter=svec.begin();
	int cnt=1;
	
	//OPERATIONS
	while(iter!=svec.end()){ //Take by one word
	
		//Change case
		if(cnt%2==0){
			changeCase(*iter,'l');
		}
		else{
			changeCase(*iter,'u');
		}
		
		//Append to output string + space " "
		
		//string word=*iter;
		//char ending=*(word.end()-1);
		char ending=*(iter->end()-1); //Shorter version
		
		if(ending==',' || ending=='.'){
			iter->append("\n");
		}else{
			 iter->append(" ");
		}
		
		output.append(*iter);
		//Control variables
		++iter;
		++cnt;
	}
	
	//Print container and string
	
	printCont(svec);
	cout<<output;
}
*/

	//Insert
	// string st="KamilPiasecki";
	// auto it=inserter(st,st.begin()+5);//Where?
	// it='\n';
	// cout<<st;

	// istream_iterator<string> in(fstr), end;
	// vector<string> svec(in,end);

	//Needed:
		//Lower case word
		//Upper case word
		//Recognize where to put new line and put it
	






//Ex.10.28
/*
Copy a vector that holds the values from 1 to 9 inclusive, into three
other containers. Use an inserter, a back_inserter, and a front_inserter,
respectivly to add elements to these containers. Predict how the output sequence varies by the kind of inserter and verify your predictions by running your programs.


template <typename T>
void print(const T &cont){
	
	for(auto el:cont){
		cout<<el<<" ";
	}
	cout<<endl;
}


int main(){
vector<int> ivec3, ivec4, ivec{1,2,3,4,5,6,7,8,9,0};
deque<int> ivec2;

//front
copy(ivec.begin(), ivec.end(), front_inserter(ivec2));
//0 9 8 7 6 5 4 3 2 1 


//back
copy(ivec.begin(), ivec.end(), back_inserter(ivec3));
//1 2 3 4 5 6 7 8 9 0 


//inserter
copy(ivec.begin(), ivec.end(), inserter(ivec4,ivec4.begin()));
//1 2 3 4 5 6 7 8 9 0

//Print
print(ivec2);
print(ivec3);
print(ivec4);
}
*/

//Ex.10.27
/*
In addition to unique (§ 10.2.3, p. 384), the library deﬁnes function
named unique_copy that takes a third iterator denoting a destination into which to copy the unique elements. Write a program that uses unique_copy to copy the unique elements from a vector into an initially empty list.


int main(){
	vector<int> ivec{1,1,2,3,3,4,5,5,6,7,8,7,8,9};
	list<int> ilst;
	
	unique_copy(ivec.begin(), ivec.end(), back_inserter(ilst));
	
	for (int el:ilst) cout<<el<<" ";
	//Out: 1 2 3 4 5 6 7 8 7 8 9
}
*/

//Ex. Play with iterators
/*
int main(){
	vector<int> ivec;
	
	fill_n(back_inserter(ivec),10,5);
	
	insert_iterator<vector<int>> it=inserter(ivec,ivec.begin()+2);
	
	it=44;
	
	for(int el:ivec) cout<<el<<" ";
}
*/

//Ex.
/*
In the exercises for § 10.3.2 (p. 392) you wrote a version of biggies
that uses partition. Rewrite that function to use check_size and bind.

Aim of function
- Take a vector of words, remove duplicates, return alpha sorted vec with words bigger than size number(sz).


//Check if nr is bigger than set size
bool checkSz( int sz,const string &str){
	return str.size()<sz;
}

int main(){
	string file="/home/cam/Documents/Programowanie/data/loremipsum.txt";
	vector<string> svec=fl2vec(file);
	size_t sz=5;
	
	//Sort and duplicates out
	sort(svec.begin(), svec.end());
	vector<string>::iterator ptr=unique(svec.begin(), svec.end());
	svec.erase(ptr, svec.end());
	
	//sort by size
	stable_sort(svec.begin(),svec.end(),
		[](const string &s1, const string &s2)->bool{
		return s1.size()<s2.size();
		});
	
	//Iterator to first element of size sz
	//ptr=find_if(svec.begin(),svec.end(),[sz](const string &s){return s.size()>=sz;});
	ptr=partition(svec.begin(),svec.end(),bind(checkSz,sz,_1));
	
	//Number of elems
	size_t elems=svec.end()-ptr;
	
	
	//Print
	for_each(ptr,svec.end(),[](const string &s){
		cout<<s<<" ";
	});
	//printVec(svec);
}
*/

//Data structures - Queue
/*

Implement queue.
Use char of ints

Use methods:
pop()
push()
size()
empty()

- no shifting inside the array round struture


const int sz=5;
int queue[sz];

int cnt=0;
int *head=begin(queue);
int *tail=head;


int size(){
	return cnt;
}

bool empty(){
	return cnt==0?true:false;
}


void printQ(){
	
	cout<<"Array:\n";
		for(auto iter=begin(queue);iter<end(queue);++iter){
		cout<<*iter<<" ";
	}
	
	auto iter=head;
	cout<<endl<<"Real queue\n";
	for(int i=0;i<size();++i){
		cout<<*iter<<" ";
		iter==(end(queue)-1)?iter=begin(queue):++iter;
		
	}
	cout<<endl<<"Size: "<<size();
}

void pop(){
	if(empty())cout<<"Empty"<<endl;
	else{
		cout<<"pop("<<*head<<")"<<endl;
		head==(end(queue)-1)?head=begin(queue):++head;
		--cnt;
	}	

}

void push(const int &value){
	
	if(cnt==sz) cout<<"Full"<<endl;
	else{
		*tail=value;
		tail==(end(queue)-1)? tail=begin(queue):++tail;
		++cnt;
		cout<<"push("<<value<<")"<<endl;
	}
}

	
int main(){

	push(16);
	push(34);
	push(44);
	pop();
	pop();
	push(23);
	push(55);
	push(66);
	push(111);

	printQ();
}
*/

//Ex.10.24
/*
Use bind and check_size to ﬁnd the ﬁrst element in a vector of
ints that has a value greater than the length of a speciﬁed string value.

bool checkSz( int sz,const int &nr){
	return nr>sz;
}

int main(){
	vector<int> ivec{67,34,22,9,7,23,4,666,342,567,543,375,338,509,679,152};
	
	int size=88;
	
	auto iter=find_if(ivec.begin(),ivec.end(), bind(checkSz,size,_1));
	int place=iter-ivec.begin();
	
	cout<<place<<" "<<*iter;
}
*/

//Ex.10.22
/*
Rewrite the program to count words of size 6 or less using functions
in place of the lambdas.


bool wordSize(string s, size_t sz){
	return s.size()==sz;
}

int main(){
	
	vector<string> svec;
	
	svec=fl2vec(flLorem);
	
	//Find biggest word
	sort(svec.begin(),svec.end(),[](string &s1, string &s2)
		{ return s1.size()<s2.size();});
	printVec(svec);
	int biggestWord= (*(svec.end()-1)).size();
	int sum=0;
	
	for (int i=1;i<=biggestWord;++i){
		int result=0;
		result=count_if(svec.begin(), svec.end(), bind(wordSize,_1,i));
		cout<<"Words with "<<i<<" letters: "<<result<<endl;
		sum+=result;
	}
	cout<<"Sum of all words: "<<sum;
}
*/

//Ex. Bind games
/*

bool fcn(const string &s, int size){
	return s.size()>size;
}

int main(){


	string name="Kamillowski";
	int sz=3;

	auto check=bind(fcn,_1,sz);
	cout<<check(name);
}
*/

//Ex.10.21
/*
Write a lambda that captures a local int variable and decrements that
variable until it reaches 0. Once the variable is 0 additional calls should no longer decrement the variable. The lambda should return a bool that indicates whether the captured variable is 0.


int main(){
	int a=10;
	
	//lambda
	auto f=[&a]()->bool{
		if(a>0){
			--a;
			return true;
		}
		else
			return false;
		
	};
	cout<<f();
	cout<<f();
	cout<<a;
}
*/

//Ex.10.20
/*
The library deﬁnes an algorithm named count_if. Like find_if,
this function takes a pair of iterators denoting an input range and a predicate that it applies to each element in the given range. count_if returns a count of how often the predicate is true. Use count_if to rewrite the portion of our program that counted how many words are greater than length 6.



int main(){
	string file="/home/cam/Documents/Programowanie/data/loremipsum.txt";
	vector<string> svec=fl2vec(file);
	size_t sz=5;
	
	//Sort and duplicates out
	sort(svec.begin(), svec.end());
	vector<string>::iterator ptr=unique(svec.begin(), svec.end());
	svec.erase(ptr, svec.end());
	
	//sort by size
	stable_sort(svec.begin(),svec.end(),
		[](const string &s1, const string &s2)->bool{
		return s1.size()<s2.size();
		});
	
	//Iterator to first element that do not match predicate
	ptr=stable_partition(svec.begin(),svec.end(),[sz](const string &s){return s.size()>=sz;});
	
	//Number of elems. Chech if each elem is bigger than sz
	size_t elems=count_if(svec.begin(),svec.end(),
		[sz](const string &s){return s.size()>=sz;});
	

	//Print
	cout<<"Elems nr: "<<elems<<endl;
	for_each(svec.begin(),ptr,[](const string &s){
		cout<<s<<" ";
	});
	//printVec(svec);
}
*/

//Ex.10.19
/*
Rewrite the previous exercise to use stable_partition, which like
stable_sort maintains the original element order in the paritioned sequence.


int main(){
	string file="/home/cam/Documents/Programowanie/data/loremipsum.txt";
	vector<string> svec=fl2vec(file);
	size_t sz=5;
	
	//Sort and duplicates out
	sort(svec.begin(), svec.end());
	vector<string>::iterator ptr=unique(svec.begin(), svec.end());
	svec.erase(ptr, svec.end());
	
	//sort by size
	stable_sort(svec.begin(),svec.end(),
		[](const string &s1, const string &s2)->bool{
		return s1.size()<s2.size();
		});
	
	//Iterator to first element that do not match predicate
	ptr=stable_partition(svec.begin(),svec.end(),[sz](const string &s){return s.size()>=sz;});
	
	//Number of elems
	size_t elems=ptr-svec.begin();
	
	
	//Print
	for_each(svec.begin(),ptr,[](const string &s){
		cout<<s<<" ";
	});
	//printVec(svec);
}
*/

//Ex.10.18
/*
Rewrite biggies to use partition instead of find_if. We described the partition algorithm in exercise 10.13 in § 10.3.1 (p. 387).

Aim of function
- Take a vector of words, remove duplicates, return alpha sorted vec with words bigger than size number(sz).


int main(){
	string file="/home/cam/Documents/Programowanie/data/loremipsum.txt";
	vector<string> svec=fl2vec(file);
	size_t sz=5;
	
	//Sort and duplicates out
	sort(svec.begin(), svec.end());
	vector<string>::iterator ptr=unique(svec.begin(), svec.end());
	svec.erase(ptr, svec.end());
	
	//sort by size
	stable_sort(svec.begin(),svec.end(),
		[](const string &s1, const string &s2)->bool{
		return s1.size()<s2.size();
		});
	
	//Iterator to first element of size sz
	//ptr=find_if(svec.begin(),svec.end(),[sz](const string &s){return s.size()>=sz;});
	ptr=partition(svec.begin(),svec.end(),[sz](string &s){return s.size()<sz;});
	
	//Number of elems
	size_t elems=svec.end()-ptr;
	
	
	//Print
	for_each(ptr,svec.end(),[](const string &s){
		cout<<s<<" ";
	});
	//printVec(svec);
}
*/

//Ex.10.17
/*
Rewrite exercise 10.12 from § 10.3.1 (p. 387) to use a lambda in the call
to sort instead of the compareIsbn function.


int main(){


	//Create 2 SD objects
	ifstream fstr("/home/cam/Documents/Programowanie/data/data.dat");
	//if (fstr.is_open()) cout<<"GOOD!";
	vector<Sales_data> sdvec;
	
	//Fill in vector
	Sales_data temp;
	while(read(fstr,temp)){
		sdvec.push_back(temp);
	}
	
	//Print vector
	for(auto el:sdvec){
		printOut(cout,el)<<endl;
	}
	
	//Sort vector
	sort(sdvec.begin(),sdvec.end(),[](Sales_data &o1, Sales_data o2){
		return o1.isbn()<o2.isbn();
	});
	cout<<endl;
	
	//Print vector
	for(auto el:sdvec){
		printOut(cout,el)<<endl;
	}
}
*/

//Ex.10.16
/*
Write your own version of the biggies function using lambdas:

// put words in alphabetical order and remove duplicates
// sort words by size, but maintain alphabetical order for words of the same size
// get an iterator to the ﬁrst element whose size() is >= sz
// compute the number of elements with size >= sz
// print words of the given size or longer, each one followed by a space



int main(){
	string file="/home/cam/Documents/Programowanie/data/loremipsum.txt";
	vector<string> svec=fl2vec(file);
	size_t sz=5;
	
	//Sort and duplicates out
	sort(svec.begin(), svec.end());
	vector<string>::iterator ptr=unique(svec.begin(), svec.end());
	svec.erase(ptr, svec.end());
	
	//sort by size
	stable_sort(svec.begin(),svec.end(),
		[](const string &s1, const string &s2)->bool{
		return s1.size()<s2.size();
		});
	
	//Iterator to first element of size sz
	ptr=find_if(svec.begin(),svec.end(),[sz](const string &s){return s.size()>=sz;});
	
	//Number of elems
	size_t elems=svec.end()-ptr;
	
	
	//Print
	for_each(ptr,svec.end(),[](const string &s){
		cout<<s<<" ";
	});
	//printVec(svec);
}
*/

//Ex.10.15
/*
 Write a lambda that captures an int from its enclosing function and
takes an int parameter. The lambda should return the sum of the captured int and the int parameter.


int main(){
	int x=15;
	auto lbd=[x](int y)->int{return x+y;};
	cout<<lbd(2)<<endl;
	
	cout<<[x](int y)->int{return x*y;}(5)<<endl;
	//int z=lbd(23,[x](int a)->int{return x*a;}(5)); NOT WORKING!
	
	cout << "This lambda returns " <<[](double x, double y) -> int {return x + y;} (3.14, 2.7) << endl;
}
*/

//Ex.10.14
/*
Write a lambda that takes two ints and returns their sum.


int main(){
	auto lbd=[](int a, int b)->int{return a+b;};
	cout<<lbd(2,5)<<endl;
}
*/

//Ex.10.13
/*
The library deﬁnes an algorithm named partition that takes a pred-
icate and partitions the container so that values for which the predicate is true appear in the ﬁrst part and those for which the predicate is false appear in the second part. The algorithm returns an iterator just past the last element for which the predicate returned true.

Write a function that takes a string and returns a bool indicating whether the string has ﬁve characters or more. Use that function to partition words. Print the elements that have ﬁve or more characters.


bool isFive(const string &s){
	return s.size()>5;
}

int main(){

string file="/home/cam/Documents/Programowanie/data/loremipsum.txt";

string str;

str=fl2str(file);
cout<<str<<endl;
vector<string> svec;

str2vec(str,svec);

partition(svec.begin(),svec.end(),isFive);
printVec(svec);
}
*/

//Ex.10.12
/*
Write a function named compareIsbn that compares the isbn() members of two Sales_data objects. Use that function to sort a vector that holds Sales_data objects.


//Put const later
bool compareIsbn(Sales_data &obj1, Sales_data &obj2){
	return obj1.isbn() < obj2.isbn();
}

int main(){


//Create 2 SD objects
ifstream fstr("/home/cam/Documents/Programowanie/data/data.dat");
//if (fstr.is_open()) cout<<"GOOD!";
vector<Sales_data> sdvec;

Sales_data temp;
while(read(fstr,temp)){
	sdvec.push_back(temp);
}

for(auto el:sdvec)
	printOut(cout,el)<<endl;

sort(sdvec.begin(),sdvec.end(),compareIsbn);
cout<<endl;
for(auto el:sdvec)
	printOut(cout,el)<<endl;
}
*/

//Ex.10.11
/*
Write a program that uses stable_sort and isShorter to sort a
vector passed to your version of elimDups. Print the vector to verify that your program is correct.


void elimDups(vector<string> &svec){

	
	sort(svec.begin(),svec.end());
	auto iter_end=unique(svec.begin(),svec.end());//Ret ptr to first dupl.
	
	svec.erase(iter_end,svec.end()); //Erase duplicates from end
}

void str2vec(const string &str, vector<string> &svec){
	//fill in vector from string;
	istringstream sStrm(str); //Create stream
	string word; //Temp variable

	//Feed vector
	while(sStrm>>word){
		svec.push_back(word);
	}
}	

bool isShorter(string &s1, string &s2){
	return s1.size()<s2.size();
}

void prntVec(const vector<string> &svec){
	for(string el: svec){
		cout<<el<<" ";
	}
	cout<<endl;
}

int main(){
	string str{"the quick red fox jumps over the slow red turtle"};
	vector<string> svec;
	
	//String to vector
	str2vec(str,svec);
	prntVec(svec);
	
	//Eliminate duplicates
	elimDups(svec);
	prntVec(svec);
	
	//Sort it by length while keep alphabetical order in "equally" long str.
	sort(svec.begin(), svec.end(),isShorter);
	prntVec(svec);
}
*/

//Ex.10.9
/*
Implement your own version of elimDups. Test your program by
printing the vector after you read the input, after the call to unique, and after the call to erase.

string elimDups(string str){
	vector<string> svec;

	//fill in vector from string;
	istringstream sStrm(str); //Create stream
	string word; //Temp variable

	//Feed vector
	while(sStrm>>word){
		svec.push_back(word);
	}	
	
	sort(svec.begin(),svec.end());
	auto iter_end=unique(svec.begin(),svec.end());//Ret ptr to first dupl.
	
	svec.erase(iter_end,svec.end()); //Erase duplicates from end

	//Place back from vector to string
	str.clear();
	for(string el:svec){
		str.append(el+"_");
	}
	
	return str;
}

int main(){

	
	
	cout<< elimDups(str);
	
}
*/

//Ex. is reserve() enough to use fill_n?
/*
int main(){
	vector<int> ivec3;
	ivec3.reserve(10);
	//ivec3.resize(10); //Without it wont work
	fill_n(ivec3.begin(), 10, 2);
	
	for (auto el:ivec3){
		cout<<el<<" ";
	}
	
}
*/

//Ex.10.6
/*
Using fill_n, write a program to set a sequence of int values to 0.


int main(){
	//Fill empty vector
	vector<int> ivec1;

	fill_n(back_inserter(ivec1),10,0);


	//Fill non-empty vector
	vector<int> ivec2{1,2,3,4,5,6,7,8,9,0};
	fill_n(ivec2.begin(), 10, 0);
	
	for (auto el:ivec1)
		cout<<el<<" ";
	cout<<endl;
	for (auto el:ivec2)
		cout<<el<<" ";
}
*/

//Ex. Checking if iter can compare two c-style strings
/*
int main(){
	char str1[]="Kamil";
	char str2[]="Kamil";
	
	bool check;
	check=equal(begin(str1),end(str1),begin(str2));
	
	cout<<"Strings are: "<<check;
}
*/

//Ex.10.3 
/*
 Use accumulate to sum the elements in a vector<int>.


int main(){
	vector<double> ivec{1.5,1.5,1.5,1.5};
	
	double sum=0;
	sum=accumulate(ivec.cbegin(),ivec.cend(),0);
	cout<<"Vector sum is: "<<sum;

}
*/

//Ex.10.2
/*
Repeat the previous program, but read values into a list of strings.

The algorithm header deﬁnes a function named count that, like
find, takes a pair of iterators and a value. count returns a count of how often that value appears. Read a sequence of ints into a vector and print the count of how many elements have a given value.


int main(){

	vector<string> ivec;
	string word, val="Kamil";
	cout<<"Enter words: ";
	while(cin>>word)
		ivec.push_back(word);

	cout<<"\n"<<val<<" apeared "
		<<count(ivec.cbegin(),ivec.cend(),"Kamil")<<" times";	
}
*/


//Ex.10.1
/*
The algorithm header deﬁnes a function named count that, like
find, takes a pair of iterators and a value. count returns a count of how often that value appears. Read a sequence of ints into a vector and print the count of how many elements have a given value.


int main(){
	
	vector<int> ivec;
	int nr;
	cout<<"Enter numbers: ";
	while(cin>>nr)
		ivec.push_back(nr);
	
	cout<<"\n15 apeared "<<count(ivec.cbegin(),ivec.cend(),15)<<" times";

}
*/

//Ex. 9.52
/*
1. Use a stack to process parenthesized expressions.
2. When you see an open parenthesis, note that it was seen.
4a. When you see a close parenthesis after an open parenthesis,
4b. pop elements down to and including the open parenthesis off the stack.
5. push a value onto the stack to indicate that a parenthesized expression was replaced.




int main(){
	
	//I like to and next
	string expr{"I like to (draw) and ((((bite)))) next (chunk (of (the) big) ass.)"};
	
	char repl='$';
	int seen=0;
	
	stack<char> stack;
	
	for (char c:expr){
		stack.push(c);
	
		if (c=='('){
			//stack.pop();
			++seen;
		}
		
		if (c==')'){
			//stack.pop();
			--seen;
		}
		
		if(seen || c==')'){
			stack.pop();
		}
		
		//if c i a par, then seen+	
	}
	deque<char> out;
	while(!stack.empty()){
		out.push_front(stack.top());
		stack.pop();
	}
	for(char e:out)
	cout<<e;
}
*/

//Ex. Stack play
/*
Read numbers from string. Push them one by one to stack. Sum and print nrs.


int main(){
	
	string number{"0123456789"};
	string expr{"12 2 22 234 55 67"};
	size_t size=expr.size(), pos=0, end=0;
	stack<int> stack;
	
	//Push to stack
	while((pos=expr.find_first_of(number,end))!=string::npos){
		end=expr.find_first_not_of(number,pos);		
		string subStr=expr.substr(pos,end-pos);
		// string *ptr=nullptr;
		int tempNr=stoi(subStr,nullptr,10);
		stack.push(tempNr);
		
		//cout<<stack.top()<<" "<<subStr<<endl;
	}

	//pop from stack and print
	int sum=0;
	while(!stack.empty()){
		cout<<stack.top()<<endl;
		sum+=stack.top();
		stack.pop();
	}
	cout<<"Sum: "<<sum;
}
*/

//Ex. 9.51
/*
Write a class that has three unsigned members representing year,
month, and day. Write a constructor that takes a string representing a date. Your constructor should handle a variety of date formats, such as January 1, 1900, 1/1/1900, Jan 1, 1900, and so on.


class Date{
	private:
	int month=0;
	int day=0;
	int year=0;
	
	public:
	//static constexpr char* nr="0123456789"; //Taki joke
	const string numbers{"0123456789"};
	Date(string str){
		//1. Check if nr if yes then take it ->3 if no ->2
		//2. take string till delim(space,/\ etc)
			//2a. trim spaces
			//2b. lowwercase
			//2c. take 3 first letters
			//2d.

		//EXTRACT MONTH
		size_t posBeg=0, posEnd=0;
		string temp;
		if((posBeg=str.find_first_of(numbers))>=2){ //Check if number
			//Take string of month and extract it
			//PosEnd is index of character before number
			//Remove leading spaces
			int begin=0;
			while(str[begin]==' ')
				++begin;
			
			temp=str.substr(begin,3);
			//To lower case
			for(char &c:temp){
				c=tolower(c);
			}
			//Create month
			if(temp=="jan") month=1;
			if(temp=="feb") month=2;
			if(temp=="mar") month=3;
			if(temp=="apr") month=4;
			if(temp=="mai") month=5;
			if(temp=="jun") month=6;
			if(temp=="jul") month=7;
			if(temp=="aug") month=8;
			if(temp=="sep") month=9;
			if(temp=="oct") month=10;
			if(temp=="nov") month=11;
			if(temp=="dec") month=12;
			
		} else{
			posBeg=str.find_first_of(numbers,posEnd);
			posEnd=str.find_first_not_of(numbers,posBeg);
			temp=str.substr(posBeg,posEnd-posBeg);
			month=stoi(temp,nullptr,10);
		}
		
		for(int i=0;i<2;++i){
		//EXTRACT DAY AND YEAR
			posBeg=str.find_first_of(numbers,posEnd);
			posEnd=str.find_first_not_of(numbers,posBeg);
			temp=str.substr(posBeg,posEnd-posBeg);
			
			if(day==0){
				day=stoi(temp,nullptr,10);
			}else{
				year=stoi(temp,nullptr,10);
			}
		}
	}
	
	void print(){
		cout<<"Month="<<month<<" Day="<<day<<" Year="<<year<<endl;
	}
};

int main(){

	Date myBD("   Septembmer 09 1985");
	myBD.print();
	
	// string bd{"05-09-1985"};
	// cout<<stoi(bd,nullptr,10);
}
*/

//Ex. 9.50
/*
Write a program to process a vector<string>s whose elements represent integral values. Produce the sum of all the elements in that vector. Change the program so that it sums of strings that represent ﬂoating-point values.


int main(){
	//INT PART
	vector<string> svec{"123","11","75","1985","09","05"};
	int sum=0;
	using iter_t=vector<string>::const_iterator;
	for(iter_t i=svec.begin();i!=svec.end();++i){
		sum+=stoi(*i,nullptr,10);
	}
	cout<<"Sum INT= "<< sum<<endl;
	
	//FLOAT PART
	vector<string> sdvec{"12.3","1.1","7.5","198.5","0.9","0.5"};
	double sumd=0.0;
	for(iter_t i=sdvec.begin();i!=sdvec.end();++i){
		sumd+=stod(*i,nullptr);
	}
	cout<<"Sum DOUBLE= "<< sumd;
}
*/

//Ex. 9.49
/*
 A letter has an ascender if, as with d or f, part of the letter extends
above the middle of the line. A letter has a descender if, as with p or g, part of the letter extends below the line. Write a program that reads a ﬁle containing words and reports the longest word that contains neither ascenders nor descenders.


bool if_asc(const string &str){
	string asc{"tdfhklb"};
	
	if (str.find_first_of(asc)==string::npos)
		return false;
	else
		return true;
}

bool if_desc(const string &str){
	string desc{"qypgj"};
	
		if (str.find_first_of(desc)==string::npos)
		return false;
	else
		return true;
}

int main(){
	//Open and read file
	ifstream file("./data/loremipsum.txt");
	file.clear();
	
	//Check if opened. If not finish program.
	if (!file.is_open()){
		cout<<"Wrong file name\n";
		return -1;
	}
	
	//Little fun with stream state
	cout<<ifstream::badbit<<endl;
	cout<<ifstream::failbit<<endl;
	cout<<ifstream::eofbit<<endl;
	cout<<ifstream::goodbit<<endl;
	
	//Look for ascenders and descenders in each word
	//If word has non then check how big it is.
	//If it is biggest for now then remember word and i size
	//Move to next word.
	
	string word, right;
	size_t wrdSize=0;
	
	while(!((file>>word).rdstate()&ifstream::eofbit)){
		if((if_desc(word)||if_asc(word))==false){ //Check if has asc or desc
			if(wrdSize<word.size()){ //if not=>check for size
				wrdSize=word.size(); //If bigger than prev  king=>new king
				right=word;
			}
		}	
	}
	
	//Output
	cout<<word<<" "<<wrdSize;
	cout<<"\nDone";
	
	file.close();
	return 0;
}
*/

//Ex. 4.47
/*
 Write a program that ﬁnds each numeric character and then each alphabetic character in the string "ab2c3d7R4E6". Write two versions of the program. The ﬁrst should use find_first_of, and the second find_first_not_of.


int main(){

	string str{"ab2c3d7R4E6"};
	string number{"0123456789"};
	string alphabet{"abcdefghijklmnopqrstuwxyzABCDEFGHIJKLMNOPQRSTUWXYZ"};
	
	size_t pos=0;
	
	//FIND_FIRST_OF VERSION
	cout<<"FIRST OF"<<endl;
	//Find each nr character
	while ((pos=str.find_first_of(number,pos))!=string::npos){
		cout<<str[pos]<<" ";
		pos++;
	}
	cout<<endl;
	
		//Find each alpha char
	pos=0;
	while ((pos=str.find_first_of(alphabet,pos))!=string::npos){
		cout<<str[pos]<<" ";
		pos++;
	}
	

	cout<<"\nNOT OF"<<endl;
	pos=0;
	//FIND_FIRST_NOT_OF VERSION
	//Find each nr character
	while ((pos=str.find_first_not_of(alphabet,pos))!=string::npos){
		cout<<str[pos]<<" ";
		pos++;
	}
	cout<<endl;
	
	//Find each alpha char
	pos=0;
	
	while ((pos=str.find_first_not_of(number,pos))!=string::npos){
		cout<<str[pos]<<" ";
		pos++;
	}
	
}
*/

//Ex. Strings compare
/*
int main(){
	
	string s1="Kamil", s2="Kamil";
	
	cout<<s1.compare(s2)<<endl;
	
}
*/

//Ex. 9.46
/*
Rewrite the previous exercise using a position and length to manage
the strings. This time use only the insert function.


void addStr(string &str, string pre, string suf){
	
	str.insert(0,pre+' ');
	str.insert(str.size(),' '+suf);
}

int main(){

string a="Kamil", p="Don", s="II";
addStr(a,p,s);
cout<<a<<endl;
}
*/

//Ex. 9.45
/*
Write a funtion that takes a string representing a name and two other
strings representing a preﬁx, such as “Mr.” or “Ms.” and a sufﬁx, such as “Jr.” or “III”.
Using iterators and the insert and append functions, generate and return a new string with the sufﬁx and preﬁx added to the given name.


void addStr(string &str, string pre, string suf){
	
	str.insert(str.begin(),{' '});
	//str.insert(str.begin(),1,' ');
	str.insert(str.begin(),pre.begin(),pre.end());
	str.append(" "+suf);
}


int main(){

string a="Kamil", p="Don", s="II";
addStr(a,p,s);
cout<<a<<endl;
}
*/

//Ex. 9.44
/*
Rewrite the previous function using an index and replace.


void find_replace(string &str, string oldVal, string newVal){
	
	size_t len=oldVal.size();
	int begin=0;
	
	while(begin+len!=str.size()){
		
		//1. Find phrase
		string temp(str,begin,len);
		if(temp==oldVal){
			//2. Replace this string with new one
			str.replace(begin,len,newVal);
			begin+=newVal.size();
		}else 
			++begin;
	}	
}

int main(){

string a="loKamillo lubi lody i lokówki";
string oldV="lo", newV="pla";

find_replace(a,oldV,newV);

cout<<a<<endl;
}
*/

//Ex. 9.43
/*
Write a function that takes three strings, s, oldVal, and newVal.
Using iterators, and the insert and erase functions replace all instances of oldVal that appear in s by newVal. Test your function by using it to replace common abbreviations, such as “tho” by ”though” and ”thru” by “through”.


void find_replace(string &str, string oldVal, string newVal){
	
	size_t len=oldVal.size();
	string::iterator begin=str.begin();

	
	while(begin+len!=str.end()){
		
		//1. Find phrase
		string temp(begin,begin+len);
		if(temp==oldVal){

			//2.Use erase(pos(iter),length) to remove oldVal.
			begin=str.erase(begin,begin+len);
			
			//3. Insert newVal in place of old.
			begin=str.insert(begin,newVal.begin(),newVal.end());
			++begin;
		}else 
			++begin;
	}	
}

int main(){

string a="loKamillo lubi lody i lokówki";
string oldV="lo", newV="pla";

find_replace(a,oldV,newV);

cout<<a<<endl;
}
*/

//Ex. 9.41
/*
 Write a program that initializes a string from a vector<char>.


int main(){
	
	vector<char> cvec{'h','e','l','l','o',' ','w','o','r','l','d'};
	string str(&cvec[0]); //Init from ADDRESS OF first element
	cout<<str<<endl;
	
	char *carr="Hello Dear!"; //Null terminated OK
	char carr2[]="Hello Friend"; //NoNull works BUT UNDEFINED!
	string str2(carr);
	string str3(carr2);
	cout<<str2<<endl<<str3<<endl;
}
*/

//Ex.9.38 How vector grows? When reallocates memory?
/*
When reach current capacity expands. Grows by doubling

int main(){

	vector<int> vec;
	
	vec.reserve(50);
	for(int i=1;i<=1000;i++){
		vec.push_back(i);
		cout<<"Nr: "<<i<<"\tCapacity: "<<vec.capacity()<<endl;
	}	
}
*/

//Ex. 9.33
/*
 In the ﬁnal example in this section what would happen if we did not
assign the result of insert to begin? Write a program that omits this assignment to
see if your expectation was correct.

int main(){
	
	vector<int> v{0,1,2,3,4,5,6,7,8,9};
	
	auto begin=v.begin();
	while (begin!=v.end()){
		++begin;
		begin=v.insert(begin,42);//If begin out program core dumps
		++begin;
	}
	
	for(auto el:v){
		cout<<el<<" ";
	}
}
*/

//Ex. 9.31
/*
The program on page 354 to remove even-valued elements and dupli-
cate odd ones will not work on a list or forward_list. Why? Revise the program so that it works on these types as well.


	// vector<int> vi = {0,1,2,3,4,5,6,7,8,9};
	// auto iter = vi.begin(); 
	// while (iter != vi.end()) {
		// if (*iter % 2) {
		// iter = vi.insert(iter, *iter); // duplicate the current element
		// iter += 2; // advance past this element and the one inserted before it
	// } else
	// iter = vi.erase(iter);

//Answer: Forward list uses different inster and erase. It is built different way.

int main(){

	forward_list<int> lst{0,1,2,3,4,5,6,7,8,9};
	
	auto prev=lst.before_begin();
	auto curr=lst.begin();
	
	while(curr!=lst.end()){
		if(*curr%2){ //odd = true
			prev=lst.insert_after(curr,*curr);
			++curr;
			++curr;
		}else{
			curr=lst.erase_after(prev);
		}
	}
	
	for(auto el:lst)
		cout<<el<<" ";
}
*/


//Ex. Where points insert_after() return?
//To new element in front of it :)
/*
int main(){
	forward_list<int> lst;
	
	auto iter= lst.before_begin();
	
	for (int i=0;i<10;i++){
		iter=lst.insert_after(iter,i);
	}
	
	for(auto el:lst){
		cout<<el<<" ";
	}
}
*/

//Ex.9.28
/*
 Write a function that takes a forward_list<string> and two additional string arguments. The function should ﬁnd the ﬁrst string and insert the second immediately following the ﬁrst. If the ﬁrst string is not found, then insert the second string at the end of the list.

void lstFcn(forward_list<string> &l, const string &cs, const string &is){
	
	//create
	using l_iter=forward_list<string>::iterator;
	l_iter prev=l.before_begin();
	l_iter curr=l.begin();
	bool found=false;
	
	while(curr!=l.end()){
		if(*curr==cs){
			//what if find
			curr=l.insert_after(curr,is);
			prev=curr;
			++curr;
			
			//Check if found
			found=true; //Do poprawy
		}else{
			//what if not find
			prev=curr;
			++curr;
		}
			
	}
	
	//In case didnt find cs
	if (found==false){
		l.insert_after(prev,is); 
	}
}

int main(){

	forward_list<string> lst{"Ala","ma","kota","i","ma","też","psa"};
	string strCond{"sok"}, strIns{"kurwa"};

	lstFcn(lst,strCond, strIns); //call function
	
	//print	
	for(auto el:lst)
		cout<<el<<" ";
	cout<<endl;
}
*/

//Ex.9.27
/*
Write a program to ﬁnd and remove the odd-valued elements in a
forward_list<int>.


int main(){
	
	forward_list<int> flist{1,2,3,4,5,6,7,8,9};
	
	
	forward_list<int>::iterator prv_iter= flist.before_begin();
	forward_list<int>::iterator curr_iter= flist.begin();
	
	//Can I assign iter to int ptr? NOPE
	// int *ptr=nullptr;
	// cout<<sizeof(curr_iter)<<" "<<sizeof(*curr_iter)<<
		// " "<<sizeof(*ptr)<<endl;
	
	// ptr= reinterpret_cast<int*>(prv_iter);
	
	//iterate through list
	//If found odd, then delete, else go forward.
	while(curr_iter!=flist.end()){
		if (*curr_iter%2!=0)
			curr_iter=flist.erase_after(prv_iter);
		else{
			prv_iter=curr_iter;
			++curr_iter;
		}
	}
}
*/

//Ex. Messing with insert. Where is elem insert? From left or right side?
/*
int main(){

	vector<int> v{1,2,3,4,5};
	
	v.insert(v.begin(),9);// INSERTED FROM LEFT!
	
	for(auto elem:v)
		cout<<elem<< " ";
}
*/

//Ex. 9.26
/*
Using the following deﬁnition of ia, copy ia into a vector and into a
list. Use the single-iterator form of erase to remove the elements with odd values from your list and the even values from your vector.
int ia[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89 };


int main(){

	int ia[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89 };
	
	//Copy to vector
	vector<int> ivec(ia,ia+(sizeof(ia)/sizeof(*ia)));
	
	//Copy to list
	list<int> ilist(ia,ia+(sizeof(ia)/sizeof(*ia)));
	
	//Remove odd from list
	using lit=list<int>::iterator;
	lit liter=ilist.begin();
	while(liter!=ilist.end()){
	//for( lit iter=ilist.begin();iter!=ilist.end();iter++){ //Wrong! iter++
		if((*liter)%2!=0)
			liter=ilist.erase(liter);
		else
			++liter;
	}
	
	//Remove even from vec
	using vit=vector<int>::iterator;
	vit viter=ivec.begin();
	while(viter!=ivec.end()){
	//for( vit iter=ivec.begin();iter!=ivec.end();iter++){ //Wrong! iter++
		if((*viter)%2==0)
			viter=ivec.erase(viter);
		else
			++viter;
	}
	
	//PRINT
	for(auto elem:ivec){
		cout<<elem<<" ";
	}
	cout<<endl;
	for(auto elem:ilist){
		cout<<elem<<" ";
	}
}
*/

//Ex. 9.23
/*
 Write a program that fetches the ﬁrst element in a vector using at,
the subscript operator, front, and begin. Test your program on an empty vector.


int main(){
	
	vector<int> lookey{1,2,3,4,5,6};
	//vector<int> lookey; //Empty vec. Error core dump
	
	auto &ref1= lookey[0];
	cout<<ref1; //Prints 1
	lookey[0]=5;
	cout<< ref1;//prints 5
	cout<<endl;
	ref1=1;
	
	int val=lookey.at(0);
	cout<<val<<" ";
	val=lookey.front();
	cout<<val<<" ";
	val=*lookey.begin();
	cout<<val<<" ";
	val=*(lookey.end()-1);
	cout<<val<<" ";
}
*/

//Ex.9.20
/*
Write a program to copy elements from a list<int> into two deques.
The even-valued elements should go into one deque and the odd ones into the other


int main(){
	list<int> lst{1,2,3,4,5,6,7,8,9};
	deque<int> even, odd;
	
	using lit=list<int>::iterator;

	for(lit iter=lst.begin();iter!=lst.end();iter++){
		if(*iter%2==0)
			even.push_back(*iter);
		else
			odd.push_back(*iter);
	}
	
	cout<<"Even: ";
	for(auto elem:even){
		cout<<elem<<" ";
	}
	cout<<endl<<"Odd: ";
	
	for(auto elem:odd){
		cout<<elem<<" ";
	}
}
*/

//Ex. 9.19
/*
Rewrite the program from the previous exercise to use a list. List the
changes you needed to make.


//CHANGES: Replaced deque for list
int main(){
	
	//in: strings from cin
	//deque<string> qstr;
	list<string> lstr;
	string word;
	
	while(cin>>word){
		lstr.push_back(word);
	}
	
	//out: print elems use iters
	
	//using qiter=deque<string>::const_iterator;
	using liter=list<string>::const_iterator;
	for(liter iter=lstr.begin();iter!=lstr.end();iter++){
		cout<<*iter<<" ";
	}
}
*/

//Ex. 9.18
/*
 Write a program to read a sequence of strings from the standard input
into a deque. Use iterators to write a loop to print the elements in the deque.


int main(){
	
	//in: strings from cin
	deque<string> qstr;
	string word;
	
	while(cin>>word){
		qstr.push_back(word);
	}
	
	//out: print elems use iters
	
	using qiter=deque<string>::const_iterator;
	for(qiter iter=qstr.begin();iter!=qstr.end();iter++){
		cout<<*iter<<" ";
	}
}
*/

//Ex. messing with insertion
/*
int main(){
	
	vector<int> vec;
	vec.insert(vec.begin(),5,10);
	
	vec.insert(vec.begin(),{1,2,3,4,5});
	vec.insert(vec.end(),{6,7,8,9,0});
	
	//Magic loop
	vector<int>::iterator iter=vec.begin();
	ifstream istr("nrdata.dat");
	int chunk;

	while(istr>>chunk){
		iter=vec.insert(iter,chunk);
	}
	
	for(auto elem:vec){
		cout<<elem<<endl;
	}
	
	//insert from init list
	
	vector<int*> vecid;
}
*/

//Ex. 9.16
/*
Repeat the previous program, but compare elements in a list<int> to a vector<int>.


int main(){
	
	vector<int> ivec{1,2,3,4,5};
	list<int> ilist{1,2,3,4,5,6,7};
	
	//Solve using initialization of TEMPORARY vector
	cout<<(vector<int>(ilist.cbegin(),ilist.cend())==ivec?"Are equal\n":"Are not equal\n");//Remember braces areound ?: operator
	
	//Solve using assignment. Compares two conts
	vector<int> tempvec;
	tempvec.assign(ilist.cbegin(),ilist.cend());
	
	if(ivec==tempvec)
		cout<<"Are equal\n";
	else
		cout<<"Are not equal\n";
	
	//Solve using iterators. Compares only elements in both ranges
	int size=ivec.size()<=ilist.size()?ivec.size():ilist.size();
	using cli=list<int>::const_iterator;
	using cvi=vector<int>::const_iterator;
	
	cli lIter=ilist.cbegin();
	cvi vIter=ivec.cbegin();
	int cnt=1;
		for(;vIter!=(ivec.cbegin()+size); ++vIter,++lIter, ++cnt){
		
		cout<<"Iteration: "<<cnt<<" lInt: "<<*lIter<<" vInt: "<<*vIter<<endl;
		if(*lIter!=*vIter){
			cout<<*lIter<<" "<<*vIter<<endl;
			cout<<"Conts elems are not equal\n";
			return 0;
		}
	}
	cout<<"Conts elems are equal\n";
	return 0;
}
*/

//Ex. 9.15
/*
 Write a program to determine whether two vector<int>s are equal.

int main(){
	
	vector<int> ivec1{1};
	vector<int> ivec2{};
	
	if (ivec1==ivec2)
		cout<<"Are equal\n";
	else
		cout<<"Are not equal\n";
}
*/

//Ex. Containers messing
/*
int main(){
	vector<string> v;
	vector<int> v2;
	
	cout<<v.max_size()<<" "<<v2.max_size()<<endl;
}
*/

//Ex. 9.14
/*
Write a program to assign the elements from a list of char* pointers
to C-style character strings to a vector of strings.


int main(){
	
	list<char*> ptrList{"Ala","ma","kota"};
	
	vector<string> svec;
	
	svec.assign(ptrList.begin(),ptrList.end());
}
*/

//Ex. Playing with container init
/*
int main(){

	//INITIALIZATION
	vector<string> names{"Kamil","Robert", "Michał"};
	list<const char*> pre{"Mr","Ms","Sir"};
	
	//1. copy
	vector<string> newNames(names);
	
	//2. interator copy
	vector<string> newPre(pre.begin(),pre.end()); //Can convert!
	//vector<string> new2Pre(pre); //Error! containers dont match!
	
	//3. Set size and fill
	list<int> ilist(10);
	deque<string> qFill(10,"Ala");
	
	array<char,5> arChar{'a','b','c'}; //Rest is null
	array<int,10> arInt={0,1,2,3,4,5,6,7,8,9}; //regular cinit
	array<int, 5> arInt2; //5 value initialized fields
	
	list<int> lint;
	vector<int> vint;
	
	vector<double> v(lint.begin(), lint.end());
	vector<double> v2(vint.begin(), vint.end()); //Iterator override mismatch
	//vector<double> v3(vint); //Error! Elem type mismatch!
	
}

*/

//Ex. 9.5
/*
Rewrite the previous program to return an iterator to the requested element. Note that the program must handle the case where the element is not found.


using iter=vector<int>::const_iterator;
iter fcn( iter i1, iter i2, int value){
	
	for(;i1!=i2;i1++){
		if(*i1==value)
			return i1; //When found
	}
	return i2;//If not found
}

int main(){
	vector<int> ivec{1,2,3,4,5,6,7,8,9,0};
	
	iter answer=fcn(ivec.begin(), ivec.end(),12);
	
	cout<<boolalpha; //set display true false
	cout<<"Value found?: "<<*answer<<endl;
}
*/


//Ex. 9.4
/*
Write a function that takes a pair of iterators to a vector<int> and an
int value. Look for that value in the range and return a bool indicating whether it was found.


using iter=vector<int>::iterator;
bool fcn( iter i1, iter i2, int value, int* & ptr){
	
	for(;i1!=i2;i1++){
		if(*i1==value)
			return true; //When found
	}
	return false;//If not found
}

int main(){
	vector<int> ivec{1,2,3,4,5,6,7,8,9,0};
	int i=5;
	int *ptr=&i;
	
	bool answer=fcn(ivec.begin(), ivec.end(),12,ptr);
	
	cout<<boolalpha; //set display true false
	cout<<"Value found?: "<<answer<<endl;
}
*/

//Ex. Messing up with stringstreams
/*
//WRITER. Takes
int main(){
	ofstream ostr("writer.txt",ofstream::app);
	istringstream isstr;
	string line, word;
	int wordCount=0;
	while(getline(cin,line)){
		ostr<<line<<endl;
		isstr.str(line);
		while(isstr>>word){
			wordCount++;
		}
		isstr.clear();
	}
	cout<<wordCount;
	ostr.close();
	
	//Remove spaces from text and print it
	ifstream ifstr("writer.txt");
	ostringstream outstr;
	
	while(ifstr>>word){
		outstr<<word;
	}
	cout<<outstr.str();
}
*/

//Ex. 8.11/8.13
/*
The program in this section deﬁned its istringstream object inside the outer while loop. What changes would you need to make if record were deﬁned outside that loop? Rewrite the program, moving the deﬁnition of record outside the while, and see whether you thought of all the changes that are needed.

struct PersonInfo{
	string name;
	vector<string> phones;
};

int main(){
	
	string line, word;
	vector<PersonInfo> people;
	istringstream record;
	ifstream ifstr("ppldata.dat");
	
	int cntp=0;
	while(getline(ifstr,line)){
		PersonInfo info;
		record.str(line);//Put line to record
		record>>info.name; //Put first word to name field.
		while(record>>word){
			info.phones.push_back(word);
		}
		people.push_back(info);
		record.clear(); //HAHAHA Without it things are not working!!!
	}
	
	//Print it
	int cnt=0;
	for(PersonInfo p:people){
		cout<<++cnt;
		cout<<p.name<<" ";
		for(auto phn: p.phones){
			cout<<phn<<" ";
		}
		cout<<endl;
	}
	
	// string a{"Ala"};
	// istringstream strng;
	// //istringstream strng(22); //Will not work! Can be only string
	// strng.str("ala");
}
*/

//Ex. 8.10
/*
 Write a program to store each line from a ﬁle in a vector<string>. Now use an istringstream to read each element from the vector a word at a time.


int main(){
	vector<string> text;
	string line;
	//read from file and store lines to vector.
	ifstream ifstr("loremipsum.txt");
	
	while(getline(ifstr,line)){		// Read line from file. Copy to line
		text.push_back(line);		// Push line to vector
	}
	
	
	
	for (string ln:text){			//Take one line of text
		istringstream isstr(ln);	//Assing this line to isstream
		string word;
		
		while(isstr>>word){			//Read each word from line...
			cout<<word<<" ";		//and print it a word at time
		}
		cout<<"\n";					//Break the line
	}
}
*/

//Ex. 8.9
/*
Use the function you wrote for the ﬁrst exercise (8.1) in § 8.1.2 (p. 314) to print the contents of an istringstream object.


istream& fcn(istream &is){
	string word;
	int cnt=0;
	while(is>>word){ //Send stream to console
		cout<<word<<" ";
		cnt++;
	}
	
	cout<<endl;
	cout<<"Word number is "<<cnt<<endl;
	cout<<is.rdstate();
	is.clear();//Reseting stream so it is valid
	return is;
}
int main(){
	
	string line{"Ala ma kota a ania ma psa!"};
	istringstream isstr(line);
	fcn(isstr);
}
*/

//Ex. 8.7/8.8
/*
Revise the bookstore program from the previous section to write its output to a ﬁle. Pass the name of that ﬁle as a second argument to main.

Make sure to append data to file


int main(int argc, char** argv){
	
	//cout<<argv[1];
	ifstream str;
	ofstream ostr;
	
	ostr.open(argv[2],ofstream::app); //Keep content
	str.open(argv[1]);
		
	Sales_data total, trans;
	
	if (read(str,total)){
		while(read(str,trans)){
			if (total.isbn()==trans.isbn())
				total=add(total,trans);
			else{
				printOut(ostr,total)<<endl;
				total=trans;
			}
		}
		printOut(ostr,total)<<endl;		
	}else
		cerr<<"Wrong input\n";
	str.close();
}
*/

//Ex. Play with file modes
/*
Check how app mode affects file

void inFile(ofstream &ostr, const string name){
	
	ostr.open(name, ofstream::app | ofstream::out);//Keep file content
	//ostr.open(name);//Erease file every time
	string data;
	cout<<"Enter data:\n";
	while(getline(cin,data) && data!="end"){
		ostr<<data<<endl;
	}
	cout<<"Insertion complete"<<endl;
}


int main(int argc, char** argv){
	
	ofstream ostr;
	
	inFile(ostr,argv[1]);
	//Enter text from keyboard
	
	//Write to file without any modes (Should delete)
	//Use app mode to append writes to end of file.	
}
*/

//Ex. 8.6
/*
Rewrite the bookstore program from § 7.1.1 (p. 256) to read its transac-
tions from a ﬁle. Pass the name of the ﬁle as an argument to main (§ 6.2.5, p. 218).



//Pass name to main arvg
int main(int argc, char** argv){
	
	//cout<<argv[1];
	ifstream str;
	str.open(argv[1]);
		
	Sales_data total, trans;
	
	if (read(str,total)){
		while(read(str,trans)){
			if (total.isbn()==trans.isbn())
				total=add(total,trans);
			else{
				printOut(cout,total)<<endl;
				total=trans;
			}
		}
		printOut(cout,total)<<endl;		
	}else
		cerr<<"Wrong input\n";
	str.close();
}
*/

//Ex. 8.5
/*
Write a function to open a ﬁle for input and read its contents into a
vector of strings, storing each line as a separate element in the vector.

Rewrite the previous program to store each word in a separate element.

vector<string> readFile(const string name){
	vector<string> content;
	
	
	//Open file
	ifstream file;
	file.open(name);
	
	string temp;
	
	//Read each line to separate string in vector
	while(file>>temp){
			content.push_back(temp);
	}
	
	file.close();
		
	return content;
}

int main(){
	
	vector<string> print;
	print=readFile("data.dat");//assigning one vector to another

	//Output with iterators
	using it=vector<string>::iterator; //Shorten type
	int cnt=0;
	for(it iter=print.begin();iter!=print.end();++iter,++cnt){
		if((cnt%3)==0) cout<<endl;
		cout<<*iter<<" ";
	}
	cout<<cnt<<endl;
}
*/

//Ex. 8.4
/*
Write a function to open a ﬁle for input and read its contents into a
vector of strings, storing each line as a separate element in the vector.


vector<string> readFile(const string name){
	vector<string> content(12);
	
	
	//Open file
	ifstream file;
	file.open(name);
	
	string temp;
	
	//Read each line to separate string in vector
	while(getline(file,temp)){
			content.push_back(temp);
	}
	
	//Input with iterator
	vector<string>::iterator it=content.begin();
	while(getline(file,temp)){
		*it=temp;
		++it;
	}
	
		file.close();
		
	return content;
	
}

int main(){
	
	vector<string> print;
	print=readFile("data.dat");//assigning one vector to another

	
	//Simple output
	for(auto &s:print)
		cout<<s<<"\n";
	
	
	//Output with iterators
	using it=vector<string>::iterator; //Shorten type
	for(it iter=print.begin();iter!=print.end();++iter)
		cout<<*iter<<endl;
		
}
*/
	
//Ex. Messing with files
/*
int main(){
	
	ifstream str("data.dat");
	ofstream ostr("output.dat",ofstream::app);
	
	
	//Open file until succeed
	while(!str.is_open()){
		string file;
		cout<<"\nEnter file name: ";
		cin>>file;
		str.open(file);	
	}
	if(str.is_open())
		cout<<"File successfully opened\n";
	else 
		cout<<"File opening failed\n";
	
	
	string buffer,a,b,c;

	getline(str,buffer);
	cout<<buffer<<endl;
	
	str>>a>>b>>c;
	ostr<<a<<b<<c<<endl;
	cout<<a+b+c<<endl;
	
	str.close();
	ostr.close();
}
*/

//Ex. Tying and untying cin with cout
/*
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);//untie cin
	int a=0;
	cout<<"Input sth: ";
	cin>>a; //cout buffer is flushed first. User knows what is happening.
	cout<<"Input value is: "<<a;
	cin.tie(&cout); //tie again
	cout<<"\nEnter nr: ";
	cin>>a;
	cout<<"New a is: "<<a<<endl;
}
*/

//Ex. 8.1/8.2
/*Write a function that takes and returns an istream&. The function should read the stream until it hits end-of-ﬁle. The function should print what it reads to the standard output. Reset the stream so that it is valid before returning the stream.


istream& fcn(istream& is){
	string a;
	int cnt=0;
	while(is>>a && cnt<10){
		cout<<a<<" ";
		cnt++;
	}
	//Send stream to console
	cout<<endl;
	cout<<"Counter is "<<cnt<<endl;
	cout<<is.rdstate();
	is.clear();//Reseting stream so it is valid
	return is;
}

int main(){
	fcn(cin);
}
*/

//Ex. Little play with stream states
/*
I coundlt have make an object of istream
isteam obj1;
goodbit,eofbit ect are variables with bit flipped
I think there is a variable holding state of stream. But maybe not. It may just return a number 0,1,2,4 of type iostate

Using clear(), rdstate() and setstate() I can manipulate on bits.


int main(){
	
	int a=0;
	if(!(cin>>a)){
		cerr<<"There was an error a= "<<a<<endl;
		cout<<iostream::goodbit<<endl;
		cout<<iostream::badbit<<endl;
		cout<<iostream::eofbit<<endl;
		cout<<iostream::failbit<<endl;
		cout<<cin.rdstate()<<endl<<endl;
		
		cin.clear(iostream::failbit);
		cout<<cin.rdstate()<<endl<<endl;
		cin.clear(iostream::eofbit);
		cout<<cin.rdstate()<<endl;
	} else {
		cout<<a<<" is good"<<endl;
		cout<<iostream::goodbit<<endl;
		cout<<iostream::badbit<<endl;
		cout<<iostream::eofbit<<endl;
		cout<<iostream::failbit<<endl;
		cout<<cin.rdstate()<<endl;
	}
}
*/

//Ex. 7.57
/*
Write your own version of the Account class.

Reqirements:
-It has amount and name as non static
-It has interestRate as common for all objects
-Amount is calculated for each object as amount*rate
-Setting of rate with function
-Fcn to return rate value
-Constructor for both variables


class Account{
	public:
	Account(string n="", double a=0.0):name(n), amount(a){}
	void setAmount(){
		amount+=amount*interestRate;
	}
	void print(){
	cout<<"Name: "<<name<<"\tAmount: "<<amount<<endl;	
	}
	
	static double getRate(){
		return interestRate;
	}
	
	static void setRate(double r){
		interestRate=r;
	}
	
	private:
	string name;
	double amount;
	static double interestRate;
};

double Account::interestRate{0.0};//Initialization

int main(){

	vector<Account> vec{{"Kamil",10000},{"Wiktor",5000}};
	using st=vector<Account>::size_type;
	
	for(st i=0;i<vec.size();i++){
		vec[i].setRate(0.05);
		vec[i].setAmount();
		vec[i].print();
	}	
}
*/

//Ex. 7.58
/*
I cant initialize vector vec in class
Rate cant be initialized either.


class Example {
public:
static double rate;
static const int vecSize = 20;
static vector<double> vec;
};
// example.C

double Example::rate;
vector<double> Example::vec (vecSize);

int main(){

cout<<Example::vec.size();}
/*

class A{
	public:
	static int test(int a=var){
		return a;
	}
	
	static int var;
	int b;
	static A obj; 
};

int A::var=7;

static int b=6;
int test2(int a=b){
		return a;
	}


int main(){

	cout<<A::obj.var+5<<endl;
	cout<<A::obj.test()<<endl;
	
}
*/

//Ex. 7.53 NOT DONE! RETURN LATER!
/*
Deﬁne your own version of Debug.

1. What is constexpr and where is it used?
2. What is constexpr function? What cechy it has? What is it used for?
3. What is literall class? What are it's cechy? What is it used for?

class Debug {
	public:
	//ctors
	constexpr Debug(bool b = true): hw(b), io(b), other(b) { }
	constexpr Debug(bool h, bool i, bool o):
	hw(h), io(i), other(o) { }
	
	//mbr fcns
	constexpr bool any() { return hw || io || other; }
	void set_io(bool b) { io = b; }
	void set_hw(bool b) { hw = b; }
	void set_other(bool b) { other = b; }
	
	//data mbrs
	private:
	bool hw; // hardware errors other than IO errors
	bool io; // IO errors
	bool other; // other errors
	};
	

int main(){

	Debug a;
}
*/

//Ex. Some fun with conversion!
/*
class A{
	public:
int a;
	A(int i=0):a(i){}
};

void print(const A &var){
cout<<var.a<<endl;
}

int main(){
print(5);//Implicit conversion from literal 5 to object
	
print(A(5));//Explicit conversion from 5 to object
	
print(int(5));
}
*/

//Ex. 7.44/7.45
/*
Is the following declaration legal? If not, why not?
vector<NoDefault> vec(10);

Nope. But can be declared like below.

What if we deﬁned the vector in the previous execercise to hold ob-
jects of type C?

Yes its possible.


class NoDef{
	int a;
	public:
	NoDef(int i):a(i){cout<<"Init with "<<i<<endl;}
};

class C{
	NoDef obj1;
	
	public:
	C():obj1(0){} //Default ctor

};

int main(){
	vector<NoDef> vec{10,20,30};
	vector<C> vec2(10);
	vector<NoDef> vec3(10,6);
	cout<<vec3.size()<<endl;
}
*/

//Ex. 7.41
/*
Rewrite your own version of the Sales_data class to use delegating constructors. Add a statement to the body of each of the constructors that prints a message whenever it is executed. Write declarations to construct a Sales_data object in every way possible. Study the output until you are certain you understand the order of execution among delegating constructors.

	
int main(){

	Sales_data sl1;
	cout<<"Next"<<endl;
	Sales_data sl2("Book",10,15);
	cout<<"Next"<<endl;
	Sales_data sl3("NoName");
	cout<<"Next"<<endl;
	Sales_data sl4(cin);
}
/*

//Ex.7.40/7.42 Vechicle
/*
Determine what data are needed in the class. Provide an appropriate
set of constructors. Explain your decisions.

I have chosen 3 constructors.
First is general. It initializes all data members.
Second is delegating default constructor. It uses first one. Necesarty one.
Last is ctor using input stream in case user want to enter data from kbrd

class Vehicle;
std::istream& read(std::istream&, Vehicle&); //Declaration without any def
class Vehicle{
	string name;
	string color;
	int doorNr;
	double hp;
	
	public:
	
	Vehicle(string n, string c, int d, double h):
	name(n), color(c), doorNr(d), hp(h){}// Main constructor
	
	Vehicle():Vehicle("","",0,0.0){}//Default
	Vehicle(iostream &is){read(is, *this);} //Input
};

int main(){}
*/

//Ex. Initializing class without default constructor.
/*
What if class doesnt have any constructor. Can another class not provide initializiators?
Nope. It has to provide initializers.

When class have no default constructor?
When it has other constructors, but non is without params(default)

What if class has no constructor at all? Then synthesized will be generated, and then object of that class does'nt have to be initialized.


class A{
	int a;
	int b;
	
	public:
	//A(){}
	//A(int putA):a(putA){}
};

class B{
	A objectA;
	public:
	B(){}
	//B():objectA(7){}
	//B(A param): objectA(param){}
	
};

int main(){}
*/

//Ex. Type name hiding
/*
When declared a type above the class, then if I want to use the same name for new type inside the class I HAVE TO DECLARE IT BEFORE FIRST USAGE OF TYPE!

typedef string Type;
Type initVal();

class Exercise {
	public:
	typedef double Type;
	Type setVal(Type);
	Type initVal(){return 2.0;}
	
	private:
	int val;
};

Exercise::Type Exercise::setVal(Type parm) {
val = parm + initVal();
return val;
}

int main(){}
*/

//Ex. Name lookup
/*
Write a class.
Declare a function set() to set a data member
Define set outside
Make set use fcn multi() wchih multiplies a number
Multi() is now:
	- declared BEFORE set() when set is defined outside class
	- declaread after class, when set() is defined inside class

What is interpretation?
When member fcn is defined outside, it looks for names ABOWE itself.
When it is defined inside the class, it looks for names ABOWE tha class. Need to make prototype. 

Can external function use private object members when used inside member function?
YES! It gets it as a parameter, which is accesed by member function.


int multip(int,int);
class A{
	int number=1;
	public:
	//void set(int);
	void set(int a){
number=multip(a+number,3);	
}
	void print(){cout<<number<<endl;}
};

int multip(int n, int m){
return n*m;	
}



int main(){

	A kam;
	kam.print();
	kam.set(5);
	kam.print();
}
*/

//Ex. 7.31
/*
Deﬁne a pair of classes X and Y, in which X has a pointer to Y, and Y has
an object of type X.

class Y;
class X{
	Y *ptrToY;//I can declare pointer and reference...
	//Y obj; //But cant declare object of incomplete type...
	
	void getA(Y& item){
		//item.a=10; //...and can't use members of incomplete class
	}
};

class Y{
	public:
	X objOfX;
	int a;
};

int main(){
}
*/

//Ex. 7.27
/*
Add the move, set, and display operations to your version of
Screen. Test your class by executing the following code:


int main(){
	Screen myScreen(5,5,'.');
	cout<<"\n";
	myScreen.move(4,0).set('#').display(cout);
	myScreen.display(cout);
	cout<<"\n";
}
*/

//Ex. 7.25
/*
Write your own version of the Screen class.

To make our class more useful, we’ll add a constructor that will let users deﬁne the size and contents of the screen, along with members to move the cursor and to get the character at a given location:

In addition to deﬁning the Screen class, we’ll deﬁne a window manager class
that represents a collection of Screens on a given display. This class will have a vector of Screens in which each element represents a particular Screen. By de-
fault, we’d like our Window_mgr class to start up with a single, default-initialized Screen. Under the new standard, the best way to specify this default value is as an in-class initializer


//Class Screen
class Screen{
public:
	using pos=std::string::size_type;
	Screen()=default;
	//Fills screen(width x height) with character c
	Screen(pos ht, pos wd, char c=' '):height(ht), width(wd), contents(ht*wd,c){}
	
	//get char on position
	char get()const{ return contents[cursor]; }//Inline implicitly
	char get(pos, pos)const;
	Screen& move(pos row, pos col);
	Screen& set(char c){
		contents[cursor]=c;
		return *this;
	}
	Screen& set(pos row, pos col, char c);
	const Screen& display(std::ostream&)const;
		
private:
	pos cursor=0;
	pos height=0, width=0;
	std::string contents;
	mutable size_t getAccess_ctr=0; //Gts modified in const object
	
};

const Screen& Screen::display(std::ostream& os)const{
	for(size_t row=0;row<height;++row){
		for(size_t col=0;col<width;col++){
			os<<contents[row*width+col];
		}
		os<<endl;
	}
	return *this;
}

Screen& Screen::set(pos row, pos col, char c){
	row*=width;
	contents[row+col]=c;
	return *this;
}

inline
char Screen::get(pos row, pos col)const{
	getAccess_ctr++;//It will modify member even in const object
	row=(row)*width;
	return contents[row+col];	
}

//Make move function. Set cursor position (row, col_. Make it chainable, 
inline
Screen& Screen::move(pos row, pos col){
	row=row*width;
	cursor=row+col;
	return *this; // (*) because I want to return an object
}

class Window_mgr{
	private:
	std::vector<Screen> screens{Screen(25,80,' ')};
};

int main(){
	const Screen obj;
	obj.get();
}
*/

//Ex. Read and write to file.
/*
Create new file
Read from data.dat
Write each data.dat line with line number
*/


//Ex. Class Teplates and member functions
/*

Make class whose member fcns gonna specialize in processing different types
char, string, int


template<class T>
	class Check{
		public:
		Check(T x){
			cout<<x<<" is a regular number\n";
		}
	};

template<>
class Check<char>{
	public:
	Check(char x){
		cout<<x<<" is a char\n";
	}
};

template<>
class Check<string>{
	public:
	Check(string s){
		cout<<s<<" is a string\n";
	}
};

int main(){

	Check<int> ob1(5);
	Check<char> ob2('F');
	Check<string> ob3("Ala ma kota");
	
}
*/

//Ex. Function Templates
/*
Make function template.


template<class T, class K>
K add(T a, K b){

	return a+b;
}

int main(){

	cout<<add(5,6.12);	
}
*/

//Ex. One class calls another
/*
I want to have one class to call object of another class.
Used to divide big classes to smaller doing one thing.
Obj is called in constructor

Desk, that will have heights and color class
Desk has print function
Color can be changed with setColor, and taken with getColor.


class Color{
private:
	string color;
	
public:
	Color (string s):color(s){}
		
	string getColor(){
		return color;
	}
};

class Desk{
private:
	int height=0;
	Color col;
public:
	//ctor
	Desk(int h, string c):height(h),col(c){
		cout<<"Params set!\n";	
	}
	
	//Output of desk params
	void print(){
		cout<<"Heights is "<<height<<" and color is "<<col.getColor()<<endl;
	}
};
	
int main(){

	Desk table(10,"Red");
	table.print();	
}
*/

//Ex. Polimorphism
/*
Make mother class
Make derived class
Override function

When calling react mother and derived functions have different reactions.
Write different thing on screen


class Person{
protected:
	int wiek=0;
public:
	Person()=default;
	
	void setWiek(int a){
	wiek=a;
	}
	//Reaction
	void react(){
		cout<<"I'm Person! "<<wiek<<"\n";
	}
};

class Kamil: public Person{
public:
	Kamil()=default;
	
	//Reaction Kamil
	void react(){
	cout<<"I'm Kamil! "<<wiek<<"\n";	
	}
};

class Wiktor:public Person{
public:
	Wiktor()=default;
	
	void react(){
		cout<<"I'm Wiki! "<<wiek<<"\n";	
	}
};

int main(){
	//use ptrs
	Person *per= new Person; //Dynamic memory alloc
	Kamil *kam= new Kamil;
	Wiktor *wik= new Wiktor;
	
	
	Person *man1= per;
	Person *man2= kam;
	Person *man3= wik;
	
	//Set age
	man2->setWiek(32);
	man3->setWiek(25);
	
	//Check reactions. Functions overridden!
	man1->react();
	man2->react();
	man3->react();
	
}
*/

//Ex. Operator overloading
/*
Youre selling computers. Create class trans
X Use pointers to access class etc.
Make it have name, items sold and price
Create costructor to initialize object with 3 params
Overload + operator to add sold items and estimate average price
Create method to print its content


//Inheritance of class!
class Mother{
	protected:
	int a;
	private:
	int b;
	int c;
	int d;
	int e;
	
	public:
	void print(){cout<<a<<endl;}
	void set(int x){a=x;}
};

//Class declaration
class Comp:public Mother
{
	public:
	Comp()=default;
	Comp(string n, int s, double p):m_name(n), m_sold(s), m_price(p){}
	Comp(istream&);
	
	Comp operator+(Comp&);//Overloaded declaration
	void printComp();
	void access(int x){a=x;}
	
	private:
	string m_name;
	int m_sold;
	double m_price;
};

//Class definitions
Comp::Comp(istream& is){ //Constructor
	is>>m_name>>m_sold>>m_price;	
}

Comp Comp::operator+(Comp &obj){
	Comp temp;
	temp.m_name=this->m_name;
	temp.m_sold=this->m_sold + obj.m_sold;
	temp.m_price=(this->m_price+obj.m_price)/2;
	return temp;
}

void Comp::printComp(){
	//Take object and print its data members
	
	cout<<m_name<<"\t"<<m_sold<<"\t"<<m_price<<endl;
}

int main(){

	Comp c1(cin);
	Comp c2(cin);
	//Initialize c3 with sum of c1 and c2
	Comp c3=c1+c2;
	
	//Print results
	c1.printComp();
	c2.printComp();
	c3.printComp();
	
	//Using inherited class
	cout<<sizeof(Comp)<<endl;//More 
	c1.access(16);
	c1.print();
}
*/
	
//Ex. Using MyClass.cpp and MyClass.h
/*
Redistribute code to header and source


int main()
{
	MyClass object("Ala");
	object.setName("Ala ma kota");
	cout<<object.getName()<<endl;
}

*/

//Ex. 7.15
/*
Add appropriate constructors to your Person class.


class Person{
	public:
	std::string m_name;
	std::string m_address;

	
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
	
	//Read data to object
	//IN - two values from keyboard
	
	std::istream& read(std::istream &is){
		is>>m_name>>m_address;
		return is;
	}
	
	//Print data
	//OUT - two values out
	
	std::ostream& print(std::ostream &os){
		os<<m_name<<"\t"<<m_address;	
		return os;
	}
	
};

int main(){}
*/

//Ex. 7.13
/*
Rewrite the program from page 255 to use the istream constructor.

int main(){
	Sales_data total(cin);
	if(!total.isbn().empty()){
		while(cin){
			Sales_data trans(cin);
			if(total.isbn()==trans.isbn())
				total.combine(trans);
			else{
				printOut(cout,total)<<endl;
				total=trans;
			}
		}
		//printOut(cout,total)<<endl; //No need for this line.
	}else
		cerr<<"Invalid input";
	return 0;
}
*/

//Ex. 7.11
/*
Add constructors to your Sales_data class and write a program to
use each of the constructors.

class Sales_data{
	private:
	std::string bookNo;
	unsigned int units_sold=0;
	double revenue=0.0;
	
	public:
	//Constructors
	//1. default
	Sales_data() = default;
	
	//2. enter data from keyboard
	Sales_data(istream& is){
	read(is,*this);
	}
	
	//3. Enter just isbn
	Sales_data(std::string& s):bookNo(s) {}
	
	//4. initialize values from param list.
	Sales_data(std::string s, unsigned int n, double p)
	:bookNo(s), units_sold(n),revenue(n*p) {} 
	
	//Function prototypes
	Sales_data& combine(const Sales_data&);
	std::string isbn() const;
};


int main(){

	Sales_data item;//Default
	printOut(cout,item)<<endl;
	
	Sales_data item2("Numerek"); //Just string, rest by inclass init
	printOut(cout,item2)<<endl;
	
	Sales_data item3(cin); //Enter from keyboard
	printOut(cout,item3)<<endl;
	
	Sales_data item4("0-201-70353-X", 4, 24.99); //Initialie all
	printOut(cout,item4)<<endl;
}
*/	

//Ex. 7.9
/*
Add operations to read and print Person objects to the code you wrote
for the exercises in § 7.1.2 (p. 260).


	//Read data to object
	//IN - two values from keyboard
	
	std::istream& read(std::istream &is){
		is>>m_name>>m_address;
		return is;
	}
	
	//Print data
	//OUT - two values out
	
	std::ostream& print(std::ostream &os){
		os<<m_name<<"\t"<<m_address;	
		return os;
	}

int main()
{}
*/

//Ex. 7.7
/*
Rewrite the transaction-processing program you wrote for the exercises
in § 7.1.2 (p. 260) to use these new functions.


int main()
{
	
	Sales_data total, trans;
	
	if (read(cin,total)){
		while(read(cin,trans)){
			if (total.isbn()==trans.isbn())
				total=add(total,trans);
			else{
				printOut(cout,total)<<endl;
				total=trans;
			}
		}
		
		printOut(cout,total)<<endl;		
	}else
		cerr<<"Wrong input\n";
}
*/

//Ex.7.6
/*
Deﬁne your own versions of the add, read, and print functions.


//Add two transactions
Sales_data add(const Sales_data &it1,const Sales_data &it2){
	
	Sales_data sum;
	sum.combine(it1).combine(it2); //Add units
		
	return sum;
}

//Read transaction
istream& read(istream &is, Sales_data &item){
	double price=0;
	is>>item.bookNo>>item.units_sold>>price;
	item.revenue=item.units_sold*price;
	
	return is;

}

//Print output
ostream& printOut(ostream& os, const Sales_data &item){
	os<<item.bookNo<<"\t"<<item.units_sold<<"\t"<<item.revenue<<"\t"
		<<item.revenue/item.units_sold;
	return os;
}

int main(){}
*/
	
//Ex. 7.5
/*
Provide operations in your Person class to return the name and ad-
dress. Should these functions be const? Explain your choice.


class Person{
	string m_name;
	string m_address;
	
	std::string getName(const Person &man) const{
		return man.m_name;
	}
	
	std:: string getAddress(const Person &man) const{
		return man.m_address;
	}
	
};

int main(){}
*/
	
//Ex. 7.4
/*
Write a class named Person that represents the name and address of
a person. Use a string to hold each of these elements. Subsequent exercises will
incrementally add features to this class.


class Person{
	string m_name;
	string m_address;
	
};
*/

//Ex. 7.3
/*
Revise your transaction-processing program from § 7.1.1 (p. 256) to use
these members.


//Read transaction
bool read(Sales_data &item){
	double price=0;
	if(cin>>item.bookNo>>item.units_sold>>price){
		item.revenue=item.units_sold*price;
		return true;
	}else
		return false;	
}

//Print output
void printOut(const Sales_data &item){
	cout<<item.bookNo<<"\t"<<item.units_sold<<"\t"<<item.revenue<<"\t"
		<<item.revenue/item.units_sold<<endl;
}

int main()
{
	
	Sales_data total, trans;
	
	if (read(total)){
		while(read(trans)){
			if (total.isbn()==trans.isbn())
				//add(total,trans);
				total.combine(trans);
			else{
				printOut(total);
				total=trans;
			}
		}
		
		printOut(total);		
	}else
		cerr<<"Wrong input\n";
}
*/


//Ex. 7.2
/*
Add the combine and isbn members to the Sales_data class you
wrote for the exercises 7.1


class Sales_data
{
	public:
		std::string bookNo;
		unsigned int units_sold=0;
		double revenue=0.0;
	
	
	Sales_data& combine(const Sales_data&);
	string isbn() const;
	
};

//combine- add one member to another
Sales_data& Sales_data:: combine(const Sales_data &rhs){
	units_sold+=rhs.units_sold;
	revenue+=rhs.revenue;
	return *this;
}

//isbn - Fetch bookNo from object
string Sales_data:: isbn()const {
	return bookNo;
}

int main()
{
}
*/

//Ex. 7.1
/*
Write a program that reads several transactions and counts how many
transactions occur for each ISBN.

Test program by giving multiple transactions representing
multiple ISBNs. The records for each ISBN should be grouped together.


//Read transaction
bool read(Sales_data &item){
	double price=0;
	if(cin>>item.bookNo>>item.units_sold>>price){
		item.revenue=item.units_sold*price;
		return true;
	}else
		return false;	
}

//Print output
void printOut(const Sales_data &item){
	cout<<item.bookNo<<"\t"<<item.units_sold<<"\t"<<item.revenue<<"\t"
		<<item.revenue/item.units_sold<<endl;
}

//Add two transactions
void add(Sales_data &it1,const Sales_data &it2){
	it1.units_sold+=it2.units_sold; //Add units
	it1.revenue+=it2.revenue; //Add revenue
}

	//Compare two transactions
string isbn(const Sales_data &item){
			return item.bookNo;
	}

int main()
{
	
	Sales_data total, trans;
	
	if (read(total)){
		while(read(trans)){
			if (isbn(total)==isbn(trans))
				add(total,trans);
			else{
				printOut(total);
				total=trans;
			}
		}
		
		printOut(total);		
	}else
		cerr<<"Wrong input\n";
}
*/

//Ex.6.54/55/56
/*
Write a declaration for a function that takes two int parameters and
returns an int, and declare a vector whose elements have this function pointer type.

Write four functions that add, subtract, multiply, and divide two int
values. Store pointers to these functions in your vector from the previous exercise.


int funct(int a, int b);


//Functions add,sub,mul,div
int add(int a, int b){
	return a+b;
}

int sub(int a, int b){
	return a-b;
}

int mul(int a, int b){
	return a*b;
}

int division(int a, int b){
	return (b!=0?a/b:a);
}

using fcnPtr=int(*)(int,int);

fcnPtr retFcnPtr(int a){
	
	if (a==1)
		return add;
	else
		return sub;
}

int main()
{
	//Vector to store pointer to above functions
	vector<int(*)(int,int)> pvec;//{add,sub,mul,division};
	
	//Fill in vector with push back...
	pvec.push_back(add);
	pvec.push_back(sub);
	pvec.push_back(mul);
	pvec.push_back(division);
	
	//using fcnPtr=int(*)(int,int);
	//decltype(pvec[0]);
	
	for( int(*fcn)(int,int) :pvec)
		cout<<fcn(10,3)<<endl;
	
	//Returing function pointer
	int a=retFcnPtr(1)(6,2);
	cout<<a;
}
*/

//Ex. 6.51
/*
 Write all four versions of f. Each function should print a distinguish-
ing message. Check your answers for the previous exercise.


void f(){
	cout<<"Empty"<<endl;
}

void f(int){
	cout<<"(int)"<<endl;	
}

void f(int, int){
	cout<<"(int, int)"<<endl;
}

void f(double, double = 3.14){
	cout<<"(double, double=3.14)"<<endl;
}

int main()
{
	//f(2.56, 42); //Ambigous
	f(42);
	f(42, 0);
	f(2.56, 3.14);
}
*/
	
//Ex. 6.47
/*
Revise the program you wrote in the exercises in § 6.3.2 (p. 228) that
used recursion to print the contents of a vector to conditionally print information about its execution. For example, you might print the size of the vector on each call.
Compile and run the program with debugging turned on and again with it turned off.

#define NDEBUG //Turn it ON or OFF to enable compilation of debugging part.
void printVec(const vector<int> &ivec, vector<int>::iterator iter){
	
	if(iter!=ivec.end()){
		//Debug info
		#ifndef NDEBUG
			cout<<ivec.size()<<" ";
		#endif
		
		cout<<*iter<<endl;	
		printVec(ivec,iter+1);
	}
}

int main()
{
	
	vector<int> ivec{1,2,3,4,5,6,7,8,9,10};
	printVec(ivec,ivec.begin());
}
*/

//Ex. 6.44
/*
Rewrite the isShorter function from § 6.2.2 (p. 211) to be inline.

// compare the length of twostrings
bool isShorter(const string &s1, const string &s2)
{
	return s1.size() < s2.size();
}
//-----------------------


inline bool isShorter(const string &s1, const string &s2){
	return s1.size()<s2.size();
}
*/
	
//Ex. 6.42
/*
Give the second parameter of make_plural (§ 6.3.2, p. 224) a default
argument of ’s’. Test your program by printing singular and plural versions of the words success and failure.


// return the plural version of word if ctr is greater than 1
string make_plural(size_t ctr, const string &word, const string &ending="s")
{
	return (ctr > 1) ? word + ending : word;
}

int main()
{
	cout<<make_plural(2,"Kamil");
}
*/

//Ex. 6.38
/*
Revise the arrPtr function on to return a reference to the array.


int odd[] = {1,3,5,7,9};
int even[] = {0,2,4,6,8};
// returns a pointer to an array of ﬁve int elements
decltype(odd) *arrPtr(int i)
{
	return (i % 2) ? &odd : &even; // returns a pointer to the array
}
//---------------------

int odd[] = {1,3,5,7,9};
int even[] = {0,2,4,6,8};

decltype(odd) &arrPtr(int i) {
	return i%2 ? odd : even;	
}


int main()	
{
	arrPtr(4)[2]=10; //Hahahah very funny :D reference + []
	cout<<even[2];
	return 0;	
}
*/

//Ex. 6.37
/*
Write three additional declarations for the function in the previous ex-
ercise. One should use a type alias, one should use a trailing return, and the third
should use decltype. Which form do you prefer and why?


string (&funct(const string s))[10]; //Main

auto funct(const string s) ->int(&)[10]; //Trailing return

using strArr=string[10];
typedef string strArr[10]; 
strArr &funct(const string s); //Using aliases

string array[10];
decltype(array) &funct(const string s);//Using decltype

*/
	
//Ex. 6.36
/*
Write the declaration for a function that returns a reference to an array
of ten strings, without using either a trailing return, decltype, or a type alias.


string (&funct(const string s)) [10];

int main()
	
{
return 0;
}
*/
//Ex. 6.33
/*
Write a recursive function to print the contents of a vector.


void printVec(const vector<int> &ivec, vector<int>::iterator iter){
	
	if(iter!=ivec.end()){
		cout<<*iter<<endl;	
		printVec(ivec,iter+1);
	}
}

int main()
{
	
	vector<int> ivec{1,2,3,4,5,6,7,8,9,10};
	printVec(ivec,ivec.begin());
}
*/
//Ex.6.30
/*
// incorrect return values, this code will not compile
bool str_subrange(const string &str1, const string &str2)
{
	// same sizes: return normal equality test
	if (str1.size() == str2.size())
		return str1 == str2; // ok: == returns bool
	// ﬁnd the size of the smaller string ; conditional operator.
	auto size = (str1.size() < str2.size()) ? str1.size() : str2.size();
	// look at each element up to the size of the smaller string
	for (decltype(size) i = 0; i != size; ++i) {
		if (str1[i] != str2[i])
		return; // error #1: no return value; compiler should detect this error
	}
	// error #2: control might ﬂow off the end of the function without a return
	// the compiler might not detect this error
}
*/

//Ex. 6.27
/*
Write a function that takes an initializer_list<int> and pro-
duces the sum of the elements in the list.


int sum(initializer_list<int> lst){
	int sum=0;
	for (initializer_list<int>::iterator iter=lst.begin();iter!=lst.end();++iter)
	sum+=*iter;
	return sum;
}

int main()
{
	cout<<sum({10,20,23,12,12,33})<<endl;
	
}
*/
	
//Ex. 6.26
/*
Write a program that accepts the options presented in this section. Print
the values of the arguments passed to main.


int main( int argc, char *argv[])
{
	//print options until null
	
	for(int i=0;argv[i]!=0;++i)
		cout<<argv[i]<<endl;
		
}
*/

//Ex. 6.25
/*
Write a main function that takes two arguments. Concatenate the sup-
plied arguments and print the resulting string.

int main(int argc, char *argv[])
{
	const size_t size=strlen(argv[1])+strlen(argv[2]);
	char cat[size+1];
	//char *s1=argv[1];
	strcpy(cat,argv[1]);
	strcat(cat,argv[2]);
	cout<<cat;
}
*/
//Ex. 6.23
/*
Write your own versions of each of the print functions presented in
this section. Call each of these functions to print i and j deﬁned as follows:
int i = 0, j[2] = {0, 1};	


void print(const int a){
	cout<<a;
}
void print(const int* a){
	cout<<*a;
}

//Passing size
void print(const int* arr,size_t size){
	for(size_t i=0;i!=size;++i)
		cout<<arr[i]<<" ";
}

//Referencing with size
void print(const int (&arr)[2]){	
	for (int i:arr)
		cout<<i<<" ";
}

//Looking by iterators
void print(const int *beg, const int *end){
	for(const int* i=beg;i!=end;++i)
		cout<<*i<<" ";
}

//By null delimiter
void print(const char *p){
	
	while(*p)
		cout<<*p++;
}

int main()
{

	int i=7, arr[2]{0,1};
	char imie[10]{"Kamil"};
	
	print(i);
	print(&i);
	
	print(arr);
	print(begin(arr),end(arr));
	print(arr,end(arr)-begin(arr));
	print(imie);
		  
	return 0;
}
*/

//Ex. 6.22
/*
Write a function to swap two int pointers.

void swapPtr(int* &ptr1, int* &ptr2){
	int *tmp=nullptr;
	
	tmp=ptr1;
	ptr1=ptr2;
	ptr2=tmp;
}

int main()
{
return 0;	
}
*/

//Ex. 6.21
/*
Write a function that takes an int and a pointer to an int and returns
the larger of the int value or the value to which the pointer points. What type should
you use for the pointer?


//Experiment to check if ref really needs a size of array
void arrFcn(const int (&arr)[10]){

	for(int i:arr)
		cout<<i<<" ";
	cout<<endl;
}

int isLarger(const int a,const int *b){

	if (a>=*b)
		return a;
	else
		return *b;
}
	
int main()
{
	int arr[10];
		for (int i=0;i!=10;++i)
			arr[i]=i;
	arrFcn(arr);
	
	cout<<isLarger(5,&arr[7])<<endl;
}
*/
	
//Ex. 6.17
/*
 Write a function to determine whether a string contains any capital
letters. Write a function to change a string to all lowercase. Do the parameters you
used in these functions have the same type? If so, why? If not, why not?

bool isCap(const string& s){
	
	for(const char i:s){
		if(isupper(i))
			return true;
	}
		return false;
}
	
string toLow(string s){
	
	for (char &c:s){
		if(isupper(c))
			c=tolower(c);
	}
		return s;
}
	
int main()
{
	cout<<(isCap("kamil")?"Yes":"No")<<endl;
	cout<<toLow("MichaLALALALA")<<endl;
}
*/
	
//Ex. 6.12
/*
Rewrite the program from exercise 6.10 in § 6.2.1 (p. 210) to use refer-
ences instead of pointers to swap the value of two ints. Which version do you think
would be easier to use and why?

void swap(int &a, int &b)
{
	int tmp=0;
	tmp=a;
	a=b;
	b=tmp;
}

int main()
{
	int x=5, y=7;
	swap(x,y);
	cout<<"x: "<<x<<" y: "<<y<<endl;
}
*/

//Ex. 6.11
/*
Write and test your own version of reset that takes a reference.

void reset(int &ref)
{
	ref=0;
}

int main()
{

	int a=5;
	
	reset(a);
	cout<<a;
}
*/
	
//Ex. 6.10
/*
Using pointers, write a function to swap the values of two ints. Test
the function by calling it and printing the swapped values.


void swap(int *a, int *b)
{
	int tmp=0;
	tmp=*a;
	*a=*b;
	*b=tmp;
}

int main()
{
	int x=5, y=7;
	swap(x,y);
	cout<<"x: "<<x<<" y: "<<y<<endl;
}
*/
//Ex.6.9
/*
Write your own versions of the fact.cc and factMain.cc ﬁles. These
ﬁles should include your Chapter6.h from the exercises in the previous section. Use
these ﬁles to understand how your compiler supports separate compilation.


int main()
{
	cout<<fact(6)<<endl;
	cout<<fact2()<<endl;
	cout<<sub(6)<<endl;
	
}
*/

//Ex.6.8
/*
 Write a header ﬁle named Chapter6.h that contains declarations for
the functions you wrote for the exercises in § 6.1 (p. 205).

#include "Chapter6.h"

int main()
{
	cout<<fact(6)<<endl;
	cout<<fact2()<<endl;
	cout<<sub(6)<<endl;
	
}
*/

//Ex. 6.7
/*
 Write a function that returns 0 when it is ﬁrst called and then generates
numbers in sequence each time it is called again.

int fcn()
{
	static int a=0;	
	return a++;
}

int main()
{
	for(int i=0; i<10;++i)
		cout<<fcn()<<endl;
}
*/

//Ex. 6.5
/*
 Write a function to return the absolute value of its argument.

int sub(int a)
{
	if(a<0)
		a*=(-1);
	return (a);	
}

int main()
{
	cout<<sub(10)<<endl;
}
*/

//Ex/ 6.4
/*
Write a function that interacts with the user, asking for a number and
generating the factorial of that number. Call this function from main.


int fact(void)
{
	//calc add from 1 to a
	//print
	cout<<"Put nr: ";
	int a=0;
	cin>>a;
	
	int i=0, sum=0;
	while(i<=a)
		sum+=i++;	
	return sum;
}

int main()
{
	cout<<"Sum is: "<<fact()<<endl;
}
*/

//Ex. 6.3
/*
 Write and test your own version of fact.
 
int fact(int val)
{
	int ret = 1; // local variable to hold the result as we calculate it
	while (val > 1)
		ret *= val--; 
	return ret; // return the result
} 	
//----------EOtxt

int fact(int a)
{
	//calc add from 1 to a
	//print
	int i=0, sum=0;
	while(i<=a)
		sum+=i++;	
	return sum;
}

int main()
{
	cout<<"Sum is: "<<fact(100)<<endl;
}
*/

//Ex. 5.23,24,25
/*
5.23 Write a program that reads two integers from the standard input and
prints the result of dividing the ﬁrst number by the second.

5.24 Revise your program to throw an exception if the second number is
zero. Test your program with a zero input to see what happens on your system if you
don’t catch an exception.

5.25 Revise your program from the previous exercise to use a try block to
catch the exception. The catch clause should print a message to the user and ask
them to supply a new number and repeat the code inside the try.


int main()
{

	int a=0,b=0;
	
	char c;
	do{
		try{
			cout<<"Enter A and B: ";
			cin>>a>>b;
				
			if(b==0)
				throw runtime_error("B cant be zero."); //#1 message
			else
				cout<<a<<'/'<<b<<'='<<a/b<<endl;
			
		}catch(runtime_error err) {
			cout<<err.what()<<endl; //Write to user message from #1
			cout<<"Do you want to repeat? (y/n): ";
			
			
			cin>>c;
			if ((c=toupper(c))!='Y')
				break;
		}
	}while(c=='Y');
}
*/

//Ex. 5.22
/*
The last example in this section that jumped back to begin could be
better written using a loop. Rewrite the code to eliminate the goto:

	begin:
	int sz = get_size();
	if (sz <= 0) {
		goto begin;
	}

int main()
{
	int sz=0;
	do
	sz=getsize();
	while(sz<=0);
	
	//Or
	int so=0;
	while(so<=0)
		so=getsize();
}
*/

//Ex. 5.21
/*
Revise the program from the exercise in § 5.5.1 (p. 191) so that it looks
only for duplicated words that start with an uppercase letter.

int main()
{
	//Read seq
	//if word with uppercase repeats break
	//Print word if repeats
	
	string s,prev;
	while(cin>>s){
		if(s==prev && isupper(s[0]))
			break;
		else
			prev=s;
	}
	
	cout<<(cin.eof()?"No repeat":("Repeated words is: "+s))<<endl;
}
*/

//Ex. 5.20
/*
Write a program to read a sequence of strings from the standard input
until either the same word occurs twice in succession or all the words have been read.
Use a while loop to read the text one word at a time. Use the break statement to
terminate the loop if a word occurs twice in succession. Print the word if it occurs
twice in succession, or else print a message saying that no word was repeated.


int main()
{
	//Read seq
	//if word repeats break
	//Print word if repeats
	
	string s,prev;
	
	while(cin>>s){
		if(s==prev){
			cout<<"Repeated words is: "<<s<<endl;
			break;
		}else
			prev=s;
	}
}
*/

//Ex. 5.19
/*
Write a program that uses a do while loop to repetitively request two
strings from the user and report which string is less than the other.


int main()
{
	string dec{"n"};
	do{
		string s1,s2;
		cout<<"Enter s1: ";
		cin>>s1;
		cout<<"Enter s2: ";
		cin>>s2;
		
		cout<<(s1>s2?s1:s2)<<" is bigger"<<endl;
		cout<<"Again? (y/n): ";
		cin>>dec;
	}while(!dec.empty() && tolower(dec[0])=='y');
		//
		
}
*/

//Ex.5.17
/*
Given two vectors of ints, write a program to determine whether
one vector is a preﬁx of the other. For vectors of unequal length, compare the num-
ber of elements of the smaller vector. For example, given the vectors containing 0,
1, 1, and 2 and 0, 1, 1, 2, 3, 5, 8, respectively your program should return true.


int main()
{
	vector<int> a{0,1,1,2,2,2,2,2,2}, b{0,1,1,2,3,5,8};	
	
	//Determine if a is smaller than b
	bool isSmaller=false;
	
	if(a.size()<b.size())
		isSmaller=true;
	else{
		for(size_t i=0;i!=a.size();++i){
			if(a[i]<b[i]){
				isSmaller=true;
				break;
			}
		}
	}
	cout<<(isSmaller?"Is smaller":"Is bigger")<<endl;
}
*/

//Ex. 5.16
/*
Write while loop as it is for and vice versa.

int main()
{
	//For 2 While
	
	int i=0;
	while(i!=10)
	{
		i++;	
	}
	
	//While 2 for
	
	for(int i=0;i!=10;)
	{	
		//....
	}
}
*/

//Ex. 5.15
/*Write a program to read strings from standard input looking for du-
plicated words. The program should ﬁnd places in the input where one word is fol-
lowed immediately by itself. Keep track of the largest number of times a single repeti-
tion occurs and which word is repeated. Print the maximum number of duplicates, or
else print a message saying that no word was repeated. For example, if the input is
how now now now brown cow cow
the output should indicate that the word now occurred three times.


int main()
{
	//IN: Take strings from input
	//OP: Count which word has occured the most
	//NTK: string wordMax- current max, int cntMax- current max cnt
	//OUT: Print word that has repeated the most
	
	//IN:
	vector<string> words;
	string input;
	string prWord;
	
	while(cin>>input)
		words.push_back(input);
	//OP:
	string maxWord;
	int maxCnt=1, currCnt=0; 
	
	//Loop going through all words
	for(vector<string>::iterator iter=words.begin();iter!=words.end();++iter){
		
		//Look and count occurences
		//Handle first element
		if(iter==words.begin())
			currCnt++; //When first element
		else {
			if (*iter==*(iter-1))
				++currCnt;
			else if (currCnt>maxCnt) {
				maxWord=*(iter-1);
				maxCnt=currCnt;
				currCnt=1; // Reset the counter				
			} else 
				currCnt=1;
		}
	}
	
	//Handle last word
	if (currCnt>maxCnt) {
				maxWord=*(words.end()-1);
				maxCnt=currCnt;
	}
	
	//OUT#1
	if(maxCnt>1)
	cout<<"Word "<<maxWord<<" has occured "<<maxCnt<<" times."<<endl;
	//OUT#2
	else
	cout<<"No word was repeated"<<endl;
}
*/

//Ex.5.9,11,12
/*
Write a program using a series of if statements to count the number of
vowels in text read from cin.

Modify our vowel-counting program so that it also counts the number
of blank spaces, tabs, and newlines read.

Modify our vowel-counting program so that it counts the number of
occurrences of the following two-character sequences: ff, fl, and fi.

int main()
{
	//Read txt from cin
	string s;
	int line=0;
	while(getline(cin,s))
	{
		int vCnt=0;
		int sCnt=0;
		int tCnt=0;
		int nCnt=0;
		int ffCnt=0;
		int flCnt=0;
		int fiCnt=0;
		char prech'\0';
		
		bool lastF=false;
		
		for(char c:s){
			//------------
			//Bool to prevent counting ff again if there is second f
			bool secF=false;
			//Count ff, fl, fi
			if (lastF==true){
				if(c=='f'){
					ffCnt++;
					secF=true;
				}
				else if(c=='l') flCnt++;
				else if(c=='i') fiCnt++;
				lastF=false;
			}
			
			if (c=='f' && secF==false)
				lastF=true;
			//--------------
			//Different approach but can repeat		
			if(prech=='f'){
				if(c=='f'){
					ffcnt++;
				else if(c=='l') flCnt++;
				else if(c=='i') fiCnt++;
			}
			prech=c;

			//count Vovels
			switch(c)
			{
				case 'a':
				case 'A':
				case 'e':
				case 'E':
				case 'o':
				case 'O':
				case 'u':
				case 'U':
				case 'i':
				case 'I':
					++vCnt;
					break;
				case ' ':
					++sCnt;
					break;
				case '\t':
					++tCnt;
					break;
				case '\n':
					++nCnt;
					break;
				
				//Just so it is	
				default:
					break;
			}
		}
		//Print it
		line++;
		cout<<"Line #"<<line
			<<"\tNumber of vowels:\t"<<vCnt
			<<"\n\tNumber of spaces:\t"<<sCnt
			<<"\n\tNumber of tabs:\t\t"<<tCnt
			<<"\n\tNumber of new lines:\t"<<nCnt
			<<"\n\tNumber of ff:\t\t"<<ffCnt
			<<"\n\tNumber of fl:\t\t"<<flCnt
			<<"\n\tNumber of fi:\t\t"<<fiCnt<<endl;
	}
}
*/

//Ex. 5.6
/*
Rewrite your grading program to use the conditional operator (§ 4.7,
p. 151) in place of the if–else statement.


int main()
{
	//Enter grade here
	int igrade;
	string sgrade;
	vector<string> litGrades{"F","D","C","B","A","A++"};	
	
	///Read grades
	while(cin>>igrade && igrade>=0){
		//Extract main letter
		sgrade= igrade<60? litGrades[0] : litGrades[(igrade-50)/10]
			//Add + or -
			+ ( igrade%10>7?'+':
			    //In case of 100 ommit -
			    igrade>=100?'\0':
			    igrade%10<4?'-':'\0') ;
		
		cout<<sgrade<<endl;
	}
}
*/

//Ex.5.5 
/*
To illustrate an if statement, we’ll calculate a letter grade from a numeric grade.
We’ll assume that the numeric grades range from zero to 100 inclusive. A grade of
100 gets an “A++,” grades below 60 get an “F,” and the others range in clumps of
ten: grades from 60 to 69 inclusive get a “D,” 70 to 79 a “C,” and so on.

To make our program more interesting, we’ll add a plus or minus to passing
grades. We’ll give a plus to grades ending in 8 or 9, and a minus to those end-
ing in 0, 1, or 2.

Using an if–else statement, write your own version of the program to
generate the letter grade from a numeric grade.


int main()
{
	//I want to transfer a number to alphabetical grade.
	//Get number
	//Transform it to grade
		//>60 F
		//>70 D
		//>80 C
		//>90 B
		//>100 A
		//=100 A+
	
	//Enter grade here
	unsigned int igrade;
	string sgrade;
	vector<string> litGrades{"F","D","C","B","A","A++"};
	
	//---------------
	//Transform grades to 
	if(igrade<60)
		sgrade='F';
	else if (igrade<70)
		sgrade='D';
	else if(igrade<80)
		sgrade='C';
	else if(igrade<90)
		sgrade='B';
	else if(igrade<100)
		sgrade='A';
	else if (igrade==100)
		sgrade="A++";
	else{
		cerr<<"Wrong grade. Terminating program!\n";
		return -1;
		}
		
	//Write + or -
	if (igrade>=60 && igrade%10<4)
		sgrade+='-';
	else if(igrade%10>7)
		sgrade+='+';
	//--------
	
	//Different Better Version!
	while(cin>>igrade){
		if (igrade<60)
			sgrade='F';
		else {
			
			sgrade= litGrades[(igrade-50)/10];	
			if (igrade!=100)
				//Checks if grade>7 then +
				sgrade+= igrade%10>7? '+':
					//Checks if grade < 4 then -
					igrade%10<4?'-':'\t';
		}
		
	//Write grade to screen
	cout<<"Grade is "<<sgrade<<endl;
	}							
}	
*/

/*
//Ex. 4.29
int main()
{
	int x[10]; int *p = x;
	cout << sizeof(x)/sizeof(*x) << endl;//Number of elements in array
	cout << sizeof(p)<<" "<<sizeof(*p) << endl;//Size of pointer/size of first array element.
}
*/

/*
//Write a program to print the size of each of the built-in types.
//Ex. 4.28
int main()
{
	//1. What are built in types?
	
	//u short int
	cout<<"short int\t"<<sizeof(short int)<<endl;
	//char
	cout<<"char\t\t"<<sizeof(char)<<endl;
	//u char
	cout<<"u char\t\t"<<sizeof(unsigned char)<<endl;
	//int
	cout<<"int\t\t"<<sizeof(int)<<endl;
	//u int
	cout<<"unsigned int\t"<<sizeof(unsigned int)<<endl;
	//long
	cout<<"long\t\t"<<sizeof(long)<<endl;
	//u long
	cout<<"u long\t\t"<<sizeof(unsigned long)<<endl;
	//long long
	cout<<"long long\t"<<sizeof(long long)<<endl;
	//u long long
	cout<<"u long long\t"<<sizeof(unsigned long long)<<endl;
	//float
	cout<<"float\t\t"<<sizeof(float)<<endl;
	//double
	cout<<"double\t\t"<<sizeof(double)<<endl;
	//long double
	cout<<"long double\t"<<sizeof(long double)<<endl;
}
*/
	
/*
//Ex.4.26 Grading program
int main()
{

//Task: As an example of using the bitwise operators let’s assume a teacher has 30 //students in a class. Each week the class is given a pass/fail quiz. We’ll track the //results of each quiz using one bit per student to represent the pass or fail grade on //a given test

	//1. Variable with at least 30 bits
	//2. Put students pass grade to quiz
	//3. Put students fail grade
	//4. Chceck students grade
	//5. Print binary quiz
	//-----------------------------------------------------------------
	
	//1. Define a quiz variable.
 	unsigned long quiz{};
	
	//2. Put students grade. Change one bit in quiz.
	
	//I want all to stay and just turn ON one bit. Use OR
	unsigned long stNr=9;
	quiz |= 1UL<<(stNr-1);
	cout<<quiz<<endl;
	
	//3. Fail grade. Flip just one bit to OFF.
	//Shift bits, negate it and AND assign it. 0000001 -> 01000000 -> 10111111
	//quiz &= ~(1UL<<24);
	
	//4. Check by putting students number if grade is fail or pass.
	
	//First shift than &
	if(quiz & 1UL<<(stNr-1))
	   cout<<"Passed\n";
	else
	   cout<<"Failed\n";
	   
	//5. Print binary representation
	
	for(int i=0;i<32;++i)
	{
		//Take last bit, check if bit is 1
		if(quiz & 1UL<<31-i) cout<<"1";
		else cout<<"0";
		
		//After 8 digits make space
		if((i+1)%8 == 0)cout<<" ";
	}
}
*/

//Ex. 4.25
/*
What is the value of ~ ’q’ << 6 on a machine with 32-bit ints and 8 bit
chars, that uses Latin-1 character set in which ’q’ has the bit pattern 01110001?

	//1. What i 'q'? 01110001
	//2. Negate it. 10001110
	//3. Shift 6 bits 1000000
	//4. Value in 32bits is 128: 00000000 00000000 00000000 10000000
*/

/*
//Ex. 4.22
int main()
{
	int grade=76;
	string finalgrade = (grade > 90) ? "high pass" 
		: (grade < 60) ? "fail" 
			:(grade>75)?"pass": "low pass";	
	cout<<finalgrade;
	
	cout<<endl;
	
	//Version with IF
	if (grade>90)
		cout<<"High pass";
	else if (grade>75)
		cout<<"Pass";
	else if (grade>=60)
		cout<<"Low pass";
	else
		cout<<"Fail";
	
}
*/
	
/*
//Ex. 4.21
int main()
{
	
	//Make vector
	
	vector<int> ivec{1,2,3,4,5,6,7,8,9};
	
	for(int &i:ivec){
		i%2==1? i*=2:0;
		cout<<i<<" ";
	}
}
*/

/*
//Ex. 3.44/45
int main()
{
	//Make array and initialize it
	
	int sz=10;
	int ia[sz];
	
	//Array init
	for(int i=0;i<sz;i++)
		ia[i]=i;
		
	//Range for
	for(int i:ia)
		cout<<i<<" ";
	
	//Subscripts
	for(int i=0;i<sz;++i)
		cout<<ia[i]<<" ";
	
	//Pointers
	using array_alias=int*;
	
	for(array_alias i=ia; i<ia+sz;++i)
		cout<<*i<<" ";
}
*/

/*
//Ex. 3.43
int main()
{
	//Make array and initialize it
	
	int sz=10;
	int ia[sz];
	
	//Array init
	for(int i=0;i<sz;i++)
		ia[i]=i;
		
	//Range for
	for(int i:ia)
		cout<<i<<" ";
	
	//Subscripts
	for(int i=0;i<sz;++i)
		cout<<ia[i]<<" ";
	
	//Pointers
	
	for(int *i=ia; i<ia+sz;++i)
		cout<<*i<<" ";
}
*/

/*
//Arrays!
int main()
{
	int arr[4][3][2]{ { {111,112},{121,122},{131,132} },
				  	  { {211,212},{221,222},{231,232} },
				  	  { {311,312},{321,322},{331,332} },
				  	  { {411,412},{421,422},{431,432} }
					};
	
	for(auto &i:arr){
		for(auto &j:i){
			for(auto k:j)
				cout<<k<<" ";
			cout<<"\t";
		}
		cout<<endl;
	}
	cout<<"\n\n";
	
	int (&row)[3][2]=arr[2]; // { {311,312},{321,322},{331,332} },
	
	for(int i=0;i<4;++i)
		cout<<*row[i]<<" "; // Takes first element from the array!
	cout<<endl;
	
	//Define array
	const int a=2,b=3,c=4;
	int arr2[a][b][c];
	
	//Initialize Multidimensional array
	for (int x=1;x<=a;x++){
		for(int y=1;y<=b;y++){
			for(int z=1;z<=c;z++){
				arr2[x-1][y-1][z-1]=100*x+10*y+z;
				cout<<arr2[x-1][y-1][z-1]<<" ";
			}
			cout<<"\t";
		}
		cout<<endl;
	}
	
	//Iteration through all elements stored in memory.
	int (*bgn)[3][4]=begin(arr2);
	cout<<bgn<<" ";
	cout<<bgn[1]<<endl;
	int (*nd)[3][4]=end(arr2);
	cout<<nd-bgn<<"\n";
	
	//Array sets on a first elemet oflast subscript
	for(int i=0;i<=24;++i)
	cout<<*(arr2[0][0]+i)<<" ";
	
	int o=5;
	o={};
	cout<<o;
	cout<<12/3*4+5*15+24%4/2<<" "<<((12/3)*4)+(5*15)+(24%(4/2))<<endl;
	cout<<-30 / 3 * 21 % 4<<endl;
}
*/

/*
//Ex. 3.41 / 3.42
int main()
{
	int ia[]{1,2,3,4,5};
	
	vector<int> ivec(begin(ia),end(ia));
	
	for(auto i:ivec)
		cout<<i<<" ";
	
	int ar2[ivec.size()]{};
	
	for (int i=0; i<ivec.size();++i){
		ar2[i]=ivec[i];
		cout<<ar2[i];
	}
}
*/

/*
//Ex. 3.40
int main()
{
	char cs1[]{"Kurka"}, cs2[]{" pieczona!"};
	
	int strLgth=strlen(cs1)+strlen(cs2);
	cout<<strLgth<<endl;
	
	char conStr[strLgth+1];
	strcpy(conStr,cs1);
	strcat(conStr,cs2);
	
	cout<<conStr;
}
*/

/*
//Ex. 3.39
int main()
{
	string s1="Ala", s2="Ala";
	char cs1[]{"Kurka"}, cs2[]{"Kurksa"};
	
	if(strcmp(cs1,cs2)){
		cerr<<"Bad C-strings\n";
	} else
		cout<<"C-strings are the same!\n";
	
	if(s1!=s2){
		cerr<<"Bad strings\n";
	} else
		cout<<"Strings are the same!\n";
	
	return 0;
}
*/

/*
//Ex. 3.36
int main()
{
	int iar1[4]{1,2,3,4};
	int iar2[]{1,2,3,4};
	
	ptrdiff_t lengthAr1=end(iar1)-begin(iar1);
	ptrdiff_t lengthAr2=end(iar2)-begin(iar2);
	
	if(lengthAr1==lengthAr2){
		for(int i=0;i<lengthAr1;++i){
			if(iar1[i]!=iar2[i]){
				cerr<<"Arrays are not equal on element "<<i+1<<endl;
				return -1;
			}
		}
		cout<<"Arrays are equal!";
	}else{
		cerr<<"Arrays lengths do not match!";
	}
			
	vector<int> ar1(10,42);
	vector<int> ar2(10,42);
	
	if(ar1!=ar2){
		cerr<<"Vectors do not match";
		return -1;
	}
	//Optional check with pointers
	if (ar1.size()!=ar2.size()){
		cerr<<"Vector lengths do not match";
		return -1;
	}
	vector<int>::iterator beg1=ar1.begin(),beg2=ar2.begin(),
						  end1=ar1.end(), end2=ar2.end();
	
	for (;beg1!=end1;++beg1,++beg2){
		if (*beg1!=*beg2){
			cerr<<"Vectors do not match on element "<<beg1-ar1.begin();
			return-1;
		}
	}
	
	cout<<"Vectors match! :)";
	return 0;
}
*/

/*
//Ex. 3.35
int main()
{
	//Set array to 0 using pointers
	constexpr unsigned sz=10;
	int iarr[sz]={0};
	
	for (int &i:iarr)
		i=37;
	
	for (int i:iarr)
		cout<<i<<" ";
	
	int *beg=iarr, *end=iarr+sz;
	for(;beg!=end;++beg)
		*beg=0;
	
	for (int i:iarr)
		cout<<i<<" ";
	//Make array and initialize it with numbers
	
	//Use begin and end to itterate through array and set it to 0
}
*/

/*
//Multi dim arrays
int main()
{
	int cnt=0;
	int arr[10][10]{};
	
	for(auto &row:arr){
		for(auto col :row){
			col=cnt;
			++cnt;
			cout<<col<<" ";
		}
		cout<<endl;
	}
}
*/

/*
//Ex. 3.32
int main()
{
	constexpr size_t sz=10;
	int array[sz];
	vector<int> ivec;
	
	
	for(int i=0; i<sz;++i){
		array[i]=i;
		ivec.push_back(i);
		cout<<array[i]<<endl;
	}
	
	int arr2[sz]{};
	for(int i=0;i<sz;++i)
		arr2[i]=array[i];
	
	vector<int> ivec2(ivec);
	for (int i:ivec2)
		cout<<i<<" ";
	
	
}
*/

/*
//Ex. 3.31
int main()
{
	constexpr size_t sz=10;
	int array[sz];
	
	for(int i=0; i<sz;++i){
		array[i]=i;
		cout<<array[i]<<endl;
	}
	
		
}
*/


/*
//Ex. 3.26 Write binary search
int main()
{
	vector<int> ivec;
	int bingo=100;
	
	for(int buff;cin>>buff;ivec.push_back(buff));
	auto beg=ivec.begin(), end=ivec.end();
	auto mid=beg+(end-beg)/2;
	
	while(beg<=end && !bingo==*mid){
		if (bingo>*mid)
			end=mid;
		else
			beg=mid;
		mid=beg+(end-beg)/2;
	}
	if (bingo==*mid)
		cout<<"It was found!";
	else
		cout<<"No such element!";
}
*/

/*
//Ex. 3.25
int main()
{
	vector<int> grades(11);
	int buff;
	
	while(cin>>buff){
		++*(grades.begin()+(buff/10));
	}
	
	for(auto nr:grades)
		cout<<nr<<" ";
}
*/

/*
//Ex. 3.24
int main()
{
	//Read integers
	vector<int> ivec;
	int a=0;
	while(cin>>a)
		ivec.push_back(a);
	
	
	;
	
	//Sum adjcent elements and print it
	for(auto beg=ivec.begin(), end=ivec.end();beg!=(end-1);++beg)
		cout<<*beg+*(beg+1)<<" ";
	
	cout<<endl;
	//Sum elements from front and back
	
	for(auto beg=ivec.begin(), end=ivec.end();beg<=end;++beg,--end)
		cout<<*beg+*(end-1)<<" ";
	
}
*/

/*
//Ex. 3.23
int main()
{
	vector<int> numbers(10,42);
	
	//Asign value x2
	auto beg=numbers.begin();
	auto end=numbers.end();
	
	for (;beg!=end;++beg){
		*beg*=2;
		cout<<*beg<<endl;
	}
}
*/

/*
//Ex.3.22
int main()
{
	vector<string> txt {"Kamil lubi programowac. ","","Ula lub lody. "};
	for (auto it=txt.begin(); it!=txt.end() && !it->empty();++it){
		//Make elements of string to upper.		
		for (auto &c:*it)
			c=toupper(c);
		cout<<*it;
	}
}
*/

/*
//Ex. 3.21
void vectorino(const vector<int> vec)
{
	//Print size of vector
	auto begin=vec.begin();
	auto end=vec.end();
	
	cout<<"Size: "<<end-begin<<endl;
	
	//Print content
	for(;begin!=end;++begin)
		cout<<*begin<<" ";
		cout<<endl;
}


void vectorinos(const vector<string> vec)
{
	//Print size of vector
	auto begin=vec.begin();
	auto end=vec.end();
	
	cout<<"Size: "<<end-begin<<endl;
	
	//Print content
	for(;begin!=end;++begin)
		cout<<*begin<<" ";

}
	
int main()
{
	vector<int> v1;
	vector<int> v2(10);
	vector<int> v3(10, 42);
	vector<int> v4{10};
	vector<int> v5{10, 42};
	vector<string> v6{10};
	vector<string> v7{10, "hi"};
	
	vectorino(v1);
	vectorino(v2);
	vectorino(v3);
	vectorino(v4);
	vectorino(v5);
	vectorinos(v6);
	vectorinos(v7);
	
}
*/

/*
int main()
{

	string str{"Kamil programuje"};
	
	auto bgn=str.begin();
	auto end=str.end();
	
	int a=end-bgn;
	for (bgn; bgn!=end;++bgn)
		cout<<*bgn;
	cout<<endl;
}
*/

/*
//Ex 3.20
int main()
{
	int a;
	vector<int> ivec;
	//Read ints
	while(cin>>a)
		ivec.push_back(a);
	cout<<"Size: "<<ivec.size()<<endl;

	
	//Sum pair of two adjcent numbers nad print it.
	for (int i; i<ivec.size()-1;i++)
		cout<<ivec[i]+ivec[i+1]<<" ";
	//Sum first-last...
	cout<<endl;
	for (int i; i<(ivec.size()/2);i++)
		cout<<ivec[i]+(ivec.size()-i)<<" ";
}
*/

/*
//Ex. 3.19
int main()
{
	vector<int> v1{10,10,10};
	vector<int> v2(3,10);
	vector<int> v3 = v2;
				   
}
*/

/*
//Ex. 3.17
int main()
{
	string word;
	vector<string> vec;
	
	//Enter
	while(cin>>word)
		vec.push_back(word);
	
	//To upper
	for(auto &wordString:vec){
		for (auto &c:wordString){
			c=toupper(c);	
		}
	}
	
	//Print 8 in line
	int cnt=0;
	for(auto wordString:vec){
		if ((cnt % 8)==0){
			cout<<endl;
			cnt=0;
		}
		cout<<wordString<<" ";
		++cnt;
	}
	cout<<endl;
}
*/

/*
//Ex. 3.16
void vectorino(vector<int> vec)
{
 	if (!vec.empty()){
		cout<<vec.size()<<" "<<endl;
		for(auto element:vec)
			cout<<element<<" ";
		cout<<"\n\n";
	}else{
		cout<<"Empty!\n\n";
	}	
}

void vectorinos(vector<string> vec)
{
 	if (!vec.empty()){
		cout<<vec.size()<<"-"<<endl;
		for(auto element:vec)
			cout<<element<<" ";
		cout<<"\n\n";
	}else{
		cout<<"Empty!\n\n";
	}	
}
int main()
{
	vector<int> v1; vector<int> v2(10);
	vector<int> v3(10, 42); vector<int> v4{10};
	vector<int> v5{10, 42}; vector<string> v6{10};
	vector<string> v7{10, "hi"};
	
	vectorino(v1);
	vectorino(v2);
	vectorino(v3);
	vectorino(v4);
	vectorino(v5);
	cout<<"Strings\n";
	vectorinos(v6);
	vectorinos(v7);
	
}
*/

/*
//Ex. 3.15
int main()
{
	//Read ints from cin
	//Store them in vectors	
	string a;
	vector<string> vec;
	while(cin>>a)		
		vec.push_back(a);
	
	for(int i=0; i!=vec.size();i++)
		cout<<vec[i]<<" ";
	cout<<endl;
	return 0;

}
*/

/*
//Ex. 3.14
int main()
{
	//Read ints from cin
	//Store them in vectors	
	int a;
	vector<int> vec;
	while(cin>>a)		
		vec.push_back(a);
	
	for(int i=0; i!=vec.size();i++)
		cout<<vec[i]<<" ";
	cout<<endl;
	return 0;

}
*/

/*
//Ex.3.10
int main()
{
	//Remove puctuation from the sentence.
	
	cout<<"Enter string: ";
	
	string str;
	getline(cin,str);
	
	for(auto &c:str)
		if (ispunct(c))
			c='\0';
	cout<<str<<endl;
}
*/

/*
//Ex. 3.8
int main()
{
	// Change all chars to X with while and then with for loops
	string str2,str{"Sierotka ma rysia"};
	str2=str;
	cout<<str<<endl;
	
	decltype(str.size()) cnt=0;
	while (cnt<str.size()){
		str[cnt]='X';
		cnt++;
	}
	cout<<str<<endl;
	
	
	for (decltype(str2.size()) i=0; i<str2.size();++i)
		str2[i]='x';
	
	cout<<str2<<endl;
	string s;
	cout<<s[0]<<endl;
	
}
*/

/*
//Ex. 3.6
int main()
{
	//Change all chars to string
	
	string str{"Sierotka ma rysia"};
		
		for(char &c:str){
			cout<<c<<endl;
			c='X';
		}
	cout<<str<<endl;
}
*/

/*
int main()
{
	string str("Ala MaKota");

	for (auto &c:str){
		c=toupper(c);
	}
	cout<<str<<endl;
	
	for (decltype(str.size()) i=0;i<str.size();i++)
		str[i]=tolower(str[i]);

	cout<<str<<endl;
	
	for (decltype(str.size()) i=0; i!=str.size() && (!isspace(str[i]));++i)
		 str[i]=toupper(str[i]);
		 
		 cout<<str<<endl;
	
	return 0;
}

*/

/*
//Ex. 2.41(1.23) 

int main()
{
	//Initialize	
	Sales_data currData, nextData;
	double currPrice=0.0, nextPrice=0.0;
	int cnt=0;
	
	//Read first
	cin>>currData.bookNo>>currData.units_sold>>currPrice;
	
	//Update counter
	cnt++;
	
	while(cin>>nextData.bookNo>>nextData.units_sold>>nextPrice) {
		//Check ISBN
		if (currData.bookNo==nextData.bookNo)
			cnt++;
		else{
			//Output
			cout<<"Tr#: "<<cnt<<" "<<currData.bookNo<<endl;

			//Reset. Next is now Current
			currData.bookNo=nextData.bookNo;
			//Make counter 1.
			cnt=1;
		}
	}
	//Output last element
	cout<<"Tr#: "<<cnt<<" "<<currData.bookNo<<endl;
}
*/

/*
//Ex. 2.41(1.22)
int main()
{
	//Read 1st transaction
	Sales_data currData,nextData;
	double currPrice=0, nextPrice=0;
	
	cin>>currData.bookNo>>currData.units_sold>>currPrice;
	//Calculate first revenue
	currData.revenue=currData.units_sold*currPrice;
	//Read next oness
	
	while(cin>>nextData.bookNo>>nextData.units_sold>>nextPrice) {
		//Compare if ISBN are the same
		if (currData.bookNo==nextData.bookNo){
			//Calc revenue for each of them
			nextData.revenue=nextData.units_sold*nextPrice;
			//Sum revenues to currData
			currData.revenue+=nextData.revenue;
			//Calc add units_sold
			currData.units_sold+=nextData.units_sold;
		}
		else{
			//Print
			cout<<currData.bookNo<<" " 			//ISBN
				<<currData.units_sold<<" "		//Total units
				<<currData.revenue<<" "			//Total Revenue
				<<currData.revenue/currData.units_sold<<endl; //Avg. Price
			
			//Next is now Current
			currData.bookNo=nextData.bookNo;
			currData.units_sold=nextData.units_sold;
			currPrice=nextPrice;
			currData.revenue= currData.revenue=currData.units_sold*currPrice;
		}
	}
	
	//Print last record
	cout<<currData.bookNo<<" " 						//ISBN
	<<currData.units_sold<<" "						//Total units
	<<currData.revenue<<" "							//Total Revenue
	<<currData.revenue/currData.units_sold<<endl;	//Avg. Price
	
	return 0;
}
*/

/*
//Ex. 2.41(1.20)
int main()
{
	Sales_data data;
	double price=0;
	//Read many transaction
	while(cin>>data.bookNo>>data.units_sold>>price)
		  cout<<data.bookNo<<" "<<data.units_sold<<" "<<data.units_sold*price<<endl;
	return 0;
	//Print it
	//Do it until EOF
}
*/

/*
//Ex. ALL 2.6
int main()
{
	//Create object of Sales Data
	Sales_data op1, op2;
	double price=0.0;
	
	//Enter ISBN, sales, price
	cout<<"Enter ISBN - number sold - price:"<<endl;
	cin>>op1.bookNo>>op1.units_sold>>price;
	//calculate and enter revenue
	op1.revenue=price*op1.units_sold;
	
	//Enter second operation
	cin>>op2.bookNo>>op2.units_sold>>price;
	op2.revenue=price*op2.units_sold;
	
	//PRINTING SUM OF TWO RECORDS
	
	//Compare if books are the same
	if (op1.bookNo==op2.bookNo) {
		unsigned totalSold=op1.units_sold + op2.units_sold;
		double totalRev=op1.revenue + op2.revenue;
	
		//if yes, then add number sold, and revenue
		cout<<endl<<op1.bookNo<<" " <<totalSold<<" " <<totalRev<< " ";
		//Calculate average price and print all
		if (totalSold!=0)
			cout<<totalRev/totalSold<<endl;
		else
		cout<<"No Sales!";
		//End program
		return 0;
	} else {
	//If not then print error message and quit
		cerr<<"ISBN does not match!";
		return -1;
	}
}
*/

/*
//Ex.2.37
int main()
{
	int a=3, b=4;
	decltype(a) c=a; //Type oc c is (int)
	decltype(a=b) d=a; //Type of d is (int&)
	
}
*/

/*
//Ex. 2.36
int main()
{
	int a=3, b=4;
	decltype(a) c=a; // Type (int)
	decltype((b)) d=a; //Type ref to int (int&)
	++c; // a+1 =3
	++d; //a+1=3
	
	cout<<c<<","<<d<<endl; //GOOD 4,4!
	
	//How to remove reference?
	int x=5;
	int *p=&x;
	//Removing reference
	remove_reference<decltype(*p)>::type u=8;
	cout<<x<<endl<<u<<endl;
	
}
*/

/*
//Ex. 2.35
int main()
{
	//What types?
	const int i=42; //Base instruction
	auto j=i; // j is int
	const auto &k=i; //k is const int reference. Because it refers to const var.
	auto *p=&i; // p is pointer to const int (const int*)
	const auto i2=i, &k2=i;//i2 is const int. k2 is a const inr reference to i. k=k2
	
	cout<<typeid(k2).name()<<endl;
}
*/

/*
//Ex. 2.34
int main()
{
	int i=2, &r=i;
	auto a=r;	
	//auto with variables ignores top level const. It means it ignores const in int.
	//It leaves const when pointer points to const or we have a reference.
	
	const int ci=i, &cr=ci;
	auto b= ci; //b is an int
	auto c=cr; //c is a int
	auto d= &i; //d is a pointer to int
	auto e=&ci;  //e is pointer to const int
	auto &g=ci; //It will be const int ref
	//auto &h=42; //Error, because ref cant point to literal. It is only alias.
	const auto &j=42; // It is OK, because its a const ref so it points to temporary.
	
	cout<<a<<endl<<b<<endl<<c<<endl<<d<<endl<<e<<endl<<g<<endl<<j<<endl<<endl;;
	
	a=42; //Its OK a is int, because it is initialized with ref to const int.
	b=42; //OK, b is int. It is initialized withconst int. COsnt is ignored.
	c=42; //OK, c is int. It is initializez with ref to const int. Const ignored.
	//d=42; //Error. Cant assign int* with int
	//e=42; //Error. Cant assign const int* with int.
	//g=42; //Error. Cant assign literal to const ref, that alias a const int. 
	
	cout<<a<<endl<<b<<endl<<c<<endl<<d<<endl<<e<<endl<<g<<endl<<j<<endl<<endl;
	
	return 0;
	
	
}
*/

/*
//Ex.2.8
int main()
{
	cout<<"\062\t\115\n";
	
}
*/
/*
//Ex. 1.22
int main()
{
	Sales_item currItem, nextItem;
	int cnt=0, trnsQt=0;
	
	if(cin>>currItem){
		cnt++;
		cout<<"Sum of all transacrions:\n";
	}
	else{
		cerr<<"Something is fucked up"<<endl;
		return -1;
	}
		
	while(cin>>nextItem){
		if(currItem.isbn()==nextItem.isbn()){
			currItem+=nextItem;
			cnt++;
		}
		else{
			trnsQt++;
			cout<<"#"<<trnsQt<<": "<<"Items:"<<cnt<<" Data: "<<currItem<<endl;
			cnt=1;
			currItem=nextItem;
		}
	}
	trnsQt++;
	cout<<"#"<<trnsQt<<": "<<"Items:"<<cnt<<" Data: "<<currItem<<endl;
	cout<<"End of file."<<endl;

	return 0;
}
*/
/*
//Ex. 21
int main()
{
	Sales_item item1, item2;
	
	cin>>item1>>item2;
	if(item1.isbn()==item2.isbn())
		cout<<"Sum of:\n"<<item1<<endl<<item2<<endl<<"is euqal to:\n"<<item1+item2<<endl;
	else
		cout<<"Wrong input or sums don't match"<<endl;
	return 0;
}
*/
/*
//Ex.1.20
int main()
{
	cout<<"Reading transactions...\n";
	Sales_item item;
	while(cin>>item)
		cout<<item<<endl;
	cout<<"End of stream.\n";
	
	return 0;
}
*/
/*
//Ex. 1.17

//Co chcę?
//Chcę aby program czytał kolejne wartości wpisywane z klawiatury i pisał ile razy dana //liczba się powtórzyła. Napisze to po każdej zmianie liczby.
//Chcę by wprowadzanie było oddzielone spacją.


int main()
{
	cout<<"Enter numbers:"<<endl;
	int currVal=0, cnt=0, nextVal=0;
	
	if (cin>>currVal)
		++cnt;
	while(cin>>nextVal && nextVal!=0)
	{
		if(currVal==nextVal)
			++cnt;
		else
		{
			cout<<currVal<<" apeared "<< cnt <<" times."<<endl;
			cnt=1;
			currVal=nextVal;
		}
	}
	cout<<currVal<<" apeared "<< cnt << " times."<<endl;
	return 0;
}
*/
/*
//ex.1.16
int main()
{
	cout<<"Keep entering numbers: ";
	int nr=0,sum=0;
	while(cin>>nr && nr!=false)
	{
		sum+=nr;
	}
	cout<<"Sum is: "<<sum<<endl;	
}
*/
/*
//ex 1.14
int main()
{
	int i1=0,i2=0;
	cin>>i1>>i2;
	if (i1<=i2)
	{
		for(;i1<=i2;i1++)
			cout<<i1<<endl;
	}else
	{
		for (;i2<=i1;i2++)
			cout<<i2<<endl;
	}
}
*/
/*
//ex.1.10
int main()
{
	int i1=0, i2=0;
	cout<<"Enter two integers: ";
	cin>>i1>>i2;
	if (i1<=i2)
	{
		while (i1<=i2)
		{
			cout<<i1<<"\n";
			++i1;
		}
	}else
	{
			while (i2<=i1)
		{
			cout<<i2<<"\n";
			++i2;
		}
	}
}
*/
/*
int main()
{
	Sales_item book1, book2;
	
	cout<<"Enter data(ISBN, Qty Sold, Sales Price: ";
	cin>>book1>>book2;
	if (book1.isbn()==book2.isbn())
		{
			cout<<"Your books sum is: "<<book1+book2<<endl;
			return 0;
		}
	else
		{
			cerr<<"Data must reffer to the same isbn"<<endl;
			return -1;
		}
}

*/
/*

int main()
{
	int suma=0;
	int value=1;
	
	while(value<=10)
	{
		suma+=value;
		++value;
	}
	
	cout<<"Suma wynosi " << suma<<endl;
	return 0;
}
*/
/*
int main()
{
	cout<< "Enter two numbers: ";
	int a,b;
	cin>>a>>b;
	cout<<"Sum of "<< a << " and "<<b<<" is "<<a+b<<endl;
	return 0;
}

*/
/*

int main()
{
	cout<< "Hello World\nInsert number: ";
	int x;
	cin>>x;
	cout<<"Number is "<<x<<endl;
	return -1;
}
*/
