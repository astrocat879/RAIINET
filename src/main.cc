#include <iostream>
#include <string>

using namespace std;

int main(int argc, const char* argv[]){
    string cmd;
    // init board
    Board * board = new Board(...);
    while (cin >> cmd) {
        if (cmd == "move") {            // move a piece given the ID of the link and the direction
            string link, dir;
            cin >> link >> dir;

        } 
        else if (cmd == "abilities") {  // display ability cards with an indication of whether its been used

        }
        else if (cmd == "ability") {    // use ability with ID n
            int n;
            cin >> n;
        }
        else if (cmd == "board") {      // display the board

        }
        else if (cmd == "sequence") {   // execute sequence of cmds found in a file

        }
        else if (cmd == "quit") {       // exit game

        }
    }
}