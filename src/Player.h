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
    int downloadCount, virusCount, abilityCount;
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
    vector<Ability*>::iterator getAbilityBeginIterator();     // returns the begin() iterator for the abilities vector
    vector<Ability*>::iterator getAbilityEndIterator();       // returns the end() iterator for the abilities vector
    vector<Link*>::iterator getDownloadBeginIterator();     // returns the begin() iterator for the downloaded vector
    vector<Link*>::iterator getDownloadEndIterator(); 
    void moveLink(Link * l, Point dir);
    void downloadLink(Link * l);
    int getDownloadCount();
    int getVirusCount();
    void removeLink(Link * l);
    Link * getLinkById(char id);
    Ability * getAbility(int id);
    int getId();
    int getAbilityCount() const;
    void initAbility(string abilityList = "LFDSP"); // initializes abilities for player
    void initAbilityParams(int id, char c, Player *other);
    void useAbility(int abilityId);
    void addObserver(Observer * o); 
    void notifyObservers();

    friend ostream &operator<<(ostream &out, const Player &p);
};
#endif
