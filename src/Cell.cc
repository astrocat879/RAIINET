#include "observer.h"
#include "Cell.h"

using namespace std;

Cell::Cell(): x(0), y(0) {

}

int Cell::getX() const { return x; }
int Cell::getY() const { return y; }

/* void Cell::setOn() {
  isOn = true;
  notifyAllObservers();
} */

/* void Cell::toggle() {
  isOn ^= 1;
  notifyAllObservers();
} */

void Cell::setCoords(int x, int y) { this->x = x; this->y = y; }

/* void Cell::attach(Observer *o) { 
  observers.emplace_back(o);
} */

bool Cell::attachLink(Link *l) {
  link = l;
  return true;
}

bool Cell::detachLink() {
  link = nullptr;
  return true;
}

Cell::~Cell () {
  delete link;
}