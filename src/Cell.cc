#include "observer.h"
#include "Cell.h"
#include "Player.h"

using namespace std;

Cell::Cell(): p{Point {0, 0}}, link{nullptr} {}
Cell::Cell(int y, int x): p{Point {y, x}}, link{nullptr} {}

int Cell::getX() const { return p.x; }
int Cell::getY() const { return p.y; }

Link* Cell::getLink() const { return link; }

char Cell::getType() const {
  return '.';
}

void Cell::setCoords(int y, int x) { p = {y, x}; }

void Cell::attachLink(Link *l) {
  /*
  Cell.attachLink(Link* l) for the new cell
      This also applies the additional effects of the cell, like Firewall's reveal/download and serverport's download
      If this cell already contains link (which can only be enemy link), battle:
        if incoming link wins, put incoming link in the cell and current enemy link is put into incomingLink.getPlayer.downloadLink(currentLink)
  */
  // cerr << "DEBUG: Atttaching link\n";
  if (link != nullptr) { //if a cell is occupied, the links must fight
    
    if (l->getPlayer()->getId() == link->getPlayer()->getId()) {
      cerr << *link << '\n';
      throw logic_error("Moving link onto another link owned by player");
    }
    cerr << "DEBUG: Battle starts\n";
    if (l->battle(link)) { //if incoming beats current, incoming's player downloads current
      cerr << "DEBUG: win\n";
      l->getPlayer()->downloadLink(link);
      link = l;
    }
    else { //if current beats incoming, current's player downloads incoming
      cerr << "DEBUG: loss\n";
      link->getPlayer()->downloadLink(l);
    } 
  }
  else {
    link = l;
  }
  cerr << "DEBUG: finish attachlink\n";
  notifyObservers();
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
  notifyObservers();
}


ostream& operator<<(ostream& out, const Cell& c) {
  if (c.link == nullptr) {
    // cerr << "DEBUG: link == nullptr" << endl;
    out << '.';
  } else {
    // cerr << "DEBUG: " << *(c.link) << endl;
    out << c.link->getId();
  }
  return out;
}

Cell::~Cell () {
  delete link;
}