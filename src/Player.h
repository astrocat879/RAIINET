#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <iostream>
#include <vector>
#include <string>
#include "Point.h"
#include "Ability.h"
#include "Link.h"

using namespace std;

class Link;
class Board;

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
    Board * board;

public:
    Player(int id, Board * board);
    ~Player();
    void init(string layout);                           // initializes the player's setup, given a layout
    void init();                                        // initializes a random layout
    vector<Link*>::iterator getLinkBeginIterator();     // returns the begin() iterator for the links vector
    vector<Link*>::iterator getLinkEndIterator();       // returns the end() iterator for the links vector
    void makeMove(Link * l, Point dir);
    void downloadLink(Link * l);
    int getDownloadCount();
    int getVirusCount();
    void removeLink(Link * l);
    Link * getLinkById(char id);
    int getId();
    int getAbilityCnt();

    friend ostream &operator<<(ostream &out, const Player &p);
};
#endif
