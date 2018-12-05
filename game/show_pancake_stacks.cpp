#include <vector>
#include <curses.h>
#include <unistd.h>
#include "get_player_flip.cpp"

using namespace std;

//Given 2 lines, 10 nlines, 10 cols, 10 ncols?

/* This function serves to print pancake stacks to screen using ncurses subwindows. The subwindows are kept in vectors
 * for organization, and are updated as need be. Both will be similar size of player and AI vectors since the integer
 * vectors are a integer representation of the game, while the stack vectors are the ncurses representation of the game.
 * Left is the player stack while right is the AI stack. Both are kept centered and orderly for aesthetic.*/
void show_pancake_stacks(WINDOW* w, vector<WINDOW*> player_stack, vector<WINDOW*> ai_stack, vector<int>& player_vec, vector<int>& ai_vec){
	int size = player_vec.size();
	mvwprintw(w, 2, 31, "FLIP, FLIP, FLIP!");
	mvwprintw(w, 8, 13, "PLAYER STACK");
	mvwprintw(w, 8, 56, "CPU STACK");
	wrefresh(w);
	
	//Player stack ncurses represenation. Subwindow vector is updated/refreshed accordingly.
	for(int i = 0; i < size; ++i){
		player_stack.at(i) = subwin(w, 3, player_vec.at(i) * 4, 11 + 3*i, 2*(9 - player_vec.at(i)) + 1);		
		box(player_stack.at(i), 124, 45);
		mvwprintw(player_stack.at(i), 1, (player_vec.at(i) * 2), to_string(player_vec.at(i)).c_str());
		wrefresh(player_stack.at(i));
	}

	//AI stack ncurses representation. Acts in similar manner to player, yet situated at right of screen.
	for(int i = 0; i < size; ++i){
		ai_stack.at(i) = subwin(w, 3, ai_vec.at(i) * 4, 11 + 3*i, 2*(9 - ai_vec.at(i)) + 43);
		box(ai_stack.at(i), 124, 45);
		mvwprintw(ai_stack.at(i), 1, ai_vec.at(i) * 2, to_string(ai_vec.at(i)).c_str());
		wrefresh(ai_stack.at(i));
	}
}

/* This function serves to print pancake stacks to screen using ncurses subwindows. The subwindows are kept in vectors
 * for organization, and are updated as need be. Both will be similar size of player and AI vectors since the integer
 * vectors are a integer representation of the game, while the stack vectors are the ncurses representation of the game.
 * Left is the player stack while right is the AI stack. Both are kept centered and orderly for aesthetic.*/
void blink_pancake_stacks(WINDOW* w, vector<WINDOW*> player_stack, vector<int>& player_vec, bool player, int p_move){
	int size = player_vec.size();
	mvwprintw(w, 2, 31, "FLIP, FLIP, FLIP!");
	mvwprintw(w, 8, 13, "PLAYER STACK");
	mvwprintw(w, 8, 56, "CPU STACK");
	wrefresh(w);
	
	int padding = player ? 1 : 43;

	//Player stack ncurses represenation. Subwindow vector is updated/refreshed accordingly.
	for(int i = 0; i < size; ++i){
		player_stack.at(i) = subwin(w, 3, player_vec.at(i) * 4, 11 + 3*i, 2*(9 - player_vec.at(i)) + padding);
		if (i < p_move)
			wattron(player_stack.at(i), A_BLINK);
		box(player_stack.at(i), 124, 45);
		mvwprintw(player_stack.at(i), 1, (player_vec.at(i) * 2), to_string(player_vec.at(i)).c_str());
		wrefresh(player_stack.at(i));
	}

	sleep(3);

	for(int i = 0; i < size; ++i){
		player_stack.at(i) = subwin(w, 3, player_vec.at(i) * 4, 11 + 3*i, 2*(9 - player_vec.at(i)) + padding);
		if (i < p_move)
			wattroff(player_stack.at(i), A_BLINK);
		box(player_stack.at(i), 124, 45);
		mvwprintw(player_stack.at(i), 1, (player_vec.at(i) * 2), to_string(player_vec.at(i)).c_str());
		wrefresh(player_stack.at(i));
	}

}

