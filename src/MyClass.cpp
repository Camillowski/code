//myClass implementation file
#include <iostream>
#include "MyClass.h"

using namespace std;s

MyClass::MyClass()=default; //Default constructor

MyClass::MyClass(string s):m_name(s) { //Constructor
	cout<<"Constructor\n";
}

MyClass::~MyClass(){
	cout<<"Destructor\n";	
}

string MyClass::getName(){return m_name;}

void MyClass::setName(string s){
m_name=s;	
}

