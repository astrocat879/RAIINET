#include <iostream>

using namespace std;

int main(int argc, const char* argv[]){
    string command;
    while (cin >> command) {
        if (command == "move") {            // move a piece given the ID of the link and the direction
            string link, dir;
            cin >> link >> dir;

        } 
        else if (command == "abilities") {  // display ability cards with an indication of whether its been used

        }
        else if (command == "ability") {    // use ability with ID n
            int n;
            cin >> n;
        }
        else if (command == "board") {      // display the board

        }
        else if (command == "sequence") {   // execute sequence of commands found in a file

        }
        else if (command == "quit") {       // exit game
            
        }
    }
}