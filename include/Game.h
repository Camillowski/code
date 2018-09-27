#ifndef GAME_H
#define GAME_H

/*
- Make him walk with regular cin and enter
- TEST IT!
*/
class Screen{
public:
	typedef std::string::size_type pos;
	Screen()=default;
	
	//ctor sets screen dimensions and fills it with one char 
	Screen(pos ht, pos wd, char c=' '):height(ht), width(wd), contents(ht*wd,c){}
	
	//get(int,int) returns character on cursor or on (row,col)
	char get()const{ return contents[cursor]; }//Inline implicitly
	char get(pos, pos)const;
	pos getHeight()const {return height;}
	pos getWidth()const {return width;}
	//move(int,int) moves cursor to coordinates
	Screen& move(pos row, pos col);
	
	//set() Sets character on cursor or on cordinates
	Screen& set(char c){
		contents[cursor]=c;
		return *this;
	}
	Screen& set(pos row, pos col, char c);
	
	//Display screen
	const Screen& display(std::ostream&)const;
		
private:
	pos cursor=0;
	pos height=0, width=0;
	std::string contents;
	mutable size_t getAccess_ctr=0; //Gts modified in const object
};

const Screen& Screen::display(std::ostream& os)const{
	for(size_t row=0;row<height;++row){
		for(size_t col=0;col<width;col++){
			os<<contents[row*width+col];
		}
		os<<std::endl;
	}
	return *this;
}

Screen& Screen::set(pos row, pos col, char c){
	row*=width;
	contents[row+col]=c;
	return *this;
}

inline
char Screen::get(pos row, pos col)const{
	getAccess_ctr++;//It will modify member even in const object
	row=(row)*width;
	return contents[row+col];	
}

//Make move function. Set cursor position (row, col_. Make it chainable, 
inline
Screen& Screen::move(pos row, pos col){
	row=row*width;
	cursor=row+col;
	return *this; // (*) because I want to return an object
}


class Hero{ 
	private: 
	typedef std::string::size_type pos;
	pos posX, posY;
	char body;
	
	public:
	
	Hero(pos x=0, pos y=0, char b='o'):posX(x), posY(y), body(b) {}
	
	//Place heroe on the screen Means change one char on the screen
	//Depending on key pressed add or substract numbers from col and row
	
	pos getPosX(){return posX;}
	pos getPosY(){return posY;}
	
	
	void move(istream& is, const Screen &scr){
		char keyPressed;
		cin>>char;
		switch(keyPressed){
			case 'up':
				if(posY!=0) --posY;
				break;
			case 'down':
				if(posY!=scr.getHeight()) --posY;
				break;
			case 'left':
				if(posX!=0) --posX;
				break;
			case 'right':
				if(posX!=scr.getWidth()) ++posX;
				break;
			default:
				break;	
		}
	}
	

};
#endif