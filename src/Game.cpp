#include <iostream>
#include "Game.h"

using namespace std;

//SCREEN

const Screen& Screen::display(std::ostream& os)const{
	for(size_t row=0;row<height;++row){
		for(size_t col=0;col<width;col++){
			os<<contents[row*width+col];
		}
		os<<std::endl;
	}
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
Screen& Screen::moveCursor(pos row, pos col){
	row=row*width;
	cursor=row+col;
	return *this; // (*) because I want to return an object
}

Screen& Screen::set(char c){
	contents[cursor]=c;
	return *this;
}

Screen& Screen::set(pos row, pos col, char c){
	row*=width;
	contents[row+col]=c;
	return *this;
}

//HERO


void Hero::move(std::istream& is, const Screen &scr){
	char keyPressed;
	is>>keyPressed;
	switch(keyPressed){
		case 'u':
			if(posY!=0) --posY; //Make point and make it moveUp method.
			break;
		case 'd':
			if(posY!=scr.getHeight()) --posY;
			break;
		case 'l':
			if(posX!=0) --posX;
			break;
		case 'r':
			if(posX!=scr.getWidth()) ++posX;
			break;
		default:
			break;	
	}
}
