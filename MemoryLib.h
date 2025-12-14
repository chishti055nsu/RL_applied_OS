#ifndef MEMORYLIB_H
#define MEMORYLIB_H

#define TOTAL_FRAMES 10
#define PAGE_SIZE 4

class MemoryManager {
public:
  void init();
  int allocatePages(int numPages);
  void deallocatePages(int startFrame, int numPages);
  void simulatePaging(int virtAddr);
  void visualizeMemory();
private:
  int frames[TOTAL_FRAMES];  // 0 free, 1 allocated
  int pageTable[20];  // virt page -> frame
};

#endif