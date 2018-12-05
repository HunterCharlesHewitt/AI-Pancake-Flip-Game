#include "Board.h"

int main() {
    Board b;
    do{
    //part 1
        werase(b.win);
        clear();
        b.print_box();
        b.display_sscreen();

        //part 2
        werase(b.win);
        clear();
        b.print_box();
        b.display_gamestate_init();

        //part 3
        werase(b.win);
        clear();
        b.print_box();
        b.display_pancake_init();
	
        //part 4
        werase(b.win);
        clear();
        b.print_box();
        b.display_top5_scores();

        b.generate_Tree();
	
	werase(b.win);
	clear();
	b.print_box();

    
	while(!(b.is_gameover())){
		b.display_pancake_stacks();
		b.get_player_move();
        b.get_AI_move(b.num_moves);
        if(b.is_gameover()) {sleep(3);}
        wrefresh(b.win);
		werase(b.win);
		clear();
		b.print_box();
        ++b.num_moves;
	}
	
	/*
        //part 5
        werase(b.win);
        clear();
        b.print_box();
        b.display_pancake_stacks();

        //part 6
        b.get_player_move();
	*/

        //part8
        werase(b.win);
        clear();
        b.print_box();
        b.display_gameover_screen();
        b.clear_pancake_stacks();
        delete b.t;
    } while(b.play);


    delwin(b.win);
    endwin();
    return 0;
}
