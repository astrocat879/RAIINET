#include "Player.h"

using namespace std;

Ability::Ability(int id, Player *player): id{id}, player{player} {}

Ability::~Ability() {} 

int Ability::getId() {
    return id;
}

bool Ability::getUsed() {
    return used;
}

string Ability::getName() {
    return name;
}

void Ability::flipUsed() {
    used = !used;
}

void Ability::displayAbility() {
    cout << "Name: " << name << "   ID: " << id << "   Used: " << (used ? "Yes" : "No") << endl;
}