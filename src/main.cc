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
    board.init();
    // process cmd arguments
    string allArgs;
    for (int i=1;i<argc;i++){
        string arg = argv[i];
        allArgs += arg + " ";
    }
    istringstream iss{allArgs};
    bool link1, link2, ability1, ability2;
    while (iss >> cmd) {
        if (cmd == "-ability1") {
            
        } else if (cmd == "-ability2") {

        } else if (cmd == "-link1") {
            string fileName;
            iss >> fileName;
            ifstream file{fileName};
            string layout;
            getline(file, layout);
            board.initPlayer(board.getPlayer(1), layout);
            link1 = true;
        } else if (cmd == "-link2") {
            string fileName;
            iss >> fileName;
            ifstream file{fileName};
            string layout;
            getline(file, layout);
            board.initPlayer(board.getPlayer(2), layout);
            link2 = true;
        } else if (cmd == "-graphics") {

        }
    }
    // set up default initializations for ability and link (TO DO)
    if (!link1) {
        board.initPlayer(board.getPlayer(1));
    }
    if (!link2) {
        board.initPlayer(board.getPlayer(2));
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
            cout << board.getPlayer(1);
            cout << board;
            cout << board.getPlayer(2);
        }
        else if (cmd == "sequence") {   // execute sequence of cmds found in a file

        }
        else if (cmd == "quit") {       // exit game

        }
    }
}