#ifndef __GRAPHICSDISPLAY_H__
#define __GRAPHICSDISPLAY_H__
#include <iostream>
#include <vector>
#include <string>
#include "observer.h"
#include "window.h"
class Cell;
class Player;

using namespace std;

class GraphicsDisplay: public Observer {
  Xwindow * theDisplay;
  std::vector<std::vector<char>> cellIDs;
  std::vector<std::vector<char>> cellLinkTypes;
  std::vector<std::vector<bool>> cellLinkIsRevealed;   
  std::vector<int> numLinksDownloaded; // just realized this was supposed to be numDataDownloaded, oops lol
  std::vector<int> numVirusesDownloaded;
  std::vector<std::vector<string>> links;
  std::vector<std::vector<bool>> isLinkRevealed;
  std::vector<int> numOfAbilities;
  const int gridSize;
  int curPlayer;
  int player1Pos;
  int player2Pos;
  int cellPx;

  void printPlayerHeaders();
  void displayCellonBoard(char type, int x, int y);
  void displayLinkOnBoard(int playerID, char id, char type, bool isRevealed, int x, int y);
  void printDataDownloaded(int playerID);
  void printVirusDownloaded(int playerID);
  void printNumOfAbilities(int playerID);
  void printLinkInPlayerList(int playerID, int index);
  void drawCoordinates();
 public:
  GraphicsDisplay(int n, Xwindow * w, int curPlayer);

  void changePlayer(int nextPlayer);
  void notify(Cell &c) override;
  void notify(Player &p) override;

  ~GraphicsDisplay();

//   friend std::ostream &operator<<(std::ostream &out, const GraphicsDisplay &td);
};

#endif
