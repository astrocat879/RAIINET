#include "Recycle.h";

using namespace std;

Recycle::Recycle(int id, Player *player): Ability(id, player) {
    used = false;
    name = "Recycle";
}

void Recycle::setAbility(Ability *a) {
    ability = a;
}

void Recycle::useAbility() {
    if (!used) { // ability has already been used
        throw invalid_argument{"Error: Ability Recycle has already been used"};
    }
    if (!ability->getUsed()) {
        throw invalid_argument{"Error: Recycled ability has not been used yet"};
    }
    ability->flipUsed(); // set it to false so it can be used again
    flipUsed(); // current ability has been used
}