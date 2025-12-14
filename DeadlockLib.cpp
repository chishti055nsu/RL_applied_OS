#include "DeadlockLib.h"
#include <Arduino.h>

void DeadlockDetector::init(int procs, int res) {
  memset(allocation, 0, sizeof(allocation));
  memset(requestGraph, 0, sizeof(requestGraph));
  pinMode(LED_PIN, OUTPUT);
}

void DeadlockDetector::request(int proc, int res) {
  requestGraph[proc][res] = 1;
}

void DeadlockDetector::release(int proc, int res) {
  requestGraph[proc][res] = 0;
  allocation[proc][res] = 0;
}

bool DeadlockDetector::detectDeadlock() {
  memset(visited, 0, sizeof(visited));
  for (int i = 0; i < MAX_PROCS; i++) {
    if (!visited[i] && detectCycle(i)) {
      Serial.println("Deadlock Detected!");
      digitalWrite(LED_PIN, HIGH);  // LED on
      delay(500);
      digitalWrite(LED_PIN, LOW);
      return true;
    }
  }
  return false;
}

bool DeadlockDetector::detectCycle(int proc) {
  visited[proc] = true;
  for (int r = 0; r < MAX_RES; r++) {
    if (requestGraph[proc][r]) {
      for (int p = 0; p < MAX_PROCS; p++) {
        if (allocation[p][r] && !visited[p]) {
          if (detectCycle(p)) return true;
        }
      }
    }
  }
  return false;
}

void DeadlockDetector::visualizeGraph() {
  Serial.println("Resource Allocation Graph:");
  for (int p = 0; p < MAX_PROCS; p++) {
    Serial.print("P");
    Serial.print(p);
    Serial.print(": ");
    for (int r = 0; r < MAX_RES; r++) {
      if (requestGraph[p][r]) {
        Serial.print("->R");
        Serial.print(r);
        Serial.print(" ");
      }
    }
    Serial.println();
  }
}