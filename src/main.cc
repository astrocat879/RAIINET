#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <istream>
#include "Board.h"
#include "Player.h"
#include "Point.h"
#include "window.h"

using namespace std;

int main(int argc, const char* argv[]){
    string cmd;
    // init board
    Board board{};
    // Xwindow w{};
    // TO DO: pass in display window into player and board
    cout << "DEBUG: Board made" << '\n';
    board.addPlayer(new Player{0, &board});
    board.addPlayer(new Player{1, &board});
    cout << "DEBUG: Added players" << '\n';
    cout << "DEBUG: Finished init" << '\n';
    // process cmd arguments
    string allArgs;
    for (int i=1;i<argc;i++){
        string arg = argv[i];
        allArgs += arg + " ";
    }
    istringstream iss{allArgs};
    bool link1 = false, link2 = false, ability1 = false, ability2 = false, graphics = false;
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
            graphics = true;
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

    board.init(graphics);

    // cout << "DEBUG: Processed default arguemnts" << '\n';

ifstream fs;
istream* inputStream = &cin;  // Initialize to cin
string fileName;
while (true) {
    (*inputStream) >> cmd;
    if (inputStream->fail() || inputStream->eof()) {
        if (inputStream == &cin) { // if no more cin, break
            break;
        }
        delete inputStream;  
        inputStream = &cin;  
        continue;
    }
        cerr << "DEBUG: "<< cmd << '\n';
        try {
            Player* curPlayer = board.getPlayer(board.getCurPlayer());
            if (cmd == "move") { // move a piece given the ID of the link and the direction
                char linkID;
                string dir;
                (*inputStream) >> linkID >> dir;
                Link* curLink = curPlayer->getLinkById(linkID);
                Point oldPos = curLink->getPoint();
                if (curLink->getIsFrozen()) {
                    throw invalid_argument{"Error: Link is currently immobilized. Please choose another link to move."};
                } else {
                    curPlayer->makeMove(curLink, Point::translate(dir));
                    for (auto l = curPlayer->getLinkBeginIterator(); l != curPlayer->getLinkEndIterator(); ++l) {
                        if ((*l)->getIsFrozen()) { // move has been made, if link is immobilized then it should no longer be immobilized
                            (*l)->flipFrozen();
                        }
                    }
                    board.switchTurns();
                }
                cout << board;
            } 
            else if (cmd == "abilities") {  // display ability cards with an indication of whether its been used
                cout << "List of Abilities for Player " << (curPlayer->getId() + 1) << ": " << endl;
                for (auto a = curPlayer->getAbilityBeginIterator(); a != curPlayer->getAbilityEndIterator(); ++a) {
                    (*a)->displayAbility();
                }
            }
            else if (cmd == "ability") {    // use ability with ID n
                if (board.getUsedAbility()) {
                    throw invalid_argument("Error: An ability has already been used this turn.");
                }
                int n;
                (*inputStream) >> n;
                string abilityName = curPlayer->getAbility(n)->getName();
                if (curPlayer->getId() == 0){
                    curPlayer->initAbilityParams(n, abilityName[0], board.getPlayer(1));
                } else {
                    curPlayer->initAbilityParams(n, abilityName[0], board.getPlayer(0));
                }
                curPlayer->useAbility(n);
                cout << "Player " << (curPlayer->getId() + 1) << " used ability ";
                cout << abilityName << "!" << endl;
                board.flipUsedAbility();
                if (curPlayer->getAbility(n)->getId() != 1) {
                    cout << board;
                }
            }
            else if (cmd == "board") {      // display the board
                cout << board;
            }
            else if (cmd == "sequence") {   // execute sequence of cmds found in a file
                cerr << "DEBUG: seq" << endl;
                fs.close();
                fs.clear();
                (*inputStream) >> fileName;
                fs.open(fileName);
                if (!fs.is_open()) {
                    throw logic_error("Error: Unable to open file");
                }
                inputStream = new ifstream(fileName); 
            }
            else if (cmd == "quit") {       // exit game
                break;
            }
        } catch (exception &e){
            cerr << e.what() << '\n';
        }
        int winner = board.isWon();
        if (winner != -1) {
            cout << "Player " << to_string(winner+1) << " wins!" << endl;
            break;
        }
        // free memory
    }
    if (inputStream != &cin) {
        delete inputStream;
    }
    // delete board;
}