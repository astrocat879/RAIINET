#ifndef _OBSERVER_H_
#define _OBSERVER_H_
class Cell;

class Observer {
 public:
  virtual void notify(Cell &c) = 0;  // c is the Cell that called the notify method
  virtual ~Observer() = default;
};
#endif
