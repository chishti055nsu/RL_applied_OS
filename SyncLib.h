#ifndef SYNCLIB_H
#define SYNCLIB_H

class Semaphore {
public:
  Semaphore(int initVal);
  void wait();
  void signal();
private:
  int value;
};

class Mutex {
public:
  Mutex();
  void lock();
  void unlock();
private:
  bool locked;
  Semaphore sem;
};

#endif