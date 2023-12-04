#ifndef __IMMOBILIZE_H__
#define __IMMOBILIZE_H__
#include "Ability.h"
#include "Link.h"

using namespace std;

class Immobilize : public Ability {
    Link *link;
    
    public:
        Immobilize(int id, Player *player);
        void setLink(Link *l);
        void useAbility() override; 
};

#endif