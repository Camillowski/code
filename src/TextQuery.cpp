#include <iostream>
#include <fstream>
#include <sstream>

#include "TextQuery.h"

/*
QUERY RESULT FUNCTIONS
*/

//GETTERS
QueryResult::File QueryResult::get_file(){
	return fileVec;
}

QueryResult::SetIter QueryResult::begin(){
	return lineNr->begin();
}
	
QueryResult::SetIter QueryResult::end(){
	return lineNr->end();
}

//PRINT QUERY RESULTS
void print(std::ostream &os, QueryResult res){
	if(res.lineNr==nullptr){
		os<<"No word "<<res.srch_word<<std::endl;
		return;
	}
	os<<"Word "<<res.srch_word<<" occurs in "<<res.lineNr->size()<<" lines:"<<std::endl;
	auto begin=res.lineNr->begin();
	while(begin!=res.lineNr->end()){
		os<<"(line #"<<*begin+1<<"): "<<res.fileVec->at(*begin)<<std::endl<<std::endl;
		++begin;
	}
}

//=======================================================================

/*
TEXT QUERY CLASS FUCTIONS
*/

//DEFAULT CTOR
TextQuery::TextQuery(std::istream& is){
	//fileVec=make_shared<vector<string>>(); //optional assignment
	fileVec.reset(new StrVec);
	
	//Fill in vector
	std::string line;
	while(std::getline(is,line)){
		fileVec->push_back(line);
	}
	
	//Fill in the map
	auto begin=fileVec->begin();
	while(begin!=fileVec->end()){
		std::istringstream sstrm(*begin);
		size_t line_no=begin-fileVec->begin();
		
		std::string word;
		while(sstrm>>word){
			
			if(wordMap[word]==nullptr) //If shared_ptr empty...
				wordMap[word].reset(new std::set<int>); //Allocate new set
			wordMap[word]->insert(line_no);
			}
		++begin;
	}
}

//QUERY FUNCTION
QueryResult TextQuery::query(std::string srch_word){
	QueryResult res;
	res.srch_word=srch_word;
	
	auto found=wordMap.find(srch_word);
	if(found!=wordMap.end()){
		res.lineNr=found->second;
		res.fileVec=fileVec;
	}
	
	return res;
}
