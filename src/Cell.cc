#include "observer.h"
#include "Cell.h"

using namespace std;

Cell::Cell(): p{Point {0, 0}}, link{nullptr} {}
Cell::Cell(int x, int y): p{Point {x, y}}, link{nullptr} {}

int Cell::getX() const { return p.x; }
int Cell::getY() const { return p.y; }

Link* Cell::getLink() const {
  return link;
}

void Cell::setCoords(int y, int x) { p = {y, x}; }

void Cell::attachLink(Link *l) {
  /*
  Cell.attachLink(Link* l) for the new cell
      This also applies the additional effects of the cell, like Firewall's reveal/download and serverport's download
      If this cell already contains link (which can only be enemy link), battle:
        if incoming link wins, put incoming link in the cell and current enemy link is put into incomingLink.getPlayer.downloadLink(currentLink)
  */
  if (link != nullptr) { //if a cell is occupied, the links must fight
    if (l->battle(link)) { //if incoming beats current, incoming's player downloads current
      l->getPlayer()->downloadLink(link);
      link = l;
    }
    else { //if current beats incoming, current's player downloads incoming
      link->getPlayer()->downloadLink(l);
    } 
  }
  else {
    link = l;
  }
}

void Cell::addObserver(Observer * o) {
  observers.push_back(o);
}

void Cell::notifyObservers(){
  for (Observer * o: observers) {
    o->notify(*this);
  }
}

void Cell::detachLink() {
  link = nullptr;
}

Cell::~Cell () {
  delete link;
}