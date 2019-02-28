#include <iostream>
#include <ncurses.h>
#include <vector>
#include <cctype>
#include <cstring>
#include <typeinfo>
//#include "Game.h"

using namespace std;

int main(){

}

//Ex. Sample menu with choosable number of positions
/*

int main(){
initscr();
	
	//ncurses init
	start_color();
	init_pair(1,1,0);
	echo();
	
	
	//variables
	int pos=0;
	int key=0;
	int strWidth=6;
	char* items[]{"First","Second","Third","Fourth","Fifth","Sixth"};
	const int arrSize=sizeof(items)/sizeof(items[0]);
	const short int minPos=0;
	short int maxPos=arrSize;
	char tempStr[12];
	
	
	
	//printw("%s %d",tempStr,strlen(tempStr));
	
	//DOESNT WORK
	// //extend items with spaces to fit strWidth. Make it equal.
	// for(int i=0;i<arrSize;++i){
		// int itDiff=strWidth-strlen(items[i]);
		// for(int j=0;j<itDiff;++j)
			// strcat(items[i]," ");
		// printw("%d\n",strlen(items[i]));
		
	// }
	//getch();
	
	//Init size
	int row,col;
	getmaxyx(stdscr,row, col);
	
	curs_set(0);
	do{
		//show menu
		for(int i=0;i<maxPos;++i){
			
			//Convert menu elements to have spaces
			string tempString(10,' '); //Make space string
			tempString.replace(0,strlen(items[i]),items[i]);//Replace chars from 0 to len with c-string
			strcpy(tempStr,tempString.c_str());//Copy string to c-string
			
			if(i!=pos)
				mvprintw(i,0,tempStr);
			else{
				attron(A_REVERSE);
				mvprintw(i,0,tempStr);
				attroff(A_REVERSE);
			}
		}
		
		//Exit. If pos = exit hoghlight if not then not
		
		if(pos!=maxPos){
			attron(A_BOLD | COLOR_PAIR(1));
			mvprintw(maxPos,0,"Exit      ");
		}else{
			attron(A_REVERSE | A_BOLD | COLOR_PAIR(1));
			mvprintw(maxPos,0,"Exit      ");
		}
		attroff(A_REVERSE | A_BOLD | COLOR_PAIR(1));
		
		//read key and change position
		noecho();
		key=getch();
		if(key==65){
			if(pos!=minPos)
				--pos;
			else
				pos=maxPos;
		}else if(key==66){
			if(pos!=maxPos)
				++pos;
			else
				pos=minPos;
		}
	}while(pos!=maxPos || key!=10);
	
endwin();
}
*/

//Lesson 7 - Simple menu
/*
int main(){
initscr();
	
	printw("Press key:\n");
	noecho();
	
	//Objects
	const char* txt[]={"First Choice", "Second Choice", "Exit"};
	const int arrSize=sizeof(txt)/sizeof(txt[0]);
	int pos=0;
	int key=0;
	const short int minPos=0;
	const short int maxPos=arrSize-1;
	
	int row,col;
	getmaxyx(stdscr,row, col);
	
	do{
		//Get char
		key=getch();
		clear();
		printw("%d",key);
		//Reaction on a / z
		if(key==65 && pos!= minPos){
			--pos;
		}else if(key==66 && pos!=maxPos){
			++pos;
		}
		
		//Reaction on Enter, prints Choice# in top left
		if(key==10){
			switch(pos){
			case 0:
				mvprintw(0,0,"Choice #1");
				break;
			case 1:
				mvprintw(0,0,"Choice #2");
				break;
			}
			
		}
		
		//Print menu depending on choice
		//#pos different rest ok
		//Option 1
		//Option 2
		//Exit
		
		switch(pos){
			case 0:
				mvprintw(5+(pos==0?1:0),5,txt[(pos==0?1:0)]);
				mvprintw(5+(pos==2?1:2),5,txt[(pos==2?1:2)]);
				attron(A_REVERSE);
				mvprintw(pos+5,5,txt[pos]); //1st changed
				break;
			case 1:
				mvprintw(5,5,txt[0]);
				mvprintw(7,5,txt[2]);
				attron(A_REVERSE);
				mvprintw(pos+5,5,txt[pos]); //2nd changed
				break;
			case 2:
				mvprintw(5,5,txt[0]);
				mvprintw(6,5,txt[1]);
				attron(A_REVERSE);
				mvprintw(pos+5,5,txt[pos]); //3rd changed
				break;
			default:
				break;
		}
		attroff(A_REVERSE);
		
	//}while(!(pos==3 && key==10)); //End if cursor on exit and hit enter
	}while(pos!=2 || key!=10); //When both are false then =is false
	
	
	char endStr[]{"End of program"};
	int strSize= sizeof(endStr)/sizeof(endStr[0]);
	move(row/2,col/2-strSize/2);
	printw("%s",endStr);
getch();
endwin();

	// for(int i=0;i<arrSize;++i){
		// printw("%s\n",txt[i]);
	// }
	//printw("%d %d",minPos,maxPos);
}
*/

//Lesson 6 - Positioning
/*
int main(){
initscr();
	int cols=0, rows=0;
	char text[]="Hello World!";
	getmaxyx(stdscr,rows,cols); //Insert to cols and rows
	
	mvprintw(rows/2,cols/2-(sizeof(text)/2),text); //Print to middle
	move(0,0);//Moves cursor
	
getch();	
endwin();
}
/*

//Lesson 5 - Colors
/*
int main(){
initscr();
	
	//Ends program if console not suited
	if (has_colors()==false){
		printw("Console don't use colors");
		getch();
		endwin();
		return -1;
	}
	
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	attron(COLOR_PAIR(1));
	printw("Colourfull stuff :)");
	attroff(COLOR_PAIR(1));
	
getch();	
endwin();
}
*/

//Lesson 4 - Underline and bold
/*
int main(){
	
	initscr();
	raw();
	keypad(stdscr, false);
	char znak;
	do{
		printw("Wpisz ");
		attron(A_UNDERLINE);
		printw("tekst: ");
		attroff(A_UNDERLINE);
		char txt[40];
		getstr(txt);
		printw("Wpisany tekst to: ");
		attron(A_BOLD | A_UNDERLINE);
		printw("%s",txt);
		attroff(A_UNDERLINE | A_BOLD);
		printw("\n\nZakonczyc(t/n)? ");
		znak=getch();
		
		if (znak=='t') znak='T';
		else if (znak!='T') printw("\n\n\n");
		
	}while(znak!='T');
	
	endwin();
	return 0;
}
*/

//Lekcja 1-3
/*
int main(){
	
	initscr();
	keypad(stdscr, true); //Allow arrows
	printw("Here is gonna come a cool game :)\nPress a key: ");
	noecho();//Dont show input
	
	int litera = getch();//Input
	
	printw("Keypressed: ");
	attron(A_BOLD);//Bold next printw
	printw("%d \n",litera);// %d - print char as int
	printw("%c \n",litera);// %c - Print char normal

	getch(); //Wait for key before end prog
	endwin();
	
	
return 0;\
}
*/
	/*
	Screeen scr;
	Hero wiz;
	
	while(true){
		//take arrow with cin and enter
		//change x,y
		wiz.move();
		
		//take hero position and write there hero character
		//take previous position and write there .
		scr.update();
		
		//print new screen
		scr.print();
	}
	*/
