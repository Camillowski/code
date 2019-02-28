#include <iostream>
#include <fstream>
#include <sstream>
#include "MyFcn.h"
using namespace std;


std::string flLorem="/home/cam/Documents/Programowanie/Cpp/data/loremipsum.txt";
std::string flText="/home/cam/Documents/Programowanie/Cpp/data/text.dat";
//SUB FUNCTIONS FOR FL2VEC

//Split one string to many ->vector
vector<string> str2vec(string &str){
	//fill in vector from string;
	istringstream sStrm(str); //Create stream
	string word; //Temp variable
	vector<string> svec;

	//Feed vector
	while(sStrm>>word){
		svec.push_back(word);
	}
	return svec;
}	

//Convert file to one string
string fl2str(const string &file){
	string str;
	ifstream fstr(file);
	
	if (!fstr.is_open()) return string("Wrong File!");

	string word;
	while(fstr>>word){
		str.append(word+" ");
	}
	
	return str;
}

//CONVERT FILE TO STRING VECTOR
vector<string> fl2vec(const string &file){
	
	string str = fl2str(file);
	vector<string> svec=str2vec(str);
	return svec;
}

//PRINT CONTENT OF CONTAINER (Use for printVec)
template <typename T>
void printCont(const T &cont){
	
	for(auto el:cont){
		cout<<el<<" ";
	}
	cout<<endl;
}
//Speciall shit for template decalration
template void printCont(const vector<string>&);