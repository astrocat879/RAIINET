#include "LinkBoost.h";

using namespace std;

LinkBoost::LinkBoost(int id, Player *player, Link *link): Ability(id, player), link{link} {
    used = false;
    name = "Link Boost";
}

void LinkBoost::useAbility() {
    if (!used) { // ability has already been used
        throw invalid_argument{"Error: Ability Link Boost has already been used"};
    }
    link->setSteps(steps);
    flipUsed(); // ability has been used
}