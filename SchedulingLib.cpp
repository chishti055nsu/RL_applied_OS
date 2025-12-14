#include "SchedulingLib.h"
#include <Arduino.h>

void Scheduler::init(Process* procs, int numProcs) {
  processes = procs;
  numProcesses = numProcs;
  for (int i = 0; i < numProcs; i++) {
    processes[i].remainingTime = processes[i].burstTime;
    processes[i].completionTime = 0;
  }
}

void Scheduler::simulateFCFS() {
  int currentTime = 0;
  int gantt[100];
  int ganttIndex = 0;

  Serial.println("FCFS Simulation:");
  for (int i = 0; i < numProcesses; i++) {
    while (currentTime < processes[i].arrivalTime) currentTime++;
    for (int t = 0; t < processes[i].burstTime; t++) {
      gantt[ganttIndex++] = processes[i].id;
      currentTime++;
    }
    processes[i].completionTime = currentTime;
  }
  printGantt("FCFS", gantt, ganttIndex);
}

void Scheduler::simulateRR(int quantum) {
  int currentTime = 0;
  int gantt[100];
  int ganttIndex = 0;
  bool done = false;

  Serial.println("RR Simulation:");
  while (!done) {
    done = true;
    for (int i = 0; i < numProcesses; i++) {
      if (processes[i].remainingTime > 0) {
        done = false;
        int exec = min(quantum, processes[i].remainingTime);
        for (int t = 0; t < exec; t++) {
          gantt[ganttIndex++] = processes[i].id;
          currentTime++;
        }
        processes[i].remainingTime -= exec;
        if (processes[i].remainingTime == 0) processes[i].completionTime = currentTime;
      }
    }
  }
  printGantt("RR", gantt, ganttIndex);
}

void Scheduler::simulatePriority(bool preemptive) {
  int currentTime = 0;
  int gantt[100];
  int ganttIndex = 0;

  Serial.println("Priority Simulation:");
  while (true) {
    int highestPri = 999;
    int selected = -1;
    for (int i = 0; i < numProcesses; i++) {
      if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
        if (processes[i].priority < highestPri) {
          highestPri = processes[i].priority;
          selected = i;
        }
      }
    }
    if (selected == -1) break;

    int exec = preemptive ? 1 : processes[selected].remainingTime;
    for (int t = 0; t < exec; t++) {
      gantt[ganttIndex++] = processes[selected].id;
      currentTime++;
      processes[selected].remainingTime--;
      if (processes[selected].remainingTime == 0) {
        processes[selected].completionTime = currentTime;
        break;
      }
    }
  }
  printGantt("Priority", gantt, ganttIndex);
}

void Scheduler::printGantt(const char* algo, int* gantt, int ganttSize) {
  Serial.print(algo);
  Serial.print(" Gantt: ");
  for (int i = 0; i < ganttSize; i++) {
    Serial.print("P");
    Serial.print(gantt[i]);
    Serial.print(" ");
  }
  Serial.println();
  Serial.print("Avg Wait: ");
  Serial.println(calculateAvgWait());
  Serial.print("Avg Turnaround: ");
  Serial.println(calculateAvgTurnaround());
}

float Scheduler::calculateAvgWait() {
  float totalWait = 0;
  for (int i = 0; i < numProcesses; i++) {
    totalWait += processes[i].completionTime - processes[i].arrivalTime - processes[i].burstTime;
  }
  return totalWait / numProcesses;
}

float Scheduler::calculateAvgTurnaround() {
  float totalTurn = 0;
  for (int i = 0; i < numProcesses; i++) {
    totalTurn += processes[i].completionTime - processes[i].arrivalTime;
  }
  return totalTurn / numProcesses;
}