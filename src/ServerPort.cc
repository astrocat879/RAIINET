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
  l->getPlayer()->downloadLink(l);
}
