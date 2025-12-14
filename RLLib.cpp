#include "RLLib.h"
#include <Arduino.h>

void RLAgent::init() {
  for (int s = 0; s < STATES; s++) {
    for (int a = 0; a < ACTIONS; a++) {
      qTable[s][a] = 0.0;
    }
  }
}

int RLAgent::chooseAction(int state) {
  if (random(100) / 100.0 < exploration) return random(ACTIONS);
  int best = 0;
  for (int a = 1; a < ACTIONS; a++) {
    if (qTable[state][a] > qTable[state][best]) best = a;
  }
  return best;
}

void RLAgent::updateQ(int state, int action, float reward, int newState) {
  float maxNext = qTable[newState][0];
  for (int a = 1; a < ACTIONS; a++) {
    if (qTable[newState][a] > maxNext) maxNext = qTable[newState][a];
  }
  qTable[state][action] += learningRate * (reward + discount * maxNext - qTable[state][action]);
}

void RLAgent::printQTable() {
  Serial.println("Q-Table:");
  for (int s = 0; s < STATES; s++) {
    Serial.print("State ");
    Serial.print(s);
    Serial.print(": ");
    for (int a = 0; a < ACTIONS; a++) {
      Serial.print(qTable[s][a]);
      Serial.print(" ");
    }
    Serial.println();
  }
}