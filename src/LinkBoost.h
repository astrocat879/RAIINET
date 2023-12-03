#ifndef __LINKBOOST_H__
#define __LINKBOOST_H__
#include "Ability.h"
#include "Link.h"

using namespace std;

class LinkBoost : public Ability {
    Link *link;

    public:
        LinkBoost(int id, Player *player);
        void setLink(Link *l);
        void useAbility() override; 
};

#endif