#ifndef __CELL_H__
#define __CELL_H__
#include <iostream>
#include <vector>
#include "textdisplay.h"
#include "observer.h"
#include "Link.h"

class Cell{
  protected: 
    std::vector<Observer*> observers;
    Point p;
    Link* link; 

  // Add other private members if necessary

  public:
    Cell();  // Default constructor
    Cell(int y, int x);
    ~Cell(); // Destructor

    int getX() const; // Returns the value of x.
    int getY() const; // Returns the value of y.
    Link* getLink() const; // Returns the pointer to the link in this cell
    virtual char getType() const; // Returns . for normal cell, S for server port, and M or W for firewall
    void setCoords(int y, int x);  // Tells me my row and column number.
    void addObserver(Observer * o);
    void detachLink();
    virtual void attachLink(Link *l);
    virtual void notifyObservers();

    // void notify(); // needed? not sure
    friend ostream& operator<<(ostream& out, const Cell& c);
};
#endif
