#ifndef __DOWNLOAD_H__
#define __DOWNLOAD_H__
#include "Ability.h"
#include "Link.h"
#include "Board.h"

using namespace std;

class Download : public Ability {
    Link *link;
    Board *board;
    
    public:
        Download(int id, Player *player);
        void setLink(Link *l, Board *b);
        Link getLink();
        void useAbility() override; 
};

#endif