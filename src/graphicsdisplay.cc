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
        theDisplay->drawRectangle(j, i, cellPx, cellPx);
    }
  }
  for (int i=0; i<4; i++) {
    links.emplace_back(vector<string>());
    isLinkRevealed.emplace_back(vector<bool>());
    for (int j=0; j<8; j++) {
      links[i].emplace_back("");
      isLinkRevealed[i].emplace_back(false);
    }
    numLinksDownloaded.emplace_back(0);
    numVirusesDownloaded.emplace_back(0);
    numOfAbilities.emplace_back(5);
  }
  // theDisplay->drawText(500, 30, "Player 2");
  if (curPlayer==0) {
    curPlayerPos = 250;
    opponentPos = 0;
    
  } else {
    curPlayerPos = 0;
    opponentPos = 250;
  }
  theDisplay->drawText(500, opponentPos + 30, "PLAYER 2:");
  theDisplay->drawText(500, curPlayerPos + 30, "PLAYER 1:");
  theDisplay->drawText(500, 55, "DOWNLOADED:");
  theDisplay->drawText(500, 305, "DOWNLOADED:");
  theDisplay->drawText(500, 80, "ABILITIES:");
  theDisplay->drawText(500, 330, "ABILITIES:");
  theDisplay->drawText(500, 105, "LINKS:");
  theDisplay->drawText(500, 355, "LINKS:");
}

void GraphicsDisplay::notify(Cell &c) {
  int x = c.getX();
  int y = c.getY();
  cerr << "DEBUG: GraphicsDisplay.notify() x: " << x << ", y: " << y << endl;
  if (curPlayer == 0) y = gridSize-1-y;
  else if (curPlayer == 1) x = gridSize-1-x;
  y *= cellPx;
  x *= cellPx;
  
  Link * link = c.getLink();
  string s;
  cerr << "DEBUG: after calculating x: " << x << ", y: " << y << endl;
  if (link == nullptr || link->getIsDead()) {
    if (c.getType() == '.') {
      theDisplay->drawRectangle(x, y, cellPx, cellPx);
    } else {
      // theDisplay->drawPiece(x, y, c.getType());
      theDisplay->drawChar(x+6, y+6, c.getType(), 50, Xwindow::Black);
    }
  } else {
    if (link->getPlayer()->getId() == curPlayer) {
      // 
      if (link->getType() == 'V'){
        theDisplay->drawRectangle(x, y, cellPx, cellPx, 5, Xwindow::Red);
      } else {
        theDisplay->drawRectangle(x, y, cellPx, cellPx, 5, Xwindow::Green);
      }
      // theDisplay->drawPiece(x, y, link->getId());
      theDisplay->drawChar(x+5, y+5, link->getId(), 50);
    } else {
      if (link->getReveal()) {
        if (link->getType() == 'V'){
          theDisplay->drawRectangle(x, y, cellPx, cellPx, 5, Xwindow::Red);
        } else {
          theDisplay->drawRectangle(x, y, cellPx, cellPx, 5, Xwindow::Green);
        }
      } else {
        theDisplay->drawRectangle(x, y, cellPx, cellPx, 5, Xwindow::Blue);
      }
      
      // theDisplay->drawPiece(x, y, link->getId());
      theDisplay->drawChar(x+5, y+5, link->getId(), 50);
    }
    
  }
  // theDisplay->drawString(x, y, s);
}

void GraphicsDisplay::notify(Player &p){
  cerr << "DEBUG: graphicsDisplay.notify's player: " << p.getId() << endl;
  
  // if (numLinksDownloaded[p.getId()] != p.getDownloadCount()){
  // }
  numLinksDownloaded[p.getId()] = p.getDownloadCount();
    
  numVirusesDownloaded[p.getId()] = p.getVirusCount();
  numOfAbilities[p.getId()] = p.getAbilityCount();
  int index = 0;
  for (auto l = p.getLinkBeginIterator(); l != p.getLinkEndIterator(); ++l) {
    cerr << "DEBUG: player notify cur link: " << *(*l) << endl;
    stringstream ss;
    ss << *(*l);
    links[p.getId()][index] = ss.str();
    if ((*(*l)).getReveal()) cerr << "DEBUG: player notify cur link is revealed: true";
    else cerr << "DEBUG: player notify cur link is revealed: false";
    isLinkRevealed[p.getId()][index] = (*(*l)).getReveal();
    ++index;
  }
  string tmp = to_string(numLinksDownloaded[p.getId()]) + "D  " + to_string(numVirusesDownloaded[p.getId()]) + "V";
  // string tmp = "0";
  if (curPlayer == p.getId()){
    theDisplay->drawText(730, curPlayerPos + 55, tmp);
  } else {
    theDisplay->drawText(730, opponentPos + 55, tmp);
  }
  
  tmp = to_string(numOfAbilities[p.getId()]);
  if (curPlayer == p.getId()){
    theDisplay->drawText(730, curPlayerPos + 80, tmp);
  } else {
    theDisplay->drawText(730, opponentPos + 80, tmp);
  }
  // out << "Downloaded: " << to_string(numLinksDownloaded[p.getId()]) << "D, " << to_string(numVirusesDownloaded[p.getId()]) << "V" << "\n";
  // out << "Abilities: " << numOfAbilities[p.getId()] << "\n";
  for (int i=0; i<4; i++) {
    if (p.getId() == curPlayer || isLinkRevealed[p.getId()][i]) 
      theDisplay->drawText(505 + i * 80, curPlayerPos+130, links[p.getId()][i], 14);
    else {
      string output = links[p.getId()][i].substr(0, 2)+" ? ";
      theDisplay->drawText(505 + i * 80, opponentPos+130, output, 14);
    }
  }
  for (int i=4; i<8; i++) {
    if (p.getId() == curPlayer || isLinkRevealed[p.getId()][i]) 
      theDisplay->drawText(505 + (i-4) * 80, curPlayerPos+150, links[p.getId()][i], 14);
    else {
      string output = links[p.getId()][i].substr(0, 2)+" ? ";
      theDisplay->drawText(505 + (i-4) * 80, opponentPos+150, output, 14);
    }
  }
}

GraphicsDisplay::~GraphicsDisplay() {

}