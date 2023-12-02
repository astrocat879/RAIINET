#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>
#include <vector>
#include "observer.h"
#include "Cell.h"

class TextDisplay: public Observer {
  std::vector<std::vector<char>> theDisplay;
  const int gridSize;
 public:
  TextDisplay(int n);

  void notify(Cell &c) override;

  ~TextDisplay();
  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
