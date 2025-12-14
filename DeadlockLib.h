#ifndef DEADLOCKLIB_H
#define DEADLOCKLIB_H

#define MAX_PROCS 5 // if i declare maximum process more than 5 , then the arduino 
#define MAX_RES 3
#define LED_PIN 13  // For visualization

class DeadlockDetector {
public:
  void init(int procs, int res);
  void request(int proc, int res);
  void release(int proc, int res);
  bool detectDeadlock();
  void visualizeGraph();
private:
  int allocation[MAX_PROCS][MAX_RES];
  int requestGraph[MAX_PROCS][MAX_RES];
  bool visited[MAX_PROCS];
  bool detectCycle(int proc);
};

#endif