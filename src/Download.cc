#include "Download.h";
#include "Player.h"

using namespace std;

Download::Download(int id, Player *player): Ability(id, player) {
    used = false;
    name = "Download";
}

void Download::setLink(Link *l) {
    link = l;
}

void Download::useAbility() {
    if (used) { // ability has already been used
        throw invalid_argument{"Error: Ability Download has already been used"};
    }
    player->downloadLink(link);
    flipUsed(); // ability has been used
}

Link Download::getLink() {
    return *link;
}