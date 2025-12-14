#include "MemoryLib.h"
#include <Arduino.h>

void MemoryManager::init() {
  memset(frames, 0, sizeof(frames));
  memset(pageTable, -1, sizeof(pageTable));
}

int MemoryManager::allocatePages(int numPages) {
  int start = -1;
  int count = 0;
  for (int i = 0; i < TOTAL_FRAMES; i++) {
    if (frames[i] == 0) {
      if (start == -1) start = i;
      count++;
      if (count == numPages) {
        for (int j = start; j < start + numPages; j++) {
          frames[j] = 1;
        }
        for (int p = 0; p < numPages; p++) {
          pageTable[p] = start + p;
        }
        return start;
      }
    } else {
      start = -1;
      count = 0;
    }
  }
  return -1;
}

void MemoryManager::deallocatePages(int startFrame, int numPages) {
  for (int i = startFrame; i < startFrame + numPages; i++) {
    frames[i] = 0;
  }
}

void MemoryManager::simulatePaging(int virtAddr) {
  int page = virtAddr / PAGE_SIZE;
  int offset = virtAddr % PAGE_SIZE;
  int frame = pageTable[page];
  if (frame != -1) {
    int physAddr = frame * PAGE_SIZE + offset;
    Serial.print("Virtual ");
    Serial.print(virtAddr);
    Serial.print(" -> Physical ");
    Serial.println(physAddr);
  } else {
    Serial.println("Page Fault!");
  }
}

void MemoryManager::visualizeMemory() {
  Serial.print("Memory Frames: ");
  for (int i = 0; i < TOTAL_FRAMES; i++) {
    Serial.print(frames[i] ? "[X]" : "[ ]");
  }
  Serial.println();
}