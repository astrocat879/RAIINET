#ifndef __SERVERPORT_H__
#define __SERVERPORT_H__
#include <iostream>
#include <vector>
#include "textdisplay.h"
#include "observer.h"
#include "Link.h"

class ServerPort : public Cell {
  Player* player;

  public:
    ServerPort();  // Default constructor
    ServerPort(int x, int y, Player* p);
    void attachLink(Link *l);
};
#endif
