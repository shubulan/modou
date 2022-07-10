#pragma once

#include <atomic>

#include "Thread.h"

namespace modou {

class EventLoop {
 public:
  EventLoop();
  ~EventLoop();
  void loop();
  void assertInLoopThread() {
    // abort if run in other thread
    if (!isInLoopThread()) {
      abortNotInLoopThread();
    }
  }

  bool isInLoopThread() { return threadId_ == CurrentThread::tid(); }

 private:
  EventLoop(const EventLoop&) = delete;
  EventLoop& operator=(const EventLoop&) = delete;
  void abortNotInLoopThread();
  void abortTwoLoopInThread();

  const tid_t threadId_;
  std::atomic<bool> looping_;
};

}  // namespace modou
