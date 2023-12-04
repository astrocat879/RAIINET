#ifndef __ABILITY_H__
#define __ABILITY_H__
#include <iostream>
#include <vector>

using namespace std;

class Player;

class Ability
{
    protected:
        const int boardSize = 8;
        int id;
        bool used;
        string name;
        Player * player;

    public:
        Ability(int id, Player *player);
        virtual ~Ability();
        int getId();
        bool getUsed();
        string getName();
        void flipUsed();
        void displayAbility();
        virtual void useAbility() = 0;
};
#endif
