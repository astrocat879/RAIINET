#ifndef __FIREWALL_H__
#define __FIREWALL_H__
#include <iostream>
#include <vector>
#include "textdisplay.h"
#include "Cell.h"
#include "Link.h"

class Firewall: public Cell {
  Player* player;
  public:
    Firewall();  // Default constructor
    Firewall(int x, int y, Player* p);
    void attachLink(Link *l);
};
#endif
