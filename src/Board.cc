#include <iostream>
#include "Board.h"
using namespace std;

Board::Board(): playerCnt{2}, td{nullptr}{
  for (int i=0;i<boardSize;i++) {
    theBoard.push_back(vector<Cell>(boardSize));
  }
  
}

Board::~Board() {
  delete td;
  for (auto &p : players) {
    delete p;
  }
}

// bool Board::isWon() const {
//   for (int i=0; i<BoardSize; i++) {
//     for (int j=0; j<BoardSize; j++) {
//       if (theBoard[i][j].getState() == 1) {
//         return false;
//       }
//     }
//   }
//   return true;
// }

// void Board::init() {
  
// }

void Board::addPlayer(Player* p) {
  players.push_back(p);
}

bool Board::moveLink(Link * l, int oldX, int oldY, int newX, int newY) {
  
}

ostream &operator<<(ostream &out, const Board &g) {
  out << *g.td;
  return out;
}
