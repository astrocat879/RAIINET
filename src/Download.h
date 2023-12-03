#ifndef __DOWNLOAD_H__
#define __DOWNLOAD_H__
#include "Ability.h"
#include "Link.h"

using namespace std;

class Download : public Ability {
    Link *link;
    
    public:
        Download(int id, Player *player, Link *link);
        void useAbility() override; 
};

#endif