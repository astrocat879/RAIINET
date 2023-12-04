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
  std::vector<std::vector<string>> downloaded;
  std::vector<std::vector<string>> links;
  std::vector<int> numOfAbilities;
  const int gridSize;
  int curPlayer;
  int cellPx;
 public:
  GraphicsDisplay(int n, Xwindow * w, int curPlayer);

  void notify(Cell &c) override;
  void notify(Player &p) override;

  ~GraphicsDisplay();

//   friend std::ostream &operator<<(std::ostream &out, const GraphicsDisplay &td);
};

#endif
