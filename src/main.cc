#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Board.h"
#include "Player.h"

using namespace std;

int main(int argc, const char* argv[]){
    string cmd;
    // init board
    Board board{};
    board.addPlayer(new Player{1});
    board.addPlayer(new Player{2});
    string allArgs;
    for (int i=1;i<argc;i++){
        string arg = argv[i];
        allArgs += arg + " ";
    }
    istringstream iss{allArgs};
    while (iss >> cmd) {
        if (cmd == "-ability1") {
            
        } else if (cmd == "-ability2") {

        } else if (cmd == "-link1") {
            string fileName;
            iss >> fileName;
            ifstream file{fileName};
            string layout;
            getline(file, layout);
        } else if (cmd == "-link2") {

        } else if (cmd == "-graphics") {

        }
    }
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