
#include "SchedulingLib.h"
#include "SyncLib.h"
#include "DeadlockLib.h"
#include "MemoryLib.h"
#include "RLLib.h"

Process procs[4] = {
  {1, 0, 24, 3},
  {2, 0, 3, 1},
  {3, 0, 3, 4},
  {60, 0, 10, 15}
};

Scheduler sched;
Semaphore sem(1);
Mutex mut;
DeadlockDetector dd;
MemoryManager mm;
RLAgent rl;

void setup() {
  Serial.begin(9600);

  // Scheduling Demo
  sched.init(procs, 4);
  sched.simulateFCFS();
  sched.simulateRR(4);
  sched.simulatePriority(true);

  // Sync Demo
  Serial.println("Sync Demo:");
  mut.lock();
  Serial.println("Resource locked");
  mut.unlock();
  Serial.println("Resource unlocked");

  // Deadlock Demo
  dd.init(5, 3);
  dd.request(0, 0);
  dd.request(1, 1);
  dd.request(0, 1);  // Potential cycle
  dd.request(1, 0);
  dd.detectDeadlock();
  dd.visualizeGraph();

  // Memory Demo
  mm.init();
  int start = mm.allocatePages(3);
  Serial.print("Allocated at: ");
  Serial.println(start);
  mm.visualizeMemory();
  mm.simulatePaging(8);  // Virt addr
  mm.deallocatePages(start, 3);
  mm.visualizeMemory();

  // RL Demo (Integrated with Scheduling)
  rl.init();
  Serial.println("RL Training on Scheduling (10 episodes):");
  for (int episode = 0; episode < 10; episode++) {
    sched.init(procs, 4);  // Reset
    int state = 4;  // Initial ready processes
    for (int i = 0; i < 4; i++) {
      int action = rl.chooseAction(state);  // Choose pri
      procs[i].priority = action + 1;  // 1-3
    }
    sched.simulatePriority();
    float reward = -sched.calculateAvgWait();  // Negative wait time
    int newState = 0;  // End state
    for (int i = 0; i < 4; i++) {  // Update per action (simplified)
      rl.updateQ(state, procs[i].priority - 1, reward, newState);
    }
    Serial.print("Episode ");
    Serial.print(episode);
    Serial.print(" Avg Wait: ");
    Serial.println(-reward);
  }
  rl.printQTable();  // See learned policy
}

void loop() {}