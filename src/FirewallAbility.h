#ifndef __FIREWALLABILITY_H__
#define __FIREWALLABILITY_H__
#include "Ability.h"
#include "Cell.h"
#include "Firewall.h"
#include "Board.h"

using namespace std;

class FirewallAbility : public Ability {
    Cell *c;
    Board *board;
    
    public:
        FirewallAbility(int id, Player *player);
        void setCell(int y, int x, Board *b);
        void useAbility() override; 
};

#endif