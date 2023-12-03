#include <iostream>
#include "Link.h"
#include "Player.h"
using namespace std;

Link::Link(char id, Point p, char type, int strength) : id{id}, p{p}, type{type}, strength{strength}, isRevealed{false} {}

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

Point Link::getNewPos(Point dir, Point up, Point right) {
    return {dir.y * up.y + p.y, dir.x * right.x + p.x};
    // TO DO: doesn't work for players 3 and 4
}

void Link::move(Point dir, Point up, Point right) {
    p = getNewPos(dir, up, right);
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
