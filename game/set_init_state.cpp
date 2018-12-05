#include <ctime>
#include <string>
#include <curses.h>
#include <iostream>
#include <unistd.h>
#include <vector>

using namespace std;

/**
 * Gets the users input from the specified spot on the screen, as well as updating the screen as the user types
 */
string get_input(int y, int x, WINDOW* win){
    string input = "";
    char c;
    wmove(win, y, x);
    do {
        c = getchar();
        if(c == 127 && input.length() > 0){
            input.pop_back();
            x -= 1;
            wmove(win, y, x);
        }
        else if(c != 13 && c != 127){
            input += c;
            x += 1;
        }
        wmove(win, y, x);
        mvwprintw(win, 14, 7, input.c_str());
        wrefresh(win);
    } while(c != 13 && c != 10);
    return input;
}

bool checkValidStrLength(string input, int n, WINDOW* win) {
    if ((int)input.length() != n*2-1) { //there should be exactly n*2 - 1 input characters
        mvwprintw(win, 16, 7, string("you didn\'t enter " + to_string(n) + " numbers, please try again").c_str());
        sleep(1);
        return false;
    }
    return true;
}

/**
 * Checks if the vector size is what it should be, and prints error messages if they aren't
 * @param {vector<int>} stack vector of ints tha represents the stack
 * @param {int} n number of pancakes on the stack
 * @param {WINDOW*} win ncurses window object
 * @returns {bool} false if not valid length, true if it is
 */
bool checkValidVectorLength(vector<int> stack, int n, WINDOW* win) {
    if ((int)stack.size() != n) {
        mvwprintw(win, 16, 7, string("you did not enter " + to_string(n) + " numbers, try again").c_str());
        sleep(1);
        return false;
    }
    return true;
}

/**
 * Checks to see if the given vector of ints contains int_to_add already, and prints error messages
 * @param {vector<int>} stack vector of ints that reporesnts the stack
 * @param {int} int_to_add the int to add to the vector
 * @param {WINDOW*} win the ncurses window to print to
 * @returns {bool} true if it contains a duplicate, false if no error/conflict
 */
bool checkDuplicateInput(vector<int> stack, int int_to_add, WINDOW* win) {
    bool exists = false;
    for (unsigned long int i = 0; i < stack.size(); i++)
        if (stack.at(i) == int_to_add)
            exists = true;
    if (exists) {
        mvwprintw(win, 16, 7, string("you entered duplicate numbers, try again").c_str());
        sleep(1);
    }
    return exists;
}

/**
 * Splits the string given into a vector<int>, and also checks for duplicate/incorrect numerical input
 */
vector<int> splitNumbers(string in, int n, WINDOW* win) {

    mvwprintw(win, 16, 2, string("                                                                             ").c_str());

    if (!checkValidStrLength(in, n, win)) return vector<int>(0);

    vector<int> stack;
    int index = 0;
    char c = 0;
    //char c = in.at(index++);
    try {
        while (c != 10 && c != 13) { //while the newline character is not the next character
            c = in.at(index++);
            if ((int)c - 48 < 0 || (int)c - 48 > 9)
                continue;
            int int_to_add = (int)c - 48;
            bool exists = checkDuplicateInput(stack, int_to_add, win);
            if (exists) return vector<int>(0); 
            // for (unsigned long int i = 0; i < stack.size(); i++)
            //     if (stack.at(i) == int_to_add)
            //         exists = true;
            // if (exists) {
            //     mvwprintw(win, 16, 7, string("you entered duplicate numbers, try again").c_str());
            //     sleep(1);
            //     return vector<int>(0);
            // }
            stack.push_back(int_to_add);
            if (index == (int)in.length())
                break;
        }
    } catch (int e) { cerr << e << endl;}

    wmove(win, 16,7);
    wrefresh(win);

    if (!checkValidVectorLength(stack, n, win)) return vector<int>(0);

    mvwprintw(win, 16, 2, string("                                                                             ").c_str());
    return stack;
}

/**
 * Gets the initial state from the user
 * This function will receive the input on the screen, and deal with various inputs
 */
vector<int> get_init_state(int n, WINDOW* win) {
    vector<int> stack;

    wmove(win, 14, 7);
    string input = get_input(14, 7, win);
    
    if (input.length() == 0 || input.at(0) == 'r') { //random order
        mvwprintw(win, 16, 2, string("                                                                             ").c_str());
        vector<int> vals;
        for (int i = 0; i < n; i++)
            vals.push_back(i+1);

        srand(time(NULL));

        while (vals.size() != 0) {
            int rand_ind = rand() % vals.size();
            stack.push_back(vals.at(rand_ind));
            vals.erase(vals.begin() + rand_ind);
        }

    } else
        stack = splitNumbers(input, n, win);

    return stack;
}

/**
 * Displays the instructions for how to choose the state of the game
 */
void display_init_screen(int n, WINDOW* win) {
    
    mvwprintw(win, 10, 2, string("To specify the initial game state, enter numbers 1 to " + to_string(n) + " in the desired order").c_str());
    mvwprintw(win, 11, 28, string("i.e. 1,3,5,7,9,2,4,6,8").c_str());
    mvwprintw(win, 12, 15, string("if a random order is desired, enter  \'r\' or nothing").c_str());
    mvwprintw(win, 14, 5, string(">                                                           ").c_str());
    wmove(win, 14, 7);
    wrefresh(win);
}

/**
 * Displays the results of the user input in the bottom half of the screen
 **/
void display_init_screen(vector<int> stack, WINDOW* win, int n) {
    for (int i = 0; i < n; i++)
        mvwprintw(win, 15+i, 40, to_string(stack.at(i)).c_str());
    wrefresh(win);
}

/**
 * Main function that calls all other functions in this file
 */
vector<int> init_main(WINDOW* win, int n) {
    refresh();

    box(win, 0, 0);  
    wrefresh(win);

    //displays the instructions for how to order the pancakes
    display_init_screen(n, win);
    
    //retrieves a vector<int> from the user input, or lack thereof
    vector<int> stack = get_init_state(n, win);

    //if incorrect input is given, recursively call this function until it isnt
    //this is a recursive function, so could eventually overflow program stack, but just dont be stupid
    if (stack.size() == 0)
        return init_main(win, n);
    
    //displays the parsed vector on the screen
    display_init_screen(stack, win, n);

    sleep(3);
    return stack;
}
