#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "observer.h"

using namespace std;

class Cell;
class Player;

class TextDisplay: public Observer {
  std::vector<std::vector<char>> theDisplay;
  std::vector<int> numLinksDownloaded;
  std::vector<int> numVirusesDownloaded;
  std::vector<std::vector<string>> links;
  std::vector<std::vector<bool>> isLinkRevealed;
  std::vector<int> numOfAbilities;
  const int gridSize;
  int curPlayer;

  void printPlayer(ostream &out, int playerID) const;

  public:
    TextDisplay(int n);

    void changePlayer(int nextPlayer);
    void notify(Cell &c) override;
    void notify(Player &p) override;

    ~TextDisplay();
    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
