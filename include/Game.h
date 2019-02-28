#ifndef GAME_H
#define GAME_H
/*
- Make him walk with regular cin and enter
- TEST IT!
*/
class Screen{
public:
	typedef std::string::size_type pos;
private:
	pos cursor;
	pos height, width;
	std::string contents;
	mutable size_t getAccess_ctr; //Gts modified in const object

public:
	//Default ctor
	Screen():cursor(0),height(0),width(0),contents(), getAccess_ctr(0){}
	
	//Ctor sets screen dimensions and fills it with one char 
	Screen(pos ht, pos wd, char c=' '):height(ht), width(wd), contents(ht*wd,c){}
	
	//get(int,int) returns character on cursor or on (row,col)
	char get()const{ return contents[cursor]; }//Inline implicitly
	char get(pos, pos)const;
	
	//Return size of screen
	pos getHeight()const {return height;}
	pos getWidth()const {return width;}
	
	//move(int,int) moves cursor to coordinates
	Screen& moveCursor(pos row, pos col);
	
	//set() Sets character on cursor or on cordinates
	Screen& set(char c);
	Screen& set(pos row, pos col, char c);
	
	//Display screen
	const Screen& display(std::ostream&)const;
};


class Hero{ 
private: 
	typedef std::string::size_type pos;
	pos posX, posY; //Implement point!
	char body;
	
public:
	
	Hero(pos x=0, pos y=0, char b='o'):posX(x), posY(y), body(b) {}
	
	//Place heroe on the screen Means change one char on the screen
	//Depending on key pressed add or substract numbers from col and row
	
	pos getPosX(){return posX;}
	pos getPosY(){return posY;}
	
	
	void move(std::istream& is, const Screen &scr);
	

};
#endif