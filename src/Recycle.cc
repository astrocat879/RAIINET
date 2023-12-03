#include "Recycle.h";

using namespace std;

Recycle::Recycle(int id, Player *player, Ability *a): Ability(id, player), a{a} {
    used = false;
    name = "Recycle";
}

void Recycle::useAbility() {
    if (!used) { // ability has already been used
        throw invalid_argument{"Error: Ability Recycle has already been used"};
    }
    if (!a->getUsed()) {
        throw invalid_argument{"Error: Recycled ability has not been used yet"};
    }
    a->flipUsed(); // set it to false so it can be used again
    flipUsed(); // current ability has been used
}