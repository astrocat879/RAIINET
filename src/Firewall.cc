#include "observer.h"
#include "Firewall.h"

using namespace std;

Firewall::Firewall(): Cell() {}

Firewall::Firewall(int x, int y, Player* p): Cell(x, y), player{p} {}

void Firewall::attachLink(Link *l) {
    if (l->getPlayer()->getId() != player->getId()) {
        if (l->getType() == 'D') {
            l->reveal();
        }
        else {
            l->getPlayer()->downloadLink();
            return;
        }
    }

    Cell::attachLink(l);
}
