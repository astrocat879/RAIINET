#ifndef __LINK_H__
#define __LINK_H__
#include <iostream>
#include <vector>
#include "Point.h"

class Player;
class LinkBoost;
class Polarize;
class Scan;
class Exchange;

class Link{
    char id;
    Point p;
    int strength;
    int steps;
    char type; // D or V
    bool isRevealed;
    // Board * Board;
    // int playerId;
    Player* player;

    void setSteps(int val); // sets steps for the link, used by LinkBoost 
    void setType(char c); // sets type for the link, used by Polarize

    public:
        friend class LinkBoost;
        friend class Polarize;
        friend class Exchange;
        Link(char id, Point p, char type, int strength);
        ~Link();
        char getType();
        char getId();
        int getStrength();
        bool getReveal();
        Player* getPlayer();
        Point getPoint();
        Point getNewPos(Point dir, Point up, Point right);
        void reveal();
        void move(Point dir, Point up, Point right);
        bool battle(Link *other); 
        friend std::ostream &operator<<(std::ostream &out, const Link &l);
};
#endif
