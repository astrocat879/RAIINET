#include <iostream>
#include "textdisplay.h"
#include "Cell.h"
using namespace std;

TextDisplay::TextDisplay(int n): gridSize{n} {
  for (int i=0; i<gridSize; i++) {
    theDisplay.emplace_back(vector<char>());
    for (int j=0; j<gridSize; j++) {
      theDisplay[i].emplace_back('.');
    }
  }
}

void TextDisplay::notify(Cell &c) {
  int x = c.getX();
  int y = c.getY();
  Link * link = c.getLink();
  if (link == nullptr) {
    theDisplay[y][x] = '.';
  } else {
    theDisplay[y][x] = link->getId();
  }
}

ostream &operator<<(ostream &out, const TextDisplay &td) {
  out << "========" << '\n';
  for (int i=0; i<td.gridSize; i++) {
    for (int j=0; j<td.gridSize; j++) {
      out << td.theDisplay[i][j];
    }
    out << '\n';
  }
  out << "========" << '\n';
  return out;
}

