#ifndef CH13_36_H
#define CH13_36_H

#include <string>
#include <set>

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
		
		//Save to folder fcn
		void save(Folder&);

		//Remove from folder fcn
		void remove(Folder&);
		
		//Adds and removes folders
		void addFolder(Folder&);
		
		void remFolder(Folder&);
		
		//Debug
		void debug();
	
	private:
		//Add to folders fcn
		void add_to_Folders(const Message&);
		
		//Remove from folders fcn
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
		//~Folder(){}
		
		//Add message
		void addMsg(Message&);
		
		//Remove message
		void remMsg(Message&);
		
		//Debug
		void debug();
		
	private:
		void add_to_Message(const Folder&);
		void rem_from_Message();
	
	private:
		std::set<Message*> messages;
};



#endif