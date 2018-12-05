#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <curses.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
using namespace std;

//flip_location refers to how many pancakes should be flipped

vector<int> flip(vector<int> stack, int flip_location) {
    vector<int> flipped_stack;
    for(int i=flip_location-1; i>=0; --i){
        flipped_stack.push_back(stack.at(i));
    }
    for(unsigned long int i=flip_location; i<((unsigned long int)(stack.size())); ++i){
        flipped_stack.push_back(stack.at(i));
    }
    return flipped_stack;
}

/*
int main(){
    vector<int> stack = {1,2,3,4,5,6,7,8,9};
    int flip_location = 1;;
    //print stack
    cout << "Original stack: ";
    for(int i=0; i<stack.size(); ++i){
        cout << stack.at(i) << " ";
    }
    do{
        cout << "\nEnter how many pancakes to flip or 0 to exit: ";
        cin >> flip_location;
        stack = flip(stack, flip_location);
        //print flipped pancakes
        cout << "Flipped stack: ";
        for(int i=0; i<stack.size(); ++i){
            cout << stack.at(i) << " ";
        }
    } while(flip_location!=0);
    cout << endl;
    return 0;
}
*/
