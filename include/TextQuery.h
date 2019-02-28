#ifndef TEXTQUERY_H
#define TEXTQUERY_H

#include <memory>
#include <set>
#include <map>
#include <vector>
#include "StrVec.h"

class TextQuery;

/*
Hold data returned by query fcn in TextQuery class
*/
/*
class QueryResult{
	public:
	using File=std::shared_ptr<std::vector<std::string>>;
	using SetIter=std::set<int>::iterator;
	//Ctors
	QueryResult(){}//Default Ctor
	//fcns
	File get_file();
	SetIter begin();
	SetIter end();
	
	private:
	std::string srch_word;
	std::shared_ptr<std::set<int>> lineNr;//Lines numbers
	std::shared_ptr<std::vector<std::string>> fileVec; //text lines
	
	friend void print(std::ostream&, QueryResult);
	//friend QueryResult TextQuery::query(string);
	friend class TextQuery;
};
*/
class QueryResult{
	public:
	using File=std::shared_ptr<StrVec>;
	using SetIter=std::set<int>::iterator;
	//Ctors
	QueryResult(){}//Default Ctor
	//fcns
	File get_file();
	SetIter begin();
	SetIter end();
	
	private:
	std::string srch_word;
	std::shared_ptr<std::set<int>> lineNr;//Lines numbers
	std::shared_ptr<StrVec> fileVec; //text lines
	
	friend void print(std::ostream&, QueryResult);
	//friend QueryResult TextQuery::query(string);
	friend class TextQuery;
};

/*
Create map with words and lines, search and return lines coresonding to searched word.
*/
class TextQuery{
	public:
	
	//ctor that fills in vector and map
	TextQuery(std::istream& is);
	
	//Functions
	QueryResult query(std::string);//Takes map and vector and Return Queryresult

	
	private:
	//string srch_word;
	std::shared_ptr<StrVec> fileVec; //text lines
	std::map<std::string,std::shared_ptr<std::set<int>>> wordMap;//Takes set
	
	friend class QueryResult;
};

/*
class TextQuery{
	public:
	
	//ctor that fills in vector and map
	TextQuery(std::istream& is);
	
	//Functions
	QueryResult query(std::string);//Takes map and vector and Return Queryresult

	
	private:
	//string srch_word;
	std::shared_ptr<std::vector<std::string>> fileVec; //text lines
	std::map<std::string,std::shared_ptr<std::set<int>>> wordMap;//Takes set
	
	friend class QueryResult;
};
*/
#endif