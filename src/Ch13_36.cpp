#include "Ch13_36.h"
#include <iostream>

using namespace std;

//MESSAGE FUNCTIONS


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


//Move ctor
Message::Message(Message&& m):contents(std::move(m.contents)),
	folders(std::move(m.folders)){
	
	mov_update_folders(m);
	
}


//Move assignment operator
Message& Message::operator=(Message&& rhs){
	
	if(this!=&rhs){//Self assignment protection
		remove_from_Folders(); //Remove this message from curent folders.
		
		//Move resources
		contents=std::move(rhs.contents);
		folders=std::move(rhs.folders);
		
		mov_update_folders(rhs);
	}
	
	return *this;
}


//Update folders to point this object and delete previous;
void Message::mov_update_folders(Message& rhs){
	
	for(Folder* fol:folders){
		fol->remMsg(rhs); //Delete RHS message from folders
		fol->addMsg(*this); //Add this message to folders
	}
}

//Save to folder fcn
void Message::save(Folder &f){
	//Add folder pointer to message set
	folders.insert(&f);
	
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


//Add folder to message
void Message::addFolder(Folder &f){
	folders.insert(&f);
}


//Remove folder from this message
void Message::remFolder(Folder &f){
	folders.erase(&f);
}


//Add message to all folders fcn
void Message::add_to_Folders(const Message &m){
	//Add new message to all folders from set
	for(Folder* el:m.folders){
		el->addMsg(*this);
	}	
}


//Remove message from all folders
void Message::remove_from_Folders(){
	for(Folder* el:folders){
		el->remMsg(*this);
	}
	folders.clear();
}


//Debug - Print contents
void Message::debug(){
	cout<<contents<<endl;
	for(Folder* el:folders){
		std::cout<<el<<std::endl;
	}
}


//Test - Return set
const set<Folder*>& Message::test(){
	return folders;
}


//Swap two Message obejcts
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


//----------------------------------------------------------------


//Folder functions

//Ctors
Folder::Folder(const Folder &f): messages(f.messages){
	
	add_to_Messages(f);
}

//Destructor

Folder::~Folder(){
	rem_from_Messages(*this);
	//cout<<this<<" Folder Destructor Done"<<endl;
}

//Assignment operator

Folder& Folder::operator=(const Folder &f){
	rem_from_Messages(*this);
	messages=f.messages;
	add_to_Messages(f);
	return *this;
}


//Move ctor
Folder::Folder(Folder&& f){
	//Move messages set to current folder.
	messages=std::move(f.messages);
	
	for(Message* el:messages){
		el->remFolder(f); //Remove previous folder from Messages
		el->addFolder(*this); //Add current folder to messages
	}
}


//Move assignment operator
Folder& Folder::operator=(Folder&& old){
	if(this != &old){
		
		//Remove current folder from messages.
		for(auto el:messages){
			el->remFolder(*this);
		}
		
		//Assign moved messages to current. It will move it(&&)
		messages=old.messages;
		
		//Remove moved folder and add current folder to messages.
		for(Message* el:messages){
			el->remFolder(old); //Remove movedfolder from Messages
			el->addFolder(*this); //Add current folder to messages
		}
		
		//Remove messages from moved folder
		old.messages.clear();
	}
	//If they are the same nothing will happen.
	return *this;
}
		
		
//Add message
void Folder::addMsg(Message &m){
	messages.insert(&m);
}


//Remove message
void Folder::remMsg(Message &m){
	messages.erase(&m);
}


//Adds folder to messages
void Folder::add_to_Messages(const Folder &f){
	
	//Add this folder to messages from set
	for(Message* el:f.messages){
		el->addFolder(*this);
	}
}

//Remove folder from all messages
void Folder::rem_from_Messages(Folder& f){
	
	//Remove this folder to messages from set
	for(Message* el:f.messages){
		el->remFolder(f);
	}
}

const set<Message*>& Folder::test(){
	return messages;
}

void Folder::debug(){
	cout<<"Folder debug\n";
	for(Message* el:messages){
		std::cout<<el<<"\t"<<el->contents<<std::endl;
	}
}




//-------------------------------------------
