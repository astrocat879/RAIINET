#include "FirewallAbility.h"
#include "Cell.h"

using namespace std;

FirewallAbility::FirewallAbility(int id, Player* player): 
    Ability(id, player) {
        used = false;
        name = "Firewall";
    }

void FirewallAbility::setCell(int y, int x, Board *b) {
    if (x>boardSize || y>boardSize) {
        throw invalid_argument{"Error: Target position (" + to_string(p.y) + "," + std::to_string(p.x) + ") is out of bounds."};
    }
    p = {x, y};
    board = b;
}

void FirewallAbility::useAbility() {
    if (used) { // ability has already been used
        throw invalid_argument{"Error: Ability Firewall has already been used."};
    }
    if (board->theBoard[p.y][p.x]->getLink() != nullptr) { // target cell has link in it
        throw logic_error{"Error: Cannot place Firewall on occupied cells."};
    }
    if (board->theBoard[p.y][p.x]->getType() != '.') { // target cell is a Firewall or server port
        throw logic_error{"Error: Cannot place Firewall on Firewalls or Server Ports."};
    }
    board->addFirewall(p, player);
    flipUsed(); // ability has been used
}
