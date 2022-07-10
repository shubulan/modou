#include "EventLoop.h"

#include "Thread.h"
#include "log.h"
namespace modou {

__thread EventLoop* t_loopInThisThread = nullptr;

void EventLoop::abortNotInLoopThread() {
  critical("abort: Not In Loop Thread");
  exit(1);
}

void EventLoop::abortTwoLoopInThread() {
  critical("abort: Two Loops In One Thread");
  exit(1);
}

EventLoop::EventLoop() : looping_(false), threadId_(CurrentThread::tid()) {
  info("EventLoop created {} in thread: {}", fmt::ptr(this), threadId_);
  if (t_loopInThisThread) {
    abortTwoLoopInThread();
  } else {
    t_loopInThisThread = this;
  }
}

EventLoop::~EventLoop() {
  assert(!looping_);
  t_loopInThisThread = nullptr;
}
void EventLoop::loop() {
  assert(!looping_);
  assertInLoopThread();
  looping_ = true;

  sleep(5);

  looping_ = false;
}
}  // namespace modou
