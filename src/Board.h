#ifndef __BOARD_H__
#define __BOARD_H__
#include <iostream>
#include <vector>
#include "Cell.h"
#include "Link.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"

class Board
{
    std::vector<std::vector<Cell>> theBoard; // The actual board
    int gridSize;                           // Size of the board
    bool won;                               // Grid in winning state
    TextDisplay *td;                        // The text display
    // GraphicsDisplay *gd;                    // The graphics display

    void clearBoard(); // Frees the grid (not sure if needed)

public:
    Board();
    ~Board();

    bool isWon() const;           // Call to determine if grid is in a winning state.
    void init(int n, Xwindow &w); // Sets up an n x n grid.  Clears old grid, if necessary.
    bool moveLink(Link * l, int oldX, int oldY, int newX, int newY);
    friend std::ostream &operator<<(std::ostream &out, const Board &g);
};

#endif
