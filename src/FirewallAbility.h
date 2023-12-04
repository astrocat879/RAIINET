#ifndef __FIREWALLABILITY_H__
#define __FIREWALLABILITY_H__
#include "Ability.h"
#include "Cell.h"
#include "Firewall.h"

using namespace std;

class FirewallAbility : public Ability {
    Cell *c;
    
    public:
        FirewallAbility(int id, Player *player);
        void setCell(int y, int x);
        void useAbility() override; 
};

#endif