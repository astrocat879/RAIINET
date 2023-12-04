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
    // cerr << "DEBUG: display ability\n";
    string padding = "";
    for (int i=0; i<2 - (name.length()/9); i++) {
        padding += "\t";
    }
    cout << "Name: " << name << padding << "ID: " << id << "\tUsed: " << (used ? "Yes" : "No") << endl;
}