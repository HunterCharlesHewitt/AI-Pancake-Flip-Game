#include "GameOver.h"

GameOver::GameOver(WINDOW* win) : DisplayScores(win){}

GameOver::~GameOver(){
    
}

void GameOver::run_part8() { //runs entire part 4
    wrefresh(my_win);
    //prints to window
    DisplayScores::populate_top5scores();
    sort_scores();
    update_file();
    display_top_5();
    DisplayScores::display_player();
    display_winner();
}

void GameOver::sort_scores(){
    vector<string> player;
    player.push_back(initials);
    player.push_back(to_string(player_score) );
    int j = -1;
    for(unsigned long int i=0; i<top5scores.size(); ++i){
        if (stoi(top5scores.at(i).at(1)) < player_score){
            j = i;
            break;
        }
    }
    if(j > -1){
        top5scores.insert(top5scores.begin()+j, player);
        top5scores.pop_back();
    }
}

void GameOver::update_file(){
    ofstream ofs{scores_filename};
    if(!ofs) {
        cerr << "can't open file\n";
        exit(0);
    }
    for(unsigned long int i=0; i<top5scores.size(); ++i) {
        ofs << top5scores.at(i).at(0) << " " << top5scores.at(i).at(1) << "\n";
    }
    ofs.close();
}

bool GameOver::play_again(){
    mvwprintw(my_win, height-5, width/2-18/2, "Play Again? (Y/N)");
    wrefresh(my_win);
    char c;
    do{
        mvwprintw(my_win, height-5, width/2-18/2, "Play Again? (Y/N)");
        c = getchar();
        wrefresh(my_win);
    }while(c!=89 && c!=121 && c!=78 && c!=110);
    if(c==89 || c==121)
        return true;
    else
        return false;
}

void GameOver::calculate_score(string name, int difficulty, int n, int gc){
    initials = name;
    game_case = gc;
    switch(game_case){
        case 1: //1. The AI stack is sorted but the human’s stack is not
            player_score = n;
            break;
        case 2: //2. Both stacks are sorted
            player_score = n * (difficulty + 1);
            break;
        case 3: //3. The human’s stack is sorted but the AI stack is not
            player_score = 2 * n * (difficulty +1);
            break;
        default:
            break;
    }
    wrefresh(my_win);
}

void GameOver::display_winner(){
    switch(game_case){
        case 1:
            print_AI_won();
            break;
        case 2:
            print_tie();
            break;
        case 3:
            print_player_won();
            break;
        default:
            break;
    }
}

void GameOver::print_AI_won(){
    mvwprintw(my_win, height-14, width/2-43/2, "          _____  __          ______  _   _ ");
    mvwprintw(my_win, height-13, width/2-43/2, "    /\\   |_   _| \\ \\        / / __ \\| \\ | |");
    mvwprintw(my_win, height-12, width/2-43/2, "   /  \\    | |    \\ \\  /\\  / / |  | |  \\| |");
    mvwprintw(my_win, height-11, width/2-43/2, "  / /\\ \\   | |     \\ \\/  \\/ /| |  | | . ` |");
    mvwprintw(my_win, height-10, width/2-43/2, " / ____ \\ _| |_     \\  /\\  / | |__| | |\\  |");
    mvwprintw(my_win, height-9, width/2-43/2, "/_/    \\_\\_____|     \\/  \\/   \\____/|_| \\_|");
}

void GameOver::print_player_won(){
    mvwprintw(my_win, height-14, width/2-49/2, "__     ______  _    _  __          ______  _   _ ");
    mvwprintw(my_win, height-13, width/2-49/2, "\\ \\   / / __ \\| |  | | \\ \\        / / __ \\| \\ | |");
    mvwprintw(my_win, height-12, width/2-49/2, " \\ \\_/ / |  | | |  | |  \\ \\  /\\  / / |  | |  \\| |");
    mvwprintw(my_win, height-11, width/2-49/2, "  \\   /| |  | | |  | |   \\ \\/  \\/ /| |  | | . ` |");
    mvwprintw(my_win, height-10, width/2-49/2, "   | | | |__| | |__| |    \\  /\\  / | |__| | |\\  |");
    mvwprintw(my_win, height-9, width/2-49/2, "   |_|  \\____/ \\____/      \\/  \\/   \\____/|_| \\_|");
}

void GameOver::print_tie(){
    mvwprintw(my_win, height-14, width/2-52/2, "__     ______  _    _   _______ _____ ______ _____  ");
    mvwprintw(my_win, height-13, width/2-52/2, "\\ \\   / / __ \\| |  | | |__   __|_   _|  ____|  __ \\ ");
    mvwprintw(my_win, height-12, width/2-52/2, " \\ \\_/ / |  | | |  | |    | |    | | | |__  | |  | |");
    mvwprintw(my_win, height-11, width/2-52/2, "  \\   /| |  | | |  | |    | |    | | |  __| | |  | |");
    mvwprintw(my_win, height-10, width/2-52/2, "   | | | |__| | |__| |    | |   _| |_| |____| |__| |");
    mvwprintw(my_win, height-9, width/2-52/2, "   |_|  \\____/ \\____/     |_|  |_____|______|_____/ ");
}