#ifndef SCHEDULINGLIB_H
#define SCHEDULINGLIB_H

struct Process {
  int id;
  int arrivalTime;
  int burstTime;
  int priority;  // Lower number = higher priority
  int remainingTime;
  int completionTime;  // Added for metrics
};

class Scheduler {
public:
  void init(Process* procs, int numProcs);
  void simulateFCFS();
  void simulateRR(int quantum);
  void simulatePriority(bool preemptive = false);
  float calculateAvgWait();
  float calculateAvgTurnaround();
private:
  Process* processes;
  int numProcesses;
  void printGantt(const char* algo, int* gantt, int ganttSize);
};

#endif