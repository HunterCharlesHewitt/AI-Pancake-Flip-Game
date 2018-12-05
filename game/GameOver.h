#include <iostream>     
#include <fstream>  
#include <sstream>      
#include <vector>    
#include <curses.h> 
#include <unistd.h>
#include <cstring>
#include <cstdlib>
using namespace std;

class GameOver : public DisplayScores {
public:
    int game_case;

public:
    GameOver(WINDOW* win);
    ~GameOver();
    void calculate_score(string name, int difficulty, int num_moves, int game_case);
    void sort_scores();
    void update_file();
    void display_winner();
    void print_AI_won();
    void print_player_won();
    void print_tie();
    bool play_again();
    void run_part8();
};