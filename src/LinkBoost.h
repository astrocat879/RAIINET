#ifndef __LINKBOOST_H__
#define __LINKBOOST_H__
#include "Ability.h"
#include "Link.h"

using namespace std;

class LinkBoost : public Ability {
    const int steps = 2;
    Link *link;
    
    public:
        LinkBoost(int id, Player *player, Link *link);
        void useAbility() override; 
};

#endif