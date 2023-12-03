#include "Immobilize.h";

using namespace std;

Immobilize::Immobilize(int id, Player *player, Link *link): Ability(id, player), link{link} {
    used = false;
    name = "Immobilize";
}

void Immobilize::useAbility() {
    if (!used) { // ability has already been used
        throw invalid_argument{"Error: Ability Immobilize has already been used"};
    }
    
    flipUsed(); // ability has been used
}