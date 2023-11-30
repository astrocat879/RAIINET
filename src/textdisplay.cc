#include <iostream>
#include "textdisplay.h"
#include "cell.h"
using namespace std;

TextDisplay::TextDisplay(int n): gridSize{n} {
  for (int i=0; i<gridSize; i++) {
    theDisplay.emplace_back(vector<char>());
    for (int j=0; j<gridSize; j++) {
      theDisplay[i].emplace_back('_');
    }
  }
}

void TextDisplay::notify(Cell &c) {
  if (c.getState()) {
    theDisplay[c.getRow()][c.getCol()] = 'X';
  } else {
    theDisplay[c.getRow()][c.getCol()] = '_';
  }
}

TextDisplay::~TextDisplay() {

}

SubscriptionType TextDisplay::subType() {
  return SubscriptionType::All;
}

ostream &operator<<(ostream &out, const TextDisplay &td) {
  for (int i=0; i<td.gridSize; i++) {
    for (int j=0; j<td.gridSize; j++) {
      out << td.theDisplay[i][j];
    }
    out << '\n';
  }
  return out;
}
