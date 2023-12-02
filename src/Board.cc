#include <iostream>
#include "Board.h"
using namespace std;

Board::Board(): playerCnt{2}, td{nullptr} {}

Board::~Board() {
  delete td;
  for (auto &p : players) {
    delete p;
  }
  for (int i=0; i<boardSize; i++) {
    for (int j=0; j<boardSize; j++) {
      delete theBoard[i][j];
    }
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

void Board::init() {
  td = new TextDisplay(boardSize);
  // adding cells
  for (int i=0; i<boardSize; i++) {
    theBoard.push_back(vector<Cell *>(boardSize));
    for (int j=0; j<boardSize; j++) {
      theBoard[i][j] = new Cell(i, j);
      theBoard[i][j]->addObserver(td);
    }
  }

  // add server ports
  delete theBoard[0][3];
  theBoard[0][3] = new ServerPort(0, 3, players[0]);
  theBoard[0][3]->addObserver(td);
  theBoard[0][3]->notifyObservers();

  delete theBoard[0][4];
  theBoard[0][4] = new ServerPort(0, 4, players[0]);
  theBoard[0][4]->addObserver(td);
  theBoard[0][4]->notifyObservers();

  delete theBoard[7][3];
  theBoard[7][3] = new ServerPort(7, 3, players[1]);
  theBoard[7][3]->addObserver(td);
  theBoard[7][3]->notifyObservers();

  delete theBoard[7][4];
  theBoard[7][4] = new ServerPort(7, 4, players[1]);
  cout << "DEBUG: VERY IMPORTANT " << theBoard[7][4]->getType() << '\n';
  theBoard[7][4]->addObserver(td);
  theBoard[7][4]->notifyObservers();

  // put links on the board
  for (Player* p : players) {
    for (auto l = p->getLinkBeginIterator(); l != p->getLinkEndIterator(); ++l) {
      Point location = (*l)->getPoint();
      theBoard[location.y][location.x]->attachLink((*l));
    }
  }
}

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

int Board::getCurPlayer(){
  return curPlayer;
}

void Board::moveLink(Link *l, Point oldP, Point newP) { // needs to use Points (TO DO)
  /*
  checks if in bounds and if new cell doesn't contain ally link
  if it goes past other side of board, remove from cell and download (see below for how to download)
  Board.moveLink() calls:
    Cell.detachLink() for the old cell
    Cell.attachLink(Link* l) for the new cell

  NOTE: that when downloading a link, you need to remove it from the other player with Player.removeLink(Link* l)
  */
    theBoard[oldP.y][oldP.x]->detachLink();
    theBoard[newP.y][newP.x]->attachLink(l);
}

ostream &operator<<(ostream &out, const Board &g) {
  out << *g.td;
  return out;
}
