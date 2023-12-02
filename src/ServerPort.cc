#include "observer.h"
#include "ServerPort.h"

using namespace std;

ServerPort::ServerPort(): Cell(){

}

bool ServerPort::attachLink(Link *l) {
  link = l;
  return true;
}

bool ServerPort::detachLink() {
  link = nullptr;
  return true;
}