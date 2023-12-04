#include "Exchange.h";
#include "Point.h";

using namespace std;

Exchange::Exchange(int id, Player *player): Ability(id, player) {
    used = false;
    name = "Exchange";
}

void Exchange::setLinks(Link *l1, Link *l2) {
    link1 = l1;
    link2 = l2;
}

void Exchange::useAbility() {
    if (used) { // ability has already been used
        throw invalid_argument{"Error: Ability Exchange has already been used"};
    }
    Point p1 = link1->getPoint(), p2 = link2->getPoint();
    
    flipUsed(); // current ability has been used
}