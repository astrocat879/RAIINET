#ifndef __POLARIZE_H__
#define __POLARIZE_H__
#include "Ability.h"
#include "Link.h"

using namespace std;

class Polarize : public Ability {
    Link *link;
    
    public:
        Polarize(int id, Player *player);
        void setLink(Link *l);
        void useAbility() override; 
};

#endif