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
    char getType() const override; // Returns . for normal cell, S for server port, and M or W for firewall
    Firewall(int y, int x, Player* p);
    void attachLink(Link *l);
    void notifyObservers() override;
};
#endif
