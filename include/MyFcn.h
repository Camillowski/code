#ifndef MYFCN_H
#define MYFCN_H

using namespace std;

string flLorem="/home/cam/Documents/Programowanie/data/loremipsum.txt";

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

vector<string> fl2vec(const string &file){
	
	string str = fl2str(file);
	vector<string> svec=str2vec(str);
	return svec;
}

//Obsolete
void printVec(const vector<string> &svec){
	for(string el: svec){
		cout<<el<<" ";
	}
	cout<<endl;
}

template <typename T>
void printCont(const T &cont){
	
	for(auto el:cont){
		cout<<el;
	}
	cout<<endl;
}
#endif