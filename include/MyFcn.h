#ifndef MYFCN_H
#define MYFCN_H
#include <vector>

extern std::string flLorem; 
extern std::string flText;

std::vector<std::string> str2vec(std::string &);

std::string fl2str(const std::string &);

std::vector<std::string> fl2vec(const std::string &);

template<typename T> void printCont(const T &cont);

#endif