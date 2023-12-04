#include "Polarize.h"

using namespace std;

Polarize::Polarize(int id, Player *player): Ability(id, player) {
    used = false;
    name = "Polarize";
}

void Polarize::setLink(Link *l) {
    link = l;    
}

void Polarize::useAbility() {
    if (used) { // ability has already been used
        throw invalid_argument{"Error: Ability Polarize has already been used"};
    }
    if (link->getType() == 'D') {
        link->setType('V');
    } else {
        link->setType('D');
    }
    flipUsed(); // ability has been used
}