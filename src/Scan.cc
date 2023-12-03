#include "Scan.h";

using namespace std;

Scan::Scan(int id, Player *player, Link *link): Ability(id, player), link{link} {
    used = false;
    name = "Scan";
}

void Scan::useAbility() {
    if (!used) { // ability has already been used
        throw invalid_argument{"Error: Ability Scan has already been used"};
    }
    link->reveal();
    flipUsed(); // ability has been used
}