//#define CATCH_CONFIG_MAIN // Tells Catch to provide a main() when function code is compiled by itself
//#include "catch.hpp"

#include <iostream>
#include <stdexcept>
#include <ctime>
#include <string>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <unistd.h>
#include <curses.h>

using namespace std;

/* This function simply obtains and integer value from the user, checks to see if it the input was an appropriate
 * integer, backspace, or DEL character value, then either adds the value to the current input string (2-9), deletes
 * the current character in the input string (backspace or DEL), or stores the input in an integer value and returns that value
 * The selection statements operate on the basis of ASCII integer representation for characters. ncurse windows and cursors are
 * updated according to the current ASCII selection. Only permissible characters are 2-9, backspace, DEL, and enter. In order to accept
 * a user input, string must have a integer character and the user must press enter to confirm. */
int get_numeric_value(WINDOW* w, int y, int x){
	string input = ""; 
        char c;
        int x1 = x;
        wmove(w,y,x);
        do{
                c = getchar();
                if((c >= 49 && c <= 57) && input.length() < 1) {
                        input += c;
                        x += 1;
                }
                else if((c == 127 || c == 8) && input.length() > 0){ 
                        input.pop_back();
                        x -= 1;
                        wmove(w, y, x); 
			mvwprintw(w, y, x, " ");
                }
                wmove(w, y, x); 
                mvwprintw(w, y, x1, input.c_str());
                wrefresh(w);

        } while(c != 13 || input.length() == 0);

        int val = atoi(input.c_str());
        return val;


}

/* The get_game_state function uses the collective window stored in a Board object to produce a prompt for the user to 
 * enter the necessary variables for game setup. It will ask the user twice for a numeric value via get_numeric_value, then stores
 * these variables in the vector that will later be returned to the Board class via wrapper function, where class variables will be 
 * mutated accordingly. User will retype an error when the difficulty for AI is greater than size, since the depth cannot extend past
 * the maximum tree depth which is tied to stack size. While cycle through error message until proper criteria for difficulty is met.*/
vector<int> get_game_state(WINDOW* w){	
	int size, difficulty;
        mvwprintw(w, 10, 10, "Please enter the number of pancakes for the stack: ");
        wrefresh(w);
       	size = get_numeric_value(w, 10, 10 + 51);

	while(size == 1){
		mvwprintw(w, 10, 10, "Please enter the number of pancakes for the stack: ");
		mvwprintw(w, 30, 10, "Stack size must be an integer value from 2 to 9!");
		wrefresh(w);
		size = get_numeric_value(w, 10, 10 + 51);
	}

        mvwprintw(w, 12, 12, "Please enter the number for AI difficulty level: ");
        wrefresh(w);
        difficulty = get_numeric_value(w, 12, 12 + 49);

        while(difficulty > size){
                mvwprintw(w, 12, 12, "Please enter the number for AI difficulty level: ");
                mvwprintw(w, 30, 10, "AI level cannot be greater than stack size!");
                wrefresh(w);
                difficulty = get_numeric_value(w, 12, 12 + 49);
        }

        wclear(w);
        wrefresh(w);
	
	vector<int> vars(2);
	vars[0] = size;
	vars[1] = difficulty;
	return vars;
}




// Observe the code down here to get a good idea of how to make use of Catch2

/*
 * With Catch2, we can place both the function code and unit test in the same file. Executing the executable 
 * created by just compiling the function code w/o arguments will allow all test cases (contained in SECTION)
 * to run. Whatever variables needed can be created inside or outside the scope of the SECTION code. The
 * following tests simply verify whether or not the get_game_state function above is mutating the variables
 * correctly.
 * */
/*
TEST_CASE("Game states are obtained", "[get_game_state]"){
	int stack_size = 0, ai_competency = 0;

	SECTION("General mutation of game state variables"){
		
		std::cout << "(Enter any valid number)" << std::endl;
		get_game_state(&stack_size, &ai_competency);

		REQUIRE(stack_size > 0);
		REQUIRE(ai_competency > 0);
	}

	SECTION("Mutation of previously used game state variables"){
		int prev_size = stack_size;
		int prev_competency = ai_competency;

		std::cout << "(Enter any other valid numbers not used previously)" << std::endl;
		get_game_state(&stack_size, &ai_competency);

		REQUIRE(stack_size != prev_size);
		REQUIRE(ai_competency != prev_competency);
	}

	SECTION("Correct mutation of game state variables"){
		std::cout << "(Enter 3 for size of stack and 2 for AI competency)" << std::endl;
		get_game_state(&stack_size, &ai_competency);

		REQUIRE(stack_size == 3);
		REQUIRE(ai_competency == 2);
	}
}
*/



