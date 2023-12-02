#ifndef __BOARD_H__
#define __BOARD_H__
#include <iostream>
#include <vector>
#include "Cell.h"
#include "ServerPort.h"
#include "Firewall.h"
#include "Link.h"
#include "textdisplay.h"
// #include "graphicsdisplay.h"

class Board
{
    std::vector<std::vector<Cell>> theBoard;        // The actual board
    int playerCnt;                                  // The player count
    vector<Player *> players;                       // Array of players
    const int boardSize = 8;                        // Size of the board
    TextDisplay *td;                                // The text display
    // GraphicsDisplay *gd;                            // The graphics display

public:
    Board();
    ~Board();

    void addPlayer(Player * p);
    // bool isWon() const;           // Call to determine if grid is in a winning state.
    void init(); // Sets up board, serverports, cells, textdisplay
    void initPlayer(Player * p, string s);
    void initPlayer(Player * p);
    Player * getPlayer(int id);
    bool moveLink(Link * l, int oldX, int oldY, int newX, int newY);
    friend std::ostream &operator<<(std::ostream &out, const Board &g);
};

#endif
