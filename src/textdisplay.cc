#include <iostream>
#include "textdisplay.h"
#include "Cell.h"
#include "Player.h"
#include <sstream>
using namespace std;

TextDisplay::TextDisplay(int n): gridSize{n}, curPlayer{0} {
  for (int i=0; i<gridSize; i++) {
    theDisplay.emplace_back(vector<char>());
    for (int j=0; j<gridSize; j++) {
      theDisplay[i].emplace_back('.');
    }
  }

  for (int i=0; i<4; i++) {
    downloaded.emplace_back(vector<string>());
    links.emplace_back(vector<string>());
    for (int j=0; j<gridSize; j++) {
      downloaded[i].emplace_back(" ");
      links[i].emplace_back(" ");
    }
    numOfAbilities.emplace_back(5);
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

void TextDisplay::notify(Player &p) {
  int index = 0;
  for (auto l = p.getDownloadBeginIterator(); l != p.getDownloadEndIterator(); ++l) {
    downloaded[p.getId()][index] = to_string((*l)->getType())+to_string((*l)->getStrength());
    ++index;
  }
  numOfAbilities[p.getId()] = p.getAbilityCnt();
  for (auto l = p.getLinkBeginIterator(); l != p.getLinkEndIterator(); ++l) {
    cerr << "DEBUG: player notify cur link: " << *(*l) << endl;
    stringstream ss;
    ss << *(*l);
    links[p.getId()][index] = ss.str();
    ++index;
  }
}
 
void TextDisplay::printPlayer(ostream &out, int playerID) const {
    // TO DO: make player have an observer so text display can do this
    out << "Player " << (playerID+1) << ":\n";
    out << "Downloaded:";
    for (int i=0; i<8; i++) {
      if (downloaded[playerID][i]!=" ") {
        if (i == 0) {
            out << ' ';
        } else {
            out << ", ";
        }
        out << downloaded[playerID][i];
      }
        
    }
    out << "\n";
    out << "Abilities: " << numOfAbilities[playerID] << "\n";
    for (int i=0; i<4; i++) {
      if (playerID == curPlayer) out << links[playerID][i] << ' ';
      else {
        string output = links[playerID][i].substr(0, 2)+" ?";
        out << output << ' ';
      }
    }
    out << '\n';
    for (int i=4; i<8; i++) {
      if (playerID == curPlayer) out << links[playerID][i] << ' ';
      else {
        string output = links[playerID][i].substr(0, 2)+" ?";
        out << output << ' ';
      }
    }
    out << '\n';
}

ostream& operator<<(ostream &out, const TextDisplay &td) {
  td.printPlayer(out, (td.curPlayer+1)%2); // TO DO: this doesn't work for 4 players
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
  td.printPlayer(out, td.curPlayer);
  return out;
}

