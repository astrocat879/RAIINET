#include <iostream>
#include <string>
#include "graphicsdisplay.h"
#include "Cell.h"
#include "Player.h"
#include "Link.h"
using namespace std;

GraphicsDisplay::GraphicsDisplay(int n, Xwindow * w, int curPlayer): gridSize{n}, curPlayer{curPlayer}{
  theDisplay = w;
  for (int i=0; i<gridSize; i++) {
    cellIDs.emplace_back(vector<char>());
    cellLinkTypes.emplace_back(vector<char>());
    cellLinkIsRevealed.emplace_back(vector<bool>());
    for (int j=0; j<gridSize; j++) {
      cellIDs[i].emplace_back('.');
      cellLinkTypes[i].emplace_back('.');
      cellLinkIsRevealed[i].emplace_back(false);
    }
  }

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
    numLinksDownloaded.emplace_back(-1);
    numVirusesDownloaded.emplace_back(-1);
    numOfAbilities.emplace_back(-1);
  }

  printPlayerHeaders();
  theDisplay->drawText(500, 55, "DOWNLOADED:");
  theDisplay->drawText(500, 305, "DOWNLOADED:");
  theDisplay->drawText(500, 80, "ABILITIES:");
  theDisplay->drawText(500, 330, "ABILITIES:");
  theDisplay->drawText(500, 105, "LINKS:");
  theDisplay->drawText(500, 355, "LINKS:");
}

void GraphicsDisplay::printPlayerHeaders() {
  if (curPlayer==0) {
    player1Pos = 250;
    player2Pos = 0;
    
  } else {
    player1Pos = 0;
    player2Pos = 250;
  }
  theDisplay->drawText(500, player2Pos + 30, "PLAYER 2:");
  theDisplay->drawText(500, player1Pos + 30, "PLAYER 1:");
}

void GraphicsDisplay::changePlayer(int nextPlayer) {
  curPlayer = nextPlayer;
  printPlayerHeaders();

  // checking if cells need to change
  for (int i=0; i<gridSize; i++) {
    for (int j=0; j<gridSize; j++) {
      if (cellIDs[i][j] == '.' || cellIDs[i][j] == 'S' || cellIDs[i][j] == 'M' || cellIDs[i][j] == 'W') {
        displayCellonBoard(cellIDs[i][j], i, j);
      } else {
        // whose player the link belongs to
        int curLinksPlayer = 1;
        if (cellIDs[i][j] < 'a') curLinksPlayer = 2;
        displayLinkOnBoard(curLinksPlayer, cellIDs[i][j], cellLinkTypes[i][j], cellLinkIsRevealed[i][j], i, j);
      }
    }
  }

  if (numLinksDownloaded[0] != numLinksDownloaded[1]) {
    printDataDownloaded(0);
    printDataDownloaded(1);
  }
  if (numVirusesDownloaded[0] != numVirusesDownloaded[1]) {
    printVirusDownloaded(0);
    printVirusDownloaded(1);
  }
  if (numOfAbilities[0] != numOfAbilities[1]) {
    printNumOfAbilities(0);
    printNumOfAbilities(1);
  }

  for (int i=0; i<8; ++i) {
    printLinkInPlayerList(0, i);
    printLinkInPlayerList(1, i);
  }
}

void GraphicsDisplay::displayCellonBoard(char type, int x, int y) {
  if (type == '.') {
    theDisplay->drawRectangle(x, y, cellPx, cellPx);
  } else {
    // theDisplay->drawPiece(x, y, c.getType());
    theDisplay->drawRectangle(x, y, cellPx, cellPx);
    theDisplay->drawChar(x+6, y+6, type, 50, Xwindow::Black);
  }
}

