#ifndef __LINK_H__
#define __LINK_H__
#include <iostream>
#include <vector>
#include "Player.h"

class Link{
    char id;
    int strength, steps;
    bool isVirus;
    bool isRevealed;
    Player * player;

    public:
        bool move(string direction);
        bool battle(Link *l, bool initiative);  // maybe should be private? cuz move would call this
};
#endif
