#include <iostream>
#include "Link.h"
using namespace std;

Link::Link(char id, int r, int c, char type, int strength) : id{id}, r{r}, c{c}, type{type}, strength{strength}, steps{0}, isRevealed{false}
{
}

Link::~Link()
{
}

char Link::getType()
{
    return type;
}

char Link::getId()
{
    return id;
}

int Link::getStrength()
{
    return strength;
}

bool Link::move(char d)
{
    if (d == 'U')
    {
        r += steps;
    }
    else if (d == 'D')
    {
        r -= steps;
    }
    else if (d == 'R')
    {
        c += steps;
    }
    else if (d == 'L')
    {
        c -= steps;
    }
    return true;
}

bool Link::battle(Link *other)
{ // true if this link wins
    if (other->getStrength() > strength)
    {
        return false;
    }
    return true; // in case of tie, you still win
}

void Link::reveal(){
    isRevealed = true;
}

ostream &operator<<(ostream &out, const Link &l)
{
    if (l.isRevealed)
        out << l.id;
    else
        out << "?";
    return out;
}
