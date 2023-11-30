#include "observer.h"
#include "cell.h"

using namespace std;

Cell::Cell(): isOn(false), r(0), c(0) {

}

bool Cell::getState() const { return isOn; }
int Cell::getRow() const { return r; }
int Cell::getCol() const { return c; }

void Cell::setOn() {
  isOn = true;
  notifyAllObservers();
}

void Cell::toggle() {
  isOn ^= 1;
  notifyAllObservers();
}

void Cell::setCoords(int r, int c) { this->r = r; this->c = c; }

void Cell::attach(Observer *o) { 
  observers.emplace_back(o);
}

void Cell::notify(Cell &c) {
  toggle();
}

SubscriptionType Cell::subType() {
  return SubscriptionType::SwitchOnly;
}

void Cell::notifyAllObservers() {
  for (auto &o : observers) {
    if (o->subType() == SubscriptionType::All) {
      o->notify(*this);
    }
  }
}

void Cell::notifySwitchObservers() {
  for (auto &o : observers) {
    if (o->subType() == SubscriptionType::SwitchOnly) {
      o->notify(*this);
    }
  }
}
