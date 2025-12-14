#include "SyncLib.h"
#include <Arduino.h>

Semaphore::Semaphore(int initVal) : value(initVal) {}

void Semaphore::wait() {
  while (value <= 0) { delay(10); }
  value--;
}

void Semaphore::signal() {
  value++;
}

Mutex::Mutex() : locked(false), sem(1) {}

void Mutex::lock() {
  sem.wait();
  locked = true;
}

void Mutex::unlock() {
  locked = false;
  sem.signal();
}