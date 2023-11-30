#ifndef __LINK_H__
#define __LINK_H__
#include <iostream>
#include <vector>
#include "Player.h"

class Link{
    char id;
    int r, c;
    int strength, steps;
    char type; // D or V
    bool isRevealed;
    int playerId;
    // Player * player;

    public:
        Link(char id, int r, int c, char type, int strength);
        ~Link();
        char getType();
        char getId();
        int getStrength();
        void reveal();
        bool move(char d);
        bool battle(Link *other); 
        friend std::ostream &operator<<(std::ostream &out, const Link &l);
};
#endif
