#include "Exchange.h";

using namespace std;

Exchange::Exchange(int id, Player *player, Link *l1, Link *l2): Ability(id, player), link1{l1}, link2{l2} {
    used = false;
    name = "Exchange";
}

void Exchange::useAbility() {
    if (!used) { // ability has already been used
        throw invalid_argument{"Error: Ability Exchange has already been used"};
    }
    
    flipUsed(); // current ability has been used
}