#include <iostream>
#include <string>
#include "graphicsdisplay.h"
#include "Cell.h"
#include "Player.h"
#include "Link.h"
using namespace std;

GraphicsDisplay::GraphicsDisplay(int n, Xwindow * w, int curPlayer): gridSize{n}, curPlayer{curPlayer}{
  theDisplay = w;
  cellPx = 500 / n;
  for (int i=0; i<gridSize*cellPx; i+=cellPx) {
    for (int j=0; j<gridSize*cellPx; j+=cellPx) {
        theDisplay->drawRectangle(i, j, cellPx, cellPx);
    }
  }
}

void GraphicsDisplay::notify(Cell &c) {
  int x = c.getX();
  int y = c.getY();
  if (curPlayer == 0) y = gridSize-1-y;
  else if (curPlayer == 1) x = gridSize-1-x;
  y *= cellPx;
  x *= cellPx;
  Link * link = c.getLink();
  cerr << "DEBUG: GraphicsDisplay.notify() x: " << x << ", y: " << y << endl;
  string s;
  if (link == nullptr) {
    if (c.getType() == '.') {
      theDisplay->drawRectangle(x, y, cellPx, cellPx);
    } else {
      theDisplay->drawPiece(x, y, c.getType());
    }
  } else {
    theDisplay->drawRectangle(x, y, cellPx, cellPx, 5, Xwindow::Blue);
    theDisplay->drawPiece(x, y, link->getId());
  }
  // theDisplay->drawString(x, y, s);
}

void GraphicsDisplay::notify(Player &p){
  int y = 50;
  int x = 550;
  
}

GraphicsDisplay::~GraphicsDisplay() {

}