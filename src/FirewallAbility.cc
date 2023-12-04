#include "FirewallAbility.h"
#include "Cell.h"

using namespace std;

FirewallAbility::FirewallAbility(int id, Player *player): 
    Ability(id, player) {
        used = false;
        name = "Firewall";
    }

void FirewallAbility::setCell(int y, int x, Board *b) {
    c = new Cell{y, x};
    board = b;
}

void FirewallAbility::useAbility() {
    if (used) { // ability has already been used
        throw invalid_argument{"Error: Ability Firewall has already been used"};
    }
    Firewall *fw = new Firewall(c->getY(), c->getX(), player);
    delete board->theBoard[c->getY()][c->getX()];
    board->theBoard[c->getY()][c->getX()] = fw;
    flipUsed(); // ability has been used
}
