#include "Download.h";
#include "Player.h"

using namespace std;

Download::Download(int id, Player *player, Link *link): Ability(id, player), link{link} {
    used = false;
    name = "Download";
}

void Download::useAbility() {
    if (!used) { // ability has already been used
        throw invalid_argument{"Error: Ability Download has already been used"};
    }
    player->downloadLink(link);
    flipUsed(); // ability has been used
}