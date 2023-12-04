#include "Download.h"
#include "Player.h"
#include "Board.h"

using namespace std;

Download::Download(int id, Player *player): Ability(id, player) {
    used = false;
    name = "Download";
}

void Download::setLink(Link *l, Board *b) {
    link = l;
    board = b;
}

void Download::useAbility() {
    if (used) { // ability has already been used
        throw invalid_argument{"Error: Ability Download has already been used"};
    }
    Point p = link->getPoint();
    board->theBoard[p.y][p.x]->detachLink();
    player->downloadLink(link);
    flipUsed(); // ability has been used
}

Link Download::getLink() {
    return *link;
}