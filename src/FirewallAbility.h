#ifndef __FIREWALLABILITY_H__
#define __FIREWALLABILITY_H__
#include "Ability.h"
#include "Cell.h"

using namespace std;

class FirewallAbility : public Ability {
    Cell *c;
    
    public:
        FirewallAbility(int id, Player *player);
        void setCell(int x, int y);
        void useAbility() override; 
};

#endif