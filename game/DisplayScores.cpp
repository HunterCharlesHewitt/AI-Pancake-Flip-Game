#include "DisplayScores.h"

DisplayScores::DisplayScores(WINDOW* win){
    refresh();
    box(win, 0, 0);
    my_win = win;
    wrefresh(my_win);
    height = 40;
    width = 80;
    scores_filename = "scores.txt";
    player_score = 0;
}

DisplayScores::~DisplayScores(){
    
}

void DisplayScores::run_part4() { //runs entire part 4
    wrefresh(my_win);
    //prints to window
    populate_top5scores();
    display_top_5();
    ask_initials();
    display_player();
    wait_for_input();
}

void DisplayScores::ask_initials(){ //asks for user to enter initials
    mvwprintw(my_win, height-10, width/2-36/2, "Enter your initials (2-3 characters)");
    wmove(my_win, height-7, width/2-2);
    wrefresh(my_win);
    initials = get_input(height-7, width/2-2);
    //keeps asking until valid initials is entered
    while(initials.length() > 3 || initials.length() < 2) {
        mvwprintw(my_win, height-9, width/2-26/2, "Invalid initials, try again");
        wmove(my_win, height-7, width/2-2);
        wrefresh(my_win);
        initials = get_input(height-7, width/2-2);
    }
    wmove(my_win, height-9, width/2-36/2);
    mvwprintw(my_win, height-9, width/2-36/2, "                                      ");
    wmove(my_win, height-10, width/2-36/2);
    mvwprintw(my_win, height-10, width/2-36/2, "                                      ");
}

void DisplayScores::print_highscores_title(){
    mvwprintw(my_win, 5, width/2-58/2, " __    ___ ,___ __       __,   ,___ ___  _ __  ______  __,");
    mvwprintw(my_win, 6, width/2-58/2, "( /  /( / /   /( /  /   (     /   //  ()( /  )(  /    (   ");
    mvwprintw(my_win, 7, width/2-58/2, " /--/  / /  __  /--/     `.  /    /   /  /--<   /--    `. ");
    mvwprintw(my_win, 8, width/2-58/2, "/  /__/_(___/  /  /_   (___)(___/(___/  /   \\_(/____/(___)");
}

void DisplayScores::display_top_5(){ //displays top scores
    print_highscores_title();
    mvwprintw(my_win, height/3-1, width/2-9, "*-----------------*");
    int j=0;
    for(unsigned long int i=0; i<top5scores.size(); ++i){
        string place = to_string(i+1) + ". |";
        mvwprintw(my_win, i*2+height/3, width/2-12, place.c_str());
        mvwprintw(my_win, i*2+height/3, width/2+9, "|");
        mvwprintw(my_win, i*2+height/3, width/2-6, top5scores.at(i).at(0).c_str());
        mvwprintw(my_win, i*2+height/3, width/2+4, top5scores.at(i).at(1).c_str());
        mvwprintw(my_win, i*2+1+height/3, width/2-9, "*-----------------*");
        j = i;
    }
    for(; j<5; ++j){ //prints empty scores
        string place = to_string(j+1) + ". |";
        mvwprintw(my_win, j*2+height/3, width/2-12, place.c_str());
        mvwprintw(my_win, j*2+height/3, width/2+9, "|");
        mvwprintw(my_win, j*2+1+height/3, width/2-9, "*-----------------*");
    }
    wrefresh(my_win);
}

void DisplayScores::display_player(){ //displays user's initials and score
    mvwprintw(my_win, 10+height/3, width/2-6, initials.c_str());
    mvwprintw(my_win, 10+height/3, width/2+4, to_string(player_score).c_str());
    wrefresh(my_win);
}

void DisplayScores::populate_top5scores(){ //reads from score file to get names and scores
    //opens file
    ifstream ifs{scores_filename};
    if(!ifs) {
        cerr << "can't open file\n";
        exit(0);
    }
    //reads line by line from file and displays it
    string line;
    while(getline(ifs, line)) {
        top5scores.push_back(parse_string(line));
    }
    ifs.close();
}

string DisplayScores::get_initials(){
    return initials;
}

string DisplayScores::get_input(int y, int x){
    string input = "";
    char c;
    int x1 = x;
    do
    {
        c = getchar();
        if(((c>=65 && c<=90) || (c>=97 && c<=122)) && input.length()<3){
            c = toupper(c); //only allows alpha and up to 3 chars
            input += c;
            x += 1;
        }
        else if((c==127 || c==8) && input.length()>0){ //backspace
            input.pop_back();
            x -= 1;
            wmove(my_win, y, x);
            //wdelch(my_win);
            mvwprintw(my_win, y, x, " ");
        }
        wmove(my_win, y, x);
        mvwprintw(my_win, y, x1, input.c_str());
        wrefresh(my_win);
    } while(c != 13); //exits if enter is pressed
    mvwprintw(my_win, y, x1, "                            ");
    return input;
}

void DisplayScores::wait_for_input(){
    do{
        wmove(my_win, height/2, width/2-23/2);
        mvwprintw(my_win, height-10, width/2-23/2, "Press ENTER to continue");
        wrefresh(my_win);
    }while(getchar()!=13);
}

vector<string> DisplayScores::parse_string(string line){ //helper function to delimit whitespace
    vector<string> vs;
    string s = "";
    while(line.length() > 0){
        if(line.at(0) != ' ' && line.at(0) != '\t' && line.length() > 1) {
            s += line.at(0);
            line.erase(0,1);
        }
        else if(line.length() == 1){ //case where there is only 1 char left
            s += line.at(0);
            vs.push_back(s);
            line.erase(0,1);
            s = "";
        }
        else { //case where there is whitespace
            vs.push_back(s);
            line.erase(0,1);
            s = "";
        }
    }
    return vs;
}
