#include "Ch13_36.h"
#include <iostream>

using namespace std;

//Message Functions

//Add to folders fcn
void Message::add_to_Folders(const Message &m){
	//Add new message to all folders from set
	for(Folder* el:m.folders){
		el->addMsg(*this);
	}	
}

//Remove message from folders
void Message::remove_from_Folders(){
	for(Folder* el:folders){
		el->remMsg(*this);
	}
	folders.clear();
}

//Copy-ctor
Message::Message(const Message &m):contents(m.contents),folders(m.folders){
add_to_Folders(m);
}
	
//Destructor
Message::~Message(){
	remove_from_Folders();
}	

//Assignment copy
Message& Message::operator=(const Message &rhs){
	//Remove old msg from folders
	remove_from_Folders();
	
	//Copy content and folders
	contents=rhs.contents;
	folders=rhs.folders;
	
	//Add new message to folders
	add_to_Folders(rhs);
	
	return *this;
}

//Save to folder fcn
void Message::save(Folder &f){
	//Add folder pointer to message set
	folders.insert(&f); //This is address of
	
	//Add mesage to folder
	f.addMsg(*this);
}

//Remove from folder fcn
void Message::remove(Folder &f){
	//Remove folder from folders set
	folders.erase(&f);
	
	//Remove msg from designated folder
	f.remMsg(*this);
}

void Message::addFolder(Folder &f){
	folders.insert(&f);
}

void Message::remFolder(Folder &f){
	folders.erase(&f);
}

void Message::debug(){
	cout<<contents<<endl;
	for(Folder* el:folders){
		std::cout<<el<<std::endl;
	}
}

void swap(Message & lhs, Message &rhs){
	using std::swap;
	
	//Remove pointers to both messages from folders
	for(Folder* el:lhs.folders){
		el->remMsg(lhs);
	}
	for(Folder* el:rhs.folders){
		el->remMsg(rhs);
	}
	
	//Swap variables
	swap(lhs.contents, rhs.contents);
	swap(lhs.folders,rhs.folders);
	
	//Add swaped messages to folders
	for(Folder* el:lhs.folders){
		el->addMsg(lhs);
	}
	for(Folder* el:rhs.folders){
		el->addMsg(rhs);
	}
}

//------------------------------------

//Folder functions

//Ctors
Folder::Folder(const Folder &f): messages(f.messages){
	
	add_to_Message(f);
}

//Assignment operator

Folder& Folder::operator=(const Folder &f){
	rem_from_Message();
	messages=f.messages;
	add_to_Message(f);
	return *this;
}
//Add message
void Folder::addMsg(Message &m){
	messages.insert(&m);
	//m.addFolder(*this);
}

//Remove message
void Folder::remMsg(Message &m){
	messages.erase(&m);
	//m.remFolder(*this);
}


void Folder::add_to_Message(const Folder &f){
	
	//Add this folder to messages from set
	for(Message* el:f.messages){
		el->addFolder(*this);
	}
}

void Folder::rem_from_Message(){
	
	//Remove this folder to messages from set
	for(Message* el:messages){
		el->remFolder(*this);
	}
}

void Folder::debug(){
	cout<<"Folder debug\n";
	for(Message* el:messages){
		std::cout<<el->contents<<std::endl;
	}
}




//-------------------------------------------
