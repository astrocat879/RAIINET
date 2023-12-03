#include <iostream>
#include "textdisplay.h"
#include "Cell.h"
using namespace std;

TextDisplay::TextDisplay(int n): gridSize{n}, curPlayer{0} {
  for (int i=0; i<gridSize; i++) {
    theDisplay.emplace_back(vector<char>());
    for (int j=0; j<gridSize; j++) {
      theDisplay[i].emplace_back('.');
    }
  }
}

TextDisplay::~TextDisplay() {}

void TextDisplay::changePlayer(int nextPlayer) {
  curPlayer = nextPlayer;
}

void TextDisplay::notify(Cell &c) {
  int x = c.getX();
  int y = c.getY();
  Link * link = c.getLink();
  cerr << "DEBUG: TextDisplay.notify() x: " << x << ", y: " << y << endl;
  if (link == nullptr) {
    cerr << "DEBUG: type of cell: " << c.getType() << endl;
    theDisplay[y][x] = c.getType();
  } else {
    cerr << "DEBUG: " << *link << endl;
    theDisplay[y][x] = link->getId();
  }
}

ostream &operator<<(ostream &out, const TextDisplay &td) {
  out << "========" << '\n';
  for (int i=0; i<td.gridSize; i++) {
    for (int j=0; j<td.gridSize; j++) {
      int displayY = i; 
      int displayX = j;
      if (td.curPlayer == 0) displayY = td.gridSize-1 - i; 
      else if (td.curPlayer == 1) displayX = td.gridSize-1 - j;
      out << td.theDisplay[displayY][displayX];
    }
    out << '\n';
  }
  out << "========" << '\n';
  return out;
}

