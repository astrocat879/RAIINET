#ifndef __SCAN_H__
#define __SCAN_H__
#include "Ability.h"
#include "Link.h"
#include "Board.h"
#include "Player.h"

using namespace std;

class Scan : public Ability {
    Link *link;
    Board * board;
    
    public:
        Scan(int id, Player *player);
        void setBoard(Board * b);
        void setLink(Link *l);
        void useAbility() override; 
};

#endif