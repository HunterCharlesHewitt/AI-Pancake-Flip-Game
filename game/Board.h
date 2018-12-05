//#include "catch.hpp"
#include <ctime>
#include <string>
#include <curses.h>
#include <iostream>
#include <algorithm>
#include <unistd.h>
#include "set_init_state.cpp"
#include "Part_One.cpp"
#include "DisplayScores.cpp"
#include "get_game_state.cpp"
#include "show_pancake_stacks.cpp"
#include "GameOver.cpp"
//#include "flip.cpp"
#include "Tree_Node.cpp"
#include <vector>
#include "find_solution.h"

/**
 * This class is what holds all variable about the game and game state, and will be used to call the various methods written by the team
 * We are using the one window throughout the program, and simply clearing it between functions so numerous windows are not created and destroyed
 * To use this class, import your .cpp files above and then call the methods needed to complete your individual function using the variables
 * stored in the instance of the class. See display_pancake_init function for an example on how to setup your functions for use with this class
 * 
 * 
 * DO NOT CALL endwin() OR delwin() INSIDE YOUR FUNCTIONS, THESE ARE CALLED AT THE VERY END OF main() AT THE BOTTOM
 * */
class Board {

public:
    vector<WINDOW*> player_stack;
    vector<WINDOW*> ai_stack;
    vector<int> player;
    vector<int> ai;
    int n;
    int difficulty;
    int player_move;
    int num_moves;
    int game_case; //if AI wins = 1, tie = 2 , user win = 3
    bool play;
    string initials;
    Tree* t = new Tree();
    Tree_Node tn;

    WINDOW* win;

    Board() {
        initscr();
        refresh();
        noecho();
        clear();
        refresh();
        this->win = newwin(40, 80, 0, 0);    
        keypad(win, TRUE);
        n = 9;
        num_moves = 0;
        game_case = 1;
        play = false;
    }
    
    void print_box() {
        box(win, 0, 0);  
        wrefresh(win);
    }

    void display_sscreen() { //part 1
        Part_One p;
        print_box();
        wrefresh(win);
        p.run_Part_One(win);
        print_box();
        wrefresh(win);
        p.print_instructions(win); 
    }

    void display_gamestate_init() { //part 2
        print_box();
        vector<int> vars = get_game_state(win);
        n = vars[0];
        difficulty = vars[1];
    }

    void display_pancake_init() { //part 3

        //gets the pancake stack from the user
        player = init_main(win, n); 

        //duplicates the vector for the ai's pancake stack
        for (int i = 0; i < n; ++i)
            this->ai.push_back(this->player.at(i));
    }

    void display_top5_scores() { //part 4
        print_box();
        DisplayScores ds = DisplayScores(win);
        ds.run_part4();
        initials = ds.get_initials();
    }

    //part 5
    void display_pancake_stacks() {
        player_stack.resize(n);
        ai_stack.resize(n);
        show_pancake_stacks(win, player_stack, ai_stack, player, ai);
    }

    void clear_pancake_stacks() {
    	for(int i = 0; i < n; ++i){
            delwin(player_stack.at(i));
            delwin(ai_stack.at(i));
        }
    }
   
    //part 6
    void get_player_move() {
	    player_move = get_player_flip(win, n);
        blink_pancake_stacks(win, player_stack, player, true, player_move);
        player = flip(player, player_move);
        werase(win);
        clear();
	    print_box();
        show_pancake_stacks(win, player_stack, ai_stack, player, ai);
    }

    //part 7

    void generate_Tree(){
        tn.node = ai;
        t->next_start_node = tn;
        std::pair<std::string,Tree_Node> tn_pair (tn.key, tn);
        t->created_map.insert(tn_pair);

    }

    void get_AI_move(int count){
        tn = make_move(tn, t, difficulty, count);
        blink_pancake_stacks(win, ai_stack, ai, false, tn.index);
        ai = tn.node;
        werase(win);
        clear();
        print_box();
        show_pancake_stacks(win, player_stack, ai_stack, player, ai);
    }

    void display_gameover_screen(){ //part 8
        print_box();
        GameOver go = GameOver(win);
        go.calculate_score(initials, difficulty, n, game_case);
        go.run_part8();
        play = go.play_again();
    }
    
    //Checks vectors to see if they are sorted. game will be over if at least one is sorted.
    bool is_gameover(){
	bool player_case = std::is_sorted(player.begin(), player.end()),
	     ai_case = std::is_sorted(ai.begin(), ai.end());
	if(player_case && ai_case){
		game_case = 2;
		return true;
	}
	else if(player_case){
		game_case = 3;
		return true;
	}
	else if(ai_case){
		game_case = 1;
		return true;
	}
	else return false;
    }	

    void clear_board() {
        wclear(this->win);
        refresh();
        wrefresh(this->win);
    }

};
