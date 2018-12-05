#include <iostream>     
#include <fstream>  
#include <sstream>      
#include <vector>    
#include <curses.h> 
#include <unistd.h>
#include <cstring>
#include <cstdlib>
using namespace std;

class DisplayScores {
public:
    vector<vector<string> > top5scores; //holds the name & score in each element
    string initials; //holds current player initials
    string scores_filename; //holds filename where scores are kept
    int player_score; //holds player's score
    WINDOW* my_win;
    //holds screen dimension info
    int width;
    int height;
    int startx;
    int starty;

public:
   DisplayScores(WINDOW* win); 
   ~DisplayScores();
   void display_top_5();
   void ask_initials();
   void populate_top5scores();
   void display_player();
   void run_part4();
   void print_highscores_title();
   void wait_for_input();
   string get_input(int y, int x);
   string get_initials();
   vector<string> parse_string(string line);
};