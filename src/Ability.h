#ifndef __ABILITY_H__
#define __ABILITY_H__
#include <iostream>
#include <vector>
#include "Player.h"

using namespace std;

class Ability
{
    int id;
    bool used;
    string name;
    Player * player;

public:
    virtual void useAbility() = 0;
};
#endif
