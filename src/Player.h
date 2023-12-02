#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <iostream>
#include <vector>
#include <string>
#include "Point.h"
#include "Ability.h"
#include "Link.h"
#include "Board.h"

using namespace std;

class Player
{
    int id;
    Point right, up;                // represents what change in x and y represents "up" and "right" for a player
    Point botLeft;                  // coordinates for the bottom left corner of the player
    int downloadCount, virusCount;
    string linkIDs;
    vector<Ability *> abilities;
    vector<Link *> links;
    vector<Link *> downloaded;
    // Board * board;

public:
    Player(int id);
    void init(string layout);       // initializes the player's setup, given a layout
    void init();                    // initializes a random layout
    void moveLink(Link * l, Point dir);
    void downloadLink(Link * l);
    void removeLink(Link * l);
    int getId();
    int getAbilityCnt();

    friend ostream &operator<<(ostream &out, const Player &p);
};
#endif