void GraphicsDisplay::displayLinkOnBoard(int playerID, char id, char type, bool isRevealed, int x, int y) {
if (playerID == curPlayer) {
    if (type == 'V'){
      theDisplay->drawRectangle(x, y, cellPx, cellPx, 5, Xwindow::Red);
    } else {
      theDisplay->drawRectangle(x, y, cellPx, cellPx, 5, Xwindow::Green);
    }
    theDisplay->drawChar(x+5, y+5, id, 50);
  } else {
    if (isRevealed) {
      if (type == 'V'){
        theDisplay->drawRectangle(x, y, cellPx, cellPx, 5, Xwindow::Red);
      } else {
        theDisplay->drawRectangle(x, y, cellPx, cellPx, 5, Xwindow::Green);
      }
    } else {
      theDisplay->drawRectangle(x, y, cellPx, cellPx, 5, Xwindow::Blue);
    }
    
    theDisplay->drawChar(x+5, y+5, id, 50);
  }
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
  cerr << "DEBUG: GraphicsDisplay.notify() x: " << x << ", y: " << y << endl;
  if (link == nullptr || link->getIsDead()) {
    cerr << "DEBUG: type of cell: " << c.getType() << endl;
    cellIDs[y][x] = c.getType();
  } else {
    cerr << "DEBUG: " << *link << endl;
    cellIDs[y][x] = link->getId();
    cellLinkTypes[y][x] = link->getType();
    cellLinkIsRevealed[y][x] = link->getReveal();
  }

  string s;
  cerr << "DEBUG: after calculating x: " << x << ", y: " << y << endl;
  if (link == nullptr || link->getIsDead()) {
    displayCellonBoard(c.getType(), x, y);
  } else {
    displayLinkOnBoard(link->getPlayer()->getId(), link->getId(), link->getType(), link->getReveal(), x, y);
  }
}

void GraphicsDisplay::printDataDownloaded(int playerID) {
  string tmp = to_string(numLinksDownloaded[playerID]) + "D";
  if (playerID == 0){
    theDisplay->drawText(730, player1Pos + 55, tmp);
  } else {
    theDisplay->drawText(730, player2Pos + 55, tmp);
  }
}

void GraphicsDisplay::printVirusDownloaded(int playerID) {
  string tmp = to_string(numVirusesDownloaded[playerID]) + "V";
  if (playerID == 0){
    theDisplay->drawText(800, player1Pos + 55, tmp);
  } else {
    theDisplay->drawText(800, player2Pos + 55, tmp);
  }
}

void GraphicsDisplay::printNumOfAbilities(int playerID) {
  string tmp = to_string(numOfAbilities[playerID]);
  if (playerID == 0){
    theDisplay->drawText(730, player1Pos + 80, tmp);
  } else {
    theDisplay->drawText(730, player2Pos + 80, tmp);
  }
}

void GraphicsDisplay::printLinkInPlayerList(int playerID, int index) {
  int curPos = player1Pos;
  if (playerID == 1) {
    curPos = player2Pos;
  }
  if (index < 4) {
    if (playerID == curPlayer || isLinkRevealed[playerID][index]) 
      theDisplay->drawText(505 + index * 80, curPos+130, links[playerID][index], 14);
    else {
      string output = links[playerID][index].substr(0, 2)+" ? ";
      theDisplay->drawText(505 + index * 80, curPos+130, output, 14);
    }
  } else {
    if (playerID == curPlayer || isLinkRevealed[playerID][index]) 
      theDisplay->drawText(505 + (index-4) * 80, curPos+150, links[playerID][index], 14);
    else {
      string output = links[playerID][index].substr(0, 2)+" ? ";
      theDisplay->drawText(505 + (index-4) * 80, curPos+150, output, 14);
    }
  }
}

void GraphicsDisplay::notify(Player &p) {
  cerr << "DEBUG: graphicsDisplay.notify's player: " << p.getId() << endl;
  
  // printing amount of links downloaded
  if (numLinksDownloaded[p.getId()] != p.getDownloadCount()){
    numLinksDownloaded[p.getId()] = p.getDownloadCount();
    printDataDownloaded(p.getId());
  }
    
  if (numVirusesDownloaded[p.getId()] != p.getVirusCount()){
    numVirusesDownloaded[p.getId()] = p.getVirusCount();
    printVirusDownloaded(p.getId());
  }

  // printing amount of abilities downloaded
  if (numOfAbilities[p.getId()] != p.getAbilityCount()){
    numOfAbilities[p.getId()] = p.getAbilityCount();
    printNumOfAbilities(p.getId());
  }
  int index = 0;

  // printing links
  for (auto l = p.getLinkBeginIterator(); l != p.getLinkEndIterator(); ++l) {
    cerr << "DEBUG: player notify cur link: " << *(*l) << endl;
    stringstream ss;
    ss << *(*l);

    // updating link type/strength
    string prev = links[p.getId()][index];
    string nxt = ss.str();
    links[p.getId()][index] = nxt;
    
    // updating whether link is revealed
    bool prevIsRevealed = isLinkRevealed[p.getId()][index];
    bool newIsRevealed = (*(*l)).getReveal();
    isLinkRevealed[p.getId()][index] = newIsRevealed;

    // only reprint the link if it changed to save time 
    if (prev != nxt || prevIsRevealed != newIsRevealed) {
      printLinkInPlayerList(p.getId(), index);
    }
    ++index;
  }
}

GraphicsDisplay::~GraphicsDisplay() {

}