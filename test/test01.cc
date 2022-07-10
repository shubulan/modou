#include "EventLoop.h"
#include "log.h"

modou::EventLoop* g_loop;
void threadFunc() {
  modou::info("executing");
  g_loop->loop();
}

int main() {
  modou::EventLoop loop;
  g_loop = &loop;
  modou::Thread t(threadFunc);
  t.start();
  t.join();
  return 0;
}
