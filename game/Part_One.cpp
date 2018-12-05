#include "Part_One.h"

void Part_One::run_Part_One(WINDOW* wind){  
  do {
      mvwprintw(wind, 6, 22, "PANCFLIPAKE: A GAME BY DRAGONFORCE"); //start printing splash screen instructions from the board object 
      mvwprintw(wind, 7, 35, "GROUP 3");
      mvwprintw(wind, 8, 15, "JOHN DORMAN, DONALD ELROD, HUNTER HEWITT, DANIEL LE"); 
      mvwprintw(wind, 16,23, "------------------------------");
      mvwprintw(wind, 14,23, "------------------------------");
      wrefresh(wind); //refresh the window 
      wattron(wind, A_BLINK); // turn on blinking
      mvwprintw(wind, 15, 23, "|PRESS ENTER TO PLAY OUR GAME|");
      wrefresh(wind);
      wattroff(wind, A_BLINK); //turn off blinking 
  }
  while(getchar() != 13); //when the user hits enter (escape key 13), break through and continue to instruction window 
  refresh();
  wclear(wind); //clear the window 
  werase(wind); //erase just in case 
  wrefresh(wind);
}

void Part_One::print_instructions(WINDOW* wind) { 
  do {
    deleteln();
    mvwprintw(wind, 6, 10, "INSTRUCTIONS: ");
    mvwprintw(wind, 7, 4, "1: The objective of the game is to order a stack of unordered pancakes ");
    mvwprintw(wind, 8, 4, "into ascending order by flipping the stack between certain cakes");
    mvwprintw(wind, 10, 4, "2: On the following screen, enter the number of pancakes you wish to sort. ");
    mvwprintw(wind, 12, 4, "3: Next, enter your desired difficulty. ");
    mvwprintw(wind, 14, 4, "4: Choose the order of pancakes you wish to begin with, or choose random. ");
    mvwprintw(wind, 16, 4, "5: Enter your initials. ");
    mvwprintw(wind, 18, 4, "6: Use the arrow keys to select a flip position for your spatula. ");
    mvwprintw(wind, 20, 4, "7: The order of the pancakes above the flip position will then be reversed.");
    mvwprintw(wind, 22, 4, "8: If you order the pancakes faster than the computer you win!");
    mvwprintw(wind, 24, 4, "Press enter to continue ");
    wrefresh(wind);
  }
  while(getchar() != 13); //when the user hits enter (escape key 13), continue to next part of main
  refresh();
  wrefresh(wind);
  clear();
  wrefresh(wind);
}