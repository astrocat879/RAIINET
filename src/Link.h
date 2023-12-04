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
    Point up;
    Point right;
    int strength;
    int steps;
    bool isDead;
    char type; // D or V
    bool isRevealed;
    bool isFrozen; // true means it is immobilized, false means its not
    // Board * Board;
    // int playerId;
    Player* player;

    void addStep(); // allows link to move one step further, used by LinkBoost 
    void setType(char c); // sets type for the link, used by Polarize

    public:
        friend class LinkBoost;
        friend class Polarize;
        friend class Exchange;
        Link(char id, Point p, Point up, Point right, char type, int strength, Player * player);
        ~Link();
        char getType();
        char getId();
        int getStrength();
        bool getReveal();
        void setDead();
        bool getIsFrozen();
        bool getIsDead();
        Player* getPlayer();
        Point getPoint();
        Point getNewPos(Point dir, Point up, Point right);
        void reveal();
        void flipFrozen(); // sets isFrozen to true if link isn't frozen and ability is used, or sets it to false if it is frozen
        void setPoint(int y, int x);
        void move(Point dir, Point up, Point right);
        bool battle(Link *other); 
        friend std::ostream &operator<<(std::ostream &out, const Link &l);
};
#endif
