#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <iostream>
#include <vector>
#include <string>
#include "Point.h"
#include "Ability.h"
#include "Link.h"
#include "textdisplay.h"

using namespace std;

class Link;

class Player
{
    vector<Observer*> observers;
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
    ~Player();
    void init(string layout);                           // initializes the player's setup, given a layout
    void init();                                        // initializes a random layout
    vector<Link*>::iterator getLinkBeginIterator();     // returns the begin() iterator for the links vector
    vector<Link*>::iterator getLinkEndIterator();       // returns the end() iterator for the links vector
    vector<Link*>::iterator getDownloadBeginIterator();     // returns the begin() iterator for the downloaded vector
    vector<Link*>::iterator getDownloadEndIterator();       // returns the end() iterator for the downloaded vector
    void moveLink(Link * l, Point dir);
    void downloadLink(Link * l);
    int getDownloadCount();
    int getVirusCount();
    void removeLink(Link * l);
    Link * getLinkById(char id);
    int getId();
    int getAbilityCnt();
    void addObserver(Observer * o); 
    void notifyObservers();

    friend ostream &operator<<(ostream &out, const Player &p);
};
#endif
