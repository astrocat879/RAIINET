#ifndef _OBSERVER_H_
#define _OBSERVER_H_
class Cell;
class Player;

class Observer {
 public:
  virtual void notify(Cell &c) = 0;  // c is the Cell that called the notify method
  virtual void notify(Player &p) = 0; // p is the Player that caclled the notify method
  virtual ~Observer() = default;
};
#endif

// subject: cell
// observer: Player

// when cell changes, you want player to react in some way

// so when cell changes, you call player.notify()