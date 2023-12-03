#ifndef __FIREWALLABILITY_H__
#define __FIREWALLABILITY_H__
#include "Ability.h"
#include "Cell.h"

using namespace std;

class FirewallAbility : public Ability {
    Cell *c;
    
    public:
        FirewallAbility(int id, Player *player, Cell *c);
        void useAbility() override; 
};

#endif