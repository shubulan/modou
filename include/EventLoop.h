#pragma once

#include <atomic>
#include <memory>
#include <vector>

#include "Thread.h"

namespace modou {
class Poller;

class Channel;
class EventLoop {
 public:
  using ChannelList = std::vector<Channel*>;
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

  void updateChannel(Channel*);
  void quit() { quit_ = true; }

 private:
  EventLoop(const EventLoop&) = delete;
  EventLoop& operator=(const EventLoop&) = delete;
  void abortNotInLoopThread();
  void abortTwoLoopInThread();

  const tid_t threadId_;
  std::atomic<bool> looping_;
  std::atomic<bool> quit_;
  ChannelList activeChannels_;
  std::shared_ptr<Poller> poller_;
};

}  // namespace modou
