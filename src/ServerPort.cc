#include "observer.h"
#include "ServerPort.h"

using namespace std;

ServerPort::ServerPort(): Cell() {}

ServerPort::ServerPort(int x, int y, Player* p): Cell(x, y), player{p} {}

void ServerPort::attachLink(Link *l) {
  l->getPlayer()->downloadLink(l);
}
