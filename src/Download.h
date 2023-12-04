#ifndef __DOWNLOAD_H__
#define __DOWNLOAD_H__
#include "Ability.h"
#include "Link.h"

using namespace std;

class Download : public Ability {
    Link *link;
    
    public:
        Download(int id, Player *player);
        void setLink(Link *l);
        Link getLink();
        void useAbility() override; 
};

#endif