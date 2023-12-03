#include <iostream>
#include "Link.h"
#include "Player.h"
using namespace std;

Link::Link(char id, Point p, Point up, Point right, char type, int strength, Player * player): id{id}, p{p}, up{up}, right{right}, type{type}, strength{strength}, isRevealed{false}, player{player} {}

Link::~Link() {}

char Link::getType() {
    return type;
}

char Link::getId() {
    return id;
}

int Link::getStrength() {
    return strength;
}

Player* Link::getPlayer() {
    return player;
}

Point Link::getPoint() {
    return p;
}

Point Link::getNewPos(Point dir) {
    return {dir.y * up.y + p.y, dir.x * right.x + p.x};
    // TO DO: doesn't work for players 3 and 4
}

void Link::move(Point dir) {
    p = getNewPos(dir);
}

bool Link::battle(Link *other) { // true if this link wins
    if (other->getStrength() > strength)
    {
        return false;
    }
    return true; // in case of tie, you still win
}

void Link::reveal() {
    isRevealed = true;
}

ostream &operator<<(ostream &out, const Link &l) {
    out << l.id << ": " << l.type << l.strength;
    return out;
}
