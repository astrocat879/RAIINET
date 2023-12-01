#ifndef __BOARD_H__
#define __BOARD_H__
#include <iostream>
#include <vector>
#include "Cell.h"
#include "Link.h"
#include "textdisplay.h"
// #include "graphicsdisplay.h"

class Board
{
    std::vector<std::vector<Cell>> theBoard; // The actual board
    int playerCnt;
    vector<Player *> players;
    const int boardSize = 8;                           // Size of the board
    TextDisplay *td;                        // The text display
    // GraphicsDisplay *gd;                    // The graphics display

public:
    Board();
    ~Board();

    void addPlayer(Player * p);
    // bool isWon() const;           // Call to determine if grid is in a winning state.
    // void init(int n); // Sets up an n x n grid.  Clears old grid, if necessary.
    void initPlayer(Player * p, string s);
    void initPlayer(Player * p);
    Player * getPlayer(int id);
    bool moveLink(Link * l, int oldX, int oldY, int newX, int newY);
    friend std::ostream &operator<<(std::ostream &out, const Board &g);
};

#endif
