#ifndef __SERVERPORT_H__
#define __SERVERPORT_H__
#include <iostream>
#include <vector>
#include "textdisplay.h"
#include "observer.h"
#include "Link.h"

class ServerPort : public Cell {
    

 public:
  ServerPort();  // Default constructor
  
  bool detachLink();
  bool attachLink(Link *l);

  void notify(); // needed? not sure
};
#endif
