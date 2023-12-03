#ifndef __RECYCLE_H__
#define __RECYCLE_H__
#include "Ability.h"

using namespace std;

class Recycle : public Ability {
    Ability *ability;
    
    public:
        Recycle(int id, Player *player);
        void setAbility(Ability *a);
        void useAbility() override; 
};

#endif