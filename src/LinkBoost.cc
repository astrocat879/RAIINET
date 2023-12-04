#include "LinkBoost.h";

using namespace std;

LinkBoost::LinkBoost(int id, Player *player): Ability(id, player) {
    used = false;
    name = "Link Boost";
}

void LinkBoost::setLink(Link *l) {
    link = l;
}

void LinkBoost::useAbility() {
    if (used) { // ability has already been used
        throw invalid_argument{"Error: Ability Link Boost has already been used"};
    }
    link->addStep();
    flipUsed(); // ability has been used
}