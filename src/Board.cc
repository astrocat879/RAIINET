#include <iostream>
#include "Board.h"
using namespace std;

Grid::Grid(): gridSize{0}, won{false}, td{nullptr}, gd{nullptr} {
}

Grid::~Grid() {
  delete td;
  delete gd;
  clearGrid();
}

void Grid::clearGrid() { 
  for (int i=gridSize-1; i>=0; --i) {
    for (auto it = theGrid[i].begin(); it != theGrid[i].end(); ) {
      theGrid[i].erase(it);
    }
    theGrid.pop_back();
  }
}

bool Grid::isWon() const {
  for (int i=0; i<gridSize; i++) {
    for (int j=0; j<gridSize; j++) {
      if (theGrid[i][j].getState() == 1) {
        return false;
      }
    }
  }
  return true;
}

void Grid::init(int n, Xwindow & w) {
  clearGrid();
  gridSize = n;
  td = new TextDisplay(n);
  gd = new GraphicsDisplay(n, w);
  for (int i=0; i<gridSize; i++) {
    theGrid.emplace_back(vector<Cell>(n, Cell{}));
  }
  for (int i=0; i<gridSize; i++) {
    for (int j=0; j<gridSize; j++) {
      theGrid[i][j].setCoords(i, j);
      if (i > 0) {
        theGrid[i][j].attach(&theGrid[i - 1][j]);
      }
      if (j > 0) {
        theGrid[i][j].attach(&theGrid[i][j - 1]);
      }
      if (i < gridSize - 1) {
        theGrid[i][j].attach(&theGrid[i + 1][j]);
      }
      if (j < gridSize - 1) {
        theGrid[i][j].attach(&theGrid[i][j + 1]);
      }
      theGrid[i][j].attach(td);
      theGrid[i][j].attach(gd);
    }
  }
}

void Grid::turnOn(int r, int c) {
  theGrid[r][c].setOn();
}

void Grid::toggle(int r, int c) {
  theGrid[r][c].toggle();
  theGrid[r][c].notifySwitchObservers();
}

ostream &operator<<(ostream &out, const Grid &g) {
  out << *g.td;
  return out;
}
