#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <iostream>
#include <vector>
#include "Ability.h"
#include "Link.h"

using namespace std;

class Player
{
    int downloadCount, virusCount;
    vector<Ability *> abilities;
    vector<Link *> links;
    vector<Link *> downloaded;

    // Add other private members if necessary

public:
    bool moveLink(Link * l);
    bool downloadLink(Link * l);
    bool removeLink(Link * l);
};
#endif
