#ifndef __CELL_H__
#define __CELL_H__
#include <iostream>
#include <vector>
#include "textdisplay.h"
#include "observer.h"
#include "Link.h"

class Cell : public Observer {
  std::vector<Observer*> observers;
  int r, c;
  Link * link;

  // Add other private members if necessary

 public:
  Cell();  // Default constructor

  int getRow() const; // Returns the value of r.
  int getCol() const; // Returns the value of c.
  void setCoords(int r, int c);  // Tells me my row and column number.

  void attach(Observer *o);

  void notify(); // needed? not sure
};
#endif
