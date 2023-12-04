#include "observer.h"
#include "ServerPort.h"
#include "Player.h"

using namespace std;

ServerPort::ServerPort(): Cell() {}

ServerPort::ServerPort(int x, int y, Player* p): Cell(x, y), player{p} {}

char ServerPort::getType() const {
  return 'S';
}

void ServerPort::attachLink(Link *l) {
  // don't allow player to download their own links
  if (player->getId() == l->getPlayer()->getId()) {
    throw logic_error("Invalid move: Target position (" + to_string(p.y) + "," + std::to_string(p.x) + ") is allied server port");
  }
  l->getPlayer()->downloadLink(l);
}

void ServerPort::notifyObservers(){
  for (Observer * o: observers) {
    o->notify(*this);
  }
}