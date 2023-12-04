#ifndef __EXCHANGE_H__
#define __EXCHANGE_H__
#include "Ability.h"
#include "Link.h"
#include "Board.h"

using namespace std;

class Exchange : public Ability {
    Link *link1;
    Link *link2;
    Board *board;

    public:
        Exchange(int id, Player *player);
        void setLinks(Link *l1, Link *l2, Board *b);
        void useAbility() override; 
};

#endif