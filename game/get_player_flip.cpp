#include <vector>
#include <curses.h>
#include <unistd.h>

using namespace std;

//Moves the spatula cursor as dicated by the user input from get_player_flip, moves y units and x units to location and refreshes window.
void move_spatula(WINDOW* spatula, int y, int x) {
        mvwin(spatula, y, x);
        mvwprintw(spatula, 0, 0, "<----");
        wrefresh(spatula);
}


/* Enables the user to choose a flip by moving a small arrow cursor around the stack with WS keys, designating 
 * what portion of the stack should be flipped. Returns an integer value later processed by another
 * function for flipping that will flip the stack the way the user desires. Cursors "moves" by
 * deleting the arrow inside of it and then moving the "spatula" window only to print the same
 * arrow inside it. Bounds are checked if the flip surpasses the stack going to far above or below it.
 * User enters to confirm the flip action.*/
int get_player_flip(WINDOW* w, int stack_size) {
	int x = 38, y = 13, flip = 1;
	int c;

	WINDOW* spatula = subwin(w, 1, 5, y, x);
	mvwprintw(spatula, 0, 0, "<----");
	wmove(spatula, 0, 0);
	wrefresh(spatula);
			
	do{
		c = getchar();
		wmove(spatula, 0, 0);

		if(flip != 1 && (c == KEY_UP || c == 119)){
			for(int i = 0; i < 5; ++i) wdelch(spatula);
			y -= 3;
			flip--;
		}
		else if(flip != stack_size && (c == KEY_DOWN || c == 115)){
			for(int i = 0; i < 5; ++i) wdelch(spatula);
			y += 3;
			flip++;
		}
		
		wrefresh(spatula);	
		move_spatula(spatula, y, x);
		
	} while(c != 13);
	
	

	return flip;	
}

