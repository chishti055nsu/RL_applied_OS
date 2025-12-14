#ifndef RLLIB_H
#define RLLIB_H

#define STATES 5   // e.g., 0-4 ready processes
#define ACTIONS 3  // 0: low pri, 1: med, 2: high

class RLAgent {
public:
  void init();
  int chooseAction(int state);  // Epsilon-greedy // Q learning 
  void updateQ(int state, int action, float reward, int newState);
  void printQTable();
private:
  float qTable[STATES][ACTIONS];
  float learningRate = 0.1;
  float discount = 0.9;
  float exploration = 0.2;
};

#endif