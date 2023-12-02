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

void Board::initPlayer(Player * p, string s) {
  p->init(s);
}

void Board::initPlayer(Player * p) {
  p->init();
}

Player * Board::getPlayer(int id) {     // erm.. could be better (TO DO)
  return players[id];
}

void Board::moveLink(Link *l, int oldX, int oldY, int newX, int newY) {
  /*
  checks if in bounds and if new cell doesn't contain ally link
  if it goes past other side of board, remove from cell and download (see below for how to download)
  Board.moveLink() calls:
    Cell.detachLink() for the old cell
    Cell.attachLink(Link* l) for the new cell

  NOTE: that when downloading a link, you need to remove it from the other player with Player.removeLink(Link* l)
  */
  if (newX<0 || newX>7 || newY<0) { //if out of bounds, throw an exception
    throw std::invalid_argument("End position (" + std::to_string(newX) + "," + std::to_string(newY) + ") is out of bounds");
  }
  else if (newY>7) { //if it reached the end of the board, download to its player
    l->getPlayer->downloadLink(l);
    return true;
  }
  else {
    theBoard[oldX][oldY].detachLink(l);
    theBoard[newX][newY].attachLink(l);
  }
}

ostream &operator<<(ostream &out, const Board &g) {
  out << *g.td;
  return out;
}
