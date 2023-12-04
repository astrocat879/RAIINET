#ifndef __BOARD_H__
#define __BOARD_H__
#include <iostream>
#include <vector>
#include "Cell.h"
#include "ServerPort.h"
#include "Firewall.h"
#include "textdisplay.h"
// #include "graphicsdisplay.h"
#include "Player.h"

class Link;
class Download;
class FirewallAbility;

class Board
{
    std::vector<std::vector<Cell *>> theBoard;        // The actual board
    int playerCnt;                                  // The player count
    int curPlayer = 0;
    vector<Player *> players;                       // Array of players
    vector<bool> playerOut;                         // Whether each player has won or lost
    int playersOutCnt;
    const int boardSize = 8;                        // Size of the board
    TextDisplay *td;                                // The text display
    // GraphicsDisplay *gd;                            // The graphics display

public:
    friend class Download;
    friend class FirewallAbility;
    Board();
    ~Board();

    void addPlayer(Player * p);
    int isWon();           // Call to determine if board is in a winning state.
    void init(); // Sets up board, serverports, cells, textdisplay
    void initPlayer(Player * p, string s);
    void initPlayer(Player * p);
    Cell * getCell(Point p);
    int getCurPlayer();
    void switchTurns();
    Player * getPlayer(int id);
    // void moveLink(Link * l, Point oldP, Point newP);
    friend std::ostream &operator<<(std::ostream &out, const Board &g);
};

#endif
