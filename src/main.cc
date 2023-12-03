#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Board.h"
#include "Player.h"
#include "Point.h"

using namespace std;

int main(int argc, const char* argv[]){
    string cmd;
    // init board
    Board board{};
    cout << "DEBUG: Board made" << '\n';
    board.addPlayer(new Player{0});
    board.addPlayer(new Player{1});
    cout << "DEBUG: Added players" << '\n';
    cout << "DEBUG: Finished init" << '\n';
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
            string abilityList;
            iss >> abilityList;
            board.getPlayer(0)->initAbility(abilityList);
            ability1 = true;
        } else if (cmd == "-ability2") {
            string abilityList;
            iss >> abilityList;
            board.getPlayer(1)->initAbility(abilityList);
            ability2 = true;
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
    cout << "DEBUG: Processed Arguments" << '\n';
    // set up default initializations for ability and link (TO DO)
    if (!link1) {
        board.initPlayer(board.getPlayer(0));
    }
    if (!link2) {
        board.initPlayer(board.getPlayer(1));
    }
    if (!ability1) {
        board.getPlayer(0)->initAbility();
    }
    if (!ability2) {
        board.getPlayer(1)->initAbility();
    }

    board.init();

    cout << "DEBUG: Processed default arguemnts" << '\n';
    while (cin >> cmd) {
        Player* curPlayer = board.getPlayer(board.getCurPlayer());
        if (cmd == "move") {            // move a piece given the ID of the link and the direction
            char linkID;
            string dir;
            cin >> linkID >> dir;
            Link* curLink = curPlayer->getLinkById(linkID);
            Point oldPos = curLink->getPoint();
            curPlayer->moveLink(curLink, Point::translate(dir));
            board.moveLink(curLink, oldPos, curLink->getPoint());
            board.switchTurns();
        } 
        else if (cmd == "abilities") {  // display ability cards with an indication of whether its been used
            cout << "List of Abilities for Player " << (curPlayer->getId() + 1) << ": " << endl;
            for (auto a = curPlayer->getAbilityBeginIterator(); a != curPlayer->getAbilityEndIterator(); ++a) {
                (*a)->displayAbility();
            }
        }
        else if (cmd == "ability") {    // use ability with ID n
            int n;
            cin >> n;
            string abilityName = curPlayer->getAbility(n)->getName();
            if (curPlayer->getId() == 0){
                curPlayer->initAbilityParams(n, abilityName[0], board.getPlayer(1));
            } else {
                curPlayer->initAbilityParams(n, abilityName[0], board.getPlayer(0));
            }
            curPlayer->useAbility(n);
            cout << "Player " << (curPlayer->getId() + 1) << " used ability ";
            cout << abilityName << "!" << endl;
        }
        else if (cmd == "board") {      // display the board
            cout << board;
        }
        else if (cmd == "sequence") {   // execute sequence of cmds found in a file
            
        }
        else if (cmd == "quit") {       // exit game

        }
        board.isWon();
    }
}