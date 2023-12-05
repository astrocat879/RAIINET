#include "Scan.h"

using namespace std;

Scan::Scan(int id, Player *player): Ability(id, player) {
    used = false;
    name = "Scan";
}

void Scan::setLink(Link *l) {
    link = l;
}


void Scan::setBoard(Board *b) {
    board = b;
}

void Scan::useAbility() {
    if (used) { // ability has already been used
        throw invalid_argument{"Error: Ability Scan has already been used"};
    }
    link->reveal();
    link->getPlayer()->notifyObservers();
    board->getCell(link->getPoint())->notifyObservers();
    
    flipUsed(); // ability has been used
}