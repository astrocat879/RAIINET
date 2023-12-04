#include "observer.h"
#include "Firewall.h"
#include "Player.h"

using namespace std;

Firewall::Firewall(): Cell() {}

Firewall::Firewall(int y, int x, Player* p): Cell(y, x), player{p} {}

char Firewall::getType() const {
    int playerID = player->getId();
    if (playerID == 0) return 'M';
    else if (playerID == 1) return 'W';
}

void Firewall::attachLink(Link *l) {
    if (l->getPlayer()->getId() != player->getId()) {
        if (l->getType() == 'D') {
            l->reveal();
        }
        else {
            l->getPlayer()->downloadLink(l);
            return;
        }
    }

    Cell::attachLink(l);
}

void Firewall::notifyObservers() {
  for (Observer * o: observers) {
    o->notify(*this);
  }
}