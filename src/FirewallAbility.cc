#include "FirewallAbility.h"
#include "Cell.h"

using namespace std;

FirewallAbility::FirewallAbility(int id, Player *player, Cell *c): 
    Ability(id, player), c{c} {
        used = false;
        name = "Firewall";
    }

void FirewallAbility::useAbility() {
    if (!used) { // ability has already been used
        throw invalid_argument{"Error: Ability Firewall has already been used"};
    }
    
    flipUsed(); // ability has been used
}
