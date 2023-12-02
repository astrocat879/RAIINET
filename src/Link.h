#ifndef __LINK_H__
#define __LINK_H__
#include <iostream>
#include <vector>
#include "Point.h"

class Player;

class Link{
    char id;
    Point p;
    int strength;
    char type; // D or V
    bool isRevealed;
    // Board * Board;
    // int playerId;
    Player* player;

    public:
        Link(char id, Point p, char type, int strength);
        ~Link();
        char getType();
        char getId();
        int getStrength();
        Player* getPlayer();
        Point getPoint();
        Point getNewPos(Point dir, Point up, Point right);
        void reveal();
        void move(Point dir);
        bool battle(Link *other); 
        friend std::ostream &operator<<(std::ostream &out, const Link &l);
};
#endif
