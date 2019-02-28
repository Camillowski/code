#ifndef CH13_36_H
#define CH13_36_H

#include <string>
#include <set>

//MESSAGE CLASSES
/*
This is a simple system to represent storing data.

It has class Messsage that contains message string and set of folder pointer where the class exists.

It has Folder class that stores pointers to messages.
*/

class Folder;

//------------------------------------------------------
class Message{
	public:
		friend void swap(Message&,Message&);
		friend class Folder;
		//Ctor
		explicit Message(std::string str=""):contents(str){}
		
		//Copy-ctor
		Message(const Message&);
		
		//Destructor
		~Message();
		
		//Assignment copy
		Message& operator=(const Message&);
		
		//Move ctor
		Message(Message&&);
		
		//Move assignment operator
		Message& operator=(Message&&);
		
		//Add or Remove message from folder
		void save(Folder&);
		void remove(Folder&);
		
		//Adds and removes folder from message
		void addFolder(Folder&);
		void remFolder(Folder&);
		
		//Debug - Print content and folder pointers
		void debug();
		
		//Test - return copy of set with folder ptrs
		const std::set<Folder*>& test();
	
	private:
		//Update folders after move operation
		void mov_update_folders(Message&);
		
		//Add message to all folderS
		void add_to_Folders(const Message&);
		
		//Remove this message from all folderS
		void remove_from_Folders();
	
	private:
		std::string contents; //Holds text
		std::set<Folder*> folders; //Holds ptrs to folders
	
};

class Folder{
	public:
		friend class Message;
		
		//Ctors
		Folder(){}
		Folder(const Folder &f);
		Folder(Folder&&);
		~Folder();
		
		//Asignment operator
		Folder& operator=(const Folder&);
		
		//Move assignment operator
		Folder& operator=(Folder&&);
		
		//Add message to this filder
		void addMsg(Message&);
		
		//Remove message from this folder
		void remMsg(Message&);
		
		//Debug
		void debug();
		
		//Test - Return copy of set.
		const std::set<Message*>& test();
		
	private:
		//Add or remove folder from Messsages in set
		void add_to_Messages(const Folder&);
		void rem_from_Messages(Folder&);
	
	private:
		std::set<Message*> messages;
};



#endif