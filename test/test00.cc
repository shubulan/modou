#include "EventLoop.h"
#include <vector>

void threadFunc() {
  modou::EventLoop loop;
  loop.loop();
}

int main() {
    std::vector<modou::Thread> threads;
    for (int i = 0; i < 5; i++) {
      threads.push_back(modou::Thread(threadFunc));
    }

    for (int i = 0; i < 5; i++) {
      threads[i].start();
    }

    for (int i = 0; i < 5; i++) {
      threads[i].join();
    }
    

  return 0;
}
