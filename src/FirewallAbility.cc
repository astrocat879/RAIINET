#include "FirewallAbility.h"
#include "Cell.h"

using namespace std;

FirewallAbility::FirewallAbility(int id, Player *player): 
    Ability(id, player) {
        used = false;
        name = "Firewall";
    }

void FirewallAbility::setCell(int x, int y) {
    c = new Cell{x, y};
}

void FirewallAbility::useAbility() {
    if (used) { // ability has already been used
        throw invalid_argument{"Error: Ability Firewall has already been used"};
    }
    
    flipUsed(); // ability has been used
}
