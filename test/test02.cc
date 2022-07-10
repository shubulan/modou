#include "EventLoop.h"
#include <vector>

void threadFunc() {
  modou::EventLoop loop;
  loop.loop();
}

int main() {
  modou::EventLoop loop1;
  modou::EventLoop loop2;
  loop2.loop();

  return 0;
}
