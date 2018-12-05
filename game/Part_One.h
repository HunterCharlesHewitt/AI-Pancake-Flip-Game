#include <string>
#include <ncurses.h>
#include <unistd.h>
#include <pthread.h>
#include <iostream>
using namespace std; 

class Part_One { //this class is used to run the two functions needed for part one of the assignment
public: 
	void run_Part_One(WINDOW* wind); //run part one will take in a window from the board class, and use it to display the splash screen
	void print_instructions(WINDOW* wind); //print instructions will print the instructions to the same screen
};
