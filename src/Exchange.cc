#include "Exchange.h"
#include "Point.h"

using namespace std;

Exchange::Exchange(int id, Player *player): Ability(id, player) {
    used = false;
    name = "Exchange";
}

void Exchange::setLinks(Link *l1, Link *l2, Board *b) {
    link1 = l1;
    link2 = l2;
    board = b;
}

void Exchange::useAbility() {
    if (used) { // ability has already been used
        throw invalid_argument{"Error: Ability Exchange has already been used"};
    }
    Point p1 = link1->getPoint(), p2 = link2->getPoint();
    int xDiff = abs(p1.y - p2.y), yDiff = abs(p1.x - p2.x);
    if (xDiff + yDiff != 1) {
        throw invalid_argument{"Error: The two links are not next to each other, cannot be exchanged."};
    }
    link1->setPoint(p2.y, p2.x);
    link2->setPoint(p1.y, p1.x);
    board->theBoard[p1.y][p1.x]->detachLink();
    board->theBoard[p2.y][p2.x]->detachLink();
    board->theBoard[p1.y][p1.x]->attachLink(link2);
    board->theBoard[p2.y][p2.x]->attachLink(link1);
    
    flipUsed(); // current ability has been used
}